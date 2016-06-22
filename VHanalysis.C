#define VHanalysis_cxx
#include "VHanalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void VHanalysis::Loop()
{
//   In a ROOT session, you can do:
//      root> .L VHanalysis.C
//      root> VHanalysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   float px_0 = -2.104;
   float px_1 = -0.07336;
   float py_0 = 0.5667;
   float py_1 = -0.0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      float oldPx = pfMET_corPt*cos(pfMET_corPhi);
      float oldPy = pfMET_corPt*sin(pfMET_corPhi);



      
      //pxfit:
      //Chi2                      =       2195.7
      //NDf                       =           29
      //p0                        =     -1.15382   +/-   0.476161    
      //p1                        =   -0.0613663   +/-   0.0037346  
	
      //pyfit
      //Chi2                      =      22.2401
      //NDf                       =           21
      //p0                        =     0.906762   +/-   0.688286    
      //p1                        =    -0.040754   +/-   0.0395147
      
      pxOLD->Fill(pfMET_corSumEt,oldPx,weight);
      pyOLD->Fill(pfMET_corSumEt,oldPy,weight);
      
      
      float newPx = oldPx - (px_0 +px_1*pfMET_corSumEt);
      float newPy = oldPy - (py_0 +py_1*pfMET_corSumEt);
      //float newPy = oldPy - (1.71741 -0.0062300*pfMET_corSumEt);
      float newPhi=pfMET_corPhi;
      newPhi = atan(newPy/newPx); //px>0
      if(newPx<0&&newPy<0)
      	newPhi = -3.14159 + newPhi;
      else if(newPx<0&&newPy>=0)
      	newPhi = 3.14159 + newPhi;
      px->Fill(pfMET_corSumEt, newPx,weight);
      py->Fill(pfMET_corSumEt, newPy,weight);
      
      phiOLD->Fill(pfMET_corPhi,weight);
      phiNEW->Fill(newPhi,weight);
      
      if(hasZ&&VhasNeutrinos)
	{
	  pfCorrSig->Fill(pfMET_corPt,weight);
	  DphiSig->Fill(fabs(pfMET_corPhi-phi),weight);
	}
      else
	{
	  pfCorrBkg->Fill(pfMET_corPt,weight);
	  DphiBkg->Fill(fabs(pfMET_corPhi-phi),weight);
	}
      // if (Cut(ientry) < 0) continue;
   }
}
