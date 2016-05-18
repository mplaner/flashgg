// system include files
#include <memory>
#include <cmath>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Common/interface/Ptr.h"
//#include "DataFormats/Common/interface/PtrVector.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/Electron.h"

#include "flashgg/DataFormats/interface/DiPhotonMVAResult.h"

#include <DataFormats/Math/interface/deltaR.h>

#include <set>
#include "TFile.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

class testHLT : public edm::EDAnalyzer
{
public:
    explicit testHLT( const edm::ParameterSet & );
    ~testHLT();
    void init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames );
    bool hltEvent(edm::Handle<edm::TriggerResults> triggerBits, vector<string> hltTrigger);
    bool genMatching( math::XYZTLorentzVector p4_lead, math::XYZTLorentzVector p4_sub, math::XYZTLorentzVector p4_genLead, math::XYZTLorentzVector p4_genSub, float dRmin );
    void makeEfficiencies(TH1F * num, TH1F * den, TGraphAsymmErrors * eff, const char* xAxisLabel);
    bool L1Matching( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold );
    std::vector<math::XYZTLorentzVector> hltP4( const edm::TriggerNames &triggerNames, edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
            std::vector<std::string> filterLabels );

private:
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;

    std::string outputFileName_;
    std::vector<std::string> leadFilterName95_;
    std::vector<std::string> subFilterName95_;
    std::vector<std::string> hltTriggerName95_;

    std::vector<std::string> leadFilterName90_;
    std::vector<std::string> subFilterName90_;
    std::vector<std::string> hltTriggerName90_;

    std::vector<std::string> leadFilterNameLoose_;
    std::vector<std::string> subFilterNameLoose_;
    std::vector<std::string> hltTriggerNameLoose_;
    
    std::vector<std::string> leadFilterNameHE_;
    std::vector<std::string> subFilterNameHE_;
    std::vector<std::string> hltTriggerNameHE_;

    std::vector<std::string> leadFilterNameHElowR9_;
    std::vector<std::string> subFilterNameHElowR9_;
    std::vector<std::string> hltTriggerNameHElowR9_;
   
    edm::EDGetTokenT<edm::View<flashgg::DiPhotonCandidate>> diphotons_;
    edm::EDGetTokenT<edm::View<reco::GenParticle>> genPhotons_;
    edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
    std::string dataType_;
    
    edm::ParameterSetID triggerNamesID_;
    std::map<std::string, unsigned int> trigger_indices;

    TH1F *Zpeak;
    TH1F *leadPt;
    TH1F *subPt;
    TH1F *leadEta;
    TH1F *subEta;
    TH1F *leadR9;
    TH1F *subR9;
    TH1F *leadHE;
    TH1F *subHE;
    
    TH1F *ZpeakHLT[5];
    TH1F *leadPtHLT[5];
    TH1F *subPtHLT[5];
    TH1F *leadEtaHLT[5];
    TH1F *subEtaHLT[5];
    TH1F *leadR9HLT[5];
    TH1F *subR9HLT[5];
    TH1F *leadHEHLT[5];
    TH1F *subHEHLT[5];
    
    
    TCanvas *c_eff_Zpeak = new TCanvas( "c_eff_Zpeak", "c_eff_Zpeak" );
    TGraphAsymmErrors *eff_Zpeak[5];
    TGraphAsymmErrors *eff_leadPt[5];
    TGraphAsymmErrors *eff_subPt[5];
    TGraphAsymmErrors *eff_leadEta[5];
    TGraphAsymmErrors *eff_subEta[5];
    TGraphAsymmErrors *eff_leadR9[5];
    TGraphAsymmErrors *eff_subR9[5];
    TGraphAsymmErrors *eff_leadHE[5];
    TGraphAsymmErrors *eff_subHE[5];
    
};

testHLT::~testHLT()
{
    std::cout << "calculating efficiencies" << std::endl;
    for(int i=0;i<5;i++)
        {
            makeEfficiencies(ZpeakHLT[i], Zpeak, eff_Zpeak[i], "invariant mass");
            makeEfficiencies(leadPtHLT[i], leadPt, eff_leadPt[i], "lead pt");
            makeEfficiencies(subPtHLT[i], subPt, eff_subPt[i], "sublead pt");
            makeEfficiencies(leadEtaHLT[i], leadEta, eff_leadEta[i], "lead eta");
            makeEfficiencies(subEtaHLT[i], subEta, eff_subEta[i], "sublead eta");
            makeEfficiencies(leadR9HLT[i], leadR9, eff_leadR9[i], "lead R9");
            makeEfficiencies(subR9HLT[i], subR9, eff_subR9[i], "sublead R9");
            makeEfficiencies(leadHEHLT[i], leadHE, eff_leadHE[i], "lead H/E");
            makeEfficiencies(subHEHLT[i], subHE, eff_subHE[i], "sublead H/E");
        }
    std::cout << "calculated efficiencies" << std::endl;

    
    TFile *file = new TFile( outputFileName_.c_str(), "recreate" );

    Zpeak->Write();
    std::cout << "wrote z peak histogram" << std::endl;
    leadPt->Write();
    leadEta->Write();
    leadR9->Write();
    leadHE->Write();
    subPt->Write();
    subEta->Write();
    subR9->Write();
    subHE->Write();
    for(int i=0;i<5;i++)
        {
            ZpeakHLT[i]->Write();
            //std::cout << eff_leadPt[i]->GetName() << std::endl;
            leadPtHLT[i]->Write();
            eff_leadPt[i]->Write();
            eff_subPt[i]->Write();
            eff_leadEta[i]->Write();
            eff_subEta[i]->Write();
            eff_leadR9[i]->Write();
            eff_subR9[i]->Write();
            eff_leadHE[i]->Write();
            eff_subHE[i]->Write();
            //c_eff_Zpeak->Write();
            eff_Zpeak[i]->Write();
        }
    file->Close();
}

testHLT::testHLT( const edm::ParameterSet &iConfig ):
    outputFileName_( iConfig.getParameter<std::string>( "outputFileName" ) ),
    leadFilterName95_( iConfig.getParameter<std::vector<std::string>>( "leadFilterName95" ) ),
    subFilterName95_( iConfig.getParameter<std::vector<std::string>>( "subFilterName95" ) ),
    hltTriggerName95_( iConfig.getParameter<std::vector<std::string>>("hltTriggerName95") ),
    leadFilterName90_( iConfig.getParameter<std::vector<std::string>>( "leadFilterName90" ) ),
    subFilterName90_( iConfig.getParameter<std::vector<std::string>>( "subFilterName90" ) ),
    hltTriggerName90_( iConfig.getParameter<std::vector<std::string>>("hltTriggerName90") ),
    leadFilterNameLoose_( iConfig.getParameter<std::vector<std::string>>( "leadFilterNameLoose" ) ),
    subFilterNameLoose_( iConfig.getParameter<std::vector<std::string>>( "subFilterNameLoose" ) ),
    hltTriggerNameLoose_( iConfig.getParameter<std::vector<std::string>>("hltTriggerNameLoose") ),
    leadFilterNameHE_( iConfig.getParameter<std::vector<std::string>>( "leadFilterNameHE" ) ),
    subFilterNameHE_( iConfig.getParameter<std::vector<std::string>>( "subFilterNameHE" ) ),
    hltTriggerNameHE_( iConfig.getParameter<std::vector<std::string>>("hltTriggerNameHE") ),
    leadFilterNameHElowR9_( iConfig.getParameter<std::vector<std::string>>( "leadFilterNameHElowR9" ) ),
    subFilterNameHElowR9_( iConfig.getParameter<std::vector<std::string>>( "subFilterNameHElowR9" ) ),
    hltTriggerNameHElowR9_( iConfig.getParameter<std::vector<std::string>>("hltTriggerNameHElowR9") ),
    diphotons_( consumes<edm::View<flashgg::DiPhotonCandidate>>( iConfig.getParameter<edm::InputTag>( "diphotons" ) ) ),
    genPhotons_( consumes<edm::View<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>( "genInput") ) ),
    triggerBits_( consumes<edm::TriggerResults>( iConfig.getParameter<edm::InputTag>( "bits" ) ) ),
    triggerObjects_( consumes<pat::TriggerObjectStandAloneCollection>( iConfig.getParameter<edm::InputTag>( "objects" ) ) ),
    dataType_( iConfig.getParameter<std::string>("dataType"))
{
    int massBins=80;
    
    //electrons
    //int massBins=60;
    //Zpeak = new TH1F( "Zpeak", "", massBins, 60, 120 );
    //ZpeakHLT = new TH1F( "ZpeakHLT", "", massBins, 60, 120 );
    
    //photons
    string tempname[5]= {"_95","_90","_Loose","_HEonly","HE_lowR9"};
    string tempName;
    for(int i=0;i<5;i++)
        {
            eff_Zpeak[i] = new TGraphAsymmErrors(); 
            eff_leadPt[i] = new TGraphAsymmErrors(); 
            eff_subPt[i] = new TGraphAsymmErrors(); 
            eff_leadEta[i] = new TGraphAsymmErrors(); 
            eff_subEta[i] = new TGraphAsymmErrors(); 
            eff_leadR9[i] = new TGraphAsymmErrors(); 
            eff_subR9[i] = new TGraphAsymmErrors(); 
            eff_leadHE[i] = new TGraphAsymmErrors(); 
            eff_subHE[i] = new TGraphAsymmErrors(); 
            tempName = "ZpeakHLT"+tempname[i];
            ZpeakHLT[i] = new TH1F(tempName.c_str(),"",massBins,100,180);
            tempName = "lead_pt_HLT"+tempname[i];
            leadPtHLT[i]= new TH1F(tempName.c_str(),"",100,0,100);
            tempName = "sublead_pt_HLT"+tempname[i];
            subPtHLT[i] = new TH1F(tempName.c_str(),"",100,0,100);
            tempName = "lead_eta_HLT"+tempname[i];
            leadEtaHLT[i] = new TH1F(tempName.c_str(),"",30,-3,3);
            tempName = "sublead_eta_HLT"+tempname[i];
            subEtaHLT[i] = new TH1F (tempName.c_str(),"",30,-3,3);
            tempName = "lead_r9_HLT"+tempname[i];
            leadR9HLT[i] = new TH1F(tempName.c_str(),"",50,0,1);
            tempName = "sublead_r9_HLT"+tempname[i];
            subR9HLT[i] = new TH1F(tempName.c_str(),"",50,0,1);
            tempName = "lead_HE_HLT"+tempname[i];
            leadHEHLT[i] = new TH1F(tempName.c_str(),"",50,0,0.5);
            tempName = "sublead_HE_HLT"+tempname[i];
            subHEHLT[i] = new TH1F(tempName.c_str(),"",50,0,0.5);
            
        }
    Zpeak = new TH1F( "Zpeak", "", massBins, 100, 180 );
    leadPt= new TH1F("lead_pt","",100,0,100);
    subPt = new TH1F("sublead_pt","",100,0,100);
    leadEta = new TH1F("lead_eta","",30,-3,3);
    subEta = new TH1F ("sublead_eta","",30,-3,3);
    leadR9 = new TH1F("lead_r9","",50,0,1);
    subR9 = new TH1F("sublead_r9","",50,0,1);
    leadHE = new TH1F("lead_HE","",50,0,0.5);
    subHE = new TH1F("sublead_HE","",50,0,0.5);
}

void testHLT::init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames )
{

    trigger_indices.clear();
    for( unsigned int i = 0; i < triggerNames.triggerNames().size(); i++ ) {
        std::string trimmedName = HLTConfigProvider::removeVersion( triggerNames.triggerName( i ) );
        std::cout << "data type: " << dataType_ << std::endl;
        std::cout << triggerNames.triggerName( i ) << std::endl;
        trigger_indices[trimmedName] = triggerNames.triggerIndex( triggerNames.triggerName( i ) );
    }
}

bool testHLT::hltEvent(edm::Handle<edm::TriggerResults> triggerBits, vector<string> hltTrigger) {
    
    for (std::map<std::string, unsigned int>::const_iterator cit = trigger_indices.begin(); cit != trigger_indices.end(); cit++) {
        if (triggerBits->accept(cit->second)) {
            std::vector<std::string>::const_iterator it = find(hltTrigger.begin(), hltTrigger.end(), cit->first);
            if (it != hltTrigger.end())
                return true;
        }
    }
    
    return false;
}



std::vector<math::XYZTLorentzVector> testHLT::hltP4( const edm::TriggerNames &triggerNames,
        edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects, std::vector<std::string> filterLabels )
{

    std::vector< math::XYZTLorentzVector> triggerCandidates;

    for( pat::TriggerObjectStandAlone obj : *triggerObjects ) {
        obj.unpackPathNames( triggerNames );
        for( std::string filter : filterLabels ) {
            if( obj.hasFilterLabel( filter ) )
            { triggerCandidates.push_back( obj.p4() ); }
        }
    }

    return triggerCandidates;
}

bool testHLT::genMatching(math::XYZTLorentzVector p4_lead, math::XYZTLorentzVector p4_sublead, math::XYZTLorentzVector genP4_lead, math::XYZTLorentzVector genP4_sublead, float dRmin = 0.15 )
{
    //diphoton match leg 1 to electron from z
    //diphoton match leg 2 to electron from z (ignore overlap for now
    //    std::cout << "in gen matching" << std::endl;
    float dRa = deltaR( p4_lead, genP4_lead );
    float dRb = deltaR( p4_lead, genP4_sublead );
    float dRc = deltaR( p4_sublead, genP4_lead );
    float dRd = deltaR( p4_sublead, genP4_sublead );
    if(dRa<dRmin && dRd<dRmin)
        {return true;}
    if(dRb<dRmin && dRc<dRmin)
        {return true;}
    return false;
}

void testHLT::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
{

    edm::Handle<edm::View<reco::GenParticle>> genParticles;
    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<edm::View<flashgg::DiPhotonCandidate>> diphotons;

    iEvent.getByToken( genPhotons_, genParticles);
    iEvent.getByToken( triggerBits_, triggerBits );
    iEvent.getByToken( triggerObjects_, triggerObjects );
    iEvent.getByToken( diphotons_, diphotons );
    if( !triggerBits.isValid() ) {
        LogDebug( "" ) << "TriggerResults product not found - returning result=false!";
        return;
    }

    const edm::TriggerNames &triggerNames = iEvent.triggerNames( *triggerBits );


    if( triggerNamesID_ != triggerNames.parameterSetID() ) {
        triggerNamesID_ = triggerNames.parameterSetID();
        init( *triggerBits, triggerNames );
    }
    //    std::cout << "data type: " << dataType_ << std::endl;
    int diphotonIndex = -1;
    int genLeadIndex = -1;
    int genSubIndex = -1;
    int particleID =22;
    //int momID =25;
    if(dataType_=="Hgg")
        {
            //momID = 25;
            particleID =22;
        }
    if(dataType_=="DY")
        {
            //momID =23;
            particleID =11;
        }
    //fill gen particles matching to higg->diphoton or Z->DY
    for( size_t i = 0; i < genParticles->size(); i++)
        {
            edm::Ptr<reco::GenParticle> gen = genParticles->ptrAt(i);
            //if(gen->mother()->pdgId()==momID)
                if(fabs(gen->pdgId())==fabs(particleID))
                    {
                        {
                            if(genLeadIndex == -1)
                                genLeadIndex = i;
                            else
                                genSubIndex = i;    
                        }
                    }
            
        }
    //no GEN matching for QCD
    if(dataType_!="QCD")
        if(genSubIndex==-1) //if can't find both electrons; skip event
            return;
    //std::cout << "diphoton size" << diphotons->size() << std::endl;
    //    if(fabs(genParticles->ptrAt(genLeadIndex)->eta())<1.5 && fabs(genParticles->ptrAt(genSubIndex)->eta())<1.5) //!EBEB only
    //if(fabs(genParticles->ptrAt(genLeadIndex)->eta())<1.5 || fabs(genParticles->ptrAt(genSubIndex)->eta())<1.5) //EEEE only
    //if(fabs(genParticles->ptrAt(genLeadIndex)->eta())>1.5 || fabs(genParticles->ptrAt(genSubIndex)->eta())>1.5) //EBEB only
    //  return;
    if(dataType_=="QCD"&& diphotons->size()>0)
        {
            diphotonIndex=0;  //make random later
        }
    else
        for( size_t i = 0; i < diphotons->size(); i++ ) 
            {
                edm::Ptr<flashgg::DiPhotonCandidate> diphoPtr = diphotons->ptrAt( i );
                if( genMatching(diphoPtr->leadingPhoton()->p4(), diphoPtr->subLeadingPhoton()->p4(), genParticles->ptrAt(genLeadIndex)->p4(), genParticles->ptrAt(genSubIndex)->p4(),  0.15 ))
                    {
                        diphotonIndex=i;
                        break;
                    }
            }
    if( diphotonIndex == -1 )
        { return; }
    //std::cout << "diphoton index " << diphotonIndex << std::endl;
    edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( diphotonIndex );
    //    std::cout << "lead photon eta: " <<  theDiPhoton->leadingPhoton()->eta() << std::endl;
    if(dataType_=="QCD")
        if( theDiPhoton->mass() < 100 or theDiPhoton->mass() > 180 ) //for QCD for now
            { return; }
    if(dataType_=="Hgg")
        if( theDiPhoton->mass() < 115 or theDiPhoton->mass() > 135 ) //for Hgg peak
            { return; }
    if(dataType_=="DY")
        if( theDiPhoton->mass() < 60 or theDiPhoton->mass() > 120 ) //for z-peak
            { return; }
    float probe_weight = 1;
    Zpeak->Fill( theDiPhoton->mass(), probe_weight );
    leadPt->Fill(theDiPhoton->leadingPhoton()->pt());
    leadEta->Fill(theDiPhoton->leadingPhoton()->eta());
    leadR9->Fill(theDiPhoton->leadingPhoton()->full5x5_r9()); 
    leadHE->Fill(theDiPhoton->leadingPhoton()->hadronicOverEm());
    
    subPt->Fill(theDiPhoton->subLeadingPhoton()->pt()); 
    subEta->Fill(theDiPhoton->subLeadingPhoton()->eta()); 
    subR9->Fill(theDiPhoton->subLeadingPhoton()->full5x5_r9()); 
    subHE->Fill(theDiPhoton->subLeadingPhoton()->hadronicOverEm()); 
    
    
    
    if(hltEvent(triggerBits, hltTriggerName95_))
        {
            ZpeakHLT[0]->Fill(theDiPhoton->mass(), probe_weight);
            leadPtHLT[0]->Fill(theDiPhoton->leadingPhoton()->pt());
            leadEtaHLT[0]->Fill(theDiPhoton->leadingPhoton()->eta());
            leadR9HLT[0]->Fill(theDiPhoton->leadingPhoton()->full5x5_r9()); 
            leadHEHLT[0]->Fill(theDiPhoton->leadingPhoton()->hadronicOverEm());
            
            subPtHLT[0]->Fill(theDiPhoton->subLeadingPhoton()->pt()); 
            subEtaHLT[0]->Fill(theDiPhoton->subLeadingPhoton()->eta()); 
            subR9HLT[0]->Fill(theDiPhoton->subLeadingPhoton()->full5x5_r9()); 
            subHEHLT[0]->Fill(theDiPhoton->subLeadingPhoton()->hadronicOverEm()); 
        }
    if(hltEvent(triggerBits, hltTriggerName90_))
        {
            ZpeakHLT[1]->Fill(theDiPhoton->mass(), probe_weight);
            leadPtHLT[1]->Fill(theDiPhoton->leadingPhoton()->pt());
            leadEtaHLT[1]->Fill(theDiPhoton->leadingPhoton()->eta());
            leadR9HLT[1]->Fill(theDiPhoton->leadingPhoton()->full5x5_r9()); 
            leadHEHLT[1]->Fill(theDiPhoton->leadingPhoton()->hadronicOverEm());
            
            subPtHLT[1]->Fill(theDiPhoton->subLeadingPhoton()->pt()); 
            subEtaHLT[1]->Fill(theDiPhoton->subLeadingPhoton()->eta()); 
            subR9HLT[1]->Fill(theDiPhoton->subLeadingPhoton()->full5x5_r9()); 
            subHEHLT[1]->Fill(theDiPhoton->subLeadingPhoton()->hadronicOverEm()); 
        }
    if(hltEvent(triggerBits, hltTriggerNameLoose_))
        {
            ZpeakHLT[2]->Fill(theDiPhoton->mass(), probe_weight);
            leadPtHLT[2]->Fill(theDiPhoton->leadingPhoton()->pt());
            leadEtaHLT[2]->Fill(theDiPhoton->leadingPhoton()->eta());
            leadR9HLT[2]->Fill(theDiPhoton->leadingPhoton()->full5x5_r9()); 
            leadHEHLT[2]->Fill(theDiPhoton->leadingPhoton()->hadronicOverEm());
            
            subPtHLT[2]->Fill(theDiPhoton->subLeadingPhoton()->pt()); 
            subEtaHLT[2]->Fill(theDiPhoton->subLeadingPhoton()->eta()); 
            subR9HLT[2]->Fill(theDiPhoton->subLeadingPhoton()->full5x5_r9()); 
            subHEHLT[2]->Fill(theDiPhoton->subLeadingPhoton()->hadronicOverEm()); 
        }
    if(hltEvent(triggerBits, hltTriggerNameHE_))
        {
            ZpeakHLT[3]->Fill(theDiPhoton->mass(), probe_weight);
            leadPtHLT[3]->Fill(theDiPhoton->leadingPhoton()->pt());
            leadEtaHLT[3]->Fill(theDiPhoton->leadingPhoton()->eta());
            leadR9HLT[3]->Fill(theDiPhoton->leadingPhoton()->full5x5_r9()); 
            leadHEHLT[3]->Fill(theDiPhoton->leadingPhoton()->hadronicOverEm());
            
            subPtHLT[3]->Fill(theDiPhoton->subLeadingPhoton()->pt()); 
            subEtaHLT[3]->Fill(theDiPhoton->subLeadingPhoton()->eta()); 
            subR9HLT[3]->Fill(theDiPhoton->subLeadingPhoton()->full5x5_r9()); 
            subHEHLT[3]->Fill(theDiPhoton->subLeadingPhoton()->hadronicOverEm()); 
        }
    if(hltEvent(triggerBits, hltTriggerNameHElowR9_))
        {
            ZpeakHLT[4]->Fill(theDiPhoton->mass(), probe_weight);
            leadPtHLT[4]->Fill(theDiPhoton->leadingPhoton()->pt());
            leadEtaHLT[4]->Fill(theDiPhoton->leadingPhoton()->eta());
            leadR9HLT[4]->Fill(theDiPhoton->leadingPhoton()->full5x5_r9()); 
            leadHEHLT[4]->Fill(theDiPhoton->leadingPhoton()->hadronicOverEm());
            
            subPtHLT[4]->Fill(theDiPhoton->subLeadingPhoton()->pt()); 
            subEtaHLT[4]->Fill(theDiPhoton->subLeadingPhoton()->eta()); 
            subR9HLT[4]->Fill(theDiPhoton->subLeadingPhoton()->full5x5_r9()); 
            subHEHLT[4]->Fill(theDiPhoton->subLeadingPhoton()->hadronicOverEm()); 
        }

}

void testHLT::makeEfficiencies(TH1F * numerator, TH1F * denominator, TGraphAsymmErrors * eff, const char* xAxisLabel)
{
    c_eff_Zpeak->cd();
    eff->BayesDivide( numerator, denominator );
    eff->SetMinimum( 0.0 );
    eff->SetMaximum( 1.1 );
    //    eff->SetTitle( "RelVal z->ee, #sqrt{s} = 13 TeV" );
    eff->SetTitle( numerator->GetName() );
    eff->SetName( numerator->GetName() );
    eff->GetXaxis()->SetTitle( xAxisLabel );
    eff->GetYaxis()->SetTitle( "HLT Efficiency" );
    eff->SetLineColor( 2 );
    eff->SetLineWidth( 2 );
    eff->SetMarkerStyle( 7 );
    eff->SetMarkerColor( 2 );
}

DEFINE_FWK_MODULE( testHLT );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

