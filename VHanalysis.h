//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Jun  5 13:00:41 2016 by ROOT version 6.06/01
// from TTree VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_13TeV_all/VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_13TeV_all
// found on file: MetaData/work/testSig/output_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root
//////////////////////////////////////////////////////////

#ifndef VHanalysis_h
#define VHanalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class VHanalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   std::string inputFiles;
   std::string inputDirs;
   std::string inputTree;
   /***********PLOTS****************/
   TProfile *px;
   TProfile *py;
   TProfile *pxOLD;
   TProfile *pyOLD;
   TH1F *pfCorrSig;
   TH1F *pfCorrBkg;
   TH1F *DphiSig;
   TH1F *DphiBkg;
   TH1F *phiOLD;
   TH1F *phiNEW;
   
   TFile *output;
   
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           candidate_id;
   Float_t         weight;
   Float_t         dipho_sumpt;
   Float_t         dipho_pt;
   Float_t         dipho_cosphi;
   Float_t         mass;
   Float_t         phi;
   Float_t         leadPt;
   Float_t         leadEt;
   Float_t         leadEta;
   Float_t         leadPhi;
   Float_t         lead_sieie;
   Float_t         lead_oldhoe;
   Float_t         lead_hoe;
   Float_t         lead_sigmaEoE;
   Float_t         lead_ptoM;
   Float_t         leadR9;
   Float_t         subleadPt;
   Float_t         subleadEt;
   Float_t         subleadEta;
   Float_t         subleadPhi;
   Float_t         sublead_sieie;
   Float_t         sublead_oldhoe;
   Float_t         sublead_hoe;
   Float_t         sublead_sigmaEoE;
   Float_t         sublead_ptoM;
   Float_t         subleadR9;
   Float_t         leadIDMVA;
   Float_t         subleadIDMVA;
   Float_t         diPhoMVA;
   Float_t         pfMET_rawPt;
   Float_t         pfMET_rawPhi;
   Float_t         pfMET_rawSumEt;
   Float_t         pfMET_corPt;
   Float_t         pfMET_corPhi;
   Float_t         pfMET_corSumEt;
   Float_t         caloMET_rawPt;
   Float_t         caloMET_rawPhi;
   Float_t         caloMET_rawSumEt;
   Float_t         hasZ;
   Float_t         hasW;
   Float_t         VhasDaughters;
   Float_t         VhasNeutrinos;
   Float_t         VhasMissingLeptons;
   Float_t         genZ;
   Float_t         Vpt;
   Float_t         rho;
   ULong64_t       event;
   UInt_t          lumi;
   Int_t           processIndex;
   UInt_t          run;
   Int_t           nvtx;
   Float_t         npu;
   Float_t         puweight;

   // List of branches
   TBranch        *b_candidate_id;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_dipho_sumpt;   //!
   TBranch        *b_dipho_pt;   //!
   TBranch        *b_dipho_cosphi;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_leadPt;   //!
   TBranch        *b_leadEt;   //!
   TBranch        *b_leadEta;   //!
   TBranch        *b_leadPhi;   //!
   TBranch        *b_lead_sieie;   //!
   TBranch        *b_lead_oldhoe;   //!
   TBranch        *b_lead_hoe;   //!
   TBranch        *b_lead_sigmaEoE;   //!
   TBranch        *b_lead_ptoM;   //!
   TBranch        *b_leadR9;   //!
   TBranch        *b_subleadPt;   //!
   TBranch        *b_subleadEt;   //!
   TBranch        *b_subleadEta;   //!
   TBranch        *b_subleadPhi;   //!
   TBranch        *b_sublead_sieie;   //!
   TBranch        *b_sublead_oldhoe;   //!
   TBranch        *b_sublead_hoe;   //!
   TBranch        *b_sublead_sigmaEoE;   //!
   TBranch        *b_sublead_ptoM;   //!
   TBranch        *b_subleadR9;   //!
   TBranch        *b_leadIDMVA;   //!
   TBranch        *b_subleadIDMVA;   //!
   TBranch        *b_diPhoMVA;   //!
   TBranch        *b_pfMET_rawPt;   //!
   TBranch        *b_pfMET_rawPhi;   //!
   TBranch        *b_pfMET_rawSumEt;   //!
   TBranch        *b_pfMET_corPt;   //!
   TBranch        *b_pfMET_corPhi;   //!
   TBranch        *b_pfMET_corSumEt;   //!
   TBranch        *b_caloMET_rawPt;   //!
   TBranch        *b_caloMET_rawPhi;   //!
   TBranch        *b_caloMET_rawSumEt;   //!
   TBranch        *b_hasZ;   //!
   TBranch        *b_hasW;   //!
   TBranch        *b_VhasDaughters;   //!
   TBranch        *b_VhasNeutrinos;   //!
   TBranch        *b_VhasMissingLeptons;   //!
   TBranch        *b_genZ;   //!
   TBranch        *b_Vpt;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_processIndex;   //!
   TBranch        *b_run;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_puweight;   //!

   VHanalysis(string filename = "MetaData/work/testSig/output_VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8.root", TTree *tree=0);
   virtual ~VHanalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     WriteOut();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef VHanalysis_cxx
VHanalysis::VHanalysis(string filename, TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  inputFiles = filename;
  //inputTree = "VHToGG_M125_13TeV_amcatnloFXFX_madspin_pythia8_13TeV_all";
  std::size_t posA = inputFiles.find("output_"); 
  std::size_t posB = inputFiles.find(".root"); 
  inputTree = inputFiles.substr(posA+7,posB-posA-7);
  inputTree = inputTree+"_13TeV_all";
  std::cout << filename << std::endl;
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(inputFiles.c_str());
    if (!f || !f->IsOpen()) {
      f = new TFile(inputFiles.c_str());
    }
    inputDirs = inputFiles+":/vhEtTagDumper/trees";
    std::cout << "dirs: " << inputDirs << std::endl;
    TDirectory * dir = (TDirectory*)f->Get(inputDirs.c_str());
    dir->ls();
    std::cout << "tree " << inputTree << std::endl;
    dir->GetObject(inputTree.c_str(),tree);
  }
  Init(tree);
}

VHanalysis::WriteOut()
{
  output = new TFile("output.root");
  px->Write();
  py->Write();
  pxOLD->Write();
  pyOLD->Write();
  pfCorrSig->Write();
  pfCorrBkg->Write();
  DphiSig->Write();
  DphiBkg->Write();
  phiOLD->Write();
  phiNEW->Write();
  
}

VHanalysis::~VHanalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t VHanalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t VHanalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void VHanalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   
   px = new TProfile("px_vs_sumET","px_vs_sumET",100,0,500);
   py = new TProfile("py_vs_sumET","py_vs_sumET",100,0,500);
   pxOLD = new TProfile("px_vs_sumETold","px_vs_sumETold",100,0,500);
   pyOLD = new TProfile("py_vs_sumETold","py_vs_sumETold",100,0,500);
   pfCorrSig = new TH1F("pfCorrSig","pfCorrSig",200,0,200);
   pfCorrBkg = new TH1F("pfCorrBkg","pfCorrBkg",200,0,200);
   DphiSig = new TH1F("dPhiSig","PhiSig",35,0,7);
   DphiBkg = new TH1F("dPhiBkg","PhiBkg",35,0,7);
   phiOLD = new TH1F("phiOLD","phiOLD",35,-3.5,3.5);
   phiNEW = new TH1F("phiNEW","phiNEW",35,-3.5,3.5);
   
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("candidate_id", &candidate_id, &b_candidate_id);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("dipho_sumpt", &dipho_sumpt, &b_dipho_sumpt);
   fChain->SetBranchAddress("dipho_pt", &dipho_pt, &b_dipho_pt);
   fChain->SetBranchAddress("dipho_cosphi", &dipho_cosphi, &b_dipho_cosphi);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("leadPt", &leadPt, &b_leadPt);
   fChain->SetBranchAddress("leadEt", &leadEt, &b_leadEt);
   fChain->SetBranchAddress("leadEta", &leadEta, &b_leadEta);
   fChain->SetBranchAddress("leadPhi", &leadPhi, &b_leadPhi);
   fChain->SetBranchAddress("lead_sieie", &lead_sieie, &b_lead_sieie);
   fChain->SetBranchAddress("lead_oldhoe", &lead_oldhoe, &b_lead_oldhoe);
   fChain->SetBranchAddress("lead_hoe", &lead_hoe, &b_lead_hoe);
   fChain->SetBranchAddress("lead_sigmaEoE", &lead_sigmaEoE, &b_lead_sigmaEoE);
   fChain->SetBranchAddress("lead_ptoM", &lead_ptoM, &b_lead_ptoM);
   fChain->SetBranchAddress("leadR9", &leadR9, &b_leadR9);
   fChain->SetBranchAddress("subleadPt", &subleadPt, &b_subleadPt);
   fChain->SetBranchAddress("subleadEt", &subleadEt, &b_subleadEt);
   fChain->SetBranchAddress("subleadEta", &subleadEta, &b_subleadEta);
   fChain->SetBranchAddress("subleadPhi", &subleadPhi, &b_subleadPhi);
   fChain->SetBranchAddress("sublead_sieie", &sublead_sieie, &b_sublead_sieie);
   fChain->SetBranchAddress("sublead_oldhoe", &sublead_oldhoe, &b_sublead_oldhoe);
   fChain->SetBranchAddress("sublead_hoe", &sublead_hoe, &b_sublead_hoe);
   fChain->SetBranchAddress("sublead_sigmaEoE", &sublead_sigmaEoE, &b_sublead_sigmaEoE);
   fChain->SetBranchAddress("sublead_ptoM", &sublead_ptoM, &b_sublead_ptoM);
   fChain->SetBranchAddress("subleadR9", &subleadR9, &b_subleadR9);
   fChain->SetBranchAddress("leadIDMVA", &leadIDMVA, &b_leadIDMVA);
   fChain->SetBranchAddress("subleadIDMVA", &subleadIDMVA, &b_subleadIDMVA);
   fChain->SetBranchAddress("diPhoMVA", &diPhoMVA, &b_diPhoMVA);
   fChain->SetBranchAddress("pfMET_rawPt", &pfMET_rawPt, &b_pfMET_rawPt);
   fChain->SetBranchAddress("pfMET_rawPhi", &pfMET_rawPhi, &b_pfMET_rawPhi);
   fChain->SetBranchAddress("pfMET_rawSumEt", &pfMET_rawSumEt, &b_pfMET_rawSumEt);
   fChain->SetBranchAddress("pfMET_corPt", &pfMET_corPt, &b_pfMET_corPt);
   fChain->SetBranchAddress("pfMET_corPhi", &pfMET_corPhi, &b_pfMET_corPhi);
   fChain->SetBranchAddress("pfMET_corSumEt", &pfMET_corSumEt, &b_pfMET_corSumEt);
   fChain->SetBranchAddress("caloMET_rawPt", &caloMET_rawPt, &b_caloMET_rawPt);
   fChain->SetBranchAddress("caloMET_rawPhi", &caloMET_rawPhi, &b_caloMET_rawPhi);
   fChain->SetBranchAddress("caloMET_rawSumEt", &caloMET_rawSumEt, &b_caloMET_rawSumEt);
   fChain->SetBranchAddress("hasZ", &hasZ, &b_hasZ);
   fChain->SetBranchAddress("hasW", &hasW, &b_hasW);
   fChain->SetBranchAddress("VhasDaughters", &VhasDaughters, &b_VhasDaughters);
   fChain->SetBranchAddress("VhasNeutrinos", &VhasNeutrinos, &b_VhasNeutrinos);
   fChain->SetBranchAddress("VhasMissingLeptons", &VhasMissingLeptons, &b_VhasMissingLeptons);
   fChain->SetBranchAddress("genZ", &genZ, &b_genZ);
   fChain->SetBranchAddress("Vpt", &Vpt, &b_Vpt);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("processIndex", &processIndex, &b_processIndex);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("puweight", &puweight, &b_puweight);
   Notify();
}

Bool_t VHanalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void VHanalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t VHanalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef VHanalysis_cxx
