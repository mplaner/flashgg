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

#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "flashgg/DataFormats/interface/GenPhotonExtra.h"
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

class r9Weights : public edm::EDAnalyzer
{
public:
    explicit r9Weights( const edm::ParameterSet & );
    ~r9Weights();
private:
    virtual void analyze( const edm::Event &, const edm::EventSetup & ) override;

    std::string outputFileName_;
    float diphoMVACut_;
    int count;
    TH1F *lead_pT;
    TH1F *sublead_pT;
    TH1F *lead_r9;
    TH1F *sublead_r9;
    TH2F *eta_r9;
    TH2F *eta_r9_norm;
    TH2F *eta_r9_std;
    TGraph * eta_r9_scat;
    TH1F *eta;
    TH1F *eta_bins;
    TH1F *normalized_eta;
    edm::EDGetTokenT<edm::View<flashgg::DiPhotonCandidate>> diphotons_;
    edm::EDGetTokenT<edm::View<flashgg::DiPhotonMVAResult> > diPhotonMVAToken_;
    edm::EDGetTokenT<edm::View<flashgg::Electron>> eles_;
    edm::EDGetTokenT<edm::View<reco::GenParticle>> genphotons_;
};

r9Weights::~r9Weights()
{

    TFile *file = new TFile( outputFileName_.c_str(), "recreate" );

    lead_pT->Write();
    sublead_pT->Write();
    lead_r9->Write();
    sublead_r9->Write();
    eta_r9->Write();
    eta_r9_norm->Write();
    eta_r9_std->Write();
    eta_r9_scat->Write();
    eta->Write();
    eta_bins->Write();
    normalized_eta->Write();
    file->Close();
}

r9Weights::r9Weights( const edm::ParameterSet &iConfig ):
    outputFileName_( iConfig.getParameter<std::string>( "outputFileName" ) ),
    diphoMVACut_( iConfig.getParameter<double>( "diphoMVACut" ) ),
    diphotons_( consumes<edm::View<flashgg::DiPhotonCandidate>>( iConfig.getParameter<edm::InputTag>( "diphotons" ) ) ),
    diPhotonMVAToken_( consumes<edm::View<flashgg::DiPhotonMVAResult> >( iConfig.getParameter<edm::InputTag> ( "diPhotonMVATag" ) ) ),
    eles_( consumes<edm::View<flashgg::Electron>>( iConfig.getParameter<edm::InputTag>( "electrons" ) ) ),
    genphotons_( consumes<edm::View<reco::GenParticle>>( iConfig.getParameter<edm::InputTag>( "genphotons" ) ) )
{
    ////////// bins /////////////////
    const double x[26] = {0.0, 0.5, 0.55, 0.60, 0.65, 0.7, 0.74, 0.76, 0.78, 0.80, 0.82, 0.84, 0.86, 0.88, 0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.0, 2.0};
    const double y[9] = {0.0, 0.8, 1.0, 1.2, 1.3, 1.444, 1.566,  2.0,  2.5};
    //const double yWidth[8]=  {0.8, 0.2, 0.2, 0.1, 0.144, 0.122, 0.433, 0.5};
    ///////////// initialize plots ///////////////////
    eta_r9 = new TH2F( "eta_vs_r9", "", 25, x, 8, y );
    eta_r9_norm = new TH2F( "eta_vs_r9_norm", "", 25, x, 8, y );
    lead_pT = new TH1F( "lead_pt", "", 100, 0, 100 );
    sublead_pT = new TH1F( "sublead_pt", "", 100, 0, 100 );
    lead_r9 = new TH1F( "lead_r9", "", 25, x );
    sublead_r9 = new TH1F( "sublead_r9", "", 25, x );
    eta_r9_std = new TH2F( "eta_vs_r9_std", "", 120, 0, 1.2, 25, 0, 2.5);
    normalized_eta = new TH1F( "eta_normalized_bin_width", "", 8, y);
    eta = new TH1F( "eta", "", 25,0,2.5);
    eta_bins = new TH1F( "eta_distribution", "", 8, y);
    eta_r9_scat = new TGraph();
    count=0;
}


//            float dR = deltaR( p4, obj.p4() );
//           if( dR < dRmin )

void r9Weights::analyze( const edm::Event &iEvent, const edm::EventSetup &iSetup )
{

    edm::Handle<edm::View<flashgg::DiPhotonCandidate>> diphotons;
    edm::Handle<edm::View<flashgg::DiPhotonMVAResult> > mvaResults;
    edm::Handle<edm::View<flashgg::Electron>> eles;
    edm::Handle<edm::View<reco::GenParticle>> genPhotons;

    iEvent.getByToken( diphotons_, diphotons );
    iEvent.getByToken(diPhotonMVAToken_, mvaResults);
    iEvent.getByToken( eles_, eles );
    iEvent.getByToken( genphotons_, genPhotons );
    if( eles.failedToGet() )
    { return; }

    int diphotonIndex = -1;
    for( size_t i = 0; i < diphotons->size(); i++ ) {
        double minDr[2] = {0.15, 0.15};
        edm::Ptr<flashgg::DiPhotonCandidate> diphoPtr = diphotons->ptrAt( i );
        edm::Ptr<flashgg::DiPhotonMVAResult> mvares = mvaResults->ptrAt( i );
        if( mvares->mvaValue() < diphoMVACut_ )
            { continue; }

        for( size_t f = 0; f < genPhotons->size(); f++ ) {
            edm::Ptr<reco::GenParticle> genphoPtr = genPhotons->ptrAt( f );
            if( minDr[0] < deltaR( diphoPtr->leadingPhoton()->p4(), genphoPtr->p4() ) ) {
                minDr[0] = deltaR( diphoPtr->leadingPhoton()->p4(), genphoPtr->p4() );
            }

            if( minDr[1] < deltaR( diphoPtr->subLeadingPhoton()->p4(), genphoPtr->p4() ) ) {
                minDr[1] = deltaR( diphoPtr->subLeadingPhoton()->p4(), genphoPtr->p4() );
            }
        }
        if( minDr[0] != 0.15 && minDr[1] != 0.15 )
        { diphotonIndex = i; }
    }

    if( diphotonIndex == -1 )
        { return; }
    
    edm::Ptr<flashgg::DiPhotonCandidate> theDiPhoton = diphotons->ptrAt( diphotonIndex );
    const flashgg::Photon *tag = theDiPhoton->leadingPhoton();
    const flashgg::Photon *probe = theDiPhoton->subLeadingPhoton();
    
    ///////apply cuts here/////// 
    const flashgg::SinglePhotonView leading = *(theDiPhoton->leadingView());
    const flashgg::SinglePhotonView subLeading = *(theDiPhoton->subLeadingView());
    if(leading.phoIdMvaWrtChosenVtx()<-0.8||subLeading.phoIdMvaWrtChosenVtx()<-0.8)
        return;
    if(tag->pt()<30||probe->pt()<20) //preselection pT cut applied again                           
        

    //////// fill distributions //////////////
    lead_pT->Fill( tag->pt() );
    sublead_pT->Fill( probe->pt() );
    lead_r9->Fill( tag->full5x5_r9() );
    sublead_r9->Fill( probe->full5x5_r9() );

    ///////// calculate weights based on bin area////////////
    double tag_weight = 1.0 / (eta_r9->GetXaxis()->GetBinWidth(eta_r9->GetXaxis()->FindBin(tag->full5x5_r9())) * eta_r9->GetYaxis()->GetBinWidth(eta_r9->GetYaxis()->FindBin(fabs(tag->eta()))));
    double probe_weight = 1.0 / (eta_r9->GetXaxis()->GetBinWidth(eta_r9->GetXaxis()->FindBin(probe->full5x5_r9())) * eta_r9->GetYaxis()->GetBinWidth(eta_r9->GetYaxis()->FindBin(fabs(probe->eta()))));
    /////////calculate weights based on bin width (eta) ////////////
    double tag_eta_weight = 1.0 / (eta_bins->GetXaxis()->GetBinWidth(eta_bins->GetXaxis()->FindBin(fabs(tag->eta()))));
    double probe_eta_weight = 1.0 / (eta_bins->GetXaxis()->GetBinWidth(eta_bins->GetXaxis()->FindBin(fabs(probe->eta()))));
    ///////////////eta vs r9 2d ///////////////////
    eta_r9->Fill( tag->full5x5_r9(), fabs( tag->eta() ));
    eta_r9->Fill( probe->full5x5_r9(), fabs( probe->eta() ));
    
    eta_r9_norm->Fill( tag->full5x5_r9(), fabs( tag->eta() ), tag_weight );
    eta_r9_norm->Fill( probe->full5x5_r9(), fabs( probe->eta() ), probe_weight );
    
    eta_r9_std->Fill( tag->full5x5_r9(), fabs( tag->eta() ) );
    eta_r9_std->Fill( probe->full5x5_r9(), fabs( probe->eta() ) );
    //////////scatter plot/////////////
    eta_r9_scat->SetPoint(count, tag->full5x5_r9(), fabs(tag->eta()));
    count++;
    eta_r9_scat->SetPoint(count, probe->full5x5_r9(), fabs(probe->eta()));
    /////////eta distributions///////////////
    normalized_eta->Fill(fabs( tag->eta()), tag_eta_weight);
    normalized_eta->Fill(fabs( probe->eta()), probe_eta_weight);
    eta->Fill(fabs( tag->eta()));
    eta->Fill(fabs( probe->eta()));
    eta_bins->Fill(fabs( tag->eta()));
    eta_bins->Fill(fabs( probe->eta()));
    
    
    count++;
    
}
DEFINE_FWK_MODULE( r9Weights );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

