//
// prepareTree
//
//
//   g++ -o prepareTree.exe prepareTree.cpp `root-config --cflags --glibs`
//
//

#include <iostream>
#include <fstream>

#include "TTree.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TStyle.h"
  


int main(int argc, char** argv) {
  
  std::string name_input_file = "out.root";
  
  if (argc>=2) {
    name_input_file = argv[1];
  }
  
  std::string name_output_file = "out_new.root";
  
  if (argc>=3) {
    name_output_file = argv[2];
  }
  
  
  TFile* inputFile = new TFile (name_input_file.c_str(), "READ");   
  TTree* inputTree = (TTree*) ((TTree*) inputFile -> Get ("tree")) -> Clone ("tree");
  
  std::cout << " entries = " << inputTree->GetEntries() << std::endl;
  
//   
//   30 < pT < 50 GeV ; |η| < 2.4 
//   Passes tight ID selection ; rel. iso (Δβ corrected) < 0.15
//   
  
  const Int_t kMaxTracks = 1000;
  
  Float_t IsoTrack_pt[kMaxTracks];
  Float_t IsoTrack_eta[kMaxTracks];
  Float_t IsoTrack_phi[kMaxTracks];
  Float_t IsoTrack_dxy[kMaxTracks];
  Float_t IsoTrack_dz[kMaxTracks];
  Int_t IsoTrack_highPurity[kMaxTracks];
  Int_t nIsoTrack;
  
  Float_t IsoTrack_dedxByLayer0[kMaxTracks];
  Float_t IsoTrack_dedxByLayer1[kMaxTracks];
  Float_t IsoTrack_dedxByLayer2[kMaxTracks];
  Float_t IsoTrack_dedxByLayer3[kMaxTracks];
  Float_t IsoTrack_dedxByLayer4[kMaxTracks];
  Float_t IsoTrack_dedxByLayer5[kMaxTracks];
  Float_t IsoTrack_dedxByLayer6[kMaxTracks];
  Float_t IsoTrack_dedxByLayer7[kMaxTracks];
  Float_t IsoTrack_dedxByLayer8[kMaxTracks];
  Float_t IsoTrack_dedxByLayer9[kMaxTracks];
  Float_t IsoTrack_dedxByLayer10[kMaxTracks];
  Float_t IsoTrack_dedxByLayer11[kMaxTracks];
  Float_t IsoTrack_dedxByLayer12[kMaxTracks];
  Float_t IsoTrack_dedxByLayer13[kMaxTracks];
  
  
  
  inputTree->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
  inputTree->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  inputTree->SetBranchAddress("IsoTrack_phi",  IsoTrack_phi);
  inputTree->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);
  inputTree->SetBranchAddress("IsoTrack_dxy",  IsoTrack_dxy);
  inputTree->SetBranchAddress("IsoTrack_dz",  IsoTrack_dz);
  inputTree->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer0",   IsoTrack_dedxByLayer0);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer1",   IsoTrack_dedxByLayer1);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer2",   IsoTrack_dedxByLayer2);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer3",   IsoTrack_dedxByLayer3);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer4",   IsoTrack_dedxByLayer4);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer5",   IsoTrack_dedxByLayer5);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer6",   IsoTrack_dedxByLayer6);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer7",   IsoTrack_dedxByLayer7);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer8",   IsoTrack_dedxByLayer8);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer9",   IsoTrack_dedxByLayer9);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer10",  IsoTrack_dedxByLayer10);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer11",  IsoTrack_dedxByLayer11);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer12",  IsoTrack_dedxByLayer12);
  inputTree->SetBranchAddress("IsoTrack_dedxByLayer13",  IsoTrack_dedxByLayer13);
  
  
  TFile* outputFile = new TFile (name_output_file.c_str(), "RECREATE");   
  TTree *outputTree = new TTree("flatTree", "flatTree");
  
  Float_t tk_dedxl0;      outputTree->Branch("tk_dedxl0", &tk_dedxl0);
  Float_t tk_dedxl1;      outputTree->Branch("tk_dedxl1", &tk_dedxl1);
  Float_t tk_dedxl2;      outputTree->Branch("tk_dedxl2", &tk_dedxl2);
  Float_t tk_dedxl3;      outputTree->Branch("tk_dedxl3", &tk_dedxl3);
  
  
  Float_t min_pt = 5; //--- no soft tracks < 5 GeV !
  Float_t max_pt = -1;
  
  for (int iEntry=0; iEntry<inputTree->GetEntries(); iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree->GetEntry(iEntry);
     
    max_pt = -1;
    int best_track = -1;
    for (int iTrack = 0; iTrack < std::min(kMaxTracks, nIsoTrack); iTrack++) {
      if (
        IsoTrack_pt[iTrack] > min_pt &&
        IsoTrack_pt[iTrack] > max_pt &&
        IsoTrack_highPurity[iTrack] == 1 && 
        fabs(IsoTrack_dxy[iTrack]) < 0.02 &&
        fabs(IsoTrack_dz[iTrack]) < 0.5
      ) {
        
        best_track = iTrack;
        max_pt = IsoTrack_pt[iTrack] ;
        
        
      }
    }
    
    if (best_track != -1) {
      
      tk_dedxl0 = IsoTrack_dedxByLayer0[best_track];
      tk_dedxl1 = IsoTrack_dedxByLayer1[best_track];
      tk_dedxl2 = IsoTrack_dedxByLayer2[best_track];
      tk_dedxl3 = IsoTrack_dedxByLayer3[best_track];
      
      outputTree->Fill();     
    }
    
    
  }

  std::cout << " saved tracks = " << outputTree->GetEntries() << " out of: " << inputTree->GetEntries() << std::endl;
  
  outputTree->AutoSave();
    
  outputFile->Close();
  
}






