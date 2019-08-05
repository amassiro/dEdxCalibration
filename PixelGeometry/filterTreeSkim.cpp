//
// filterTreeSkim
//
//
//   g++ -o filterTreeSkim.exe filterTreeSkim.cpp `root-config --cflags --glibs`
//
// 
//      - skim the tree to remove unneeded variables and speed up next steps
// 
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
//   IsoTrack_sizeXbyLayer2[0]:IsoTrack_subDetIdByLayer2[0]
//   
//   sizeXbyLayer is 0 for strips
//                is != 0 for pixels
//
//   subDetIdByLayer is filled for strips and for pixels
//                values: 0, 1, ... 5, 6, 7
//
  
  
  //---- muon
  const Int_t kMaxLepGood = 10;
  Float_t LepGood_pt[kMaxLepGood];
  Float_t LepGood_eta[kMaxLepGood];
  Float_t LepGood_phi[kMaxLepGood];
  Int_t LepGood_tightId[kMaxLepGood];
  Int_t   LepGood_pdgId[kMaxLepGood];
  Int_t nLepGood;
  
  
  inputTree->SetBranchAddress("LepGood_pt",  LepGood_pt);
  inputTree->SetBranchAddress("LepGood_eta",  LepGood_eta);
  inputTree->SetBranchAddress("LepGood_phi",  LepGood_phi);
  inputTree->SetBranchAddress("LepGood_tightId",  LepGood_tightId);
  inputTree->SetBranchAddress("LepGood_pdgId",  LepGood_pdgId);
  inputTree->SetBranchAddress("nLepGood",    &nLepGood);
  
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
  
  
  
  inputTree->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
  inputTree->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  inputTree->SetBranchAddress("IsoTrack_phi",  IsoTrack_phi);
  inputTree->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);
  inputTree->SetBranchAddress("IsoTrack_dxy",  IsoTrack_dxy);
  inputTree->SetBranchAddress("IsoTrack_dz",  IsoTrack_dz);
  inputTree->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  
//   
//   p T > 50 GeV ; |η| < 2.4 ; High purity track
//   |d xy | < 0.02 ; |d z | < 0.5
//   miniPFIsolation().chargedHadronIso() / p T < 1.0
//   EM energy around the track < 10 GeV ; Had energy around the track < 10 GeV
//   Mass(μ, track) between 86 and 106 GeV
//   
 
  //
  //---- disable all branches except the ones you want to keep
  //
  
  inputTree->SetBranchStatus("*",0);

  std::string variables_to_be_kept[] = {
    "run",
    "lumi",
    "evt",
// 
    "IsoTrack_pt",
    "IsoTrack_eta", 
    "IsoTrack_phi",
    "IsoTrack_highPurity",
    "IsoTrack_dxy",
    "IsoTrack_dz",
    "nIsoTrack",
//     
    "LepGood_pt",  
    "LepGood_eta", 
    "LepGood_phi", 
    "LepGood_tightId",  
    "LepGood_pdgId", 
    "nLepGood",  
//     
    "IsoTrack_layerOrSideByLayer*",  
    "IsoTrack_ladderOrBladeByLayer*",  
    "IsoTrack_dedxUnSmearedByLayer*",  
    "IsoTrack_dedxByLayer*",  
    "IsoTrack_pixByLayer*",  
    "IsoTrack_subDetIdByLayer*"
  };
  
  
  std::vector<std::string> std_variables_to_be_kept(variables_to_be_kept, variables_to_be_kept + sizeof(variables_to_be_kept)/sizeof(std::string));
  for(std::string itera : std_variables_to_be_kept) {
    inputTree->SetBranchStatus(itera.c_str(),1);
  }
  
  
  TFile* outputFile = new TFile (name_output_file.c_str(), "RECREATE");   
  TTree *outputTree = inputTree->CloneTree(0);
  
  
  int best_track; 
  outputTree->Branch("best_track",  &best_track, "best_track/I");
  
  
      
  for (int iEntry=0; iEntry<inputTree->GetEntries(); iEntry++) {
//   for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree->GetEntry(iEntry);
     
    best_track = -1;
    
    float max_pt = 0;
    int best_iMuon = -1;
    //---- muon
    for (int iMuon = 0; iMuon < std::min(kMaxLepGood, nLepGood); iMuon++) {
      if (LepGood_pdgId[iMuon] == 13 && LepGood_tightId[iMuon] == 1 && LepGood_pt[iMuon] > max_pt && fabs(LepGood_eta[iMuon])<2.4) {
        max_pt = LepGood_pt[iMuon];
        best_iMuon = iMuon;
      }
    }
    
    if (best_iMuon != -1) {
      TLorentzVector muon;
      muon.SetPtEtaPhiM(LepGood_pt[best_iMuon], LepGood_eta[best_iMuon], LepGood_phi[best_iMuon], 0);
       
      //---- tracks
      max_pt = 0;   
      best_track = -1;
      for (int iTrack = 0; iTrack < std::min(kMaxTracks, nIsoTrack); iTrack++) {
        if (
          IsoTrack_pt[iTrack] > max_pt &&
          IsoTrack_highPurity[iTrack] == 1 && 
          fabs(IsoTrack_dxy[iTrack]) < 0.02 &&
          fabs(IsoTrack_dz[iTrack]) < 0.5
        ) {
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[iTrack], IsoTrack_eta[iTrack], IsoTrack_phi[iTrack], 0);
          
          float mass_mu_track = (track+muon).M();
          
          if (mass_mu_track > 86 && mass_mu_track < 106) {
            best_track = iTrack;
            max_pt = IsoTrack_pt[iTrack];
          }
        }
      }
      if (best_track != -1) {
        outputTree->Fill();     
      }
    }
    
  }
  
  std::cout << " saved entries = " << outputTree->GetEntries() << " out of: " << inputTree->GetEntries() << std::endl;
  
  outputTree->AutoSave();
    
  outputFile->Close();
  
}






