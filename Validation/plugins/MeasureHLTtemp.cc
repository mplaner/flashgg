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

class HLTtest : public edm::EDAnalyzer
{
public:
    explicit HLTtest( const edm::ParameterSet & );
    ~HLTtest();
    void init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames );
    //bool hltEvent(edm::Handle<edm::TriggerResults> triggerBits);
    bool onlineOfflineMatching( const edm::TriggerNames &triggerNames, edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
                                math::XYZTLorentzVector p4, std::string filterLabel, float dRmin );
    int getPtBin(double pt);
    float getWeights( double eta, double r9 );
    float getWeights( double r9 );
    int GetR9Bin( double r9 );
    //void endJob(const edm::LuminosityBlock& lumiSeg, const edm::EventSetup& c);
    float bestL1Dr( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold, float bestDr );
    bool L1Matching( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold );
    std::vector<math::XYZTLorentzVector> hltP4( const edm::TriggerNames &triggerNames, edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
            std::vector<std::string> filterLabels );

private:
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;

    std::string outputFileName_;
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
    float weights2d[8][120] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.201031, 0.237288, 0.185792, 0.246377, 0.282051, 0.274112, 0.306122, 0.211712, 0.234742, 0.285047, 0.295652, 0.213992, 0.305785, 0.271552, 0.239819, 0.253165, 0.236162, 0.175573, 0.231441, 0.238636, 0.276018, 0.272085, 0.292181, 0.342742, 0.299242, 0.329457, 0.30566, 0.32197, 0.269231, 0.305556, 0.239437, 0.302239, 0.259786, 0.340741, 0.371324, 0.323944, 0.35, 0.400763, 0.452107, 0.330798, 0.389493, 0.378965, 0.397833, 0.40085, 0.507812, 0.794041, 1.24661, 2.25941, 3.09643, 3.5037, 2.13043, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.299882, 0.269333, 0.254846, 0.249695, 0.244496, 0.253102, 0.257659, 0.222795, 0.229061, 0.242062, 0.235556, 0.222461, 0.233763, 0.204858, 0.230786, 0.239385, 0.221424, 0.222539, 0.224543, 0.24514, 0.240581, 0.227478, 0.236597, 0.236358, 0.234492, 0.250657, 0.248488, 0.244914, 0.243453, 0.24445, 0.240084, 0.243663, 0.237026, 0.242305, 0.247476, 0.245392, 0.248212, 0.23235, 0.234457, 0.224393, 0.221186, 0.220652, 0.246175, 0.347522, 0.610506, 0.847925, 0.77073, 0.581148, 0.609492, 0.58871, 0.539683, 0.357143, 0.413793, 0.290909, 0.512821, 0.0588235, 0.236842, 0.0952381, 0.238095, 0.421053, 0.4, 0.555556, 0.3, 0, 0.285714, 0.375, 0.125, 0.25, 0.666667}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.255605, 0.267684, 0.250301, 0.233918, 0.2369, 0.216008, 0.233205, 0.217117, 0.19846, 0.218775, 0.212211, 0.21736, 0.182796, 0.22449, 0.245449, 0.219438, 0.216595, 0.200448, 0.213933, 0.214249, 0.233679, 0.234336, 0.247934, 0.203292, 0.250891, 0.232905, 0.229955, 0.23774, 0.2297, 0.246068, 0.229153, 0.242604, 0.223228, 0.232759, 0.236916, 0.244728, 0.240829, 0.224359, 0.226677, 0.237584, 0.228889, 0.246466, 0.287596, 0.396658, 0.759791, 1.27109, 1.40326, 1.02342, 0.888889, 0.636364, 1.33333, 0.357143, 0.0625, 0.411765, 0.333333, 0.333333, 0.444444, 0.333333, 0.2, 0.166667, 0.333333, 0, 0, 0, 0.333333, 0, 0.5, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.207386, 0.197722, 0.230893, 0.184211, 0.224964, 0.185734, 0.200394, 0.190418, 0.194064, 0.210762, 0.242627, 0.200828, 0.21726, 0.226809, 0.219118, 0.233706, 0.223283, 0.217373, 0.233718, 0.225542, 0.229191, 0.223412, 0.240795, 0.231915, 0.227102, 0.243684, 0.245035, 0.242887, 0.246608, 0.236171, 0.2513, 0.247696, 0.240093, 0.257992, 0.261465, 0.273043, 0.289978, 0.287282, 0.287864, 0.299237, 0.329556, 0.362031, 0.445851, 0.616647, 1.19141, 2.40091, 3.00281, 2.22642, 1.74468, 1.4375, 0.875, 0.5, 0.6, 1.25, 0.25, 0.75, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.225, 0.222938, 0.207729, 0.199148, 0.218679, 0.226115, 0.22591, 0.235294, 0.214286, 0.222635, 0.213533, 0.226009, 0.230035, 0.216795, 0.253441, 0.210084, 0.250971, 0.231338, 0.221318, 0.279273, 0.253776, 0.249482, 0.266994, 0.227781, 0.244025, 0.240099, 0.273482, 0.224378, 0.246082, 0.277059, 0.273629, 0.296076, 0.304692, 0.341216, 0.282548, 0.331576, 0.309316, 0.374621, 0.357686, 0.371399, 0.444022, 0.413442, 0.557335, 0.873897, 1.80888, 4.06884, 4.99662, 3.22857, 2, 1.16667, 1, 0.5, 0.25, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.209828, 0.216804, 0.217236, 0.196224, 0.220729, 0.195883, 0.215385, 0.211194, 0.227064, 0.231419, 0.224433, 0.2033, 0.215736, 0.228884, 0.226693, 0.228922, 0.235212, 0.237892, 0.237987, 0.251133, 0.227532, 0.251855, 0.250742, 0.255766, 0.251436, 0.256817, 0.270138, 0.270388, 0.300881, 0.298671, 0.301439, 0.292952, 0.318959, 0.332058, 0.319529, 0.372172, 0.359908, 0.368896, 0.384587, 0.385314, 0.43763, 0.470139, 0.537429, 0.720687, 1.28776, 3.15712, 4.24843, 3.23555, 3.39557, 2.98261, 1.1875, 0.375, 0.5, 0.333333, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0.5, 0, 0, 3, 0, 0.4, 0.333333, 0, 0.3, 0.28928, 0.319687, 0.332476, 0.360412, 0.425681, 0.617679, 1.11872, 2.32877, 2.90897, 2.3592, 1.89634, 1, 0.4, 0, 0.5, 0.5, 1, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.232972, 0.250593, 0.277706, 0.292785, 0.367083, 0.549679, 1.04694, 2.04282, 2.77351, 2.30481, 1.03448, 0.285714, 0.166667, 0.2, 0, 0.5, 0, 0, 0.5, 0, 0.333333, 0, 0, 0.5, 0, 0, 0, 0.5, 0}};



    double weights[100] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.514777, 0.515062, 0.533989, 0.466876, 0.486839, 0.469298, 0.478957, 0.441555, 0.487262, 0.461604, 0.442469, 0.45576, 0.476261, 0.475864, 0.476184, 0.452791, 0.498611, 0.476031, 0.483828, 0.486875, 0.484094, 0.490637, 0.520348, 0.503588, 0.519901, 0.526705, 0.519882, 0.535151, 0.560224, 0.547786, 0.566284, 0.558558, 0.562697, 0.548262, 0.516354, 0.537443, 0.641497, 1.06991, 1.80848, 1.92913, 2.59732, 3.96539, 3.17888, 0.885604, 0.875504, 0.62741, 0.70148, 0.542207, 0.731979, 0.292792, 1.3013, 2.92792, 0.487986, 0.609982, 0.731979, 0, 0.609982, 0.325324};
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

HLTtest::~HLTtest()
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

HLTtest::HLTtest( const edm::ParameterSet &iConfig ):
    outputFileName_( iConfig.getParameter<std::string>( "outputFileName" ) ),
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


float HLTtest::getWeights( double eta, double r9 )
{
    int r9Bin = GetR9Bin( r9 );
    if( fabs( eta ) < 0.8 )
    { return( weights2d[0][r9Bin] ); }
    if( fabs( eta ) < 1.0 )
    { return weights2d[1][r9Bin]; }
    if( fabs( eta ) < 1.2 )
    { return weights2d[2][r9Bin]; }
    if( fabs( eta ) < 1.3 )
    { return weights2d[3][r9Bin]; }
    if( fabs( eta ) < 1.444 )
    { return( weights2d[4][r9Bin] ); }
    if( fabs( eta ) < 1.8 )
    { return weights2d[5][r9Bin]; }
    if( fabs( eta ) < 2.0 )
    { return weights2d[6][r9Bin]; }
    if( fabs( eta ) < 2.5 )
    { return weights2d[7][r9Bin]; }
    return 0;
}


float HLTtest::getWeights( double r9 )
{
    return weights[GetR9Bin( r9 )];
}


int HLTtest::GetR9Bin( double r9 )
{
    double binWidth = 0.01;
    for( int i = 0; i < 1.2 / binWidth; i++ ) {
        if( r9 < i * binWidth )
        { return( i ); }
    }
    return( 0 );
}



int HLTtest::getPtBin( double pt)
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

void HLTtest::init( const edm::TriggerResults &result, const edm::TriggerNames &triggerNames )
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

//bool HLTtest::hltEvent(edm::Handle<edm::TriggerResults> triggerBits) {
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

bool HLTtest::L1Matching( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold )
{

// const edm::PtrVector<l1extra::L1EmParticle>& l1Pointers = l1H->ptrVector();
    for( unsigned int i = 0; i < l1H->size(); i++ ) {

// for (edm::Ptr<l1extra::L1EmParticle> l1Ptr : l1H) {
        //dr < 0.2
        
        //if((l1H->ptrAt( i )->eta() < 2.4) && (l1H->ptrAt( i )->eta() > 2.2))

        float dR = deltaR( l1H->ptrAt( i )->p4(), cand );
        //if(ptThreshold==25 && fabs(cand.eta())<2.4 && fabs(cand.eta())>2.0)
        //   std::cout << "                       TAG l1 eta " << l1H->ptrAt( i )->eta() << " -- reco eta " << cand.eta() << " DR " << dR << " l1 pT: " << l1H->ptrAt(i)->et() << " reco pT " << cand.pt()  << std::endl;
        // if(ptThreshold==1 && fabs(cand.eta())<2.4 && fabs(cand.eta())>2.0)
        //   std::cout << "                     PROBE l1 eta " << l1H->ptrAt( i )->eta() << " -- reco eta " << cand.eta() << " DR " << dR << " l1 pT: " << l1H->ptrAt(i)->et() << " reco pT " << cand.pt()  << std::endl;
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

float HLTtest::bestL1Dr( edm::Handle<edm::View<l1extra::L1EmParticle>> l1H, math::XYZTLorentzVector cand, float ptThreshold, float bestDr = 2.0 )
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

std::vector<math::XYZTLorentzVector> HLTtest::hltP4( const edm::TriggerNames &triggerNames,
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

bool HLTtest::onlineOfflineMatching( const edm::TriggerNames &triggerNames, edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects,
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

void HLTtest::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
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

    int diphotonIndex = -1;
    bool isInverted = false;
    bool isMatched  = false;
    preselected_diphotons ++;
    //std::cout << "diphoton size: " << diphotons->size() << std::endl;
    for( size_t i = 0; i < diphotons->size(); i++ ) {
        
        edm::Ptr<flashgg::DiPhotonCandidate> diphoPtr = diphotons->ptrAt( i );
        edm::Ptr<flashgg::DiPhotonMVAResult> mvares = mvaResults->ptrAt( i );
        if( mvares->mvaValue() < diphoMVACut_ )
            { continue; }
        // FIXME add check same size filter collections
        //        std::cout << "tag filter size : " << tagFilterName_.size() << std::endl;
        if(useSingleEG_)
            {
                for( size_t f = 0; f < tagSingleElectronFilterName_.size(); f++)
                    {
                        isInverted = false;
                        isMatched = false;
                        diphotonIndex =-1;
                        bool leadMatchedToTag = onlineOfflineMatching( triggerNames, triggerObjects, diphoPtr->leadingPhoton()->p4(), tagSingleElectronFilterName_[f] );
                        bool subLeadMatchedToTag = onlineOfflineMatching( triggerNames, triggerObjects, diphoPtr->subLeadingPhoton()->p4(), tagSingleElectronFilterName_[f] );

                         if(fabs(diphoPtr->leadingPhoton()->eta())>2.5)
                             leadMatchedToTag = false;
                         if(fabs(diphoPtr->subLeadingPhoton()->eta())>2.5)
                             subLeadMatchedToTag = false;
                         const flashgg::SinglePhotonView leading = *(diphoPtr->leadingView()); 
                         const flashgg::SinglePhotonView subLeading = *(diphoPtr->subLeadingView()); 
                         if(leading.phoIdMvaWrtChosenVtx()<-0.5||subLeading.phoIdMvaWrtChosenVtx()<-0.8)
                             leadMatchedToTag=false; 
                         if(subLeading.phoIdMvaWrtChosenVtx()<-0.5||leading.phoIdMvaWrtChosenVtx()<-0.8)
                             subLeadMatchedToTag=false;
                         if(diphoPtr->leadingPhoton()->pt()<30||diphoPtr->subLeadingPhoton()->pt()<20) //tag pt cut; probe pt cut
                             leadMatchedToTag=false;
                         if(diphoPtr->subLeadingPhoton()->pt()<30||diphoPtr->leadingPhoton()->pt()<20) //tag pt cut; probe pt cut
                             subLeadMatchedToTag=false;
                         if( diphoPtr->mass() < 60 || diphoPtr->mass() > 120 ) //mass cut
                             {
                                 leadMatchedToTag=false;
                                 subLeadMatchedToTag=false;
                             }

                         if( subLeadMatchedToTag ) {
                             diphotonIndex = i;
                             isInverted = true;
                         }
                         if( leadMatchedToTag ) {
                             diphotonIndex = i;
                             isMatched = true;
                             break;
                         }
                         if( isInverted )
                             { break; }
                     }
             }
     }
     if(!isMatched&&!isInverted)
         return;
     if( diphotonIndex == -1 )
         { return; }
     matched_to_tag ++;
     edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( diphotonIndex );
     const flashgg::Photon *tag = theDiPhoton->leadingPhoton();
     const flashgg::Photon *probe = theDiPhoton->subLeadingPhoton();

     edm::Handle<edm::View<l1extra::L1EmParticle>> l1iso;
     edm::Handle<edm::View<l1extra::L1EmParticle>> l1noniso;
     iEvent.getByToken( l1iso_, l1iso );
     iEvent.getByToken( l1noniso_, l1noniso );

     float probe_weight = 1;
     if(probe_weight==1)
         {}
     float probe_nvtx = theDiPhoton->nVert();
     //////////need to apply reweighting for R9 for photons vs electrons/////////////////
     //    probe_weight = weights[GetR9Bin( probe->full5x5_r9() )];                          
     //    probe_weight = getWeights( probe->eta(), probe->full5x5_r9() );

     //mark event if TAG is matched to HLT seeded leg 
          
     /////////////////////L1 efficiency denominators///////////////////////
     if(probe->pt()>15)
         {
             TAG_L1_10_eta->Fill( probe->eta(), 1.000 );
             TAG_L1_10_ptoM->Fill( probe->phi(), 1.000 );
             TAG_L1_10_nvtx->Fill( probe_nvtx, 1.000 );
         }
     if(probe->pt()>20)
         {
             TAG_L1_15_eta->Fill( probe->eta(), 1.000 );
             TAG_L1_15_ptoM->Fill( probe->phi(), 1.000 );
             TAG_L1_15_nvtx->Fill( probe_nvtx, 1.000 );
         }
     if(probe->pt()>45)
         {
             TAG_L1_35_eta->Fill( probe->eta(), 1.000 );
             TAG_L1_35_ptoM->Fill( probe->phi(), 1.000 );
             TAG_L1_35_nvtx->Fill( probe_nvtx, 1.000 );
         }
     TAG_L1_10_pt->Fill( probe->pt(), 1.000 );
     TAG_L1_15_pt->Fill( probe->pt(), 1.000 );
     TAG_L1_35_pt->Fill( probe->pt(), 1.000 );

     bool flag_L1_probe10 = false;
     bool flag_L1_probe15 = false;
     bool flag_L1_probe35 = false;
     bool flag_L1_probe22 = false;

     if( L1Matching( l1iso, probe->p4(), 40 ) )
         {
             if(probe->pt()>45)
                 {
                     PROBE_L1_35_eta->Fill( probe->eta(), 1.000 );
                     PROBE_L1_35_ptoM->Fill( probe->phi(), 1.000 );
                     PROBE_L1_35_nvtx->Fill( probe_nvtx, 1.000 );
                     PROBE_L1_35_pt->Fill( probe->pt(), 1.000 );
                 }
             flag_L1_probe35 = true;
         }

     if( !flag_L1_probe35 && L1Matching( l1noniso, probe->p4(), 40 ) )
         {
             if(probe->pt()>45)
                 {
                     PROBE_L1_35_eta->Fill( probe->eta(), 1.000 );
                     PROBE_L1_35_ptoM->Fill( probe->phi(), 1.000 );
                     PROBE_L1_35_nvtx->Fill( probe_nvtx, 1.000 );
                     PROBE_L1_35_pt->Fill( probe->pt(), 1.000 );
                 }
             flag_L1_probe35 = true;
         }

     if( L1Matching( l1iso, probe->p4(), 22 ) )
         {
             flag_L1_probe22 = true;
         }

     if( !flag_L1_probe22 and L1Matching( l1noniso, probe->p4(), 22 ) )
         {
             flag_L1_probe22 = true;
         }

     if( L1Matching( l1iso, probe->p4(), 15 ) )
         {
             PROBE_L1_15_eta->Fill( probe->eta(), 1.000 );
             PROBE_L1_15_ptoM->Fill( probe->phi(), 1.000 );
             PROBE_L1_15_pt->Fill( probe->pt(), 1.000 );
             PROBE_L1_15_nvtx->Fill( probe_nvtx, 1.000 );
             flag_L1_probe15 = true;
         }

     if( !flag_L1_probe15 and L1Matching( l1noniso, probe->p4(), 15 ) )
         {
             PROBE_L1_15_eta->Fill( probe->eta(), 1.000 );
             PROBE_L1_15_ptoM->Fill( probe->phi(), 1.000 );
             PROBE_L1_15_pt->Fill( probe->pt(), 1.000 );
             PROBE_L1_15_nvtx->Fill( probe_nvtx, 1.000 );
             flag_L1_probe15 = true;
         }

     if( L1Matching( l1iso, probe->p4(), 10 ) )
         {
             PROBE_L1_10_eta->Fill( probe->eta(), 1.000 );
             PROBE_L1_10_ptoM->Fill( probe->phi(), 1.000 );
             PROBE_L1_10_pt->Fill( probe->pt(), 1.000 );
             PROBE_L1_10_nvtx->Fill( probe_nvtx, 1.000 );
             flag_L1_probe10 = true;
         }

     if( !flag_L1_probe10 and L1Matching( l1noniso, probe->p4(), 10 ) )
         {
             PROBE_L1_10_eta->Fill( probe->eta(), 1.000 );
             PROBE_L1_10_ptoM->Fill( probe->phi(), 1.000 );
             PROBE_L1_10_pt->Fill( probe->pt(), 1.000 );
             PROBE_L1_10_nvtx->Fill( probe_nvtx, 1.000 );
             flag_L1_probe10 = true;
         }

     if( tag->pt()>30. && probe->pt()>20.)
         //    if(probe->pt()>25.0) //minimum scaling pT cut
         {
             TAG_HLT_pt_unseeded->Fill( probe->pt(), 1.000 );
             TAG_HLT_pt_seeded->Fill( tag->pt(), 1.000 );
             
             if(probe->pt()>25.0&&tag->pt()>33.3333)
                 {
                     TAG_HLT_eta_unseeded->Fill( probe->eta(), 1.000 );
                     TAG_HLT_ptoM_unseeded->Fill( probe->phi(), 1.000 );
                     TAG_HLT_nvtx_unseeded->Fill( probe_nvtx, 1.000 );
                     TAG_HLT_eta_seeded->Fill( tag->eta(), 1.000 );
                     TAG_HLT_ptoM_seeded->Fill( tag->phi(), 1.000 );
                     TAG_HLT_nvtx_seeded->Fill( probe_nvtx, 1.000 );
                     Zpeak[1][0]->Fill( theDiPhoton->mass(), 1.000 ); //fill unseeded all zpeak plot
                 }
             bool subflag = 0;
             bool leadflag = 0;
             //sublead HLT only                                                                                                     
             
             if( onlineOfflineMatching( triggerNames, triggerObjects, probe->p4(), filterName_[2] ) ||
                 onlineOfflineMatching( triggerNames, triggerObjects, probe->p4(), filterName_[3] ) )
                 {
                     subflag = 1;
                     PROBE_HLT_R9_pt_unseeded->Fill( probe->pt(), 1.000 );
                     PROBE_HLT_R9_pt_seeded->Fill( tag->pt(), 1.000 );
                     
                     if(probe->pt()>25.0 && tag->pt()>33.3333)
                         {
                             PROBE_HLT_R9_eta_unseeded->Fill( probe->eta(), 1.000 );
                             PROBE_HLT_R9_ptoM_unseeded->Fill( probe->phi(), 1.000 );
                             PROBE_HLT_R9_nvtx_unseeded->Fill( probe_nvtx, 1.000 );
                             PROBE_HLT_R9_eta_seeded->Fill( tag->eta(), 1.000 );
                             PROBE_HLT_R9_ptoM_seeded->Fill( tag->phi(), 1.000 );
                             PROBE_HLT_R9_nvtx_seeded->Fill( probe_nvtx, 1.000 );
                         }
                 }
             
             if( onlineOfflineMatching( triggerNames, triggerObjects, tag->p4(), filterName_[0] )||
                 onlineOfflineMatching( triggerNames, triggerObjects, tag->p4(), filterName_[1] )) 
                 {
                     subflag = 1;
                     PROBE_HLT_Iso_pt_unseeded->Fill( probe->pt(), 1.000 );
                     PROBE_HLT_Iso_pt_seeded->Fill( tag->pt(), 1.000 );
                     if(probe->pt()>25.0 && tag->pt()>33.333)
                         {                     
                             PROBE_HLT_Iso_eta_unseeded->Fill( probe->eta(), 1.000 );
                             PROBE_HLT_Iso_ptoM_unseeded->Fill( probe->phi(), 1.000 );
                             PROBE_HLT_Iso_nvtx_unseeded->Fill( probe_nvtx, 1.000 );
                             PROBE_HLT_Iso_eta_unseeded->Fill( tag->eta(), 1.000 );
                             PROBE_HLT_Iso_ptoM_unseeded->Fill( tag->phi(), 1.000 );
                             PROBE_HLT_Iso_nvtx_unseeded->Fill( probe_nvtx, 1.000 );
                         }
                 }
             if( leadflag or subflag ) 
                 {
                     PROBE_HLT_OR_pt_unseeded->Fill( probe->pt(), 1.000 );
                     PROBE_HLT_OR_pt_seeded->Fill( tag->pt(), 1.000 );
                     
                     if(probe->pt()>25.0 && tag->pt()>33.333)
                         {
                             PROBE_HLT_OR_eta_unseeded->Fill( probe->eta(), 1.000 );
                             PROBE_HLT_OR_ptoM_unseeded->Fill( probe->phi(), 1.000 );
                             PROBE_HLT_OR_nvtx_unseeded->Fill( probe_nvtx, 1.000 );
                             PROBE_HLT_OR_eta_unseeded->Fill( tag->eta(), 1.000 );
                             PROBE_HLT_OR_ptoM_unseeded->Fill( tag->phi(), 1.000 );
                             PROBE_HLT_OR_nvtx_unseeded->Fill( probe_nvtx, 1.000 );
                             Zpeak[1][1]->Fill( theDiPhoton->mass(), 1.000 ); //fill unseeded pass zpeak plot 
                             //Zpeak[getPtBin(probe->pt())][1]->Fill( theDiPhoton->mass(), 1.000 ); //fill unseeded pass zpeak plot
                         }
                 }
             else
                 {
                     if(probe->pt()>25.0&& tag->pt()>33.333)
                         Zpeak[1][2]->Fill( theDiPhoton->mass(), 1.000 ); //fill unseeded fail zpeak plot                              //Zpeak[getPtBin(probe->pt())][2]->Fill( theDiPhoton->mass(), 1.000 ); //fill seeded fail zpeak plot  
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
}

DEFINE_FWK_MODULE( HLTtest );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

