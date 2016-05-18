// File: HLTAnalyzer.cc
// Description:  Example of Analysis driver originally from Jeremy Mans, 
// Date:  13-October-2006

#ifndef flashgg_HLTanalyzers_HLTEgamma_h
#define flashgg_HLTanalyzers_HLTEgamma_h

#include "TTree.h"
#include "TFile.h"
#include "TH2F.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <map>

#include <DataFormats/Math/interface/deltaR.h>
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateFwd.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidateIsolation.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefProd.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/AssociationMap.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"

#include "DataFormats/TrajectorySeed/interface/TrajectorySeedCollection.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/EgammaReco/interface/HFEMClusterShape.h"
#include "DataFormats/EgammaReco/interface/HFEMClusterShapeAssociation.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"

#include "RecoEgamma/EgammaTools/interface/ECALPositionCalculator.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/Engine/interface/MagneticField.h"

#include "DataFormats/EgammaReco/interface/SuperCluster.h"


class HLTOpenEgamma {
public:
  HLTOpenEgamma();

  TH2F * pt2d[2];
  TH2F * phi2d[2];
  TH2F * eta2d[2];
  TH2F * trkiso2d[2];
  TH2F * ecaliso2d[2];
  TH2F * hoverE2d[2];
  TH2F * r92d[2];
  TH2F * sieie2d[2];

  TH1F* Hpt[4];
  TH1F* Hphi[4];
  TH1F* Heta[4];
  TH1F* HtrkIso[4];
  TH1F* HecalIso[4];
  TH1F* HhoverE[4];
  TH1F* Hr9[4];
  TH1F* Hsieie[4];

  void setup(const edm::ParameterSet& pSet, TTree* tree);
  void clear(void);
  void analyze(
	       const edm::Handle<double>  & rhos,
	       const edm::Handle<edm::View<flashgg::DiPhotonCandidate>>  & diphotons,
               const edm::Handle<reco::RecoEcalCandidateCollection>   & activityECAL,
               const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityEcalIsoMap,
               const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityTrackIsoMap,
               const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityR9Map,
               const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityHoverEHMap,
               TTree* tree);



private:
  void MakeL1NonIsolatedPhotons(
				int photonIndex,
                                const edm::Handle<reco::RecoEcalCandidateCollection>   & recoNonIsolecalcands,
                                const edm::Handle<reco::RecoEcalCandidateIsolationMap> & EcalNonIsolMap,
                                const edm::Handle<reco::RecoEcalCandidateIsolationMap> & TrackNonIsolMap,
                                const edm::Handle<reco::RecoEcalCandidateIsolationMap> & photonR9NonIsoMap,
                                const edm::Handle<reco::RecoEcalCandidateIsolationMap> & photonHoverEHNonIsoMap
                                );
  // Tree variables


  float *  photonpt;  
  float *  photonphi;
  float *  photoneta; 
  float *  photonet;  
  float *  photone;   
  float *  photontrkiso;  
  float *  photonecaliso;  
  float *  photonhovere;   
  float *  photonClusShap; 
  float *  photonr9;       
  
  float *  hecalactivet;  
  float *  hecalactiveta;  
  float *  hecalactivphi;  
  float *  hecalactiveiso; 
  float *  hecalactivtiso;     
  float *  hecalactivClusShap; 
  float *  hecalactivR9;       
  float *  hecalactivhovereh;  
  int      nphoton;
};

#endif // flashgg_HLTanalyzers_HLTEgamma_h


static const size_t kMaxPhot   = 10000;
static const size_t kMaxhPhot   = 10000;

HLTOpenEgamma::HLTOpenEgamma() {
}

/*  Setup the analysis to put the branch-variables size_to the tree. */
void HLTOpenEgamma::setup(const edm::ParameterSet& pSet, TTree* HltTree)
{
  
  pt2d[0] = new TH2F("EB_pt","EB_pt",100,0,100,100,0,100);
  phi2d[0] = new TH2F("EB_phi","EB_phi",32,-3.2,3.2,32,-3.2,3.2);
  eta2d[0]= new TH2F("EB_eta","EB_eta",30,-3,3,30,-3,3);
  trkiso2d[0]= new TH2F("EB_trkiso","EB_trkiso",80,0,20,80,0,20);
  ecaliso2d[0] = new TH2F("EB_ecaliso","EB_ecaliso",80,-2,18,80,-2,18);
  hoverE2d[0] = new TH2F("EB_hovere","EB_hovere",100,0,0.5,100,0,0.5);
  r92d[0] = new TH2F("EB_r9","EB_r9",50,0,1,50,0,1);
  sieie2d[0] = new TH2F("EB_sieie","EB_sieie",50,0,0.05,50,0,0.05);

  pt2d[1] = new TH2F("EE_pt","EE_pt",100,0,100,100,0,100);
  phi2d[1] = new TH2F("EE_phi","EE_phi",32,-3.2,3.2,32,-3.2,3.2);
  eta2d[1]= new TH2F("EE_eta","EE_eta",30,-3,3,30,-3,3);
  trkiso2d[1]= new TH2F("EE_trkiso","EE_trkiso",80,0,20,80,0,20);
  ecaliso2d[1] = new TH2F("EE_ecaliso","EE_ecaliso",80,-2,18,80,-2,18);
  hoverE2d[1] = new TH2F("EE_hovere","EE_hovere",100,0,0.5,100,0,0.5);
  r92d[1] = new TH2F("EE_r9","EE_r9",50,0,1,50,0,1);
  sieie2d[1] = new TH2F("EE_sieie","EE_sieie",50,0,0.05,50,0,0.05);

  Hpt[0] = new TH1F("offline_EB_pt","offline_EB_pt",100,0,100);
  Hpt[1] = new TH1F("offline_EE_pt","offline_EE_pt",100,0,100);
  Hpt[2] = new TH1F("HLT_EB_pt","HLT_EB_pt",100,0,100);
  Hpt[3] = new TH1F("HLT_EE_pt","HLT_EE_pt",100,0,100);

  Hphi[0] = new TH1F("offline_EB_phi","offline_EB_phi",32,-3.2,3.2);
  Hphi[1] = new TH1F("offline_EE_phi","offline_EE_phi",32,-3.2,3.2);
  Hphi[2] = new TH1F("HLT_EB_phi","HLT_EB_phi",32,-3.2,3.2);
  Hphi[3] = new TH1F("HLT_EE_phi","HLT_EE_phi",32,-3.2,3.2);
  
  Heta[0] = new TH1F("offline_EB_eta","offline_EB_eta",30,-3,3);
  Heta[1] = new TH1F("offline_EE_eta","offline_EE_eta",30,-3,3);
  Heta[2] = new TH1F("HLT_EB_eta","HLT_EB_eta",30,-3,3);
  Heta[3] = new TH1F("HLT_EE_eta","HLT_EE_eta",30,-3,3);

  HtrkIso[0] = new TH1F("offline_EB_trkIso","offline_EB_trkIso",80,0,20);
  HtrkIso[1] = new TH1F("offline_EE_trkIso","offline_EE_trkIso",80,0,20);
  HtrkIso[2] = new TH1F("HLT_EB_trkIso","HLT_EB_trkIso",80,0,20);
  HtrkIso[3] = new TH1F("HLT_EE_trkIso","HLT_EE_trkIso",80,0,20);
  
  HecalIso[0] = new TH1F("offline_EB_ecalIso","offline_EB_ecalIso",80,-2,18);
  HecalIso[1] = new TH1F("offline_EE_ecalIso","offline_EE_ecalIso",80,-2,18);
  HecalIso[2] = new TH1F("HLT_EB_ecalIso","HLT_EB_ecalIso",80,-2,18);
  HecalIso[3] = new TH1F("HLT_EE_ecalIso","HLT_EE_ecalIso",80,-2,18);

  HhoverE[0] = new TH1F("offline_EB_hoverE","offline_EB_hoverE",100,0,0.5);
  HhoverE[1] = new TH1F("offline_EE_hoverE","offline_EE_hoverE",100,0,0.5);
  HhoverE[2] = new TH1F("HLT_EB_hoverE","HLT_EB_hoverE",100,0,0.5);
  HhoverE[3] = new TH1F("HLT_EE_hoverE","HLT_EE_hoverE",100,0,0.5);
  
  Hr9[0] = new TH1F("offline_EB_r9","offline_EB_r9",50,0,1);
  Hr9[1] = new TH1F("offline_EE_r9","offline_EE_r9",50,0,1);
  Hr9[2] = new TH1F("HLT_EB_r9","HLT_EB_r9",50,0,1);
  Hr9[3] = new TH1F("HLT_EE_r9","HLT_EE_r9",50,0,1);
  
  Hsieie[0] = new TH1F("offline_EB_sieie","offline_EB_sieie",50,0,0.05);
  Hsieie[1] = new TH1F("offline_EE_sieie","offline_EE_sieie",50,0,0.05);
  Hsieie[2] = new TH1F("HLT_EB_sieie","HLT_EB_sieie",50,0,0.05);
  Hsieie[3] = new TH1F("HLT_EE_sieie","HLT_EE_sieie",50,0,0.05);
  
  for(int i=0;i<4;i++)
    {
      Hpt[i]->SetLineColor(i);
      Hphi[i]->SetLineColor(i);
      Heta[i]->SetLineColor(i);
      HtrkIso[i]->SetLineColor(i);
      HecalIso[i]->SetLineColor(i);
      HhoverE[i]->SetLineColor(i);
      Hr9[i]->SetLineColor(i);
      Hsieie[i]->SetLineColor(i);
    }
  
  for(int i =0;i<2;i++)
    {
      pt2d[i]->GetXaxis()->SetTitle("offline pT");
      phi2d[i]->GetXaxis()->SetTitle("offline phi");
      eta2d[i]->GetXaxis()->SetTitle("offline eta");
      trkiso2d[i]->GetXaxis()->SetTitle("offline trk iso");
      ecaliso2d[i]->GetXaxis()->SetTitle("offline ecal iso");
      hoverE2d[i]->GetXaxis()->SetTitle("offline h/e");
      r92d[i]->GetXaxis()->SetTitle("offline r9");
      sieie2d[i]->GetXaxis()->SetTitle("offline sieie");

      pt2d[i]->GetYaxis()->SetTitle("HLT pT");
      phi2d[i]->GetYaxis()->SetTitle("HLT phi");
      eta2d[i]->GetYaxis()->SetTitle("HLT eta");
      trkiso2d[i]->GetYaxis()->SetTitle("HLT trk iso");
      ecaliso2d[i]->GetYaxis()->SetTitle("HLT ecal iso");
      hoverE2d[i]->GetYaxis()->SetTitle("HLT h/e");
      r92d[i]->GetYaxis()->SetTitle("HLT r9");
      sieie2d[i]->GetYaxis()->SetTitle("HLT sieie");
    }
  
  photonpt          = new float[kMaxPhot];
  photonphi         = new float[kMaxPhot];
  photoneta         = new float[kMaxPhot];
  photonet          = new float[kMaxPhot];
  photone           = new float[kMaxPhot];
  photontrkiso      = new float[kMaxPhot];
  photonecaliso     = new float[kMaxPhot];
  photonhovere      = new float[kMaxPhot];
  photonClusShap    = new float[kMaxPhot];
  photonr9          = new float[kMaxPhot];

  hecalactivet           = new float[kMaxhPhot];
  hecalactiveta          = new float[kMaxhPhot];
  hecalactivphi          = new float[kMaxhPhot];
  hecalactiveiso         = new float[kMaxhPhot];
  hecalactivtiso         = new float[kMaxhPhot];
  hecalactivClusShap     = new float[kMaxhPhot];
  hecalactivR9           = new float[kMaxhPhot];
  hecalactivhovereh      = new float[kMaxhPhot];
  nphoton     = 0;

  HltTree->Branch("NrecoPhot",          &nphoton,           "NrecoPhot/I");
  HltTree->Branch("recoPhotPt",         photonpt,           "recoPhotPt[NrecoPhot]/F");
  HltTree->Branch("recoPhotPhi",        photonphi,          "recoPhotPhi[NrecoPhot]/F");
  HltTree->Branch("recoPhotEta",        photoneta,          "recoPhotEta[NrecoPhot]/F");
  HltTree->Branch("recoPhotEt",         photonet,           "recoPhotEt[NrecoPhot]/F");
  HltTree->Branch("recoPhotE",          photone,            "recoPhotE[NrecoPhot]/F");
  HltTree->Branch("recoPhotTiso",       photontrkiso,            "recoPhotTiso[NrecoPhot]/F");
  HltTree->Branch("recoPhotEiso",       photonecaliso,            "recoPhotEiso[NrecoPhot]/F");
  HltTree->Branch("recoPhotHoverE",     photonhovere,            "recoPhotHoverE[NrecoPhot]/F");
  HltTree->Branch("recoPhotClusShap",   photonClusShap,          "recoPhotClusShap[NrecoPhot]/F");
  HltTree->Branch("recoPhotR9",         photonr9,                "recoPhotR9[NrecoPhot]/F");

  HltTree->Branch("NohEcalActiv",            & nphoton,               "NohEcalActiv/I");
  HltTree->Branch("ohEcalActivEt",           hecalactivet,            "ohEcalActivEt[NohEcalActiv]/F");
  HltTree->Branch("ohEcalActivEta",          hecalactiveta,           "ohEcalActivEta[NohEcalActiv]/F");
  HltTree->Branch("ohEcalActivPhi",          hecalactivphi,           "ohEcalActivPhi[NohEcalActiv]/F");
  HltTree->Branch("ohEcalActivEiso",         hecalactiveiso,          "ohEcalActivEiso[NohEcalActiv]/F");
  HltTree->Branch("ohEcalActivTiso",         hecalactivtiso,          "ohEcalActivTiso[NohEcalActiv]/F");
  HltTree->Branch("ohEcalActivClusShap",     hecalactivClusShap,      "ohEcalActivClusShap[NohEcalActiv]/F");
  HltTree->Branch("ohEcalActivR9",           hecalactivR9,            "ohEcalActivR9[NohEcalActiv]/F");
  HltTree->Branch("ohEcalActivHforHoverE",   hecalactivhovereh,       "ohEcalActivHforHoverE[NohEcalActiv]/F");
}

void HLTOpenEgamma::clear(void)
{
  std::memset(photonpt,         '\0', kMaxPhot   * sizeof(float));
  std::memset(photonphi,        '\0', kMaxPhot   * sizeof(float));
  std::memset(photoneta,        '\0', kMaxPhot   * sizeof(float));
  std::memset(photonet,         '\0', kMaxPhot   * sizeof(float));
  std::memset(photone,          '\0', kMaxPhot   * sizeof(float));
  std::memset(photontrkiso,     '\0', kMaxPhot   * sizeof(float));
  std::memset(photonecaliso,    '\0', kMaxPhot   * sizeof(float));
  std::memset(photonhovere,     '\0', kMaxPhot   * sizeof(float));
  std::memset(photonClusShap,   '\0', kMaxPhot   * sizeof(float));
  std::memset(photonr9,         '\0', kMaxPhot   * sizeof(float));

  std::memset(hecalactiveta,         '\0', kMaxPhot   * sizeof(float));
  std::memset(hecalactivphi,         '\0', kMaxPhot   * sizeof(float));
  std::memset(hecalactivet,          '\0', kMaxPhot   * sizeof(float));
  std::memset(hecalactivtiso,        '\0', kMaxPhot   * sizeof(float));
  std::memset(hecalactiveiso,        '\0', kMaxPhot   * sizeof(float));
  std::memset(hecalactivhovereh,     '\0', kMaxPhot   * sizeof(float));
  std::memset(hecalactivClusShap,    '\0', kMaxPhot   * sizeof(float));
  std::memset(hecalactivR9,          '\0', kMaxPhot   * sizeof(float));

  nphoton   = 0;

}

/* **Analyze the event** */
void HLTOpenEgamma::analyze(
			    const edm::Handle<double> & rhos,
			    const edm::Handle<edm::View<flashgg::DiPhotonCandidate>>  & diphotons,
			    const edm::Handle<reco::RecoEcalCandidateCollection>   & activityECAL,
			    const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityEcalIsoMap,
			    const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityTrackIsoMap,
			    const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityR9Map,
			    const edm::Handle<reco::RecoEcalCandidateIsolationMap> & activityHoverEHMap,
			    TTree* tree)
{
  nphoton=0;
  const double rho = *(rhos.product());
  //reco::RecoEcalCandidateCollection::const_iterator recoecalcand = recoNonIsolecalcands->begin()
  //  if(diphotons->isValid())
  if(diphotons->size()>0)
    {
      edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( 0 );
      //edm::Ptr<flashgg::DiPhotonMVAResult> mvares = mvaResults->ptrAt(diphotonIndex);
      const flashgg::SinglePhotonView phot[2] = {*(theDiPhoton->leadingView()), *(theDiPhoton->subLeadingView())};
      
      for(int ipho=0;ipho<2;ipho++)
	{
	  photonpt[ipho] = phot[ipho].photon()->pt();
	  photonphi[ipho] = phot[ipho].photon()->phi(); 
	  photoneta[ipho] = phot[ipho].photon()->eta();
	  photonet[ipho] = phot[ipho].photon()->et();
	  photone[ipho] = phot[ipho].photon()->energy();
	  photontrkiso[ipho] = phot[ipho].photon()->trkSumPtHollowConeDR03();   
	  if(fabs(photoneta[ipho])<1.5)
	    photonecaliso[ipho] = phot[ipho].photon()->pfPhoIso03() - (rho*0.16544);
	  else 
	    photonecaliso[ipho] = phot[ipho].photon()->pfPhoIso03() - (rho*0.13212);
	  
	  photonhovere[ipho] = phot[ipho].photon()->hadronicOverEm();   
	  photonClusShap[ipho] = phot[ipho].photon()->full5x5_sigmaIetaIeta();
	  photonr9[ipho] = phot[ipho].photon()->full5x5_r9(); 
	  //float dR = deltaR( p4, obj.p4() );
	  MakeL1NonIsolatedPhotons(
				   ipho,
				   activityECAL,
				   activityEcalIsoMap,
				   activityTrackIsoMap,
				   activityR9Map,
				   activityHoverEHMap
				   );
	}
      nphoton=2;
    }
  else
    return;
  /////////////////////////////// Open-HLT Egammas ///////////////////////////////
  /*
  for (int u = 0; u < nhltecalactiv; u++) 
    {
      hecalactivet[u]    = theHLTActivityPhotons[u].Et;
      hecalactiveta[u]   = theHLTActivityPhotons[u].eta;
      hecalactivphi[u]   = theHLTActivityPhotons[u].phi;
      hecalactiveiso[u]  = theHLTActivityPhotons[u].ecalIsol;
      hecalactivtiso[u]  = theHLTActivityPhotons[u].trackIsol;
      hecalactivClusShap[u] = theHLTActivityPhotons[u].clusterShape;
      hecalactivhovereh[u] = theHLTActivityPhotons[u].hovereh;
      hecalactivR9[u] = theHLTActivityPhotons[u].r9;
    }
  */
}

void HLTOpenEgamma::MakeL1NonIsolatedPhotons(
					     int photonIndex,
					     const edm::Handle<reco::RecoEcalCandidateCollection>   & recoNonIsolecalcands,
					     const edm::Handle<reco::RecoEcalCandidateIsolationMap> & EcalNonIsolMap,
					     const edm::Handle<reco::RecoEcalCandidateIsolationMap> & TrackNonIsolMap,
					     const edm::Handle<reco::RecoEcalCandidateIsolationMap> & photonR9NonIsoMap,
					     const edm::Handle<reco::RecoEcalCandidateIsolationMap> & photonHoverEHNonIsoMap
					     )
{
  reco::RecoEcalCandidateIsolationMap::const_iterator mapi;
  //  std::cout << "in makel1nonisolatedphotons" << std::endl;
  bool match=0;
  if (recoNonIsolecalcands.isValid()) {
    for (reco::RecoEcalCandidateCollection::const_iterator recoecalcand = recoNonIsolecalcands->begin();
         recoecalcand!= recoNonIsolecalcands->end(); recoecalcand++) {
      if(recoecalcand->et()<15)
	continue;

      double deta = recoecalcand->eta()-photoneta[photonIndex];
      double dphi = recoecalcand->phi()-photonphi[photonIndex];
      if(dphi > 6.1)
	dphi = dphi-2*3.14159;
      if(dphi < -6.1)
	dphi = dphi+2*3.14159;
      if((deta*deta)+(dphi*dphi)>(0.3*0.3))
	{
	  //	  std::cout << "bad deta: " << deta << " bad dphi: " << dphi << std::endl;
	  continue;
	}
      //      std::cout << "good deta: " << deta << " good dphi: " << dphi << std::endl;
      hecalactivet[photonIndex]    = recoecalcand->et();
      hecalactiveta[photonIndex]   = recoecalcand->eta();
      hecalactivphi[photonIndex]   = recoecalcand->phi();
      hecalactiveiso[photonIndex]  = 0;
      hecalactivtiso[photonIndex]  = 0;
      hecalactivClusShap[photonIndex] = 0;
      hecalactivhovereh[photonIndex] = 0;
      hecalactivR9[photonIndex] = 0;
      
      reco::RecoEcalCandidateRef ref = reco::RecoEcalCandidateRef(recoNonIsolecalcands, distance(recoNonIsolecalcands->begin(), recoecalcand));

      // fill the ecal Isolation
      if (EcalNonIsolMap.isValid()) {
        mapi = (*EcalNonIsolMap).find(ref);
        if (mapi !=(*EcalNonIsolMap).end()) { hecalactiveiso[photonIndex] = mapi->val;}
      }
      // fill the track Isolation
      if (TrackNonIsolMap.isValid()) {
        mapi = (*TrackNonIsolMap).find(ref);
        if (mapi !=(*TrackNonIsolMap).end()) { hecalactivtiso[photonIndex] = mapi->val;}
      }
      // fill the R9
      if (photonR9NonIsoMap.isValid()) {
        mapi = (*photonR9NonIsoMap).find(ref);
        if (mapi !=(*photonR9NonIsoMap).end()) { hecalactivR9[photonIndex] = mapi->val;}
      }
      // fill the H for H/E
      if (photonHoverEHNonIsoMap.isValid()) {
        mapi = (*photonHoverEHNonIsoMap).find(ref);
        if (mapi !=(*photonHoverEHNonIsoMap).end()) { hecalactivhovereh[photonIndex] = mapi->val/(recoecalcand->et());}
      }
      //      std::cout << "pho h/e " << hecalactivhovereh[photonIndex] << std::endl;
      
      int j=0;
      if(fabs(photoneta[photonIndex])>1.5)
	j=1;
      pt2d[j]->Fill(photonpt[photonIndex],hecalactivet[photonIndex]);
      phi2d[j]->Fill(photonphi[photonIndex],hecalactivphi[photonIndex]);
      eta2d[j]->Fill(photoneta[photonIndex],hecalactiveta[photonIndex]);
      trkiso2d[j]->Fill(photontrkiso[photonIndex],hecalactivtiso[photonIndex]);
      ecaliso2d[j]->Fill(photonecaliso[photonIndex],hecalactiveiso[photonIndex]);
      hoverE2d[j]->Fill(photonhovere[photonIndex],hecalactivhovereh[photonIndex]);
      r92d[j]->Fill(photonr9[photonIndex],hecalactivR9[photonIndex]);
      sieie2d[j]->Fill(photonClusShap[photonIndex],hecalactivClusShap[photonIndex]);
      Hpt[j]->Fill(photonpt[photonIndex]);
      Hphi[j]->Fill(photonphi[photonIndex]);
      Heta[j]->Fill(photoneta[photonIndex]);
      HtrkIso[j]->Fill(photontrkiso[photonIndex]);
      HecalIso[j]->Fill(photonecaliso[photonIndex]);
      HhoverE[j]->Fill(photonhovere[photonIndex]);
      Hr9[j]->Fill(photonr9[photonIndex]);
      Hsieie[j]->Fill(photonClusShap[photonIndex]);

      Hpt[j+2]->Fill(hecalactivet[photonIndex]);
      Hphi[j+2]->Fill(hecalactivphi[photonIndex]);
      Heta[j+2]->Fill(hecalactiveta[photonIndex]);
      HtrkIso[j+2]->Fill(hecalactivtiso[photonIndex]);
      HecalIso[j+2]->Fill(hecalactiveiso[photonIndex]);
      HhoverE[j+2]->Fill(hecalactivhovereh[photonIndex]);
      Hr9[j+2]->Fill(hecalactivR9[photonIndex]);
      Hsieie[j+2]->Fill(hecalactivClusShap[photonIndex]);
    }
  }
  if(!match)
    nphoton=0;
}





#include <boost/foreach.hpp>


#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/Records/interface/HcalRecNumberingRecord.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "Geometry/CaloTopology/interface/CaloTowerTopology.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
//#include "flashgg/Validation/plugins/HLTEgamma.cc"
//#include "flashgg/Validation/interface/HLTEgamma.h"

class HLTOpen : public edm::EDAnalyzer {
public:
  explicit HLTOpen(edm::ParameterSet const& conf);
  virtual void analyze(edm::Event const& e, edm::EventSetup const& iSetup);
  virtual void beginRun(const edm::Run& , const edm::EventSetup& );
  virtual void endJob();
  TFile *file;
  TTree *HltTree;
  
private:
  HLTOpenEgamma   elm_analysis_;

  edm::EDGetTokenT<double> RhoToken_;
  edm::EDGetTokenT<edm::View<flashgg::DiPhotonCandidate>> DiPhotonToken_;
  edm::EDGetTokenT<reco::RecoEcalCandidateCollection>    ECALActivityToken_;
  edm::EDGetTokenT<reco::RecoEcalCandidateIsolationMap>  ActivityEcalIsoToken_;
  edm::EDGetTokenT<reco::RecoEcalCandidateIsolationMap>  ActivityTrackIsoToken_;
  edm::EDGetTokenT<reco::RecoEcalCandidateIsolationMap>  ActivityR9Token_;
  edm::EDGetTokenT<reco::RecoEcalCandidateIsolationMap>  ActivityHoverEHToken_;
  edm::InputTag Rho_;
  edm::InputTag DiPhoton_;
  edm::InputTag ECALActivity_;
  edm::InputTag ActivityEcalIso_;
  edm::InputTag ActivityTrackIso_;
  edm::InputTag ActivityR9_;
  edm::InputTag ActivityHoverEH_;
};

typedef std::pair<const char *, const edm::InputTag *> MissingCollectionInfo;

template <class T>
static inline
bool getCollection(const edm::Event & event, std::vector<MissingCollectionInfo> & missing, edm::Handle<T> & handle, const edm::InputTag & name, const edm::EDGetTokenT<T> token, const char * description) 
{
  event.getByToken(token, handle);
  bool valid = handle.isValid();
  if (not valid) {
    missing.push_back( std::make_pair(description, & name) );
    handle.clear();
    //std::cout << "not valid "<< description << " " << name << std::endl;
  }
  return valid;
}

// Boiler-plate constructor definition of an analyzer module:
HLTOpen::HLTOpen(edm::ParameterSet const& conf) {
  
  // If your module takes parameters, here is where you would define
  // their names and types, and access them to initialize internal
  // variables. Example as follows:
  //  std::cout << " Beginning HLTOpen Analysis " << std::endl;
  
  // Add ECAL Activity
  
  DiPhoton_                        = conf.getParameter<edm::InputTag> ("DiPhotons");
  ECALActivity_                    = conf.getParameter<edm::InputTag> ("ECALActivity");
  ActivityEcalIso_                 = conf.getParameter<edm::InputTag> ("ActivityEcalIso");
  ActivityTrackIso_                = conf.getParameter<edm::InputTag> ("ActivityTrackIso");
  ActivityR9_                      = conf.getParameter<edm::InputTag> ("ActivityR9");
  ActivityHoverEH_                 = conf.getParameter<edm::InputTag> ("ActivityHcalForHoverE");
  
  
  // Define all consumed products  
  Rho_                             = conf.getParameter<edm::InputTag> ("Rho" );
  RhoToken_      = consumes<double>(Rho_);
  
  DiPhotonToken_ = consumes<edm::View<flashgg::DiPhotonCandidate>>(DiPhoton_);
  ECALActivityToken_ = consumes<reco::RecoEcalCandidateCollection>(ECALActivity_);
  ActivityEcalIsoToken_ = consumes<reco::RecoEcalCandidateIsolationMap>(ActivityEcalIso_);
  ActivityTrackIsoToken_ = consumes<reco::RecoEcalCandidateIsolationMap>(ActivityTrackIso_);
  ActivityR9Token_ = consumes<reco::RecoEcalCandidateIsolationMap>(ActivityR9_);
  ActivityHoverEHToken_ = consumes<reco::RecoEcalCandidateIsolationMap>(ActivityHoverEH_);
  file = new TFile( "openHLTtest.root", "recreate" );
  file->cd();
  HltTree = new TTree("HltTree", "");
  elm_analysis_.setup(conf, HltTree);
  
}

void HLTOpen::beginRun(const edm::Run& run, const edm::EventSetup& c){ 

}

// Boiler-plate "analyze" method declaration for an analyzer module.
void HLTOpen::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup) {
  
  // To get information from the event setup, you must request the "Record"
  // which contains it and then extract the object you need
  //edm::ESHandle<CaloGeometry> geometry;
  //iSetup.get<IdealGeometryRecord>().get(geometry);
  
  // These declarations create handles to the types of records that you want
  // to retrieve from event "iEvent".
  
  // ECAL Activity

  
  edm::Handle<double> RhoHandle;
  edm::Handle<edm::View<flashgg::DiPhotonCandidate>> DiPhotonHandle;
  edm::Handle<reco::RecoEcalCandidateCollection>    ActivityCandsHandle;  
  edm::Handle<reco::RecoEcalCandidateIsolationMap>  ActivityEcalIsoHandle;
  edm::Handle<reco::RecoEcalCandidateIsolationMap>  ActivityTrackIsoHandle;
  edm::Handle<reco::RecoEcalCandidateIsolationMap>  ActivityR9Handle;
  edm::Handle<reco::RecoEcalCandidateIsolationMap>  ActivityHoverEHHandle;
  
  std::vector<MissingCollectionInfo> missing;
  getCollection( iEvent, missing, RhoHandle,              Rho_,                       RhoToken_,                      "Rho");
  getCollection( iEvent, missing, DiPhotonHandle,         DiPhoton_,                  DiPhotonToken_,                  "DiPhotons");
  getCollection( iEvent, missing, ActivityCandsHandle,    ECALActivity_,              ECALActivityToken_,              "ECAL Actvity clust");
  getCollection( iEvent, missing, ActivityEcalIsoHandle,  ActivityEcalIso_,           ActivityEcalIsoToken_,           "ECAL Actvity EIso");
  getCollection( iEvent, missing, ActivityTrackIsoHandle, ActivityTrackIso_,          ActivityTrackIsoToken_,          "ECAL Activity TIso");
  getCollection( iEvent, missing, ActivityR9Handle,       ActivityR9_,                ActivityR9Token_,                "ECAL Activity R9");
  getCollection( iEvent, missing, ActivityHoverEHHandle,  ActivityHoverEH_,           ActivityHoverEHToken_,           "ECAL Activity H for HoverE");
  
  // print missing collections
  if (not missing.empty()) {
    std::stringstream out;       
    out <<  "OpenHLT analyser - missing collections (This message is for information only. RECO collections will always be missing when running on RAW, MC collections will always be missing when running on data):";
    BOOST_FOREACH(const MissingCollectionInfo & entry, missing)
      out << "\n\t" << entry.first << ": " << entry.second->encode();
    edm::LogPrint("OpenHLT") << out.str() << std::endl; 
    return;
  }
  
  // run the analysis, passing required event fragments
  elm_analysis_.analyze(
			RhoHandle,
			DiPhotonHandle,
			ActivityCandsHandle,
			ActivityEcalIsoHandle,
			ActivityTrackIsoHandle,
			ActivityR9Handle,
			ActivityHoverEHHandle,
			HltTree);
  if (file)
    file->cd();
  HltTree->Fill();

  
}

// "endJob" is an inherited method that you may implement to do post-EOF processing and produce final output.
void HLTOpen::endJob() {
  //  std::cout << "in endjob" << std::endl;
  if(file)
    file->cd();
  //  std::cout << "openedfile " << std::endl;
  for(int i=0;i<2;i++)
    {
      
      elm_analysis_.pt2d[i]->Write();
      elm_analysis_.phi2d[i]->Write();
      elm_analysis_.eta2d[i]->Write();
      elm_analysis_.trkiso2d[i]->Write();
      elm_analysis_.ecaliso2d[i]->Write();
      elm_analysis_.hoverE2d[i]->Write();
      elm_analysis_.r92d[i]->Write();
      elm_analysis_.sieie2d[i]->Write();
    }
  for(int i=0;i<4;i++)
    {
      elm_analysis_.Hpt[i]->Write();
      elm_analysis_.Hphi[i]->Write();
      elm_analysis_.Heta[i]->Write();
      elm_analysis_.HtrkIso[i]->Write();
      elm_analysis_.HecalIso[i]->Write();
      elm_analysis_.HhoverE[i]->Write();
      elm_analysis_.Hr9[i]->Write();
      elm_analysis_.Hsieie[i]->Write();
    }
  HltTree->Write();
  delete HltTree;
  //  std::cout << "wrote hlt-tree " << std::endl;
  if(file)
    file->Write();
  file->Close();
  //  std::cout << "closed file " << std::endl;
}
DEFINE_FWK_MODULE(HLTOpen);
