

/*
Attaching file DYroots/TT.root as _file2... very important
Attaching file DYroots/TTJets.root as _file4... very important
Attaching file DYroots/doubleEG.root as _file10...
Attaching file DYroots/dy.root as _file0...

  
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


*/
int StackPlot(TCanvas* canvas, THStack * hs, string xTitle, string drawOption, string cuts);
int StackPlot(TCanvas* canvas, THStack * hs, string xTitle, string drawOption, string cuts)
{
  canvas->SetGridx();
  canvas->SetGridy();
  
  TH1F* hist[4];
  TH1F* sum;
  int color[4] = {4,2,8,1};
  string titles[4] = {"DY","TT", "TTjets","data"};
  ((TTree*)_file0->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  hist[0] = (TH1F*)gPad->GetPrimitive("")->Clone("DY");
  ((TTree*)_file2->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  hist[1] = (TH1F*)gPad->GetPrimitive("")->Clone("TT");
  ((TTree*)_file4->Get("tagsDumper/trees/Background_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  hist[2] = (TH1F*)gPad->GetPrimitive("")->Clone("TTjets");
  ((TTree*)_file10->Get("tagsDumper/trees/DoubleEG_13TeV_VHMetTag"))->Draw(drawOption.c_str(),cuts.c_str());
  hist[3] = (TH1F*)gPad->GetPrimitive("")->Clone("data");

  //scale plots to account for similar shapes:
  
  for(int i=0;i<3;i++)
    {
      hist[i]->Scale(27.);
      hist[i]->SetTitle(titles[i].c_str());
      hist[i]->SetLineWidth(2);
      hist[i]->SetLineColor(color[i]);
      hist[i]->SetFillColor(color[i]);
      hist[i]->SetFillStyle(3001);
    }
  hist[0]->Scale(1.07);
  sum = (TH1F*)hist[0]->Clone("summed");
  sum->Add(hist[1]);
  sum->Add(hist[2]);
  sum->SetLineWidth(2);
  sum->SetLineColor(4);
  sum->SetTitle("error");
  sum->GetXaxis()->SetTitle(xTitle.c_str());
  sum->GetYaxis()->SetRangeUser(0,sum->GetMaximum()+sum->GetBinError(sum->GetMaximumBin()));
  
  hist[3]->SetLineWidth(2);
  hist[3]->SetTitle(titles[3].c_str());
  hist[3]->SetLineColor(color[3]);
  hist[3]->SetMarkerStyle(20);
  hist[3]->SetMarkerSize(3);
  sum->Draw();
  
  hs->Add(hist[0]);
  hs->Add(hist[1]);
  hs->Add(hist[2]);
  hs->Draw("HISTSAME");
  hist[3]->Draw("same");
  canvas->BuildLegend(.5,.67,.88,.88);

  return(0);
}
