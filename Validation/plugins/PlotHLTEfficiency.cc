// user include files
#include "TFile.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "../test/tdrstyle.C"
#include <string>

class HLTPlotter
{
public:
    HLTPlotter( std::string fname );
    ~HLTPlotter();
    void makePlots();
    void writeEfficiencies();
    void makeEfficiencies();
    void formatCanvas(TCanvas *can);
    TGraphAsymmErrors * formatTGraph(TGraphAsymmErrors *graph, std::string xTitle, std::string yTitle, int color);
    TH1F *TAG_L1_10_eta;
    TH1F *TAG_L1_15_eta;
    TH1F *TAG_L1_35_eta;
    TH1F *PROBE_L1_15_eta;
    TH1F *PROBE_L1_10_eta;
    TH1F *PROBE_L1_35_eta;
    TH1F *TAG_L1_10_pt;    
    TH1F *TAG_L1_15_pt;
    TH1F *TAG_L1_35_pt;
    TH1F *PROBE_L1_15_pt;
    TH1F *PROBE_L1_10_pt;
    TH1F *PROBE_L1_35_pt;
    TH1F *TAG_L1_10_ptoM;
    TH1F *TAG_L1_15_ptoM;
    TH1F *TAG_L1_35_ptoM;
    TH1F *PROBE_L1_15_ptoM;
    TH1F *PROBE_L1_10_ptoM;
    TH1F *PROBE_L1_35_ptoM;
    TH1F *TAG_L1_10_nvtx;
    TH1F *TAG_L1_15_nvtx;
    TH1F *TAG_L1_35_nvtx;
    TH1F *PROBE_L1_15_nvtx;
    TH1F *PROBE_L1_10_nvtx;
    TH1F *PROBE_L1_35_nvtx;
    TH1F *Zpeak;

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

private:
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

HLTPlotter::~HLTPlotter()
{

    TFile *file = new TFile( "tempoutput.root", "recreate" );

    c_eff_HLT_OR_pt_seeded->Write();
    c_eff_HLT_OR_pt_unseeded->Write();
    c_eff_L1_7_pt->Write();

    //    c_eff_HLT_OR_ptoM_seeded->Write();
    //c_eff_HLT_OR_ptoM_unseeded->Write();
    //c_eff_L1_7_ptoM->Write();

    c_eff_HLT_OR_eta_seeded->Write();
    c_eff_HLT_OR_eta_unseeded->Write();
    c_eff_L1_7_eta->Write();

    c_eff_HLT_OR_nvtx_seeded->Write();
    c_eff_HLT_OR_nvtx_unseeded->Write();
    c_eff_L1_7_nvtx->Write();

    eff_HLT_OR_pt_seeded->Write();
    eff_HLT_Iso_pt_seeded->Write();
    eff_HLT_R9_pt_seeded->Write();

    eff_HLT_OR_pt_unseeded->Write();
    eff_HLT_Iso_pt_unseeded->Write();
    eff_HLT_R9_pt_unseeded->Write();

    Zpeak->Write();
    TAG_L1_35_eta->Write();
    TAG_L1_15_eta->Write();
    TAG_L1_10_eta->Write();
    PROBE_L1_35_eta->Write();
    PROBE_L1_15_eta->Write();
    PROBE_L1_10_eta->Write();
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
    PROBE_HLT_OR_nvtx_seeded->Write();
    PROBE_HLT_Iso_nvtx_seeded->Write();
    PROBE_HLT_R9_nvtx_seeded->Write();
    TAG_HLT_pt_seeded->Write();
    TAG_HLT_eta_seeded->Write();
    TAG_HLT_nvtx_seeded->Write();

    PROBE_HLT_OR_pt_unseeded->Write();
    PROBE_HLT_Iso_pt_unseeded->Write();
    PROBE_HLT_R9_pt_unseeded->Write();
    PROBE_HLT_OR_eta_unseeded->Write();
    PROBE_HLT_Iso_eta_unseeded->Write();
    PROBE_HLT_R9_eta_unseeded->Write();
    PROBE_HLT_OR_nvtx_unseeded->Write();
    PROBE_HLT_Iso_nvtx_unseeded->Write();
    PROBE_HLT_R9_nvtx_unseeded->Write();
    TAG_HLT_pt_unseeded->Write();
    TAG_HLT_eta_unseeded->Write();
    TAG_HLT_nvtx_unseeded->Write();
    file->Close();
}

HLTPlotter::HLTPlotter( std::string fname )
{
    //    TFile * inputFile = new TFile("output_DoubleEG.root");
    TFile *inputFile = new TFile( fname.c_str() );

    //int etaBin = 30;
    //int nvtxBin = 50;
    //int ptBin = 30;
    Zpeak = ( TH1F * )inputFile->Get( "Zpeak" );
    TAG_L1_35_eta = ( TH1F * )inputFile->Get( "DEN_L1_35_eta" );
    TAG_L1_15_eta = ( TH1F * )inputFile->Get( "DEN_L1_15_eta" );
    TAG_L1_10_eta = ( TH1F * )inputFile->Get( "DEN_L1_10_eta" );
    PROBE_L1_35_eta = ( TH1F * )inputFile->Get( "PROBE_L1_35_eta" );
    PROBE_L1_15_eta = ( TH1F * )inputFile->Get( "PROBE_L1_15_eta" );
    PROBE_L1_10_eta = ( TH1F * )inputFile->Get( "PROBE_L1_10_eta" );
    TAG_L1_35_pt = ( TH1F * )inputFile->Get( "DEN_L1_35_pt" );
    TAG_L1_15_pt = ( TH1F * )inputFile->Get( "DEN_L1_15_pt" );
    TAG_L1_10_pt = ( TH1F * )inputFile->Get( "DEN_L1_10_pt" );
    PROBE_L1_15_pt = ( TH1F * )inputFile->Get( "PROBE_L1_15_pt" );
    PROBE_L1_10_pt = ( TH1F * )inputFile->Get( "PROBE_L1_10_pt" );
    PROBE_L1_35_pt = ( TH1F * )inputFile->Get( "PROBE_L1_35_pt" );
    TAG_L1_35_ptoM = ( TH1F * )inputFile->Get( "DEN_L1_35_ptoM" );
    TAG_L1_15_ptoM = ( TH1F * )inputFile->Get( "DEN_L1_15_ptoM" );
    TAG_L1_10_ptoM = ( TH1F * )inputFile->Get( "DEN_L1_10_ptoM" );
    PROBE_L1_15_ptoM = ( TH1F * )inputFile->Get( "PROBE_L1_15_ptoM" );
    PROBE_L1_10_ptoM = ( TH1F * )inputFile->Get( "PROBE_L1_10_ptoM" );
    PROBE_L1_35_ptoM = ( TH1F * )inputFile->Get( "PROBE_L1_35_ptoM" );
    TAG_L1_35_nvtx = ( TH1F * )inputFile->Get( "DEN_L1_35_nvtx" );
    TAG_L1_15_nvtx = ( TH1F * )inputFile->Get( "DEN_L1_15_nvtx" );
    TAG_L1_10_nvtx = ( TH1F * )inputFile->Get( "DEN_L1_10_nvtx" );
    PROBE_L1_35_nvtx = ( TH1F * )inputFile->Get( "PROBE_L1_35_nvtx" );
    PROBE_L1_15_nvtx = ( TH1F * )inputFile->Get( "PROBE_L1_15_nvtx" );
    PROBE_L1_10_nvtx = ( TH1F * )inputFile->Get( "PROBE_L1_10_nvtx" );

    PROBE_HLT_OR_pt_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_pt_unseeded" );
    PROBE_HLT_Iso_pt_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_pt_unseeded" );
    PROBE_HLT_R9_pt_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_pt_unseeded" );
    PROBE_HLT_OR_ptoM_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_ptoM_unseeded" );
    PROBE_HLT_Iso_ptoM_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_ptoM_unseeded" );
    PROBE_HLT_R9_ptoM_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_ptoM_unseeded" );
    PROBE_HLT_OR_eta_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_eta_unseeded" );
    PROBE_HLT_Iso_eta_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_eta_unseeded" );
    PROBE_HLT_R9_eta_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_eta_unseeded" );
    PROBE_HLT_OR_nvtx_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_nvtx_unseeded" );
    PROBE_HLT_Iso_nvtx_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_nvtx_unseeded" );
    PROBE_HLT_R9_nvtx_unseeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_nvtx_unseeded" );
    TAG_HLT_eta_unseeded = ( TH1F * )inputFile->Get( "DEN_HLT_eta_unseeded" );
    TAG_HLT_pt_unseeded = ( TH1F * )inputFile->Get( "DEN_HLT_pt_unseeded" );
    TAG_HLT_ptoM_unseeded = ( TH1F * )inputFile->Get( "DEN_HLT_ptoM_unseeded" );
    TAG_HLT_nvtx_unseeded = ( TH1F * )inputFile->Get( "DEN_HLT_nvtx_unseeded" );


    PROBE_HLT_OR_pt_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_pt_seeded" );
    PROBE_HLT_Iso_pt_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_pt_seeded" );
    PROBE_HLT_R9_pt_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_pt_seeded" );
    PROBE_HLT_OR_ptoM_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_ptoM_seeded" );
    PROBE_HLT_Iso_ptoM_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_ptoM_seeded" );
    PROBE_HLT_R9_ptoM_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_ptoM_seeded" );
    PROBE_HLT_OR_eta_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_eta_seeded" );
    PROBE_HLT_Iso_eta_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_eta_seeded" );
    PROBE_HLT_R9_eta_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_eta_seeded" );
    PROBE_HLT_OR_nvtx_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_OR_nvtx_seeded" );
    PROBE_HLT_Iso_nvtx_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_ISO_nvtx_seeded" );
    PROBE_HLT_R9_nvtx_seeded = ( TH1F * )inputFile->Get( "PROBE_HLT_R9_nvtx_seeded" );
    TAG_HLT_pt_seeded = ( TH1F * )inputFile->Get( "DEN_HLT_pt_seeded" );
    TAG_HLT_ptoM_seeded = ( TH1F * )inputFile->Get( "DEN_HLT_ptoM_seeded" );
    TAG_HLT_eta_seeded = ( TH1F * )inputFile->Get( "DEN_HLT_eta_seeded" );
    TAG_HLT_nvtx_seeded = ( TH1F * )inputFile->Get( "DEN_HLT_nvtx_seeded" );
}

void HLTPlotter::makePlots()
{
    c_eff_L1_7_pt->cd();
    eff_L1_10_pt->Divide( PROBE_L1_10_pt, TAG_L1_10_pt, "b(1,1) mode" );
    formatTGraph(eff_L1_10_pt, "p_{T} (GeV)", "L1 trigger efficiency", 2);    
    eff_L1_10_pt->GetYaxis()->SetRangeUser(0.6,1.05);
    eff_L1_10_pt->GetXaxis()->SetRangeUser(0,250);
    eff_L1_10_pt->Draw( "AP" );
    
    //    eff_L1_15_pt->Divide( PROBE_L1_15_pt, TAG_L1_15_pt, "b(1,1) mode" );
    //formatTGraph(eff_L1_15_pt, "p_{T} (GeV)", "L1 Efficiency", 2);    
    //eff_L1_15_pt->Draw( "SAMEP" );

    eff_L1_15_pt->Divide( PROBE_L1_35_pt, TAG_L1_35_pt, "b(1,1) mode" );
    formatTGraph(eff_L1_15_pt, "p_{T} (GeV)", "L1 trigger efficiency", 1);    
    eff_L1_15_pt->Draw( "SAMEP" );
    
    formatCanvas(c_eff_L1_7_pt);

    TLegend *l_eff_L1_7_pt = new TLegend( 0.40, 0.20, 0.87, 0.37 );
    l_eff_L1_7_pt->SetShadowColor( 0 );
    l_eff_L1_7_pt->SetTextFont( 42 );
    l_eff_L1_7_pt->SetFillColor( 0 );
    l_eff_L1_7_pt->SetLineColor( 0 );
    l_eff_L1_7_pt->SetTextSize( 0.03 );
    l_eff_L1_7_pt->AddEntry( eff_L1_10_pt, " L1 single EG, E_{T} > 10 GeV", "l" );
    //l_eff_L1_7_pt->AddEntry( eff_L1_15_pt, "L1_EG15", "l" );
    l_eff_L1_7_pt->AddEntry( eff_L1_15_pt, " L1 single EG, E_{T} > 22 GeV", "l" );
    l_eff_L1_7_pt->SetTextSize( 0.05 );
    l_eff_L1_7_pt->Draw();

    c_eff_HLT_OR_pt_seeded->cd();

    //PROBE_HLT_OR_pt_seeded->SetBinContent(13,PROBE_HLT_OR_pt_seeded->GetBinContent(13)-33); //bugfix, overflow bin was incremented.
    //PROBE_HLT_OR_pt_seeded->SetBinContent(12,PROBE_HLT_OR_pt_seeded->GetBinContent(12)-46); //bugfix, overflow bin was incremented.
    eff_HLT_OR_pt_unseeded->Divide( PROBE_HLT_OR_pt_unseeded, TAG_HLT_pt_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_pt_unseeded, "p_{T} (GeV)", "HLT-Only Efficiency", 2);    
    eff_HLT_OR_pt_seeded->Divide( PROBE_HLT_OR_pt_seeded, TAG_HLT_pt_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_pt_seeded, "p_{T} (GeV)", "HLT-Only Efficiency", 1);    
    eff_HLT_OR_pt_unseeded->GetYaxis()->SetRangeUser(0.7,1.05);
    eff_HLT_OR_pt_unseeded->GetXaxis()->SetRangeUser(0,250);
    eff_HLT_OR_pt_unseeded->Draw( "AP" );
    eff_HLT_OR_pt_seeded->Draw( "SAMEP" );
    
    formatCanvas(c_eff_HLT_OR_pt_seeded);
    
    TLegend *l_eff_HLT_OR_pt_seeded = new TLegend( 0.37, 0.20, 0.94, 0.37 );
    l_eff_HLT_OR_pt_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_pt_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_pt_seeded->SetTextFont( 42 );
    l_eff_HLT_OR_pt_seeded->SetLineColor( 0 );
    l_eff_HLT_OR_pt_seeded->SetTextSize( 0.05 );
    l_eff_HLT_OR_pt_seeded->AddEntry( eff_HLT_OR_pt_seeded, "HLT leading p_{T} photon", "l" );
    l_eff_HLT_OR_pt_seeded->AddEntry( eff_HLT_OR_pt_unseeded, "HLT sub-leading p_{T} photon ", "l" );
    l_eff_HLT_OR_pt_seeded->SetTextSize( 0.05 );
    l_eff_HLT_OR_pt_seeded->Draw();

    
    
    c_eff_HLT_OR_eta_seeded->cd();
    eff_HLT_OR_eta_unseeded->Divide( PROBE_HLT_OR_eta_unseeded, TAG_HLT_eta_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_eta_unseeded, "#eta", "HLT-only efficiency", 2);    
    eff_HLT_OR_eta_seeded->Divide( PROBE_HLT_OR_eta_seeded, TAG_HLT_eta_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_eta_seeded, "#eta", "HLT-only efficiency", 1);    
    eff_HLT_OR_eta_unseeded->GetYaxis()->SetRangeUser(0.95,1.02);
    eff_HLT_OR_eta_unseeded->Draw( "AP" );
    eff_HLT_OR_eta_seeded->Draw( "SAMEP" );

    formatCanvas(c_eff_HLT_OR_eta_seeded);
    
    TLegend *l_eff_HLT_OR_eta_seeded = new TLegend( 0.37, 0.20, 0.94, 0.37 );
    l_eff_HLT_OR_eta_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_eta_seeded->SetTextFont( 42 );
    l_eff_HLT_OR_eta_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_eta_seeded->SetLineColor( 0 );
    l_eff_HLT_OR_eta_seeded->SetTextSize( 0.05 );
    l_eff_HLT_OR_eta_seeded->AddEntry( eff_HLT_OR_eta_seeded, "HLT leading p_{T} photon", "l" );
    l_eff_HLT_OR_eta_seeded->AddEntry( eff_HLT_OR_eta_unseeded, "HLT sub-leading p_{T} photon", "l" );
    l_eff_HLT_OR_eta_seeded->SetTextSize( 0.05 );
    l_eff_HLT_OR_eta_seeded->Draw();


    
    c_eff_HLT_OR_nvtx_seeded->cd();
    eff_HLT_OR_nvtx_seeded->Divide( PROBE_HLT_OR_nvtx_seeded, TAG_HLT_nvtx_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_nvtx_seeded, "number of reconstructed vertices", "HLT-only efficiency", 1);
    eff_HLT_OR_nvtx_unseeded->Divide( PROBE_HLT_OR_nvtx_unseeded, TAG_HLT_nvtx_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_nvtx_unseeded, "number of reconstructed vertices", "HLT-only efficiency", 2);
    eff_HLT_OR_nvtx_unseeded->GetYaxis()->SetRangeUser(0.95,1.02);
    //eff_HLT_OR_nvtx_unseeded->GetXaxis()->SetRangeUser(0,22);
    eff_HLT_OR_nvtx_unseeded->GetXaxis()->SetRangeUser(2,22);
    eff_HLT_OR_nvtx_unseeded->Draw( "AP" );
    eff_HLT_OR_nvtx_seeded->Draw( "SAMEP" );
    
    formatCanvas(c_eff_HLT_OR_nvtx_seeded);

    TLegend *l_eff_HLT_OR_nvtx_seeded = new TLegend( 0.37, 0.20, 0.94, 0.37 );
    l_eff_HLT_OR_nvtx_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_nvtx_seeded->SetLineColor( 0 );
    l_eff_HLT_OR_nvtx_seeded->SetTextFont( 42 );
    l_eff_HLT_OR_nvtx_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_nvtx_seeded->SetTextSize( 0.05 );
    l_eff_HLT_OR_nvtx_seeded->AddEntry( eff_HLT_OR_nvtx_seeded, "HLT leading p_{T} photon", "l" );
    l_eff_HLT_OR_nvtx_seeded->AddEntry( eff_HLT_OR_nvtx_unseeded, "HLT sub-leading p_{T} photon", "l" );
    l_eff_HLT_OR_nvtx_seeded->SetTextSize( 0.05 );
    l_eff_HLT_OR_nvtx_seeded->Draw();



}

void HLTPlotter::makeEfficiencies()
{

    //string sample = "RelVal z->ee, #sqrt{s} = 13 TeV";
    //const char *sample = "2015D ReMiniAOD V7, #sqrt{s} = 13 TeV";
    //const char *sample = "2015D ReMiniAOD V7, (13 TeV)";
    //const char *sample = "2015B (Golden JSON), #sqrt{s} = 13 TeV";
    c_eff_L1_7_pt->cd();
    eff_L1_10_pt->Divide( PROBE_L1_10_pt, TAG_L1_10_pt, "b(1,1) mode" );
    formatTGraph(eff_L1_10_pt, "p_{T} (GeV)", "L1 Efficiency", 2);    
    eff_L1_10_pt->Draw( "AP" );
    
    eff_L1_15_pt->Divide( PROBE_L1_15_pt, TAG_L1_15_pt, "b(1,1) mode" );
    formatTGraph(eff_L1_15_pt, "p_{T} (GeV)", "L1 Efficiency", 4);    
    eff_L1_15_pt->Draw( "SAMEP" );
    /*
    eff_L1_35_pt->Divide( PROBE_L1_35_pt, TAG_L1_35_pt, "b(1,1) mode" );
    eff_L1_35_pt->SetMinimum( 0.0 );
    eff_L1_35_pt->SetMaximum( 1.1 );
    eff_L1_35_pt->SetLineColor( 6 );
    eff_L1_35_pt->SetMarkerColor( 6 );
    eff_L1_35_pt->SetLineWidth( 2 );
    eff_L1_35_pt->SetMarkerStyle( 7 );
    eff_L1_35_pt->Draw( "SAMEP" );
    */
    formatCanvas(c_eff_L1_7_pt);

    TLegend *l_eff_L1_7_pt = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_L1_7_pt->SetShadowColor( 0 );
    l_eff_L1_7_pt->SetFillColor( 0 );
    l_eff_L1_7_pt->SetLineColor( 1 );
    l_eff_L1_7_pt->SetTextSize( 0.03 );
    l_eff_L1_7_pt->AddEntry( eff_L1_10_pt, "L1_EG10", "l" );
    l_eff_L1_7_pt->AddEntry( eff_L1_15_pt, "L1_EG15", "l" );
    //l_eff_L1_7_pt->AddEntry( eff_L1_35_pt, "L1_EG40", "l" );
    l_eff_L1_7_pt->SetTextSize( 0.03 );
    l_eff_L1_7_pt->Draw();

    //HLT seeded pt efficiencies
    c_eff_HLT_OR_pt_seeded->cd();
    //12 den  2322.18num: 2335.63
    //den 13: 852.533num: 867.788
    PROBE_HLT_OR_pt_seeded->SetBinContent(13,PROBE_HLT_OR_pt_seeded->GetBinContent(13)-30); //bugfix, overflow bin was incremented.
    PROBE_HLT_OR_pt_seeded->SetBinContent(12,PROBE_HLT_OR_pt_seeded->GetBinContent(12)-20); //bugfix, overflow bin was incremented.
    eff_HLT_OR_pt_seeded->Divide( PROBE_HLT_OR_pt_seeded, TAG_HLT_pt_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_pt_seeded, "p_{T} (GeV)", "HLT-Only Efficiency", 1);    
    eff_HLT_OR_pt_seeded->Draw( "AP" );

    eff_HLT_Iso_pt_seeded->Divide( PROBE_HLT_Iso_pt_seeded, TAG_HLT_pt_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_Iso_pt_seeded, "p_{T} (GeV)", "HLT-Only Efficiency", 2);    
    eff_HLT_Iso_pt_seeded->Draw( "SAMEP" );
    
    eff_HLT_R9_pt_seeded->Divide( PROBE_HLT_R9_pt_seeded, TAG_HLT_pt_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_R9_pt_seeded, "p_{T} (GeV)", "HLT-Only Efficiency", 4);    
    eff_HLT_R9_pt_seeded->Draw( "SAMEP" );
    formatCanvas(c_eff_HLT_OR_pt_seeded);
    
    TLegend *l_eff_HLT_OR_pt_seeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_pt_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_pt_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_pt_seeded->SetLineColor( 1 );
    l_eff_HLT_OR_pt_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_pt_seeded->AddEntry( eff_HLT_OR_pt_seeded, "HLT_Photon30_Iso60CaloId_OR_R9Id", "l" );
    l_eff_HLT_OR_pt_seeded->AddEntry( eff_HLT_Iso_pt_seeded, "HLT_Photon30_Iso60CaloId", "l" );
    l_eff_HLT_OR_pt_seeded->AddEntry( eff_HLT_R9_pt_seeded, "HLT_Photon30_R9Id", "l" );
    l_eff_HLT_OR_pt_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_pt_seeded->Draw();

    //HLT unseeded pt efficiencies
    c_eff_HLT_OR_pt_unseeded->cd();
    eff_HLT_OR_pt_unseeded->Divide( PROBE_HLT_OR_pt_unseeded, TAG_HLT_pt_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_pt_unseeded, "p_{T} (GeV)", "HLT-Only Efficiency", 1);    
    eff_HLT_OR_pt_unseeded->Draw( "AP" );

    eff_HLT_Iso_pt_unseeded->Divide( PROBE_HLT_Iso_pt_unseeded, TAG_HLT_pt_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_Iso_pt_unseeded, "p_{T} (GeV)", "HLT-Only Efficiency", 2);    
    eff_HLT_Iso_pt_unseeded->Draw( "SAMEP" );
    
    eff_HLT_R9_pt_unseeded->Divide( PROBE_HLT_R9_pt_unseeded, TAG_HLT_pt_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_R9_pt_unseeded, "p_{T} (GeV)", "HLT-Only Efficiency", 4);    
    eff_HLT_R9_pt_unseeded->Draw( "SAMEP" );
    formatCanvas(c_eff_HLT_OR_pt_unseeded);

    TLegend *l_eff_HLT_OR_pt_unseeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_pt_unseeded->SetShadowColor( 0 );
    l_eff_HLT_OR_pt_unseeded->SetFillColor( 0 );
    l_eff_HLT_OR_pt_unseeded->SetLineColor( 0 );
    l_eff_HLT_OR_pt_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_pt_unseeded->AddEntry( eff_HLT_OR_pt_unseeded, "HLT_Photon18_Iso60CaloId_OR_R9ID", "l" );
    l_eff_HLT_OR_pt_unseeded->AddEntry( eff_HLT_Iso_pt_unseeded, "HLT_Photon18_Iso60CaloId", "l" );
    l_eff_HLT_OR_pt_unseeded->AddEntry( eff_HLT_R9_pt_unseeded, "HLT_Photon18_R9Id", "l" );
    l_eff_HLT_OR_pt_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_pt_unseeded->Draw();

    //pt/M efficiencies
    /*
    c_eff_L1_7_ptoM->cd();
    eff_L1_10_ptoM->Divide( PROBE_L1_10_ptoM, TAG_L1_10_ptoM, "b(1,1) mode" );
    eff_L1_10_ptoM->SetMinimum( 0.0 );
    eff_L1_10_ptoM->SetMaximum( 1.1 );
    eff_L1_10_ptoM->SetTitle( sample );
    eff_L1_10_ptoM->GetXaxis()->SetTitle( "p_{T}/M_{#gamma#gamma} (GeV)" );
    eff_L1_10_ptoM->GetYaxis()->SetTitle( "L1 Efficiency" );
    eff_L1_10_ptoM->SetLineColor( 2 );
    eff_L1_10_ptoM->SetLineWidth( 2 );
    eff_L1_10_ptoM->SetMarkerStyle( 7 );
    eff_L1_10_ptoM->SetMarkerColor( 2 );

    eff_L1_10_ptoM->Draw( "AP" );
    eff_L1_15_ptoM->Divide( PROBE_L1_15_ptoM, TAG_L1_15_ptoM, "b(1,1) mode" );
    eff_L1_15_ptoM->SetMinimum( 0.0 );
    eff_L1_15_ptoM->SetMaximum( 1.1 );
    eff_L1_15_ptoM->SetLineColor( 4 );
    eff_L1_15_ptoM->SetLineWidth( 2 );
    eff_L1_15_ptoM->SetMarkerStyle( 7 );
    eff_L1_15_ptoM->SetMarkerColor( 4 );
    eff_L1_15_ptoM->Draw( "SAMEP" );

    TLegend *l_eff_L1_7_ptoM = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_L1_7_ptoM->SetShadowColor( 0 );
    l_eff_L1_7_ptoM->SetFillColor( 0 );
    l_eff_L1_7_ptoM->SetLineColor( 0 );
    l_eff_L1_7_ptoM->SetTextSize( 0.03 );
    l_eff_L1_7_ptoM->AddEntry( eff_L1_10_ptoM, "L1_EG10", "l" );
    l_eff_L1_7_ptoM->AddEntry( eff_L1_15_ptoM, "L1_EG15", "l" );
    //    l_eff_L1_7_ptoM->AddEntry( eff_L1_35_ptoM, "L1_EG40", "l" );
    l_eff_L1_7_ptoM->SetTextSize( 0.03 );
    l_eff_L1_7_ptoM->Draw();
    
    //HLT seeded ptoM efficiencies
    c_eff_HLT_OR_ptoM_seeded->cd();
    eff_HLT_OR_ptoM_seeded->Divide( PROBE_HLT_OR_ptoM_seeded, TAG_HLT_ptoM_seeded, "b(1,1) mode" );
    eff_HLT_OR_ptoM_seeded->SetMinimum( 0.0 );
    eff_HLT_OR_ptoM_seeded->SetMaximum( 1.1 );
    eff_HLT_OR_ptoM_seeded->SetTitle( sample );
    eff_HLT_OR_ptoM_seeded->GetXaxis()->SetTitle( "p_{T}/M_{#gamma#gamma} (GeV)" );
    eff_HLT_OR_ptoM_seeded->GetYaxis()->SetTitle( "HLT-Only Efficiency" );
    eff_HLT_OR_ptoM_seeded->SetLineColor( 1 );
    eff_HLT_OR_ptoM_seeded->SetMarkerColor( 1 );

    eff_HLT_OR_ptoM_seeded->SetLineWidth( 2 );
    eff_HLT_OR_ptoM_seeded->SetMarkerStyle( 7 );
    eff_HLT_OR_ptoM_seeded->Draw( "AP" );
    eff_HLT_Iso_ptoM_seeded->Divide( PROBE_HLT_Iso_ptoM_seeded, TAG_HLT_ptoM_seeded, "b(1,1) mode" );
    eff_HLT_Iso_ptoM_seeded->SetMinimum( 0.0 );
    eff_HLT_Iso_ptoM_seeded->SetMaximum( 1.1 );
    eff_HLT_Iso_ptoM_seeded->SetLineColor( 2 );
    eff_HLT_Iso_ptoM_seeded->SetMarkerColor( 2 );

    eff_HLT_Iso_ptoM_seeded->SetLineWidth( 2 );
    eff_HLT_Iso_ptoM_seeded->SetMarkerStyle( 7 );
    eff_HLT_Iso_ptoM_seeded->Draw( "SAMEP" );
    eff_HLT_R9_ptoM_seeded->Divide( PROBE_HLT_R9_ptoM_seeded, TAG_HLT_ptoM_seeded, "b(1,1) mode" );
    eff_HLT_R9_ptoM_seeded->SetMinimum( 0.0 );
    eff_HLT_R9_ptoM_seeded->SetMaximum( 1.1 );
    eff_HLT_R9_ptoM_seeded->SetLineColor( 4 );
    eff_HLT_R9_ptoM_seeded->SetMarkerColor( 4 );

    eff_HLT_R9_ptoM_seeded->SetLineWidth( 2 );
    eff_HLT_R9_ptoM_seeded->SetMarkerStyle( 7 );
    eff_HLT_R9_ptoM_seeded->Draw( "SAMEP" );
    TLegend *l_eff_HLT_OR_ptoM_seeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_ptoM_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_ptoM_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_ptoM_seeded->SetLineColor( 0 );
    l_eff_HLT_OR_ptoM_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_ptoM_seeded->AddEntry( eff_HLT_OR_ptoM_seeded, "HLT_Photon30_Iso60CaloId_OR_R9Id", "l" );
    l_eff_HLT_OR_ptoM_seeded->AddEntry( eff_HLT_Iso_ptoM_seeded, "HLT_Photon30_Iso60CaloId", "l" );
    l_eff_HLT_OR_ptoM_seeded->AddEntry( eff_HLT_R9_ptoM_seeded, "HLT_Photon30_R9Id", "l" );
    l_eff_HLT_OR_ptoM_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_ptoM_seeded->Draw();

    //HLT unseeded ptoM efficiencies
    c_eff_HLT_OR_ptoM_unseeded->cd();
    eff_HLT_OR_ptoM_unseeded->Divide( PROBE_HLT_OR_ptoM_unseeded, TAG_HLT_ptoM_unseeded, "b(1,1) mode" );
    eff_HLT_OR_ptoM_unseeded->SetMinimum( 0.0 );
    eff_HLT_OR_ptoM_unseeded->SetMaximum( 1.1 );
    eff_HLT_OR_ptoM_unseeded->SetTitle( sample );
    eff_HLT_OR_ptoM_unseeded->GetXaxis()->SetTitle( "p_{T}/M_{%gamma%gamma} (GeV)" );
    eff_HLT_OR_ptoM_unseeded->GetYaxis()->SetTitle( "HLT-Only Efficiency" );
    eff_HLT_OR_ptoM_unseeded->SetLineColor( 1 );
    eff_HLT_OR_ptoM_unseeded->SetMarkerColor( 1 );

    eff_HLT_OR_ptoM_unseeded->SetLineWidth( 2 );
    eff_HLT_OR_ptoM_unseeded->SetMarkerStyle( 7 );
    eff_HLT_OR_ptoM_unseeded->Draw( "AP" );
    eff_HLT_Iso_ptoM_unseeded->Divide( PROBE_HLT_Iso_ptoM_unseeded, TAG_HLT_ptoM_unseeded, "b(1,1) mode" );
    eff_HLT_Iso_ptoM_unseeded->SetMinimum( 0.0 );
    eff_HLT_Iso_ptoM_unseeded->SetMaximum( 1.1 );
    eff_HLT_Iso_ptoM_unseeded->SetLineColor( 2 );
    eff_HLT_Iso_ptoM_unseeded->SetMarkerColor( 2 );

    eff_HLT_Iso_ptoM_unseeded->SetLineWidth( 2 );
    eff_HLT_Iso_ptoM_unseeded->SetMarkerStyle( 7 );
    eff_HLT_Iso_ptoM_unseeded->Draw( "SAMEP" );
    eff_HLT_R9_ptoM_unseeded->Divide( PROBE_HLT_R9_ptoM_unseeded, TAG_HLT_ptoM_unseeded, "b(1,1) mode" );
    eff_HLT_R9_ptoM_unseeded->SetMinimum( 0.0 );
    eff_HLT_R9_ptoM_unseeded->SetMaximum( 1.1 );
    eff_HLT_R9_ptoM_unseeded->SetLineColor( 4 );
    eff_HLT_R9_ptoM_unseeded->SetMarkerColor( 4 );

    eff_HLT_R9_ptoM_unseeded->SetLineWidth( 2 );
    eff_HLT_R9_ptoM_unseeded->SetMarkerStyle( 7 );
    eff_HLT_R9_ptoM_unseeded->Draw( "SAMEP" );
    TLegend *l_eff_HLT_OR_ptoM_unseeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_ptoM_unseeded->SetShadowColor( 0 );
    l_eff_HLT_OR_ptoM_unseeded->SetFillColor( 0 );
    l_eff_HLT_OR_ptoM_unseeded->SetLineColor( 0 );
    l_eff_HLT_OR_ptoM_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_ptoM_unseeded->AddEntry( eff_HLT_OR_ptoM_unseeded, "HLT_Photon18_Iso60CaloId_OR_R9ID", "l" );
    l_eff_HLT_OR_ptoM_unseeded->AddEntry( eff_HLT_Iso_ptoM_unseeded, "HLT_Photon18_Iso60CaloId", "l" );
    l_eff_HLT_OR_ptoM_unseeded->AddEntry( eff_HLT_R9_ptoM_unseeded, "HLT_Photon18_R9Id", "l" );
    l_eff_HLT_OR_ptoM_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_ptoM_unseeded->Draw();

    */
    //eta efficiencies
    c_eff_L1_7_eta->cd();
    eff_L1_10_eta->Divide( PROBE_L1_10_eta, TAG_L1_10_eta, "b(1,1) mode" );
    formatTGraph(eff_L1_10_eta, "#eta", "L1 Efficiency", 2);    
    eff_L1_10_eta->Draw( "AP" );
    
    eff_L1_15_eta->Divide( PROBE_L1_15_eta, TAG_L1_15_eta, "b(1,1) mode" );
    formatTGraph(eff_L1_15_eta, "#eta", "L1 Efficiency", 4);    
    eff_L1_15_eta->Draw( "SAMEP" );
    /*
    eff_L1_35_eta->Divide( PROBE_L1_35_eta, TAG_L1_35_eta, "b(1,1) mode" );
    eff_L1_35_eta->SetMinimum( 0.0 );
    eff_L1_35_eta->SetMaximum( 1.1 );
    eff_L1_35_eta->SetLineColor( 6 );
    eff_L1_35_eta->SetMarkerColor( 6 );
    eff_L1_35_eta->SetLineWidth( 2 );
    eff_L1_35_eta->SetMarkerStyle( 7 );
    eff_L1_35_eta->Draw( "SAMEP" );
    */
    formatCanvas(c_eff_L1_7_eta);

    TLegend *l_eff_L1_7_eta = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_L1_7_eta->SetShadowColor( 0 );
    l_eff_L1_7_eta->SetFillColor( 0 );
    l_eff_L1_7_eta->SetLineColor( 0 );
    l_eff_L1_7_eta->SetTextSize( 0.03 );
    l_eff_L1_7_eta->AddEntry( eff_L1_10_eta, "L1_EG10", "l" );
    l_eff_L1_7_eta->AddEntry( eff_L1_15_eta, "L1_EG15", "l" );
    //l_eff_L1_7_eta->AddEntry( eff_L1_35_eta, "L1_EG40", "l" );
    l_eff_L1_7_eta->SetTextSize( 0.03 );
    l_eff_L1_7_eta->Draw();

    //HLT seeded eta efficiencies
    c_eff_HLT_OR_eta_seeded->cd();
    eff_HLT_OR_eta_seeded->Divide( PROBE_HLT_OR_eta_seeded, TAG_HLT_eta_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_eta_seeded, "#eta", "HLT-Only Efficiency", 1);    
    eff_HLT_OR_eta_seeded->Draw( "AP" );

    eff_HLT_Iso_eta_seeded->Divide( PROBE_HLT_Iso_eta_seeded, TAG_HLT_eta_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_Iso_eta_seeded, "#eta", "HLT-Only Efficiency", 2);    
    eff_HLT_Iso_eta_seeded->Draw( "SAMEP" );

    
    eff_HLT_R9_eta_seeded->Divide( PROBE_HLT_R9_eta_seeded, TAG_HLT_eta_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_R9_eta_seeded, "#eta", "HLT-Only Efficiency", 4);    
    eff_HLT_R9_eta_seeded->Draw( "SAMEP" );
    formatCanvas(c_eff_HLT_OR_eta_seeded);
    
    TLegend *l_eff_HLT_OR_eta_seeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_eta_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_eta_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_eta_seeded->SetLineColor( 0 );
    l_eff_HLT_OR_eta_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_eta_seeded->AddEntry( eff_HLT_OR_eta_seeded, "HLT_Photon30_Iso60CaloId_OR_R9Id", "l" );
    l_eff_HLT_OR_eta_seeded->AddEntry( eff_HLT_Iso_eta_seeded, "HLT_Photon30_Iso60CaloId", "l" );
    l_eff_HLT_OR_eta_seeded->AddEntry( eff_HLT_R9_eta_seeded, "HLT_Photon30_R9Id", "l" );
    l_eff_HLT_OR_eta_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_eta_seeded->Draw();

    //HLT unseeded eta efficiencies
    c_eff_HLT_OR_eta_unseeded->cd();
    eff_HLT_OR_eta_unseeded->Divide( PROBE_HLT_OR_eta_unseeded, TAG_HLT_eta_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_eta_unseeded, "#eta", "HLT-Only Efficiency", 1);    
    eff_HLT_OR_eta_unseeded->Draw( "AP" );

    eff_HLT_Iso_eta_unseeded->Divide( PROBE_HLT_Iso_eta_unseeded, TAG_HLT_eta_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_Iso_eta_unseeded, "#eta", "HLT-Only Efficiency", 2);    
    eff_HLT_Iso_eta_unseeded->Draw( "SAMEP" );

    
    eff_HLT_R9_eta_unseeded->Divide( PROBE_HLT_R9_eta_unseeded, TAG_HLT_eta_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_R9_eta_unseeded, "#eta", "HLT-Only Efficiency", 4);    
    eff_HLT_R9_eta_unseeded->Draw( "SAMEP" );
    formatCanvas(c_eff_HLT_OR_eta_unseeded);
    
    TLegend *l_eff_HLT_OR_eta_unseeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_eta_unseeded->SetShadowColor( 0 );
    l_eff_HLT_OR_eta_unseeded->SetFillColor( 0 );
    l_eff_HLT_OR_eta_unseeded->SetLineColor( 0 );
    l_eff_HLT_OR_eta_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_eta_unseeded->AddEntry( eff_HLT_OR_eta_unseeded, "HLT_Photon18_Iso60CaloId_OR_R9ID", "l" );
    l_eff_HLT_OR_eta_unseeded->AddEntry( eff_HLT_Iso_eta_unseeded, "HLT_Photon18_Iso60CaloId", "l" );
    l_eff_HLT_OR_eta_unseeded->AddEntry( eff_HLT_R9_eta_unseeded, "HLT_Photon18_R9Id", "l" );
    l_eff_HLT_OR_eta_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_eta_unseeded->Draw();


    //nvtx efficiencies
    c_eff_L1_7_nvtx->cd();
    eff_L1_10_nvtx->Divide( PROBE_L1_10_nvtx, TAG_L1_10_nvtx, "b(1,1) mode" );
    formatTGraph(eff_L1_10_nvtx, "nvtx", "L1 Efficiency", 2);    
    eff_L1_10_nvtx->Draw( "AP" );
    eff_L1_15_nvtx->Divide( PROBE_L1_15_nvtx, TAG_L1_15_nvtx, "b(1,1) mode" );
    formatTGraph(eff_L1_15_nvtx, "nvtx", "L1 Efficiency", 4);    
    eff_L1_15_nvtx->Draw( "SAMEP" );
    /*
    eff_L1_35_nvtx->Divide( PROBE_L1_35_nvtx, TAG_L1_35_nvtx, "b(1,1) mode" );
    eff_L1_35_nvtx->SetMinimum( 0.0 );
    eff_L1_35_nvtx->SetMaximum( 1.1 );
    eff_L1_35_nvtx->SetLineColor( 6 );
    eff_L1_35_nvtx->SetMarkerColor( 6 );
    eff_L1_35_nvtx->SetLineWidth( 2 );
    eff_L1_35_nvtx->SetMarkerStyle( 7 );
    eff_L1_35_nvtx->Draw( "SAMEP" );
    */
    formatCanvas(c_eff_L1_7_nvtx);
    TLegend *l_eff_L1_7_nvtx = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_L1_7_nvtx->SetShadowColor( 0 );
    l_eff_L1_7_nvtx->SetFillColor( 0 );
    l_eff_L1_7_nvtx->SetLineColor( 0 );
    l_eff_L1_7_nvtx->SetTextSize( 0.03 );
    l_eff_L1_7_nvtx->AddEntry( eff_L1_10_nvtx, "L1_EG10", "l" );
    l_eff_L1_7_nvtx->AddEntry( eff_L1_15_nvtx, "L1_EG15", "l" );
    //    l_eff_L1_7_nvtx->AddEntry( eff_L1_35_nvtx, "L1_EG40", "l" );
    l_eff_L1_7_nvtx->SetTextSize( 0.03 );
    l_eff_L1_7_nvtx->Draw();

    //HLT seeded nvtx efficiencies
    c_eff_HLT_OR_nvtx_seeded->cd();
    eff_HLT_OR_nvtx_seeded->Divide( PROBE_HLT_OR_nvtx_seeded, TAG_HLT_nvtx_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_nvtx_seeded, "nvtx", "HLT-Only Efficiency", 1);
    eff_HLT_OR_nvtx_seeded->Draw( "AP" );
    eff_HLT_Iso_nvtx_seeded->Divide( PROBE_HLT_Iso_nvtx_seeded, TAG_HLT_nvtx_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_Iso_nvtx_seeded, "nvtx", "HLT-Only Efficiency", 2);
    eff_HLT_Iso_nvtx_seeded->Draw( "SAMEP" );
    eff_HLT_R9_nvtx_seeded->Divide( PROBE_HLT_R9_nvtx_seeded, TAG_HLT_nvtx_seeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_R9_nvtx_seeded, "nvtx", "HLT-Only Efficiency", 4);
    eff_HLT_R9_nvtx_seeded->Draw( "SAMEP" );
    formatCanvas(c_eff_HLT_OR_nvtx_seeded);
    
    TLegend *l_eff_HLT_OR_nvtx_seeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_nvtx_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_nvtx_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_nvtx_seeded->SetLineColor( 0 );
    l_eff_HLT_OR_nvtx_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_nvtx_seeded->AddEntry( eff_HLT_OR_nvtx_seeded, "HLT_Photon30_Iso60CaloId_OR_R9Id", "l" );
    l_eff_HLT_OR_nvtx_seeded->AddEntry( eff_HLT_Iso_nvtx_seeded, "HLT_Photon30_Iso60CaloId", "l" );
    l_eff_HLT_OR_nvtx_seeded->AddEntry( eff_HLT_R9_nvtx_seeded, "HLT_Photon30_R9Id", "l" );
    l_eff_HLT_OR_nvtx_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_nvtx_seeded->Draw();

    //HLT unseeded nvtx efficiencies
    c_eff_HLT_OR_nvtx_unseeded->cd();
    eff_HLT_OR_nvtx_unseeded->Divide( PROBE_HLT_OR_nvtx_unseeded, TAG_HLT_nvtx_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_OR_nvtx_unseeded, "nvtx", "HLT-Only Efficiency", 1);
    eff_HLT_OR_nvtx_unseeded->Draw( "AP" );
    eff_HLT_Iso_nvtx_unseeded->Divide( PROBE_HLT_Iso_nvtx_unseeded, TAG_HLT_nvtx_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_Iso_nvtx_unseeded, "nvtx", "HLT-Only Efficiency", 2);
    eff_HLT_Iso_nvtx_unseeded->Draw( "SAMEP" );
    eff_HLT_R9_nvtx_unseeded->Divide( PROBE_HLT_R9_nvtx_unseeded, TAG_HLT_nvtx_unseeded, "b(1,1) mode" );
    formatTGraph(eff_HLT_R9_nvtx_unseeded, "nvtx", "HLT-Only Efficiency", 4);
    eff_HLT_R9_nvtx_unseeded->Draw( "SAMEP" );
    formatCanvas(c_eff_HLT_OR_nvtx_unseeded);
    
    TLegend *l_eff_HLT_OR_nvtx_unseeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_nvtx_unseeded->SetShadowColor( 0 );
    l_eff_HLT_OR_nvtx_unseeded->SetFillColor( 0 );
    l_eff_HLT_OR_nvtx_unseeded->SetLineColor( 0 );
    l_eff_HLT_OR_nvtx_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_nvtx_unseeded->AddEntry( eff_HLT_OR_nvtx_unseeded, "HLT_Photon18_Iso60CaloId_OR_R9ID", "l" );
    l_eff_HLT_OR_nvtx_unseeded->AddEntry( eff_HLT_Iso_nvtx_unseeded, "HLT_Photon18_Iso60CaloId", "l" );
    l_eff_HLT_OR_nvtx_unseeded->AddEntry( eff_HLT_R9_nvtx_unseeded, "HLT_Photon18_R9Id", "l" );
    l_eff_HLT_OR_nvtx_unseeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_nvtx_unseeded->Draw();

}
void HLTPlotter::writeEfficiencies()
{
    

    c_eff_HLT_OR_pt_seeded->SaveAs("HLT_pt_seeded.png");
    c_eff_HLT_OR_pt_unseeded->SaveAs("HLT_pt_unseeded.png");
    c_eff_L1_7_pt->SaveAs("L1_pt.png");

    c_eff_HLT_OR_eta_seeded->SaveAs("HLT_eta_seeded.png");
    c_eff_HLT_OR_eta_unseeded->SaveAs("HLT_eta_unseeded.png");
    c_eff_L1_7_eta->SaveAs("L1_eta.png");

    c_eff_HLT_OR_nvtx_seeded->SaveAs("HLT_nvtx_seeded.png");
    c_eff_HLT_OR_nvtx_unseeded->SaveAs("HLT_nvtx_unseeded.png");
    c_eff_L1_7_nvtx->SaveAs("L1_nvtx.png");

}

TGraphAsymmErrors * HLTPlotter::formatTGraph(TGraphAsymmErrors *graph, std::string xTitle, std::string yTitle, int color)
{
        setTDRStyle();

    //const char *sample = "2015D ReMiniAOD V7, (13 TeV)";
        //    const char *sample = "2.11 fb^{-1}   (13 TeV)";
    graph->SetMinimum( 0.0 );
    graph->SetMaximum( 1.1 );
    //graph->SetTitle( sample );
    graph->GetXaxis()->SetTitle( xTitle.c_str() );
    graph->GetYaxis()->SetTitle( yTitle.c_str() );
    graph->SetLineColor( color );
    graph->SetLineWidth( 2 );
    graph->SetMarkerStyle( 7 );
    graph->SetMarkerColor( color );
    
    return(graph);
}

void HLTPlotter::formatCanvas(TCanvas *pad)
{
    TString extraText  = "Preliminary";  // default extra text is "Preliminary"
    //    TString lumiTexta = "2.11 fb^{-1}   (13 TeV)";
    //TString lumiTexta = "0.553 fb^{-1}   (13 TeV)"; //lumi from runD re-minaod
    //TString lumiTexta = "0.566 fb^{-1}   (13 TeV)";  //lumi from Spring extension (prompt !re-mini)
    //TString lumiTexta = "1.12 fb^{-1}   (13 TeV)"; //lumi from runD + extension (full run D re-mini+prompt !remini)
    TString lumiTexta = "2.2 fb^{-1}   (13 TeV)"; //lumi from michael rePreselection campaign
    //TString lumiTexta = "2.22 fb^{-1}   (13 TeV)"; //lumi from michael rePreselection campaign RunD only
    setTDRStyle();
    //    float H = pad->GetWh();
    //float W = pad->GetWw();
    pad->SetLeftMargin(0.12);
    pad->SetRightMargin(0.04);
    pad->SetTopMargin(0.08);
    pad->SetBottomMargin(0.12);
    //    float l = pad->GetLeftMargin();
    float t = pad->GetTopMargin();
    float r = pad->GetRightMargin();
    //float b = pad->GetBottomMargin();
    float lumiTextSize     = 0.7; //0.6
    float lumiTextOffset   = 0.2;
    float cmsTextSize      = 0.7;
    float extraTextFont = 52;  // default is helvetica-italics    
    float extraOverCmsTextSize  = 1.0; //0.76
    float extraTextSize = cmsTextSize*extraOverCmsTextSize;
    
    //float relExtraDY = 1.0;    

    TLatex latex;
    latex.SetNDC();
    pad->SetGridx(1);
    pad->SetGridy(1);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);
    latex.SetTextFont(61); //helvetica
    latex.SetTextAlign(11); 
    
    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t);    
    latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiTexta);
    
    pad->cd();    

    latex.SetTextFont(61);  //helvetica
    latex.SetTextSize(cmsTextSize*t);
    latex.SetTextAlign(11);
    //    latex.DrawLatex(0.95, .865, "CMS");
    latex.DrawLatex(0.12, 1-t+lumiTextOffset*t, "CMS");
    
    latex.SetTextFont(extraTextFont);
    latex.SetTextAlign(11);
    latex.SetTextSize(extraTextSize*t);
    //latex.DrawLatex(0.95, 0.865 - relExtraDY*cmsTextSize*t, extraText);
    latex.DrawLatex(0.23, 1-t+lumiTextOffset*t, extraText);

    pad->Update();
    //    latex.DrawLatex(pad->GetLeftMargin(),1-pad->GetTopMargin()*0.02,"CMS");
    //latex.DrawLatex(0.05,0.95,"CMS");
}
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
