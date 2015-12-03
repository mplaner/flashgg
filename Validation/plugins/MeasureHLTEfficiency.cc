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

class HLTEfficiency : public edm::EDAnalyzer
{
public:
    explicit HLTEfficiency( const edm::ParameterSet & );
    ~HLTEfficiency();
    void init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames );
    //bool hltEvent(edm::Handle<edm::TriggerResults> triggerBits);
    bool onlineOfflineMatching( const edm::TriggerNames &triggerNames, edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
                                math::XYZTLorentzVector p4, std::string filterLabel, float dRmin );
    int getPtBin(double pt);
    float getWeights( double eta, double r9 );
    //void endJob(const edm::LuminosityBlock& lumiSeg, const edm::EventSetup& c);
    float bestL1Dr( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold, float bestDr );
    bool L1Matching( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold );
    std::vector<math::XYZTLorentzVector> hltP4( const edm::TriggerNames &triggerNames, edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
            std::vector<std::string> filterLabels );

private:
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;

    std::string outputFileName_;
    std::string weightsFileName_;
    float diphoMVACut_;
    bool useSingleEG_;
    std::vector<std::string> tagSingleElectronFilterName_;
    std::vector<std::string> tagFilterName_;
    std::vector<std::string> probeFilterName_;
    std::vector<std::string> filterName_;

    edm::EDGetTokenT<edm::View<flashgg::DiPhotonCandidate>> diphotons_;
    edm::EDGetTokenT<edm::View<flashgg::DiPhotonMVAResult> > diPhotonMVAToken_;
    edm::EDGetTokenT<edm::View<flashgg::Electron>> eles_;
    edm::EDGetTokenT<edm::View<l1extra::L1EmParticle>> l1iso_;
    edm::EDGetTokenT<edm::View<l1extra::L1EmParticle>> l1noniso_;
    edm::EDGetTokenT<edm::TriggerResults> triggerBits_;
    edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjects_;
    edm::EDGetTokenT<pat::PackedTriggerPrescales> triggerPrescales_;

    edm::ParameterSetID triggerNamesID_;
    std::map<std::string, unsigned int> trigger_indices;
    std::map<std::string, unsigned int> prescales;
    std::map<std::string, unsigned int> prescale_counter;

    //cutBased working points from:  cmssw/RecoEgamma/PhotonIdentification/python/Identification/cutBasedPhotonID_Spring15_50ns_V1_cff.py
    double lead_ptCut = 125.0/3.0; //40 120/3 100
    double sub_ptCut = 125.0/4.0; //30 120/4
    double preselected_diphotons =0;
    double matched_to_tag        =0;
    double probe_passed_IDMVA    =0;
    double probe_passed_pt       =0;

    TH1F *best_l1_dr[2];
    TH1F *l1_dr[2];
    TH2F *dr_vs_eta;
    
    TH1F *TAG_L1_35_eta;
    TH1F *TAG_L1_15_eta;
    TH1F *TAG_L1_10_eta;
    TH1F *PROBE_L1_15_eta;
    TH1F *PROBE_L1_10_eta;
    TH1F *PROBE_L1_35_eta;
    TH1F *TAG_L1_35_pt;
    TH1F *TAG_L1_15_pt;
    TH1F *TAG_L1_10_pt;
    TH1F *PROBE_L1_15_pt;
    TH1F *PROBE_L1_10_pt;
    TH1F *PROBE_L1_35_pt;
    TH1F *TAG_L1_35_ptoM;
    TH1F *TAG_L1_15_ptoM;
    TH1F *TAG_L1_10_ptoM;
    TH1F *PROBE_L1_15_ptoM;
    TH1F *PROBE_L1_10_ptoM;
    TH1F *PROBE_L1_35_ptoM;
    TH1F *TAG_L1_35_nvtx;
    TH1F *TAG_L1_15_nvtx;
    TH1F *TAG_L1_10_nvtx;
    TH1F *PROBE_L1_15_nvtx;
    TH1F *PROBE_L1_10_nvtx;
    TH1F *PROBE_L1_35_nvtx;
    TH1F *Zpeak[14][3];
    //TH1F *Zpeak;

    TH1F *PROBE_HLT_OR_pt_seeded;
    TH1F *PROBE_HLT_Iso_pt_seeded;
    TH1F *PROBE_HLT_R9_pt_seeded;
    TH1F *PROBE_HLT_OR_ptoM_seeded;
    TH1F *PROBE_HLT_Iso_ptoM_seeded;
    TH1F *PROBE_HLT_R9_ptoM_seeded;
    TH1F *PROBE_HLT_OR_eta_seeded;
    TH1F *PROBE_HLT_Iso_eta_seeded;
    TH1F *PROBE_HLT_R9_eta_seeded;
    TH1F *PROBE_HLT_OR_nvtx_seeded;
    TH1F *PROBE_HLT_Iso_nvtx_seeded;
    TH1F *PROBE_HLT_R9_nvtx_seeded;
    TH1F *TAG_HLT_eta_seeded;
    TH1F *TAG_HLT_pt_seeded;
    TH1F *TAG_HLT_ptoM_seeded;
    TH1F *TAG_HLT_nvtx_seeded;

    TH1F *PROBE_HLT_R9_pt_unseeded;
    TH1F *PROBE_HLT_OR_pt_unseeded;
    TH1F *PROBE_HLT_Iso_pt_unseeded;
    TH1F *PROBE_HLT_R9_ptoM_unseeded;
    TH1F *PROBE_HLT_OR_ptoM_unseeded;
    TH1F *PROBE_HLT_Iso_ptoM_unseeded;
    TH1F *PROBE_HLT_Iso_eta_unseeded;
    TH1F *PROBE_HLT_OR_eta_unseeded;
    TH1F *PROBE_HLT_R9_eta_unseeded;
    TH1F *PROBE_HLT_OR_nvtx_unseeded;
    TH1F *PROBE_HLT_Iso_nvtx_unseeded;
    TH1F *PROBE_HLT_R9_nvtx_unseeded;
    TH1F *TAG_HLT_eta_unseeded;
    TH1F *TAG_HLT_pt_unseeded;
    TH1F *TAG_HLT_ptoM_unseeded;
    TH1F *TAG_HLT_nvtx_unseeded;
    TH2F *Weights2D;

    TCanvas *c_eff_L1_7_ptoM = new TCanvas( "c_eff_L1_7_ptoM", "c_eff_L1_7_ptoM" );
    TGraphAsymmErrors *eff_L1_35_ptoM = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_15_ptoM = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_10_ptoM = new TGraphAsymmErrors();
    TCanvas *c_eff_L1_7_pt = new TCanvas( "c_eff_L1_7_pt", "c_eff_L1_7_pt" );
    TGraphAsymmErrors *eff_L1_35_pt = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_15_pt = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_10_pt = new TGraphAsymmErrors();

    TCanvas *c_eff_L1_7_eta = new TCanvas( "c_eff_L1_7_eta", "c_eff_L1_7_eta" );
    TGraphAsymmErrors *eff_L1_35_eta = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_15_eta = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_10_eta = new TGraphAsymmErrors();

    TCanvas *c_eff_L1_7_nvtx = new TCanvas( "c_eff_L1_7_nvtx", "c_eff_L1_7_nvtx" );
    TGraphAsymmErrors *eff_L1_35_nvtx = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_15_nvtx = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_L1_10_nvtx = new TGraphAsymmErrors();

    TCanvas *c_eff_HLT_OR_pt_seeded = new TCanvas( "c_eff_HLT_OR_pt_seeded", "c_eff_HLT_OR_pt_seeded" );
    TGraphAsymmErrors *eff_HLT_OR_pt_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_pt_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_pt_seeded = new TGraphAsymmErrors();
    TCanvas *c_eff_HLT_OR_ptoM_seeded = new TCanvas( "c_eff_HLT_OR_ptoM_seeded", "c_eff_HLT_OR_ptoM_seeded" );
    TGraphAsymmErrors *eff_HLT_OR_ptoM_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_ptoM_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_ptoM_seeded = new TGraphAsymmErrors();
    TCanvas *c_eff_HLT_OR_eta_seeded = new TCanvas( "c_eff_HLT_OR_eta_seeded", "c_eff_HLT_OR_eta_seeded" );
    TGraphAsymmErrors *eff_HLT_OR_eta_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_eta_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_eta_seeded = new TGraphAsymmErrors();
    TCanvas *c_eff_HLT_OR_nvtx_seeded = new TCanvas( "c_eff_HLT_OR_nvtx_seeded", "c_eff_HLT_OR_nvtx_seeded" );
    TGraphAsymmErrors *eff_HLT_OR_nvtx_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_nvtx_seeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_nvtx_seeded = new TGraphAsymmErrors();

    TCanvas *c_eff_HLT_OR_pt_unseeded = new TCanvas( "c_eff_HLT_OR_pt_unseeded", "c_eff_HLT_OR_pt_unseeded" );
    TGraphAsymmErrors *eff_HLT_OR_pt_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_pt_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_pt_unseeded = new TGraphAsymmErrors();
    TCanvas *c_eff_HLT_OR_ptoM_unseeded = new TCanvas( "c_eff_HLT_OR_ptoM_unseeded", "c_eff_HLT_OR_ptoM_unseeded" );
    TGraphAsymmErrors *eff_HLT_OR_ptoM_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_ptoM_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_ptoM_unseeded = new TGraphAsymmErrors();
    TCanvas *c_eff_HLT_OR_eta_unseeded = new TCanvas( "c_eff_HLT_OR_eta_unseeded", "c_eff_HLT_OR_eta_unseeded" );
    TGraphAsymmErrors *eff_HLT_OR_eta_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_eta_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_eta_unseeded = new TGraphAsymmErrors();
    TCanvas *c_eff_HLT_OR_nvtx_unseeded = new TCanvas( "c_eff_HLT_OR_nvtx_unseeded", "c_eff_HLT_OR_nvtx_unseeded" );
    TGraphAsymmErrors *eff_HLT_OR_nvtx_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_Iso_nvtx_unseeded = new TGraphAsymmErrors();
    TGraphAsymmErrors *eff_HLT_R9_nvtx_unseeded = new TGraphAsymmErrors();


};

HLTEfficiency::~HLTEfficiency()
{

    TFile *file = new TFile( outputFileName_.c_str(), "recreate" );

    TH1F * Ecounters = new TH1F("counters","counters",6,0,6);
    Ecounters->Fill(0.0,preselected_diphotons);
    Ecounters->Fill(1.0,matched_to_tag);
    Ecounters->Fill(2.0,probe_passed_IDMVA);
    Ecounters->Fill(3.0,probe_passed_pt);
    Ecounters->Write();
    dr_vs_eta->Write();
    best_l1_dr[0]->Write();
    best_l1_dr[1]->Write();
    l1_dr[0]->Write();
    l1_dr[1]->Write();
    
    for(int i=0;i<14;i++)
        {
            Zpeak[i][0]->Write();
            Zpeak[i][1]->Write();
            Zpeak[i][2]->Write();
        }
    TAG_L1_35_eta->Write();
    TAG_L1_15_eta->Write();
    TAG_L1_10_eta->Write();
    PROBE_L1_35_eta->Write();
    PROBE_L1_15_eta->Write();
    PROBE_L1_10_eta->Write();
    TAG_L1_35_ptoM->Write();
    TAG_L1_15_ptoM->Write();
    TAG_L1_10_ptoM->Write();
    PROBE_L1_35_ptoM->Write();
    PROBE_L1_15_ptoM->Write();
    PROBE_L1_10_ptoM->Write();
    TAG_L1_35_nvtx->Write();
    TAG_L1_15_nvtx->Write();
    TAG_L1_10_nvtx->Write();
    PROBE_L1_35_nvtx->Write();
    PROBE_L1_15_nvtx->Write();
    PROBE_L1_10_nvtx->Write();
    TAG_L1_35_pt->Write();
    TAG_L1_15_pt->Write();
    TAG_L1_10_pt->Write();
    PROBE_L1_15_pt->Write();
    PROBE_L1_10_pt->Write();
    PROBE_L1_35_pt->Write();

    PROBE_HLT_OR_pt_seeded->Write();
    PROBE_HLT_Iso_pt_seeded->Write();
    PROBE_HLT_R9_pt_seeded->Write();
    PROBE_HLT_OR_eta_seeded->Write();
    PROBE_HLT_Iso_eta_seeded->Write();
    PROBE_HLT_R9_eta_seeded->Write();
    PROBE_HLT_OR_ptoM_seeded->Write();
    PROBE_HLT_Iso_ptoM_seeded->Write();
    PROBE_HLT_R9_ptoM_seeded->Write();
    PROBE_HLT_OR_nvtx_seeded->Write();
    PROBE_HLT_Iso_nvtx_seeded->Write();
    PROBE_HLT_R9_nvtx_seeded->Write();
    TAG_HLT_pt_seeded->Write();
    TAG_HLT_eta_seeded->Write();
    TAG_HLT_ptoM_seeded->Write();
    TAG_HLT_nvtx_seeded->Write();

    PROBE_HLT_OR_pt_unseeded->Write();
    PROBE_HLT_Iso_pt_unseeded->Write();
    PROBE_HLT_R9_pt_unseeded->Write();
    PROBE_HLT_OR_eta_unseeded->Write();
    PROBE_HLT_Iso_eta_unseeded->Write();
    PROBE_HLT_R9_eta_unseeded->Write();
    PROBE_HLT_OR_ptoM_unseeded->Write();
    PROBE_HLT_Iso_ptoM_unseeded->Write();
    PROBE_HLT_R9_ptoM_unseeded->Write();
    PROBE_HLT_OR_nvtx_unseeded->Write();
    PROBE_HLT_Iso_nvtx_unseeded->Write();
    PROBE_HLT_R9_nvtx_unseeded->Write();
    TAG_HLT_pt_unseeded->Write();
    TAG_HLT_eta_unseeded->Write();
    TAG_HLT_ptoM_unseeded->Write();
    TAG_HLT_nvtx_unseeded->Write();
    file->Close();
}

HLTEfficiency::HLTEfficiency( const edm::ParameterSet &iConfig ):
    outputFileName_( iConfig.getParameter<std::string>( "outputFileName" ) ),
    weightsFileName_( iConfig.getParameter<std::string>( "weightsFileName" ) ),
    diphoMVACut_( iConfig.getParameter<double>( "diphoMVACut" ) ),
    useSingleEG_( iConfig.getParameter<bool>( "useSingleEG" ) ),
    tagSingleElectronFilterName_( iConfig.getParameter<std::vector<std::string> >( "tagSingleElectronFilterName" ) ),
    tagFilterName_( iConfig.getParameter<std::vector<std::string> >( "tagFilterName" ) ),
    probeFilterName_( iConfig.getParameter<std::vector<std::string> >( "probeFilterName" ) ),
    filterName_( iConfig.getParameter<std::vector<std::string>>( "filterName" ) ),
    diphotons_( consumes<edm::View<flashgg::DiPhotonCandidate>>( iConfig.getParameter<edm::InputTag>( "diphotons" ) ) ),
    diPhotonMVAToken_( consumes<edm::View<flashgg::DiPhotonMVAResult> >( iConfig.getParameter<edm::InputTag> ( "diPhotonMVATag" ) ) ),
    eles_( consumes<edm::View<flashgg::Electron>>( iConfig.getParameter<edm::InputTag>( "electrons" ) ) ),
    l1iso_( consumes<edm::View<l1extra::L1EmParticle>>( iConfig.getParameter<edm::InputTag>( "l1Iso" ) ) ),
    l1noniso_( consumes<edm::View<l1extra::L1EmParticle>>( iConfig.getParameter<edm::InputTag>( "l1NonIso" ) ) ),
    triggerBits_( consumes<edm::TriggerResults>( iConfig.getParameter<edm::InputTag>( "bits" ) ) ),
    triggerObjects_( consumes<pat::TriggerObjectStandAloneCollection>( iConfig.getParameter<edm::InputTag>( "objects" ) ) ),
    triggerPrescales_( consumes<pat::PackedTriggerPrescales>( iConfig.getParameter<edm::InputTag>( "prescales" ) ) )
{

    if( tagFilterName_.size() != probeFilterName_.size() ) {
        std::cout << "Need to specify the same numbers of tag and probe filters." << std::endl;
        abort();
    }

    int etaBin = 30;
    int nvtxBin = 50;
    int ptBin = 15; //33
    double  ptBins[ptBin+1] = {20,22.5,25,27.5,30,33,35,40,45,50,60,70,90,130,180,250}; //{10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,100,150,200};
    TFile *weightsFile = new TFile( weightsFileName_.c_str() );
    Weights2D = ( TH2F * )weightsFile->Get("eta_vs_r9_norm");
    //    weightsFile->Close();
    dr_vs_eta = new TH2F( "best dr vs eta", "", 30, 0, .6, 90,1.5,3 );
    best_l1_dr[0] = new TH1F( "lowest matched l1 dr good eta", "", 100, 0, 2 );
    best_l1_dr[1] = new TH1F( "lowest matched l1 dr 2.4>eta>2.05", "", 100, 0, 2 );
    l1_dr[0] =      new TH1F( "all matched l1 dr good eta", "", 100, 0, 2 );
    l1_dr[1] =      new TH1F( "all matched l1 dr 2.4>eta>2.05", "", 100, 0, 2 );
    //    Zpeak = new TH1F( "Zpeak_all", "", 120, 60, 120 );
    Zpeak[0][0] = new TH1F( "Zpeak_all_seeded", "", 120, 60, 120 );
    Zpeak[0][1] = new TH1F( "Zpeak_pass_seeded", "", 120, 60, 120 );
    Zpeak[0][2] = new TH1F( "Zpeak_fail_seeded", "", 120, 60, 120 );
    Zpeak[1][0] = new TH1F( "Zpeak_all_unseeded", "", 120, 60, 120 );
    Zpeak[1][1] = new TH1F( "Zpeak_pass_unseeded", "", 120, 60, 120 );
    Zpeak[1][2] = new TH1F( "Zpeak_fail_unseeded", "", 120, 60, 120 );

    Zpeak[2][0] = new TH1F( "Zpeak_all_25", "", 120, 60, 120 );  //( 25., 30., 35., 40., 45., 50., 60., 70., 90., 130., 180., 250. )
    Zpeak[2][1] = new TH1F( "Zpeak_pass_25", "", 120, 60, 120 );
    Zpeak[2][2] = new TH1F( "Zpeak_fail_25", "", 120, 60, 120 );
    Zpeak[3][0] = new TH1F( "Zpeak_all_30", "", 120, 60, 120 );
    Zpeak[3][1] = new TH1F( "Zpeak_pass_30", "", 120, 60, 120 );
    Zpeak[3][2] = new TH1F( "Zpeak_fail_30", "", 120, 60, 120 );

    Zpeak[4][0] = new TH1F( "Zpeak_all_35", "", 120, 60, 120 );  //( 25., 30., 35., 40., 45., 50., 60., 70., 90., 130., 180., 250. )
    Zpeak[4][1] = new TH1F( "Zpeak_pass_35", "", 120, 60, 120 );
    Zpeak[4][2] = new TH1F( "Zpeak_fail_35", "", 120, 60, 120 );
    Zpeak[5][0] = new TH1F( "Zpeak_all_40", "", 120, 60, 120 );
    Zpeak[5][1] = new TH1F( "Zpeak_pass_40", "", 120, 60, 120 );
    Zpeak[5][2] = new TH1F( "Zpeak_fail_40", "", 120, 60, 120 );

    Zpeak[6][0] = new TH1F( "Zpeak_all_45", "", 120, 60, 120 );  //( 25., 30., 35., 40., 45., 50., 60., 70., 90., 130., 180., 250. )
    Zpeak[6][1] = new TH1F( "Zpeak_pass_45", "", 120, 60, 120 );
    Zpeak[6][2] = new TH1F( "Zpeak_fail_45", "", 120, 60, 120 );
    Zpeak[7][0] = new TH1F( "Zpeak_all_50", "", 120, 60, 120 );
    Zpeak[7][1] = new TH1F( "Zpeak_pass_50", "", 120, 60, 120 );
    Zpeak[7][2] = new TH1F( "Zpeak_fail_50", "", 120, 60, 120 );

    Zpeak[8][0] = new TH1F( "Zpeak_all_60", "", 120, 60, 120 );  //( 25., 30., 35., 40., 45., 50., 60., 70., 90., 130., 180., 250. )
    Zpeak[8][1] = new TH1F( "Zpeak_pass_60", "", 120, 60, 120 );
    Zpeak[8][2] = new TH1F( "Zpeak_fail_60", "", 120, 60, 120 );
    Zpeak[9][0] = new TH1F( "Zpeak_all_70", "", 120, 60, 120 );
    Zpeak[9][1] = new TH1F( "Zpeak_pass_70", "", 120, 60, 120 );
    Zpeak[9][2] = new TH1F( "Zpeak_fail_70", "", 120, 60, 120 );

    Zpeak[10][0] = new TH1F( "Zpeak_all_90", "", 120, 60, 120 );  //( 25., 30., 35., 40., 45., 50., 60., 70., 90., 130., 180., 250. )
    Zpeak[10][1] = new TH1F( "Zpeak_pass_90", "", 120, 60, 120 );
    Zpeak[10][2] = new TH1F( "Zpeak_fail_90", "", 120, 60, 120 );
    Zpeak[11][0] = new TH1F( "Zpeak_all_130", "", 120, 60, 120 );
    Zpeak[11][1] = new TH1F( "Zpeak_pass_130", "", 120, 60, 120 );
    Zpeak[11][2] = new TH1F( "Zpeak_fail_130", "", 120, 60, 120 );

    Zpeak[12][0] = new TH1F( "Zpeak_all_180", "", 120, 60, 120 );  //( 25., 30., 35., 40., 45., 50., 60., 70., 90., 130., 180., 250. )
    Zpeak[12][1] = new TH1F( "Zpeak_pass_180", "", 120, 60, 120 );
    Zpeak[12][2] = new TH1F( "Zpeak_fail_180", "", 120, 60, 120 );
    Zpeak[13][0] = new TH1F( "Zpeak_all_250", "", 120, 60, 120 );
    Zpeak[13][1] = new TH1F( "Zpeak_pass_250", "", 120, 60, 120 );
    Zpeak[13][2] = new TH1F( "Zpeak_fail_250", "", 120, 60, 120 );


    TAG_L1_35_eta = new TH1F( "DEN_L1_35_eta", "", etaBin, -3, 3 );
    TAG_L1_15_eta = new TH1F( "DEN_L1_15_eta", "", etaBin, -3, 3 );
    TAG_L1_10_eta = new TH1F( "DEN_L1_10_eta", "", etaBin, -3, 3 );
    PROBE_L1_35_eta = new TH1F( "PROBE_L1_35_eta", "", etaBin, -3, 3 );
    PROBE_L1_15_eta = new TH1F( "PROBE_L1_15_eta", "", etaBin, -3, 3 );
    PROBE_L1_10_eta = new TH1F( "PROBE_L1_10_eta", "", etaBin, -3, 3 );
    TAG_L1_35_pt = new TH1F( "DEN_L1_35_pt", "", ptBin, ptBins );
    TAG_L1_15_pt = new TH1F( "DEN_L1_15_pt", "", ptBin, ptBins );
    TAG_L1_10_pt = new TH1F( "DEN_L1_10_pt", "", ptBin, ptBins );
    PROBE_L1_15_pt = new TH1F( "PROBE_L1_15_pt", "", ptBin, ptBins );
    PROBE_L1_10_pt = new TH1F( "PROBE_L1_10_pt", "", ptBin, ptBins );
    PROBE_L1_35_pt = new TH1F( "PROBE_L1_35_pt", "", ptBin, ptBins );
    
    TAG_L1_35_ptoM = new TH1F( "DEN_L1_35_ptoM", "", 20, -3.2, 3.2 );
    TAG_L1_15_ptoM = new TH1F( "DEN_L1_15_ptoM", "", 20, -3.2, 3.2 );
    TAG_L1_10_ptoM = new TH1F( "DEN_L1_10_ptoM", "", 20, -3.2, 3.2 );
    PROBE_L1_15_ptoM = new TH1F( "PROBE_L1_15_ptoM", "", 20, -3.2, 3.2 );
    PROBE_L1_10_ptoM = new TH1F( "PROBE_L1_10_ptoM", "", 20, -3.2, 3.2 );
    PROBE_L1_35_ptoM = new TH1F( "PROBE_L1_35_ptoM", "", 20, -3.2, 3.2 );
    
    TAG_L1_15_nvtx = new TH1F( "DEN_L1_35_nvtx", "", nvtxBin, 0, 100 );
    TAG_L1_35_nvtx = new TH1F( "DEN_L1_15_nvtx", "", nvtxBin, 0, 100 );
    TAG_L1_10_nvtx = new TH1F( "DEN_L1_10_nvtx", "", nvtxBin, 0, 100 );
    PROBE_L1_35_nvtx = new TH1F( "PROBE_L1_35_nvtx", "", nvtxBin, 0, 100 );
    PROBE_L1_15_nvtx = new TH1F( "PROBE_L1_15_nvtx", "", nvtxBin, 0, 100 );
    PROBE_L1_10_nvtx = new TH1F( "PROBE_L1_10_nvtx", "", nvtxBin, 0, 100 );



    PROBE_HLT_OR_pt_unseeded = new TH1F( "PROBE_HLT_OR_pt_unseeded", "", ptBin, ptBins );
    PROBE_HLT_Iso_pt_unseeded = new TH1F( "PROBE_HLT_ISO_pt_unseeded", "", ptBin, ptBins );
    PROBE_HLT_R9_pt_unseeded = new TH1F( "PROBE_HLT_R9_pt_unseeded", "", ptBin, ptBins );
    PROBE_HLT_OR_ptoM_unseeded = new TH1F( "PROBE_HLT_OR_ptoM_unseeded", "", 20, -3.2, 3.2 );
    PROBE_HLT_Iso_ptoM_unseeded = new TH1F( "PROBE_HLT_ISO_ptoM_unseeded", "", 20, -3.2, 3.2 );
    PROBE_HLT_R9_ptoM_unseeded = new TH1F( "PROBE_HLT_R9_ptoM_unseeded", "", 20, -3.2, 3.2 );
    PROBE_HLT_OR_eta_unseeded = new TH1F( "PROBE_HLT_OR_eta_unseeded", "", etaBin, -3, 3 );
    PROBE_HLT_Iso_eta_unseeded = new TH1F( "PROBE_HLT_ISO_eta_unseeded", "", etaBin, -3, 3 );
    PROBE_HLT_R9_eta_unseeded = new TH1F( "PROBE_HLT_R9_eta_unseeded", "", etaBin, -3, 3 );
    PROBE_HLT_OR_nvtx_unseeded = new TH1F( "PROBE_HLT_OR_nvtx_unseeded", "", nvtxBin, 0, 100 );
    PROBE_HLT_Iso_nvtx_unseeded = new TH1F( "PROBE_HLT_ISO_nvtx_unseeded", "", nvtxBin, 0, 100 );
    PROBE_HLT_R9_nvtx_unseeded = new TH1F( "PROBE_HLT_R9_nvtx_unseeded", "", nvtxBin, 0, 100 );
    TAG_HLT_eta_unseeded = new TH1F( "DEN_HLT_eta_unseeded", "", etaBin, -3, 3 );
    TAG_HLT_pt_unseeded = new TH1F( "DEN_HLT_pt_unseeded", "", ptBin, ptBins );
    TAG_HLT_ptoM_unseeded = new TH1F( "DEN_HLT_ptoM_unseeded", "", 20, -3.2, 3.2 );
    TAG_HLT_nvtx_unseeded = new TH1F( "DEN_HLT_nvtx_unseeded", "", nvtxBin, 0, 100 );


    PROBE_HLT_OR_pt_seeded = new TH1F( "PROBE_HLT_OR_pt_seeded", "", ptBin, ptBins );
    PROBE_HLT_Iso_pt_seeded = new TH1F( "PROBE_HLT_ISO_pt_seeded", "", ptBin, ptBins );
    PROBE_HLT_R9_pt_seeded = new TH1F( "PROBE_HLT_R9_pt_seeded", "", ptBin, ptBins );
    PROBE_HLT_OR_ptoM_seeded = new TH1F( "PROBE_HLT_OR_ptoM_seeded", "", 20, -3.2,3.2 );
    PROBE_HLT_Iso_ptoM_seeded = new TH1F( "PROBE_HLT_ISO_ptoM_seeded", "", 20, -3.2, 3.2);
    PROBE_HLT_R9_ptoM_seeded = new TH1F( "PROBE_HLT_R9_ptoM_seeded", "", 20, -3.2, 3.2 );
    PROBE_HLT_OR_eta_seeded = new TH1F( "PROBE_HLT_OR_eta_seeded", "", etaBin, -3, 3 );
    PROBE_HLT_Iso_eta_seeded = new TH1F( "PROBE_HLT_ISO_eta_seeded", "", etaBin, -3, 3 );
    PROBE_HLT_R9_eta_seeded = new TH1F( "PROBE_HLT_R9_eta_seeded", "", etaBin, -3, 3 );
    PROBE_HLT_OR_nvtx_seeded = new TH1F( "PROBE_HLT_OR_nvtx_seeded", "", nvtxBin, 0, 100 );
    PROBE_HLT_Iso_nvtx_seeded = new TH1F( "PROBE_HLT_ISO_nvtx_seeded", "", nvtxBin, 0, 100 );
    PROBE_HLT_R9_nvtx_seeded = new TH1F( "PROBE_HLT_R9_nvtx_seeded", "", nvtxBin, 0, 100 );
    TAG_HLT_pt_seeded = new TH1F( "DEN_HLT_pt_seeded", "", ptBin, ptBins );
    TAG_HLT_ptoM_seeded = new TH1F( "DEN_HLT_ptoM_seeded", "", 20, -3.2, 3.2 );
    TAG_HLT_eta_seeded = new TH1F( "DEN_HLT_eta_seeded", "", etaBin, -3, 3 );
    TAG_HLT_nvtx_seeded = new TH1F( "DEN_HLT_nvtx_seeded", "", nvtxBin, 0, 100 );
}


float HLTEfficiency::getWeights( double eta, double r9 )
{
    return( (float)Weights2D->GetBinContent(Weights2D->FindBin(fabs(eta), r9)));
}







int HLTEfficiency::getPtBin( double pt)
{
    if(pt<25)
        return(2);
    else if(pt<30)
        return(3);
    else if(pt<35)
        return(4);
    else if(pt<40)
        return(5);
    else if(pt<45)
        return(6);
    else if(pt<50)
        return(7);
    else if(pt<60)
        return(8);
    else if(pt<70)
        return(9);
    else if(pt<90)
        return(10);
    else if(pt<130)
        return(11);
    else if(pt<180)
        return(12);
    else if(pt<250)
        return(13);
    else
        return(14);
            //( 25., 30., 35., 40., 45., 50., 60., 70., 90., 130., 180., 250. )
            }

void HLTEfficiency::init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames )
{

    std::cout << "in init function" << std::endl;
    trigger_indices.clear();
    for( unsigned int i = 0; i < triggerNames.triggerNames().size(); i++ ) {
        std::string trimmedName = HLTConfigProvider::removeVersion( triggerNames.triggerName( i ) );
        std::cout << triggerNames.triggerName( i ) << std::endl;
        trigger_indices[trimmedName] = triggerNames.triggerIndex( triggerNames.triggerName( i ) );
    }
    srand( ( unsigned int ) time( NULL ) );
}

//bool HLTEfficiency::hltEvent(edm::Handle<edm::TriggerResults> triggerBits) {
//
//  for (std::map<std::string, unsigned int>::const_iterator cit = trigger_indices.begin(); cit != trigger_indices.end(); cit++) {
//    if (triggerBits->accept(cit->second)) {
//      std::vector<std::string>::const_iterator it = find(tpTriggerName_.begin(), tpTriggerName_.end(), cit->first);
//      if (it != tpTriggerName_.end())
//	return true;
//    }
//  }
//
//  return false;
//}

bool HLTEfficiency::L1Matching( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold )
{

// const edm::PtrVector<l1extra::L1EmParticle>& l1Pointers = l1H->ptrVector();
    for( unsigned int i = 0; i < l1H->size(); i++ ) {


        float dR = deltaR( l1H->ptrAt( i )->p4(), cand );
        if(fabs(cand.eta())<2.4&&fabs(cand.eta())>2.05)  //2.4>eta>2.05 (from 2d plot)
            {
                if( dR < 0.5 && l1H->ptrAt( i )->et() > ptThreshold )
                    { return true; }
            }
        else
            if( dR < 0.3 && l1H->ptrAt( i )->et() > ptThreshold )
                { return true; }
    }

    return false;
}

float HLTEfficiency::bestL1Dr( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold, float bestDr = 2.0 )
{
// const edm::PtrVector<l1extra::L1EmParticle>& l1Pointers = l1H->ptrVector();
    for( unsigned int i = 0; i < l1H->size(); i++ ) 
        {
            float dR = deltaR( l1H->ptrAt( i )->p4(), cand );
            
            if(fabs(cand.eta())<2.4&&fabs(cand.eta())>2.05)  //2.4>eta>2.05
                l1_dr[1]->Fill(dR);
            else
                l1_dr[0]->Fill(dR);
            
            if( dR < bestDr && l1H->ptrAt( i )->et() > ptThreshold )
                { 
                    bestDr = dR;
                }
        }
    return bestDr;
}

std::vector<math::XYZTLorentzVector> HLTEfficiency::hltP4( const edm::TriggerNames &triggerNames,
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

bool HLTEfficiency::onlineOfflineMatching( const edm::TriggerNames &triggerNames, edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
        math::XYZTLorentzVector p4, std::string filterLabel, float dRmin = 0.15 )
{
    //    std::cout << "searching for filterLabel: " << filterLabel << std::endl;
    
    for( pat::TriggerObjectStandAlone obj : *triggerObjects ) {
        obj.unpackPathNames( triggerNames );
        if( obj.hasFilterLabel( filterLabel ) ) {
            //for (unsigned h = 0; h < obj.filterLabels().size(); ++h) std::cout << " " << obj.filterLabels()[h];
            //std::cout << "found filterLabel: " << filterLabel << std::endl;
            float dR = deltaR( p4, obj.p4() );
            //std::cout << "dR: " << dR << std::endl;
            if( dR < dRmin )
                { return true; }
        }
    }

    return false;
}

void HLTEfficiency::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
{
    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<pat::PackedTriggerPrescales> triggerPrescales;
    edm::Handle<edm::View<flashgg::DiPhotonCandidate>> diphotons;
    edm::Handle<edm::View<flashgg::Electron>> eles;
    edm::Handle<edm::View<flashgg::DiPhotonMVAResult> > mvaResults;
    
    
    iEvent.getByToken( triggerBits_, triggerBits );
    iEvent.getByToken( triggerObjects_, triggerObjects );
    iEvent.getByToken( triggerPrescales_, triggerPrescales );
    iEvent.getByToken( diphotons_, diphotons );
    iEvent.getByToken(diPhotonMVAToken_, mvaResults);
           
    iEvent.getByToken( eles_, eles );
    //if( eles.failedToGet() )
    //{ return; }


    if( !triggerBits.isValid() ) {
        LogDebug( "" ) << "TriggerResults product not found - returning result=false!";
        return;
    }

    // Apply event selection
    const edm::TriggerNames &triggerNames = iEvent.triggerNames( *triggerBits );
    
    //temp
    //    std::cout << "testing--------------------------------------------------------" << std::endl;
    //endtemp
    
    if( triggerNamesID_ != triggerNames.parameterSetID() ) {
        triggerNamesID_ = triggerNames.parameterSetID();
        init( *triggerBits, triggerNames );
    }

    uint diphotonIndex = -1;
    bool isInverted = false;
    bool isMatched  = false;
    preselected_diphotons ++;
    //std::cout << "diphoton size: " << diphotons->size() << std::endl;
    if( ( rand() ) / ( RAND_MAX / 2 ) ) //choose which photon to try for tag
        {    
            isInverted=true;
        }
    if(diphotons->size()==0)
        return;
    
    diphotonIndex = rand()/(RAND_MAX/(diphotons->size()));  //choose random diphoton
    
    if(diphotonIndex > diphotons->size())
        return;
    edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( diphotonIndex );
    edm::Ptr<flashgg::DiPhotonMVAResult> mvares = mvaResults->ptrAt(diphotonIndex);
    
    const flashgg::Photon *tag;
    const flashgg::Photon *probe;
    if(isInverted)
        {
            tag = theDiPhoton->subLeadingPhoton();
            probe = theDiPhoton->leadingPhoton();
        }
    else
        {
            tag = theDiPhoton->leadingPhoton();
            probe = theDiPhoton->subLeadingPhoton();
        }
    
    if( mvares->mvaValue() < diphoMVACut_ )
        { return; }
    // FIXME add check same size filter collections
    //        std::cout << "tag filter size : " << tagFilterName_.size() << std::endl;
    const flashgg::SinglePhotonView pLead = *(theDiPhoton->leadingView()); 
    const flashgg::SinglePhotonView pSub = *(theDiPhoton->subLeadingView()); 

    if(useSingleEG_)
        {
            for( size_t f = 0; f < tagSingleElectronFilterName_.size(); f++)
                {
                    if(isInverted) //sublead==tag
                        {  
                            if(onlineOfflineMatching( triggerNames, triggerObjects, theDiPhoton->subLeadingPhoton()->p4(), tagSingleElectronFilterName_[f] ))
                                {
                                    
                                    if(pSub.phoIdMvaWrtChosenVtx()<-0.5||pLead.phoIdMvaWrtChosenVtx()<-0.8)  //skip event based on photon IDMVA
                                        return; 
                                    isMatched=true;
                                }
                            else
                                return;
                        }
                    
                    else //lead==tab
                        if(onlineOfflineMatching( triggerNames, triggerObjects, theDiPhoton->leadingPhoton()->p4(), tagSingleElectronFilterName_[f] ))
                            {
                                if(pLead.phoIdMvaWrtChosenVtx()<-0.5||pSub.phoIdMvaWrtChosenVtx()<-0.8)  //skip event based on photon IDMVA
                                    return; 
                                isMatched=true;
                            }
                        else
                            return;
                    if(fabs(tag->eta())>2.1) //skip event where tag is high eta
                        return;
                    if(fabs(tag->eta())>1.444&&fabs(tag->eta())<1.566)  //skip tag in gap
                        return;
                    if(fabs(probe->eta())>1.444&&fabs(probe->eta())<1.566)  //skip probe in gap
                       return;
                    
                    if(theDiPhoton->leadingPhoton()->pt()<30||theDiPhoton->subLeadingPhoton()->pt()<20) //apply again the preselection pT cuts
                        return;
                    
                    if( theDiPhoton->mass() < 60 || theDiPhoton->mass() > 120 ) //mass cut
                        {
                            return;
                        }
                    
                }
            
        }
    if(!isMatched)
        return;
    matched_to_tag ++;

     edm::Handle<edm::View<l1extra::L1EmParticle>> l1iso;
     edm::Handle<edm::View<l1extra::L1EmParticle>> l1noniso;
     iEvent.getByToken( l1iso_, l1iso );
     iEvent.getByToken( l1noniso_, l1noniso );

     float probe_weight = 1;
     //     if(probe_weight==1)
     //   {}
     float probe_nvtx = theDiPhoton->nVert();
     //////////need to apply reweighting for R9 for photons vs electrons/////////////////
     probe_weight = getWeights( probe->eta(), probe->full5x5_r9() );

     bool taggedHLTlead = false;
     //mark event if TAG is matched to HLT seeded leg 
     if( onlineOfflineMatching( triggerNames, triggerObjects, tag->p4(), filterName_[0] ) ||
         onlineOfflineMatching( triggerNames, triggerObjects, tag->p4(), filterName_[1] ) )
         { taggedHLTlead = true; }
     
     /////////////////////L1 efficiency denominators///////////////////////
     if(probe->pt()>15)
         {
             TAG_L1_10_eta->Fill( probe->eta(), probe_weight );
             TAG_L1_10_ptoM->Fill( probe->phi(), probe_weight );
             TAG_L1_10_nvtx->Fill( probe_nvtx, probe_weight );
         }
     if(probe->pt()>20)
         {
             TAG_L1_15_eta->Fill( probe->eta(), probe_weight );
             TAG_L1_15_ptoM->Fill( probe->phi(), probe_weight );
             TAG_L1_15_nvtx->Fill( probe_nvtx, probe_weight );
         }
     if(probe->pt()>45)
         {
             TAG_L1_35_eta->Fill( probe->eta(), probe_weight );
             TAG_L1_35_ptoM->Fill( probe->phi(), probe_weight );
             TAG_L1_35_nvtx->Fill( probe_nvtx, probe_weight );
         }
     TAG_L1_10_pt->Fill( probe->pt(), probe_weight );
     TAG_L1_15_pt->Fill( probe->pt(), probe_weight );
     TAG_L1_35_pt->Fill( probe->pt(), probe_weight );

     bool flag_L1_probe10 = false;
     bool flag_L1_probe15 = false;
     bool flag_L1_probe35 = false;
     bool flag_L1_probe22 = false;

     if( L1Matching( l1iso, probe->p4(), 40 ) )
         {
             if(probe->pt()>45)
                 {
                 }
             flag_L1_probe35 = true;
         }

     if( !flag_L1_probe35 && L1Matching( l1noniso, probe->p4(), 40 ) )
         {
             if(probe->pt()>45)
                 {
                 }
             flag_L1_probe35 = true;
         }
     
     if( L1Matching( l1iso, probe->p4(), 22 ) )
         {
             flag_L1_probe22 = true;
             if(probe->pt()>27)
                 {
                     PROBE_L1_35_eta->Fill( probe->eta(), probe_weight );
                     PROBE_L1_35_ptoM->Fill( probe->phi(), probe_weight );
                     PROBE_L1_35_nvtx->Fill( probe_nvtx, probe_weight );
                 }
             PROBE_L1_35_pt->Fill( probe->pt(), probe_weight );
         }

     if( !flag_L1_probe22 and L1Matching( l1noniso, probe->p4(), 22 ) )
         {
             if(probe->pt()>27)
                 {
                     PROBE_L1_35_eta->Fill( probe->eta(), probe_weight );
                     PROBE_L1_35_ptoM->Fill( probe->phi(), probe_weight );
                     PROBE_L1_35_nvtx->Fill( probe_nvtx, probe_weight );
                 }
             PROBE_L1_35_pt->Fill( probe->pt(), probe_weight );
             flag_L1_probe22 = true;
         }

     if( L1Matching( l1iso, probe->p4(), 15 ) )
         {
             if(probe->pt()>20)
                 {
                     PROBE_L1_15_eta->Fill( probe->eta(), probe_weight );
                     PROBE_L1_15_ptoM->Fill( probe->phi(), probe_weight );
                     PROBE_L1_15_nvtx->Fill( probe_nvtx, probe_weight );
                 }
             PROBE_L1_15_pt->Fill( probe->pt(), probe_weight );
             flag_L1_probe15 = true;
         }

     if( !flag_L1_probe15 and L1Matching( l1noniso, probe->p4(), 15 ) )
         {
             if(probe->pt()>20)
                 {
                     PROBE_L1_15_eta->Fill( probe->eta(), probe_weight );
                     PROBE_L1_15_ptoM->Fill( probe->phi(), probe_weight );
                     PROBE_L1_15_nvtx->Fill( probe_nvtx, probe_weight );
                 }
             PROBE_L1_15_pt->Fill( probe->pt(), probe_weight );
             flag_L1_probe15 = true;
         }

     if( L1Matching( l1iso, probe->p4(), 10 ) )
         {
             if(probe->pt()>15)
                 {
                     PROBE_L1_10_eta->Fill( probe->eta(), probe_weight );
                     PROBE_L1_10_ptoM->Fill( probe->phi(), probe_weight );
                     PROBE_L1_10_nvtx->Fill( probe_nvtx, probe_weight );
                 }
             PROBE_L1_10_pt->Fill( probe->pt(), probe_weight );
             flag_L1_probe10 = true;
         }

     if( !flag_L1_probe10 and L1Matching( l1noniso, probe->p4(), 10 ) )
         {
             if(probe->pt()>15)
                 {
                     PROBE_L1_10_eta->Fill( probe->eta(), probe_weight );
                     PROBE_L1_10_ptoM->Fill( probe->phi(), probe_weight );
                     PROBE_L1_10_nvtx->Fill( probe_nvtx, probe_weight );
                 }
             PROBE_L1_10_pt->Fill( probe->pt(), probe_weight );
             flag_L1_probe10 = true;
         }

     if( flag_L1_probe10 && taggedHLTlead)
         //    if(probe->pt()>25.0) //minimum scaling pT cut
         {
             TAG_HLT_pt_unseeded->Fill( probe->pt(), probe_weight );
             if(probe->pt()>sub_ptCut)
                 {
                     TAG_HLT_eta_unseeded->Fill( probe->eta(), probe_weight );
                     TAG_HLT_ptoM_unseeded->Fill( probe->phi(), probe_weight );
                     TAG_HLT_nvtx_unseeded->Fill( probe_nvtx, probe_weight );
                     Zpeak[1][0]->Fill( theDiPhoton->mass(), probe_weight ); //fill unseeded all zpeak plot
                 }
             bool isoflag = 0;
             bool r9flag = 0;
             //sublead HLT only                                                                                                     
             
             if( onlineOfflineMatching( triggerNames, triggerObjects, probe->p4(), filterName_[2] ) )
                 {
                     r9flag = 1;
                     PROBE_HLT_R9_pt_unseeded->Fill( probe->pt(), probe_weight );
                     
                     if(probe->pt()>sub_ptCut)
                         {
                             PROBE_HLT_R9_eta_unseeded->Fill( probe->eta(), probe_weight );
                             PROBE_HLT_R9_ptoM_unseeded->Fill( probe->phi(), probe_weight );
                             PROBE_HLT_R9_nvtx_unseeded->Fill( probe_nvtx, probe_weight );
                         }
                 }
             
             if( onlineOfflineMatching( triggerNames, triggerObjects, probe->p4(), filterName_[3] ) ) 
                 {
                     isoflag = 1;
                     PROBE_HLT_Iso_pt_unseeded->Fill( probe->pt(), probe_weight );
                     if(probe->pt()>sub_ptCut)
                         {                     
                             PROBE_HLT_Iso_eta_unseeded->Fill( probe->eta(), probe_weight );
                             PROBE_HLT_Iso_ptoM_unseeded->Fill( probe->phi(), probe_weight );
                             PROBE_HLT_Iso_nvtx_unseeded->Fill( probe_nvtx, probe_weight );
                         }
                 }
             if( isoflag or r9flag ) 
                 {
                     PROBE_HLT_OR_pt_unseeded->Fill( probe->pt(), probe_weight );
                     
                     if(probe->pt()>sub_ptCut)
                         {
                             PROBE_HLT_OR_eta_unseeded->Fill( probe->eta(), probe_weight );
                             PROBE_HLT_OR_ptoM_unseeded->Fill( probe->phi(), probe_weight );
                             PROBE_HLT_OR_nvtx_unseeded->Fill( probe_nvtx, probe_weight );
                             Zpeak[1][1]->Fill( theDiPhoton->mass(), probe_weight ); //fill unseeded pass zpeak plot 
                             //Zpeak[getPtBin(probe->pt())][1]->Fill( theDiPhoton->mass(), probe_weight ); //fill unseeded pass zpeak plot
                         }
                 }
             else
                 {
                     if(probe->pt()>sub_ptCut)
                         Zpeak[1][2]->Fill( theDiPhoton->mass(), probe_weight ); //fill unseeded fail zpeak plot                              //Zpeak[getPtBin(probe->pt())][2]->Fill( theDiPhoton->mass(), probe_weight ); //fill seeded fail zpeak plot  
                 }
         }
     
     //Step II: seeded leg efficiency                                                                                           
     //  if Probe has a lead L1 seed matched to it                                                                              
     //  no HLT requirement on tag (tag==unseeded leg of HLT)                                                                   
     //if( !flag_L1_probe22 )
     //    { return; }
     //only include events which could pass the trigger                                                                         
     //if( probe->pt() < 30.00 )
     //    {return;}
     probe_passed_pt  ++;
     
     //     probe_weight=1;
     if( flag_L1_probe22 && probe->pt()>30) 
         //if(probe->pt()>33.3334) //minimum scaling pT cut
             {
                 TAG_HLT_pt_seeded->Fill( probe->pt(), probe_weight );
                 
                 if(probe->pt()>lead_ptCut) 
                     {
                         TAG_HLT_eta_seeded->Fill( probe->eta(), probe_weight );
                         TAG_HLT_ptoM_seeded->Fill( probe->phi(), probe_weight );
                         TAG_HLT_nvtx_seeded->Fill( probe_nvtx, probe_weight );
                         Zpeak[0][0]->Fill( theDiPhoton->mass(), probe_weight ); //fill seeded all zpeak plot                                        
                         Zpeak[getPtBin(probe->pt())][0]->Fill( theDiPhoton->mass(), probe_weight ); //fill seeded all zpeak plot                    
                     }
                 bool isoflag = 0;
                 bool r9flag =0;
                 if( onlineOfflineMatching( triggerNames, triggerObjects, probe->p4(), filterName_[1] ) ) {
                     r9flag = 1;
                     PROBE_HLT_R9_pt_seeded->Fill( probe->pt(), probe_weight );
                     if(probe->pt()>lead_ptCut) 
                         {
                             PROBE_HLT_R9_eta_seeded->Fill( probe->eta(), probe_weight );
                             PROBE_HLT_R9_ptoM_seeded->Fill( probe->phi(), probe_weight );
                             PROBE_HLT_R9_nvtx_seeded->Fill( probe_nvtx, probe_weight );
                         }
                 }
                 if( onlineOfflineMatching( triggerNames, triggerObjects, probe->p4(), filterName_[0] ) ) {
                     isoflag = 1;
                     PROBE_HLT_Iso_pt_seeded->Fill( probe->pt(), probe_weight );
                     if(probe->pt()>lead_ptCut) 
                         {
                             PROBE_HLT_Iso_eta_seeded->Fill( probe->eta(), probe_weight );
                             PROBE_HLT_Iso_ptoM_seeded->Fill( probe->phi(), probe_weight );
                             PROBE_HLT_Iso_nvtx_seeded->Fill( probe_nvtx, probe_weight );
                         }
                 }
                 if( isoflag || r9flag ) 
                     {
                         PROBE_HLT_OR_pt_seeded->Fill( probe->pt(), probe_weight );
                         if(probe->pt()>lead_ptCut) 
                             {
                                 PROBE_HLT_OR_eta_seeded->Fill( probe->eta(), probe_weight );
                                 PROBE_HLT_OR_ptoM_seeded->Fill( probe->phi(), probe_weight );
                                 PROBE_HLT_OR_nvtx_seeded->Fill( probe_nvtx, probe_weight );
                                 Zpeak[0][1]->Fill( theDiPhoton->mass(), probe_weight ); //fill seeded pass zpeak plot                                   
                                 Zpeak[getPtBin(probe->pt())][1]->Fill( theDiPhoton->mass(), probe_weight ); //fill seeded pass zpeak plot 
                             }
                     }
                 else
                     {
                         if(probe->pt()>lead_ptCut) 
                             {
                                 Zpeak[0][2]->Fill( theDiPhoton->mass(), probe_weight ); //fill seeded fail zpeak plot 
                                 Zpeak[getPtBin(probe->pt())][2]->Fill( theDiPhoton->mass(), probe_weight ); //fill seeded fail zpeak plot 
                             }
                     }
             }
}

DEFINE_FWK_MODULE( HLTEfficiency );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

