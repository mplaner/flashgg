
/*
.L histoDraw.C
TCanvas *c1 = new TCanvas("c1","c1")
THStack *mass = new THStack("hs","")
StackPlot(c1,mass,"diphoton_mass (GeV)", "diphoton_mass>>(40,100,180)","weight*(diphoton_mass>100&&diphoton_mass<180&&diphoMVA>0)")

TCanvas *c2 = new TCanvas("c2","c2")
THStack *met = new THStack("hmet","")
StackPlot(c2,met,"MET (GeV)", "pfMET_corPt>>(80,0,400)","weight*(diphoton_mass>100&&diphoton_mass<180&&diphoMVA>0)")

TCanvas *c3 = new TCanvas("c2","c2")                                                                                                                                                                                                                                  THStack *dPhiMETjet = new THStack("hdPhiMetJet","") 
StackPlot(c3,dPhiMETjet,"#Delta#phi(met,lead jet)", "dPhi_pfMetJet>>(13,0,3.14)","weight*(diphoton_mass>100&&diphoton_mass<180&&diphoMVA>0)")

TCanvas *c4 = new TCanvas("c4","c4");      THStack *dPhiMETdipho = new THStack("hdPhiMetDipho","");
 StackPlot(c4,dPhiMETdipho,"#Delta#phi(met,#gamma#gamma)", "pfMET_dPhi>>(13,0,3.14)","weight*(diphoton_mass>100&&diphoton_mass<180&&diphoMVA>0&&pfMET_corPt>70)",1)

 StackPlot(c4,mva,"diphoton MVA", "diphoMVA>>(50,-1,1)","weight*(diphoton_mass>100&&diphoton_mass<180&&(leadPt/diphoton_mass)>1./3.&&(subleadPt/diphoton_mass)>1./4.)",0) 

*/

int StackPlot(TCanvas* canvas, THStack * hs, string xTitle, string drawOption, string cuts);
int StackPlot(TCanvas* canvas, THStack * hs, string xTitle, string drawOption, string cuts)
{
  canvas->SetGridx();
  canvas->SetGridy();
  

  TPad *plot = new TPad("plot","plot",0.0,0.3,1.0,1.0);
  plot->SetGridx();
  plot->SetGridy();
  TPad *ratio = new TPad("ratio","ratio",0.0,0.0,1.0,0.3);
  ratio->SetGridx();
  ratio->SetGridy();

  plot->Draw();
  plot->cd();
    
  TH1F* hist[6];
  TH1F* sum;
  int color[6] = {4,2,8,kViolet,1,1};
  //  string titles[5] = {"#gamma + jet", "TT/TTjets","Wg->l#nu","diphoton","data"};
  //  string titles[6] = {"#gamma + jet","qcd","diphoton","TTjets","Z#gamma->ll#gamma","data"};
  string titles[6] = {"#gamma + jet","qcd","diphoton","TTjets","dy","data"};
  //((TTree*)_file2->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  TFile *_file0 = TFile::Open("background_diphoton.root");
  TFile *_file1 = TFile::Open("background_gjet.root");
  TFile *_file2 = TFile::Open("background_qcd.root");
  TFile *_file3 = TFile::Open("data_doubleEG.root");
  TFile *_file4 = TFile::Open("background_ttall.root");
  //  TFile *_file5 = TFile::Open("background_zgto2lg.root");
  TFile *_file5 = TFile::Open("background_dy.root");
  
  string tempCuts = cuts.c_str();
  string temp ="";
  temp = "&&((leadMatchType==1&&subleadMatchType!=1)||(leadMatchType!=1&&subleadMatchType==1))";//prompt fake
  tempCuts.insert(tempCuts.end()-1,temp.begin(),temp.end()); 
  ((TTree*)_file1->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),tempCuts.c_str());
  hist[0] = (TH1F*)gPad->GetPrimitive("")->Clone("gjet"); 
  tempCuts = cuts.c_str();
  temp = "&&(leadMatchType!=1||subleadMatchType!=1)";// fake-fake or prompt fake
  tempCuts.insert(tempCuts.end()-1,temp.begin(),temp.end()); 
  ((TTree*)_file2->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),tempCuts.c_str());
  hist[1] = (TH1F*)gPad->GetPrimitive("")->Clone("qcd");
  tempCuts = cuts.c_str();
  temp = "&&(leadMatchType==1&&subleadMatchType==1)";//prompt prompt
  tempCuts.insert(tempCuts.end()-1,temp.begin(),temp.end()); 
  ((TTree*)_file0->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),tempCuts.c_str());
  hist[2] = (TH1F*)gPad->GetPrimitive("")->Clone("diphoton");
  ((TTree*)_file3->Get("tagsDumper/trees/data_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  hist[5] = (TH1F*)gPad->GetPrimitive("")->Clone("data");
  ((TTree*)_file4->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  hist[3] = (TH1F*)gPad->GetPrimitive("")->Clone("ttgjets");
  ((TTree*)_file5->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  hist[4] = (TH1F*)gPad->GetPrimitive("")->Clone("dy");


  std::cout << "saved histos" << std::endl;
  //scale plots to account for similar shapes:
  
  for(int i=0;i<5;i++)
    {
      //hist[i]->Scale(36.8);
      hist[i]->Scale(35.9);
      hist[i]->Scale(1.38);
      //hist[i]->Scale(1.77);
      hist[i]->SetTitle(titles[i].c_str());
      hist[i]->SetLineWidth(2);
      hist[i]->SetLineColor(color[i]);
      hist[i]->SetFillColor(color[i]);
      hist[i]->SetFillStyle(3001);
    }
  
  sum = (TH1F*)hist[2]->Clone("summed");
  sum->Add(hist[0]);
  sum->Add(hist[1]);
  sum->Add(hist[3]);
  sum->Add(hist[4]);
  sum->SetLineWidth(2);
  sum->SetLineColor(4);
  sum->SetTitle("error");
  sum->GetXaxis()->SetTitle(xTitle.c_str());
  sum->GetYaxis()->SetRangeUser(0,sum->GetMaximum()+sum->GetBinError(sum->GetMaximumBin()));
  
  hist[5]->SetLineWidth(2);
  hist[5]->SetTitle(titles[5].c_str());
  hist[5]->SetLineColor(1);
  hist[5]->SetMarkerStyle(20);
  hist[5]->SetMarkerSize(1);
  sum->Draw();
  
  hs->Add(hist[2]);
  hs->Add(hist[0]);
  hs->Add(hist[3]);
  hs->Add(hist[4]);
  hs->Add(hist[1]);
  hs->Draw("HISTSAME");
  hist[5]->Draw("sameP");
  leg = new TLegend(.5,.67,.88,.88);
  leg->AddEntry(hist[2],hist[2]->GetTitle());
  leg->AddEntry(hist[0],hist[0]->GetTitle());
  leg->AddEntry(hist[3],hist[3]->GetTitle());
  leg->AddEntry(hist[4],hist[4]->GetTitle());
  leg->AddEntry(hist[1],hist[1]->GetTitle());
  leg->AddEntry(hist[5],hist[5]->GetTitle());
  
  //canvas->BuildLegend(.5,.67,.88,.88);
  sum->Draw("same");
  gStyle->SetOptStat(false);
  
  plot->Update();
  canvas->cd(0);
  ratio->Draw();
  ratio->cd();

  TH1F* ratioF = (TH1F*)hist[5]->Clone("ratio");
  ratioF->Divide(sum);
  ratioF->SetTitle("data/MC");
  ratioF->Draw("P");
  ratioF->GetYaxis()->SetRangeUser(.7,1.3);
  ratio->Update();
  plot->cd();
  leg->Draw();
  plot->RedrawAxis();
  plot->Update();
  
  return(0);
}
