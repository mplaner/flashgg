// user include files
#include "TFile.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "tdrstyle.C"
#include <string>

class HLTPlotter
{
public:
    HLTPlotter( std::string fname, std::string fname2, std::string xtitle, std::string plot_to_load );
    HLTPlotter();
    ~HLTPlotter();
    void makePlots();
    void writeEfficiencies();
    void printEfficiencies();
    void makeEfficiencies();
    void formatCanvas(TCanvas *can);
    TGraphAsymmErrors * formatTGraph(TGraphAsymmErrors *graph, std::string xTitle, std::string yTitle, int color);
private:
    TCanvas *c_eff_HLT_OR_pt_seeded = new TCanvas( "c_eff_HLT_OR_pt_seeded", "c_eff_HLT_OR_pt_seeded" );
    TCanvas *c_eff_HLT_OR_pt_unseeded = new TCanvas( "c_eff_HLT_OR_pt_unseeded", "c_eff_HLT_OR_pt_unseeded" );
    std::string x_title;
    int color[8] ={1,6,2,4,1,6,2,4};
    TGraphAsymmErrors *eff_HLT_OR_eta_seeded;
    TGraphAsymmErrors *eff_HLT_OR_nvtx_seeded;
    TGraphAsymmErrors *eff_HLT_OR_pt_seeded;
    TGraphAsymmErrors *eff_HLT_OR_pt_unseeded;
    TGraphAsymmErrors *eff_HLT_OR_eta_unseeded;
    TGraphAsymmErrors *eff_HLT_OR_nvtx_unseeded;
    TGraphAsymmErrors *eff_graph[8];
    std::string eff_graph_label[8];
};

HLTPlotter::~HLTPlotter()
{

    TFile *file = new TFile( "tempoutput.root", "recreate" );

    c_eff_HLT_OR_pt_seeded->Write();

    file->Close();
}

HLTPlotter::HLTPlotter( std::string fname, std::string fname2, std::string xtitle, std::string plot_to_load)
{
    //    TFile * inputFile = new TFile("output_DoubleEG.root");
    TFile *inputFile = new TFile( fname.c_str() );
    TFile *inputFile2 = new TFile( fname2.c_str() );
    x_title= xtitle;
    //int etaBin = 30;
    //int nvtxBin = 50;
    //int ptBin = 30
    std::string canvasName = "PhotonToRECOpre/passingHLTpre/fit_eff_plots/" + plot_to_load;

    TCanvas *c1 = (TCanvas*)inputFile->Get(canvasName.c_str() );
    //TCanvas *c1 = (TCanvas*)inputFile->Get("PhotonToRECOpre/passingHLTpre/fit_eff_plots/probe_sc_et_PLOT" );
    //eff_HLT_OR_pt_seeded = (TGraphAsymmErrors*)c1->GetPrimitive("probe_sc_et_PLOT")->Clone();
    eff_HLT_OR_pt_seeded = (TGraphAsymmErrors*)c1->GetPrimitive(plot_to_load.c_str())->Clone();
    eff_HLT_OR_pt_seeded->SetName("temp1");
    
    TCanvas *c2 = (TCanvas*)inputFile2->Get(canvasName.c_str() );
    eff_HLT_OR_pt_unseeded = (TGraphAsymmErrors*)c2->GetPrimitive(plot_to_load.c_str())->Clone();
    //TCanvas *c2 = (TCanvas*)inputFile2->Get("PhotonToRECOpre/passingHLTpre/fit_eff_plots/probe_sc_et_PLOT" );
    //eff_HLT_OR_pt_unseeded = (TGraphAsymmErrors*)c2->GetPrimitive("probe_sc_et_PLOT")->Clone();
    //inputFile->Close();
}

HLTPlotter::HLTPlotter()
{
    /*    
    eff_graph_label[0]="lead_HLT_highR9_m100";
    eff_graph_label[1]="lead_HLT_lowR9_m100";
    eff_graph_label[2]="sub_HLT_highR9_m100";
    eff_graph_label[3]="sub_HLT_lowR9_m100";

    eff_graph_label[4]="lead_HLT_highR9_m100";
    eff_graph_label[5]="lead_HLT_lowR9_m100";
    eff_graph_label[6]="sub_HLT_highR9_m100";
    eff_graph_label[7]="sub_HLT_lowR9_m100";
    x_title= "probe #eta";
    
    string plot_to_load = "probe_sc_eta_PLOT_probe_Pho_r9_bin0_and_probe_sc_et_bin0";
    string filename = "egmData_final/eta/";    
    */
    
    eff_graph_label[0]="lead_HLT_highR9_EB";
    eff_graph_label[1]="lead_HLT_lowR9_EB";
    eff_graph_label[2]="lead_HLT_highR9_EE";
    eff_graph_label[3]="lead_HLT_lowR9_EE";

    eff_graph_label[4]="sub_HLT_highR9_EB";
    eff_graph_label[5]="sub_HLT_lowR9_EB";
    eff_graph_label[6]="sub_HLT_highR9_EE";
    eff_graph_label[7]="sub_HLT_lowR9_EE";
    x_title= "probe p_{T} (GeV)";
    string plot_to_load = "probe_sc_et_PLOT_probe_Pho_r9_bin0_and_probe_sc_abseta_bin0";
    string filename = "egmData_final/";    
    


    TFile *inputFile[8];
    TCanvas *c1;
    std::string canvasName = "PhotonToRECO/passingHLT/fit_eff_plots/" + plot_to_load;
    for(int i=0;i<8;i++)
        {
            std::string tempFileName = filename + eff_graph_label[i] + ".root";
            inputFile[i] = new TFile(tempFileName.c_str());
            c1 = (TCanvas*)inputFile[i]->Get(canvasName.c_str());
            eff_graph[i] = (TGraphAsymmErrors*)c1->GetPrimitive(plot_to_load.c_str())->Clone(); //fails here for HLT
            //std::cout << tempFileName << std::endl;
            //eff_HLT_OR_pt_a->SetName("temp1");
            inputFile[i]->Close();
        }
    
    //inputFile->Close();
}

void HLTPlotter::printEfficiencies()
{
    //[5] and [18] are gaps
    //float etaBins[23] = {-2.5,-2.2,-1.9,-1.75,-1.566,-1.444,-1.2,-1.0,-0.8,-0.5,-0.25,0,0.25,0.5,0.8,1.0,1.2,1.444,1.566,1.75,1.9,2.2, 2.5};
    float ptBinsSub[16] =  {20.,22.5, 25. ,27.5, 30.,33.33, 35., 40., 45., 50., 60., 70., 90., 120., 150.,200};
    float ptBins[12] =  {30.,33.33, 35., 40., 45., 50., 60., 70., 90., 120., 150.,200};
    //float ptBinsSub[23] = {-2.5,-2.2,-1.9,-1.75,-1.566,-1.444,-1.2,-1.0,-0.8,-0.5,-0.25,0,0.25,0.5,0.8,1.0,1.2,1.444,1.566,1.75,1.9,2.2, 2.5};
    //float    ptBins[23] = {-2.5,-2.2,-1.9,-1.75,-1.566,-1.444,-1.2,-1.0,-0.8,-0.5,-0.25,0,0.25,0.5,0.8,1.0,1.2,1.444,1.566,1.75,1.9,2.2, 2.5}; 
    
    /*
    eff_graph_label[0]="  seeded HLT highR9";
    eff_graph_label[1]="  seeded HLT lowR9";
    eff_graph_label[2]="unseeded HLT highR9";
    eff_graph_label[3]="unseeded HLT lowR9";
    */
    eff_graph_label[4]="lead_HLT_highR9_EB";
    eff_graph_label[5]="lead_HLT_lowR9_EB";
    eff_graph_label[6]="lead_HLT_highR9_EE";
    eff_graph_label[7]="lead_HLT_lowR9_EE";
    
    eff_graph_label[4]="sub_HLT_highR9_EB";
    eff_graph_label[5]="sub_HLT_lowR9_EB";
    eff_graph_label[6]="sub_HLT_highR9_EE";
    eff_graph_label[7]="sub_HLT_lowR9_EE";
    
    for(int i=0;i<4;i++)
        {
            for(int j=0;j<  eff_graph[i]->GetN(); j++)
                {
                    eff_graph[i]->SetPointEXlow(j,(ptBins[j+1]-ptBins[j])/2);
                    eff_graph[i]->SetPointEXhigh(j,(ptBins[j+1]-ptBins[j])/2);
                }
            eff_graph[i]->RemovePoint(4);
            eff_graph[i]->RemovePoint(16);
            formatTGraph(eff_graph[i], x_title, "HLT Efficiency", color[i]);
            if(i==0)
                eff_graph[i]->Draw("AP");
            else
                eff_graph[i]->Draw("SAMEP");
        }
    TLegend *l_eff_graph = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_graph->SetShadowColor( 0 );
    l_eff_graph->SetFillColor( 0 );
    l_eff_graph->SetLineColor( 1 );
    l_eff_graph->SetTextSize( 0.03 );
    for(int i=0;i<4;i++)
        l_eff_graph->AddEntry( eff_graph[i], eff_graph_label[i].c_str() , "l" );
    l_eff_graph->SetTextSize( 0.03 );
    l_eff_graph->Draw();
    formatCanvas(c_eff_HLT_OR_pt_seeded);
        
    c_eff_HLT_OR_pt_unseeded->cd();
    
    for(int i=4;i<8;i++)
        {
            for(int j=0;j<  eff_graph[i]->GetN(); j++)
                {
                    eff_graph[i]->SetPointEXlow(j,(ptBinsSub[j+1]-ptBinsSub[j])/2);
                    eff_graph[i]->SetPointEXhigh(j,(ptBinsSub[j+1]-ptBinsSub[j])/2);
                }
            eff_graph[i]->RemovePoint(4);
            eff_graph[i]->RemovePoint(16);
            formatTGraph(eff_graph[i], x_title, "HLT Efficiency", color[i]);
            if(i==4)
                eff_graph[i]->Draw("AP");
            else
                eff_graph[i]->Draw("SAMEP");
        }
    TLegend *l_eff2_graph = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff2_graph->SetShadowColor( 0 );
    l_eff2_graph->SetFillColor( 0 );
    l_eff2_graph->SetLineColor( 1 );
    l_eff2_graph->SetTextSize( 0.03 );
    for(int i=4;i<8;i++)
        l_eff2_graph->AddEntry( eff_graph[i], eff_graph_label[i].c_str() , "l" );
    l_eff2_graph->SetTextSize( 0.03 );
    l_eff2_graph->Draw();
    formatCanvas(c_eff_HLT_OR_pt_unseeded);
}

void HLTPlotter::makePlots()
{


    formatTGraph(eff_HLT_OR_pt_seeded, "p_{T} (GeV)", "HLT-Only Efficiency", 2);    
    formatTGraph(eff_HLT_OR_pt_unseeded, "p_{T} (GeV)", "HLT-Only Efficiency", 1);    
    eff_HLT_OR_pt_seeded->GetYaxis()->SetRangeUser(0.7,1.05);
    eff_HLT_OR_pt_seeded->GetXaxis()->SetRangeUser(0,250);
    eff_HLT_OR_pt_seeded->Draw( "AP" );
    eff_HLT_OR_pt_unseeded->Draw( "SAMEP" );
    
    //    formatCanvas(c_eff_HLT_OR_pt_seeded);
    
}

void HLTPlotter::makeEfficiencies()
{
    
    formatTGraph(eff_HLT_OR_pt_seeded, x_title, "HLT-Only Efficiency", 2);    
    //formatTGraph(eff_HLT_OR_pt_seeded, "p_{T} (GeV)", "HLT-Only Efficiency", 2);    
    eff_HLT_OR_pt_seeded->Draw( "AP" );
    formatTGraph(eff_HLT_OR_pt_unseeded, x_title, "HLT-Only Efficiency", 1);    
    //    formatTGraph(eff_HLT_OR_pt_unseeded, "p_{T} (GeV)", "HLT-Only Efficiency", 1);    
    eff_HLT_OR_pt_unseeded->Draw( "SAMEP" );
    formatCanvas(c_eff_HLT_OR_pt_seeded);
    
    TLegend *l_eff_HLT_OR_pt_seeded = new TLegend( 0.45, 0.15, 0.55, 0.32 );
    l_eff_HLT_OR_pt_seeded->SetShadowColor( 0 );
    l_eff_HLT_OR_pt_seeded->SetFillColor( 0 );
    l_eff_HLT_OR_pt_seeded->SetLineColor( 1 );
    l_eff_HLT_OR_pt_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_pt_seeded->AddEntry( eff_HLT_OR_pt_seeded, "DY", "l" );
    l_eff_HLT_OR_pt_seeded->AddEntry( eff_HLT_OR_pt_unseeded, "Data", "l" );
    l_eff_HLT_OR_pt_seeded->SetTextSize( 0.03 );
    l_eff_HLT_OR_pt_seeded->Draw();

    double * x1 =  eff_HLT_OR_pt_unseeded->GetX();
    double * y1 =  eff_HLT_OR_pt_unseeded->GetY();
    double * y1ErrorsHigh =  eff_HLT_OR_pt_unseeded->GetEYhigh();
    double * y1ErrorsLow =  eff_HLT_OR_pt_unseeded->GetEYlow();

    double * x2 =  eff_HLT_OR_pt_seeded->GetX();
    double * y2 =  eff_HLT_OR_pt_seeded->GetY();
    double * y2ErrorsHigh =  eff_HLT_OR_pt_seeded->GetEYhigh();
    double * y2ErrorsLow =  eff_HLT_OR_pt_seeded->GetEYlow();
    
    for(int i=0;i<  eff_HLT_OR_pt_unseeded->GetN(); i++)
        {
            //int j=i+1;
            int j=i;
            //efficiency only
            std::cout << "x: " << x1[i] <<  " y: " << y1[i] << " yup: " << y1ErrorsHigh[i]  << " ydown: " << y1ErrorsLow[i]  << std::endl;
            //scale factor
            //std::cout << "x: " << x1[j] << " x2: " << x2[i] << " y: " << ((double)y1[j])/((double)y2[i]) << " yup: " << sqrt((y1ErrorsHigh[j]/y1[j])*(y1ErrorsHigh[j]/y1[j]) + (y2ErrorsLow[i]/y2[i])*(y2ErrorsLow[i]/y2[i]))*y1[j]/y2[i]  << " ydown: " << sqrt((y1ErrorsLow[j]/y1[j])*(y1ErrorsLow[j]/y1[j]) + (y2ErrorsHigh[i]/y2[i])*(y2ErrorsHigh[i]/y2[i]))*y1[j]/y2[i]  << std::endl;
        }
}
void HLTPlotter::writeEfficiencies()
{
    

    c_eff_HLT_OR_pt_seeded->SaveAs("HLT_pt_seeded.png");
}

TGraphAsymmErrors * HLTPlotter::formatTGraph(TGraphAsymmErrors *graph, std::string xTitle, std::string yTitle, int color)
{
    setTDRStyle();

    //const char *sample = "2015D ReMiniAOD V7, (13 TeV)";
    //    const char *sample = "2.11 fb^{-1}   (13 TeV)";
    //graph->SetTitle( sample );
    
    graph->SetMinimum( 0.9 );
    graph->SetMaximum( 1.02 );
    graph->GetXaxis()->SetTitle( xTitle.c_str() );
    graph->GetYaxis()->SetTitle( yTitle.c_str() );
    graph->SetLineColor( color );
    //graph->SetLineWidth( 3 );
    //    graph->SetMarkerStyle( 7 );
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
    TString lumiTexta = "2.5 fb^{-1}   (13 TeV)"; //lumi from michael rePreselection campaign
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

