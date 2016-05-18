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
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/Electron.h"

#include "flashgg/DataFormats/interface/DiPhotonMVAResult.h"

#include <DataFormats/Math/interface/deltaR.h>

#include <set>
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

class L1Compare : public edm::EDAnalyzer
{
public:
    explicit L1Compare( const edm::ParameterSet & );
    ~L1Compare();
    void init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames );
    TH1F *hpt[2];
    TH1F *heta[2];
    TH1F *hphi[2];
    TH1F *hr9[2];
    TH1F *hsieie[2];
    TH1F *dr[2];
    
    TH1F *bpt;
    TH1F *beta;
    TH1F *bphi;
    TH1F *br9;
    TH1F *bsieie;

    TCanvas *c_eff_stage1[5];
    TCanvas *c_eff_stage2[5];    
    TGraphAsymmErrors *eff_stage1[5];
    TGraphAsymmErrors *eff_stage2[5];
    
    TH2F *L1pt[2];
    TH2F *L1eta[2];
    TH2F *L1phi[2];
    
private:
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;
    virtual void makeEfficiency(TH1F * numerator, TH1F * denominator, TGraphAsymmErrors * eff, TCanvas * can, const char* xAxisLabel, const char* yAxisLabel);
    std::string outputFileName_;
    
    edm::EDGetTokenT<edm::View<flashgg::DiPhotonCandidate>> diphotons_;
    
    edm::EDGetTokenT<edm::View<l1extra::L1EmParticle>> l1iso_;
    edm::EDGetTokenT<edm::View<l1extra::L1EmParticle>> l1noniso_;
    
    edm::EDGetTokenT<edm::View<l1extra::L1EmParticle>> l1isoold_;
    edm::EDGetTokenT<edm::View<l1extra::L1EmParticle>> l1nonisoold_;
    
    edm::EDGetTokenT<l1t::EGammaBxCollection> newL1_;
    
    edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
    edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;

    edm::ParameterSetID triggerNamesID_;
    std::map<std::string, unsigned int> trigger_indices;
    std::map<std::string, unsigned int> prescales;
    std::map<std::string, unsigned int> prescale_counter;

    double lead_ptCut = 125.0/3.0; //40 120/3 100
    double sub_ptCut = 125.0/4.0; //30 120/4

};

L1Compare::~L1Compare()
{
    
    makeEfficiency(hpt[0],bpt,eff_stage1[0],c_eff_stage1[0],"offline pT","L1 inefficiency");
    makeEfficiency(heta[0],beta,eff_stage1[1],c_eff_stage1[1],"offline eta","L1 inefficiency");
    makeEfficiency(hphi[0],bphi,eff_stage1[2],c_eff_stage1[2],"offline phi","L1 inefficiency");
    makeEfficiency(hr9[0],br9,eff_stage1[3],c_eff_stage1[3],"offline r9","L1 inefficiency");
    makeEfficiency(hsieie[0],bsieie,eff_stage1[4],c_eff_stage1[4],"offline sieie","L1 inefficiency");

    makeEfficiency(hpt[1],bpt,eff_stage2[0],c_eff_stage2[0],"offline pT","stage2 L1 inEfficiency");
    makeEfficiency(heta[1],beta,eff_stage2[1],c_eff_stage2[1],"offline eta","stage2 L1 inEfficiency");
    makeEfficiency(hphi[1],bphi,eff_stage2[2],c_eff_stage2[2],"offline phi","stage2 L1 inEfficiency");
    makeEfficiency(hr9[1],br9,eff_stage2[3],c_eff_stage2[3],"offline r9","stage2 L1 inEfficiency");
    makeEfficiency(hsieie[1],bsieie,eff_stage2[4],c_eff_stage2[4],"offline sieie","stage2 L1 inEfficiency");
    
    TFile *file = new TFile( outputFileName_.c_str(), "recreate" );
    dr[0]->Write();
    dr[1]->Write();
    L1pt[0]->Write();
    L1eta[0]->Write();
    L1phi[0]->Write();
    L1pt[1]->Write();
    L1eta[1]->Write();
    L1phi[1]->Write();
    
    
    for(int i=0;i<5;i++)
        {
            eff_stage1[i]->Write();
            eff_stage2[i]->Write();
        }
    
    
    //write events which fail the stage1 l1
    hpt[0]->Write();
    heta[0]->Write();
    hphi[0]->Write();
    hr9[0]->Write();
    hsieie[0]->Write();

    //write events which fail the stage2 l1
    hpt[1]->Write();
    heta[1]->Write();
    hphi[1]->Write();
    hr9[1]->Write();
    hsieie[1]->Write();


    
    
    file->Close();
}

void L1Compare::makeEfficiency(TH1F * numerator, TH1F * denominator, TGraphAsymmErrors * eff, TCanvas * can, const char* xAxisLabel, const char* yAxisLabel)
{
    can->cd();
    eff->BayesDivide( numerator, denominator );
    eff->SetMinimum( 0.0 );
    eff->SetMaximum( 0.1 );
    
    eff->SetTitle( "");
    eff->SetName( numerator->GetName() );
    eff->GetXaxis()->SetTitle( xAxisLabel );
    eff->GetYaxis()->SetTitle( yAxisLabel );
    eff->SetLineColor( 2 );
    eff->SetLineWidth( 2 );
    eff->SetMarkerStyle( 7 );
    eff->SetMarkerColor( 2 );
    eff->Draw("AP");

}

L1Compare::L1Compare( const edm::ParameterSet &iConfig ):
    outputFileName_( iConfig.getParameter<std::string>( "outputFileName" ) ),
    diphotons_( consumes<edm::View<flashgg::DiPhotonCandidate>>( iConfig.getParameter<edm::InputTag>( "diphotons" ) ) ),
    l1iso_( consumes<edm::View<l1extra::L1EmParticle>>( iConfig.getParameter<edm::InputTag>( "l1Iso" ) ) ),
    l1noniso_( consumes<edm::View<l1extra::L1EmParticle>>( iConfig.getParameter<edm::InputTag>( "l1NonIso" ) ) ),
    l1isoold_( consumes<edm::View<l1extra::L1EmParticle>>( iConfig.getParameter<edm::InputTag>( "l1IsoOld" ) ) ),
    l1nonisoold_( consumes<edm::View<l1extra::L1EmParticle>>( iConfig.getParameter<edm::InputTag>( "l1NonIsoOld" ) ) ),
    newL1_( consumes<l1t::EGammaBxCollection> ( iConfig.getParameter<edm::InputTag>( "newL1" ) ) ),
    triggerBits_( consumes<edm::TriggerResults>( iConfig.getParameter<edm::InputTag>( "bits" ) ) ),
    triggerObjects_( consumes<pat::TriggerObjectStandAloneCollection>( iConfig.getParameter<edm::InputTag>( "objects" ) ) ),
    triggerPrescales_( consumes<pat::PackedTriggerPrescales>( iConfig.getParameter<edm::InputTag>( "prescales" ) ) )
{
    L1pt[1] = new TH2F("stage2 vs stage1 L1 sub pT","", 50,0,100,50,0,100);
    L1eta[1] = new TH2F("stage2 vs stage1 L1 sub eta", "",10,-3,3,32,-3,3);
    L1phi[1] = new TH2F("stage2 vs stage1 L1 sub phi", "",10,-3.2,3.2,32,-3.2,3.2);
    
    L1pt[0] = new TH2F("stage2 vs stage1 L1 lead pT","", 50,0,100,50,0,100);
    L1eta[0] = new TH2F("stage2 vs stage1 L1 lead eta", "",10,-3,3,30,-3,3);
    L1phi[0] = new TH2F("stage2 vs stage1 L1 lead phi", "",10,-3.2,3.2,30,-3.2,3.2);

    dr[0] = new TH1F("stage1 dr", "",100,0,0.5);
    dr[1] = new TH1F("stage2 dr", "",100,0,0.5);
    for(int i=0;i<2;i++)
        {
            L1pt[i]->GetXaxis()->SetTitle("stage1 L1 pT"); 
            L1eta[i]->GetXaxis()->SetTitle("stage1 L1 eta"); 
            L1phi[i]->GetXaxis()->SetTitle("stage1 L1 phi"); 

            L1pt[i]->GetYaxis()->SetTitle("stage2 L1 pT"); 
            L1eta[i]->GetYaxis()->SetTitle("stage2 L1 eta"); 
            L1phi[i]->GetYaxis()->SetTitle("stage2 L1 phi"); 
        }
    
    hpt[0] = new TH1F("offline pt for stage1 failures","",25,0,100);
    heta[0] = new TH1F("offline eta for stage1 failures","",15,-3,3);
    hphi[0] = new TH1F("offline phi for stage1 failures","",16,-3.2,3.2);
    hr9[0] = new TH1F("offline r9 for stage1 failures","",25,0,1.0);
    hsieie[0] = new TH1F("offline sieie for stage1 failures","",25,0,0.05);

    hpt[1] = new TH1F("offline pt for stage2 failures","",25,0,100);
    heta[1] = new TH1F("offline eta for stage2 failures","",15,-3,3);
    hphi[1] = new TH1F("offline phi for stage2 failures","",16,-3.2,3.2);
    hr9[1] = new TH1F("offline r9 for stage2 failures","",25,0,1.0);
    hsieie[1] = new TH1F("offline sieie for stage2 failures","",25,0,0.05);

    bpt = new TH1F("offline pt","",25,0,100);
    beta = new TH1F("offline eta","",15,-3,3);
    bphi = new TH1F("offline phi","",16,-3.2,3.2);
    br9 = new TH1F("offline r9","",25,0,1.0);
    bsieie = new TH1F("offline sieie","",25,0,0.05);
    
    c_eff_stage1[0] = new TCanvas( "c_eff1_pt","c_eff1_pt");
    c_eff_stage1[1] = new TCanvas( "c_eff1_eta","c_eff1_eta");
    c_eff_stage1[2] = new TCanvas( "c_eff1_phi","c_eff1_phi");
    c_eff_stage1[3] = new TCanvas( "c_eff1_r9","c_eff1_r9");
    c_eff_stage1[4] = new TCanvas( "c_eff1_sieie","c_eff1_sieie");

    c_eff_stage2[0] = new TCanvas( "c_eff2_pt","c_eff2_pt");
    c_eff_stage2[1] = new TCanvas( "c_eff2_eta","c_eff2_eta");
    c_eff_stage2[2] = new TCanvas( "c_eff2_phi","c_eff2_phi");
    c_eff_stage2[3] = new TCanvas( "c_eff2_r9","c_eff2_r9");
    c_eff_stage2[4] = new TCanvas( "c_eff2_sieie","c_eff2_sieie");
    
    for(int i=0;i<5;i++)
        {
            eff_stage1[i]= new TGraphAsymmErrors();
            eff_stage2[i]= new TGraphAsymmErrors();
        }
    
    
}

void L1Compare::init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames )
{
    srand( ( unsigned int ) time( NULL ) );
}

void L1Compare::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
{
    
        
    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    //    edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
    edm::Handle<edm::View<flashgg::DiPhotonCandidate>> diphotons;
    iEvent.getByToken( triggerBits_, triggerBits );
    iEvent.getByToken( triggerObjects_, triggerObjects );
    //    iEvent.getByToken( triggerPrescales_, triggerPrescales );
    iEvent.getByToken( diphotons_, diphotons );
    //if( eles.failedToGet() )
    //{ return; }
    
    
    if( !triggerBits.isValid() ) {
        LogDebug( "" ) << "TriggerResults product not found - returning result=false!";
        return;
    }
    
    // Apply event selection
    
    //temp
    //    std::cout << "testing--------------------------------------------------------" << std::endl;
    //endtemp
    int diphotonIndex=0;
    
    if(diphotons->size()!=1)
        {
            if(diphotons->size()>1)
                std::cout << "                                   diphotons size: " << diphotons->size() <<std::endl;
            return;
        }
    edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( diphotonIndex );
    const flashgg::Photon *pho[2];
    pho[0] = theDiPhoton->leadingPhoton();
    pho[1] = theDiPhoton->subLeadingPhoton();
    
    edm::Handle<edm::View<l1extra::L1EmParticle>> l1iso;
    edm::Handle<edm::View<l1extra::L1EmParticle>> l1noniso;
    edm::Handle<edm::View<l1extra::L1EmParticle>> l1isoold;
    edm::Handle<edm::View<l1extra::L1EmParticle>> l1nonisoold;
    iEvent.getByToken( l1iso_, l1iso );
    iEvent.getByToken( l1noniso_, l1noniso );
    iEvent.getByToken( l1isoold_, l1isoold );
    iEvent.getByToken( l1nonisoold_, l1nonisoold );
    edm::Handle<l1t::EGammaBxCollection> XTMP; 
    iEvent.getByToken(newL1_, XTMP);
    
    float pt[4] = {0,0,0,0};
    float eta[4] = {-6,-6,-6,-6};
    float phi[4] = {-6,-6,-6,-6};
    
    //    unsigned int l1matchIndex = {999,999,999,999};
    //    float bestDr[4] = {0.5,0.5,0.3,0.3};
    //    float minDr[4]={0.3,0.3,0.05,0.05};
    float minDr[2]={0.3,0.3};
    if(fabs(pho[0]->eta())>1.5)
        minDr[0]=0.5;
    if(fabs(pho[1]->eta())>1.5)
        minDr[1]=0.5;
    //    std::cout << "isolated L1" << std::endl;
    for(unsigned int i=0;i< l1noniso->size();i++)
        {    
            std::cout << "l1 noniso: " << l1noniso->ptrAt(i)->et() << " eta : " << l1noniso->ptrAt(i)->eta() << " phi : " << l1noniso->ptrAt(i)->phi() << std::endl;
            if(minDr[0] > deltaR(l1noniso->ptrAt(i)->eta(),l1noniso->ptrAt(i)->phi(),pho[0]->eta(),pho[0]->phi()))
                if(pt[0]<l1noniso->ptrAt(i)->et())
                    {
                        pt[0]=l1noniso->ptrAt(i)->et();
                        eta[0]=l1noniso->ptrAt(i)->eta();
                        phi[0]=l1noniso->ptrAt(i)->phi();
                        //l1matchIndex[0]=i;
                    }
        }
    for(unsigned int i=0;i< l1noniso->size();i++)
        {    
            if(l1noniso->ptrAt(i)->eta()==eta[0]&&l1noniso->ptrAt(i)->phi()==phi[0]&&l1noniso->ptrAt(i)->et()==pt[0]) //skip l1 object already matched to lead photon
                continue;
            if(minDr[1]> deltaR(l1noniso->ptrAt(i)->eta(),l1noniso->ptrAt(i)->phi(),pho[1]->eta(),pho[1]->phi()))
                if(pt[1]<l1noniso->ptrAt(i)->et())
                    {
                        pt[1]=l1noniso->ptrAt(i)->et();
                        eta[1]=l1noniso->ptrAt(i)->eta();
                        phi[1]=l1noniso->ptrAt(i)->phi();
                        //l1matchIndex[1]=i;
                    }
        }

    for(unsigned int i=0;i< l1iso->size();i++)
        {    
            if(minDr[0] > deltaR(l1iso->ptrAt(i)->eta(),l1iso->ptrAt(i)->phi(),pho[0]->eta(),pho[0]->phi()))
                if(pt[0]<l1iso->ptrAt(i)->et())
                    {
                        pt[0]=l1iso->ptrAt(i)->et();
                        eta[0]=l1iso->ptrAt(i)->eta();
                        phi[0]=l1iso->ptrAt(i)->phi();
                        //l1matchIndex[0]=i;
                    }
        }
    for(unsigned int i=0;i< l1iso->size();i++)
        {     
            if(l1iso->ptrAt(i)->eta()==eta[0]&&l1iso->ptrAt(i)->phi()==phi[0]&&l1iso->ptrAt(i)->et()==pt[0]) //skip l1 object already matched to lead photon
                continue;
            if(minDr[1]> deltaR(l1iso->ptrAt(i)->eta(),l1iso->ptrAt(i)->phi(),pho[1]->eta(),pho[1]->phi()))
                if(pt[1]<l1iso->ptrAt(i)->et())
                    {
                        pt[1]=l1iso->ptrAt(i)->et();
                        eta[1]=l1iso->ptrAt(i)->eta();
                        phi[1]=l1iso->ptrAt(i)->phi();
                        //l1matchIndex[1]=i;
                    }
        }
    int stage1_only_comp=1;
    if(stage1_only_comp==1)
        {
            for(unsigned int i=0;i< l1nonisoold->size();i++)
                {    
                    std::cout << "l1 nonisoOLD: " << l1nonisoold->ptrAt(i)->et() << " eta : " << l1nonisoold->ptrAt(i)->eta() << " phi : " << l1nonisoold->ptrAt(i)->phi() << std::endl;
                    if(minDr[0] > deltaR(l1nonisoold->ptrAt(i)->eta(),l1nonisoold->ptrAt(i)->phi(),pho[0]->eta(),pho[0]->phi()))
                        if(pt[2]<l1nonisoold->ptrAt(i)->et())
                            {
                                pt[2]=l1nonisoold->ptrAt(i)->et();
                                eta[2]=l1nonisoold->ptrAt(i)->eta();
                                phi[2]=l1nonisoold->ptrAt(i)->phi();
                                //l1matchIndex[0]=i;
                            }
                }
            for(unsigned int i=0;i< l1nonisoold->size();i++)
                {    
                    if(l1nonisoold->ptrAt(i)->eta()==eta[0]&&l1nonisoold->ptrAt(i)->phi()==phi[0]&&l1nonisoold->ptrAt(i)->et()==pt[0]) //skip l1 object already matched to lead photon
                        continue;
                    if(minDr[1]> deltaR(l1nonisoold->ptrAt(i)->eta(),l1nonisoold->ptrAt(i)->phi(),pho[1]->eta(),pho[1]->phi()))
                        if(pt[3]<l1nonisoold->ptrAt(i)->et())
                            {
                                pt[3]=l1nonisoold->ptrAt(i)->et();
                                eta[3]=l1nonisoold->ptrAt(i)->eta();
                                phi[3]=l1nonisoold->ptrAt(i)->phi();
                                //l1matchIndex[1]=i;
                            }
                }
            
            for(unsigned int i=0;i< l1isoold->size();i++)
                {    
                    if(minDr[0] > deltaR(l1isoold->ptrAt(i)->eta(),l1isoold->ptrAt(i)->phi(),pho[0]->eta(),pho[0]->phi()))
                        if(pt[2]<l1isoold->ptrAt(i)->et())
                            {
                                pt[2]=l1isoold->ptrAt(i)->et();
                                eta[2]=l1isoold->ptrAt(i)->eta();
                                phi[2]=l1isoold->ptrAt(i)->phi();
                                //l1matchIndex[0]=i;
                            }
                }
            for(unsigned int i=0;i< l1isoold->size();i++)
                {     
                    if(l1isoold->ptrAt(i)->eta()==eta[0]&&l1isoold->ptrAt(i)->phi()==phi[0]&&l1isoold->ptrAt(i)->et()==pt[0]) //skip l1 object already matched to lead photon
                        continue;
                    if(minDr[1]> deltaR(l1isoold->ptrAt(i)->eta(),l1isoold->ptrAt(i)->phi(),pho[1]->eta(),pho[1]->phi()))
                        if(pt[3]<l1isoold->ptrAt(i)->et())
                            {
                                pt[3]=l1isoold->ptrAt(i)->et();
                                eta[3]=l1isoold->ptrAt(i)->eta();
                                phi[3]=l1isoold->ptrAt(i)->phi();
                                //l1matchIndex[1]=i;
                            }
                }
            
        }
    else
        {
            for(auto it=XTMP->begin(0); it!=XTMP->end(0); it++)
                {
                    if(minDr[0]> deltaR(it->eta(),it->phi(),pho[0]->eta(),pho[0]->phi()))
                        if(pt[2]<it->et())
                            {
                                pt[2]=it->et();
                                eta[2]=it->eta();
                                phi[2]=it->phi();
                                //l1matchIndex[2]=it;
                            }
                }
            for(int ibx = XTMP->getFirstBX(); ibx <= XTMP->getLastBX(); ++ibx) {
                //for(auto it=XTMP->begin(0); it!=XTMP->end(0); it++)
                for(auto it=XTMP->begin(ibx); it!=XTMP->end(ibx); it++)
                    {
                        if(it->eta()==eta[2]&&it->phi()==phi[2]&&it->et()==pt[2])
                            continue;
                        if(minDr[1]> deltaR(it->eta(),it->phi(),pho[1]->eta(),pho[1]->phi()))
                            if(pt[3]<it->et())
                                {
                                    pt[3]=it->et();
                                    eta[3]=it->eta();
                                    phi[3]=it->phi();
                                    //l1matchIndex[3]=it;
                                }
                        //deltaR2(it->eta(),it->phi(),pho[0]->eta(),pho[0]->phi());
                        //deltaR2(it->eta(),it->phi(),pho[1]->eta(),pho[1]->phi());
                        //std::cout << "stage2 L1:  " << "  et:  " << it->et() << "  eta:  " << it->eta() << "  phi:  " << it->phi() << std::endl;
                    }
            }
        }
    //if(l1matchIndex[0]==l1matchIndex[1])
    if(pt[0]==pt[1]&&eta[0]==eta[1]&&phi[2]==phi[3])
        if(pt[0]>0)
            return;
    //if(l1matchIndex[2]==l1matchIndex[3])
    if(pt[2]==pt[3]&&eta[2]==eta[3]&&phi[2]==phi[3])
        if(pt[2]>0)
            return;
    //std::cout << "pt 0: " << pt[0] << " pt[1]: " << pt[1] << " pt2: " << pt[2] << " pt 3: " << pt[3] << std::endl;

    dr[0]->Fill(deltaR(eta[0],phi[0],pho[0]->eta(),pho[0]->phi()));
    dr[0]->Fill(deltaR(eta[1],phi[1],pho[1]->eta(),pho[1]->phi()));

    dr[1]->Fill(deltaR(eta[2],phi[2],pho[0]->eta(),pho[0]->phi()));
    dr[1]->Fill(deltaR(eta[3],phi[3],pho[1]->eta(),pho[1]->phi()));
    
    if(pt[2]==0)
        {
            std::cout << "--------------------------------------------------------- no match for stage2 L1" << std::endl;
            std::cout << "sublead pt: " << pho[1]->et() << " eta: " << pho[1]->eta() << " phi: " << pho[1]->phi() << std::endl;
            std::cout << "lead    pt: " << pho[0]->et() << " eta: " << pho[0]->eta() << " phi: " << pho[0]->phi() << std::endl;
            
            for(int ibx = XTMP->getFirstBX(); ibx <= XTMP->getLastBX(); ++ibx) {
                //for(auto it=XTMP->begin(0); it!=XTMP->end(0); it++)
                std::cout << "ibx: " << ibx << std::endl;
                for(auto it=XTMP->begin(ibx); it!=XTMP->end(ibx); it++)
                    {
                        //if(minDr[0]> deltaR2(it->eta(),it->phi(),pho[0]->eta(),pho[0]->phi()))
                        {
                            std::cout << "deltaR : " << deltaR(it->eta(),it->phi(),pho[0]->eta(),pho[0]->phi()) << std::endl;
                            std::cout << "stage2  pt: " << it->et() << " eta: " << it->eta() << " phi: " << it->phi() << std::endl;
                        }
                    }
            }
        }
    L1pt[0]->Fill(pt[0],pt[2]);
    L1eta[0]->Fill(eta[0],eta[2]);
    L1phi[0]->Fill(phi[0],phi[2]);
    L1pt[1]->Fill(pt[1],pt[3]);
    L1eta[1]->Fill(eta[1],eta[3]);
    L1phi[1]->Fill(phi[1],phi[3]);
    for(int i=0;i<2;i++)
        {
            //full distribution of offline variables
            bpt->Fill(pho[i]->pt());
            beta->Fill(pho[i]->eta());
            bphi->Fill(pho[i]->phi());
            br9->Fill(pho[i]->full5x5_r9());
            bsieie->Fill(pho[i]->full5x5_sigmaIetaIeta());
            
            if(pt[i]==0) //stage1 l1 failed
                {
                    hpt[0]->Fill(pho[i]->pt());
                    heta[0]->Fill(pho[i]->eta());
                    hphi[0]->Fill(pho[i]->phi());
                    hr9[0]->Fill(pho[i]->full5x5_r9());
                    hsieie[0]->Fill(pho[i]->full5x5_sigmaIetaIeta());
                }
            if(pt[i+2]==0) //stage2 l1 failed
                {
                    hpt[1]->Fill(pho[i]->pt());
                    heta[1]->Fill(pho[i]->eta());
                    hphi[1]->Fill(pho[i]->phi());
                    hr9[1]->Fill(pho[i]->full5x5_r9());
                    hsieie[1]->Fill(pho[i]->full5x5_sigmaIetaIeta());
                }
            
            
        }
}
DEFINE_FWK_MODULE(L1Compare);
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

