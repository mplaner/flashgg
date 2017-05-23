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
  std::vector<std::string> leadFilterName_;
  std::vector<std::string> subFilterName_;
  std::vector<std::string> hltTriggerName_;

  edm::EDGetTokenT<edm::View<flashgg::DiPhotonCandidate>> diphotons_;
  edm::EDGetTokenT<edm::View<reco::GenParticle>> genPhotons_;
  edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
  std::string dataType_;
    
  edm::ParameterSetID triggerNamesID_;
  std::map<std::string, unsigned int> trigger_indices;
  TH1F *MassPeak;
  TH1F *MassPeakHLT[5];
  TCanvas *c_eff_MassPeak = new TCanvas( "c_eff_MassPeak", "c_eff_MassPeak" );
  TGraphAsymmErrors *eff_MassPeak[5];
  int massMin; 
  int massMax;

};

testHLT::~testHLT()
{
  std::cout << "calculating efficiencies" << std::endl;
  for(int i=0;i<5;i++)
    {
      makeEfficiencies(MassPeakHLT[i], MassPeak, eff_MassPeak[i], "invariant mass");
    }
  std::cout << "calculated efficiencies" << std::endl;

    
  TFile *file = new TFile( outputFileName_.c_str(), "recreate" );
  MassPeak->Write();

  for(int i=0;i<5;i++)
      {
          MassPeakHLT[i]->Write();
          // c_eff_MassPeak[i]->Write();
          eff_MassPeak[i]->Write();
      }
  std::cout << "wrote Mass peak histogram" << std::endl;
  file->Close();
}

testHLT::testHLT( const edm::ParameterSet &iConfig ):
  outputFileName_( iConfig.getParameter<std::string>( "outputFileName" ) ),
  leadFilterName_( iConfig.getParameter<std::vector<std::string>>( "leadFilterName" ) ),
  subFilterName_( iConfig.getParameter<std::vector<std::string>>( "subFilterName" ) ),
  hltTriggerName_( iConfig.getParameter<std::vector<std::string>>("hltTriggerName") ),
  diphotons_( consumes<edm::View<flashgg::DiPhotonCandidate>>( iConfig.getParameter<edm::InputTag>( "diphotons" ) ) ),
  genPhotons_( consumes<edm::View<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>( "genInput") ) ),
  triggerBits_( consumes<edm::TriggerResults>( iConfig.getParameter<edm::InputTag>( "bits" ) ) ),
  triggerObjects_( consumes<pat::TriggerObjectStandAloneCollection>( iConfig.getParameter<edm::InputTag>( "objects" ) ) ),
  dataType_( iConfig.getParameter<std::string>("dataType"))
{
  int massBins=40;
  if(dataType_=="QCD")
      {massMin = 100; massMax=180;}
  if(dataType_=="Hgg")
      {massMin=115; massMax = 135; } //for Hgg peak
  if(dataType_=="DY")
      {massMin= 60;massMax=120; } //for z-peak
  //massMin = 60; massMax=100; //fixme: remove for rediscovery
  massMin = 100; massMax=180; //fixme: remove for rediscovery
  
  string tempname[5]= {"_90","_925","_95","_975","_100"};
  string tempName;
  for(int i=0;i<5;i++)
    {
      eff_MassPeak[i] = new TGraphAsymmErrors(); 
      tempName = "Mass > "+tempname[i];
      MassPeakHLT[i] = new TH1F(tempName.c_str(),"",massBins,massMin,massMax); 
    }
  
  MassPeak = new TH1F( "MassPeak", "", massBins, massMin, massMax );
}

void testHLT::init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames )
{
  
  trigger_indices.clear();
  for( unsigned int i = 0; i < triggerNames.triggerNames().size(); i++ ) {
    std::string trimmedName = HLTConfigProvider::removeVersion( triggerNames.triggerName( i ) );
    //std::cout << "data type: " << dataType_ << std::endl;
    //std::cout << triggerNames.triggerName( i ) << std::endl;
    trigger_indices[trimmedName] = triggerNames.triggerIndex( triggerNames.triggerName( i ) );
  }
}

bool testHLT::hltEvent(edm::Handle<edm::TriggerResults> triggerBits, vector<string> hltTrigger) {
    for (std::map<std::string, unsigned int>::const_iterator cit = trigger_indices.begin(); cit != trigger_indices.end(); cit++) 
        {
            if (triggerBits->accept(cit->second))
                {
                    //std::cout << cit->first << "  ----- on " << std::endl;
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
        //std::cout << filter << " filter search:" << std::endl;
      if( obj.hasFilterLabel( filter ) )
	{ 
        //std::cout << "filter matched" << std::endl;
        triggerCandidates.push_back( obj.p4() ); 
    }
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

  //  iEvent.getByToken( genPhotons_, genParticles);
  iEvent.getByToken( triggerBits_, triggerBits );
  iEvent.getByToken( triggerObjects_, triggerObjects );
  iEvent.getByToken( diphotons_, diphotons );
  if( !triggerBits.isValid() ) {
    LogDebug( "" ) << "TriggerResults product not found - returning result=false!";
    return;
  }

  const edm::TriggerNames &triggerNames = iEvent.triggerNames( *triggerBits );
  

  if( triggerNamesID_ != triggerNames.parameterSetID() ) 
      {
          triggerNamesID_ = triggerNames.parameterSetID();
          init( *triggerBits, triggerNames );
      }
  int diphotonIndex = -1;
  /*
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
  */
  //std::cout << "diphoton index " << diphotonIndex << std::endl;
  if(diphotons->size()<1)
      return;

  edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( 0 );
  //edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( diphotonIndex );
  //    std::cout << "lead photon eta: " <<  theDiPhoton->leadingPhoton()->eta() << std::endl;
  if( theDiPhoton->mass() < massMin or theDiPhoton->mass() > massMax ) //for QCD for now
      { return; }

  float probe_weight[5] = {0,0,0,0,0};

  MassPeak->Fill( theDiPhoton->mass() );

  if(hltEvent(triggerBits, hltTriggerName_))
    {
        //std::cout << "trigger found" << std::endl;
        std::vector<math::XYZTLorentzVector> hltP4s;
        hltP4s = hltP4(triggerNames, triggerObjects, leadFilterName_);
        //recalculate HLT mass and enumerate here.
        //std::vector<T>::iterator it
        
        math::XYZTLorentzVector sum;
        //math::XYZTLorentzVector* va, vb;
        for(std::vector<math::XYZTLorentzVector>::const_iterator vit = hltP4s.begin(); vit != hltP4s.end(); ++vit)
            //for(auto const& p4: hltP4s)
            {
                for(std::vector<math::XYZTLorentzVector>::const_iterator vit2 = vit; vit2 != hltP4s.end(); ++vit2)
                    {
                        //                        std::cout << "lead pho pT: " << vit->pt() << " eta: " << vit->eta() << " phi: " << vit->phi() <<  std::endl;
                        //std::cout << "vit2 pho pT: " << vit2->pt() << " eta: " << vit2->eta() << " phi: " << vit2->phi() <<  std::endl;
                        //tighter pT cuts
                        /*
                        if(vit->pt()<22||vit2->pt()<22)
                           continue;
                        if(vit->pt()<30&&vit2->pt()<30)
                           continue;
                        */
                        sum = *vit+*vit2;
                        //std::cout << sum.mass() << std::endl;
                        if(sum.mass()>90)
                            {
                                probe_weight[0]=1;
                            
                            if(sum.mass()>92.5)
                                {
                                    probe_weight[1]=1;
                                    
                            if(sum.mass()>95)
                                {
                                    probe_weight[2]=1;
                                    
                            if(sum.mass()>97.5)
                                {
                                    probe_weight[3]=1;
                                    
                            if(sum.mass()>100)
                                {
                                    probe_weight[4]=1;
                                }}}}}
                    }
            }
        for(int j=0;j<5;j++)
            MassPeakHLT[j]->Fill(theDiPhoton->mass(), probe_weight[j]);
    }

}
  void testHLT::makeEfficiencies(TH1F * numerator, TH1F * denominator, TGraphAsymmErrors * eff, const char* xAxisLabel)
  {
      std::cout << numerator->GetTitle() << ": " << numerator->GetEntries() << std::endl;
      c_eff_MassPeak->cd();
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
