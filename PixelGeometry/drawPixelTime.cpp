//
// drawPixelTime
//
//
//   g++ -o drawPixelTime.exe drawPixelTime.cpp `root-config --cflags --glibs`
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
  
  

int FindInterval(int run, int minRun, int deltaRun) {
  
  return int ((run - minRun) / deltaRun);
  
}


void Normalize(TH1F* histo) {
  
  float integral = histo->Integral();
  if (integral != 0) {
    histo-> Scale (1./integral);
  }
}

  
void setupHisto(TH1F* histo, int icolor) {
  
  Color_t* color = new Color_t [200];
  color[0] = kAzure; //kRed ;
  color[1] = kAzure + 10 ;
  color[2] = kYellow + 2 ;
  color[3] = kGreen ;
  color[4] = kGreen + 4 ;
  color[5] = kBlue ;
  color[6] = kCyan ;
  color[7] = kPink + 1 ;
  color[8] = kBlack ;
  color[9] = kYellow + 4 ;
  color[10]= kRed ;
  for (int i=0; i<30; i++) {
    color[i+11] = kBlue + i;
  }
  
  
  histo->SetLineColor(color[icolor]);
  histo->SetMarkerColor(color[icolor]);
  histo->SetMarkerSize(1);
  histo->SetMarkerStyle(20+icolor);
}


//---- find the eta range bin corresponding to the "eta" value
int FindEdge (float eta, std::vector<float> eta_edges) {
  
  int ieta = -1;
  
  for (int iEdge = 0; iEdge<(eta_edges.size()-1); iEdge++) {
    if (eta >= eta_edges.at(iEdge) && eta < eta_edges.at(iEdge+1)) {
      ieta = iEdge;
    }
  }
  
  return ieta;
}



//---- find the eta range bin corresponding to the "eta" value
//----  |eta|
int FindEdgeAbs (float eta, std::vector<float> eta_edges) {
  
  int ieta = -1;
  
  for (int iEdge = 0; iEdge<(eta_edges.size()-1); iEdge++) {
    if (fabs(eta) >= eta_edges.at(iEdge) && fabs(eta) < eta_edges.at(iEdge+1)) {
      ieta = iEdge;
    }
  }
  
  return ieta;
}



int main(int argc, char** argv) {
  
  std::string name_input_file_data = "out.root";
  
  if (argc>=2) {
    name_input_file_data = argv[1];
  }
  
  std::string name_input_file_mc = "outmc.root";
  
  if (argc>=3) {
    name_input_file_mc = argv[2];
  }
  
  
  
  int num_run_intervals = 10;
  if (argc>=4) {
    num_run_intervals = atoi(argv[3]);
  }
  
  
  
  
  std::vector<float> eta_edges;
  eta_edges.push_back(2.5);
  eta_edges.push_back(2.1);
  eta_edges.push_back(1.6);
  eta_edges.push_back(1.3);
  eta_edges.push_back(1.0);
  eta_edges.push_back(0.6);
  eta_edges.push_back(0.3);

  eta_edges.push_back(0.0);

  eta_edges.push_back(0.3);
  eta_edges.push_back(0.6);
  eta_edges.push_back(1.0);
  eta_edges.push_back(1.3);
  eta_edges.push_back(1.6);
  eta_edges.push_back(2.1);
  eta_edges.push_back(2.5);
  
  
  //---- BPIX vs FPIX
  std::vector<int> detId;
  for (int idet = 0; idet<2; idet++) {
    detId.push_back(idet);
  }
  
  //---- 
  //---- layer in BPIX [0 --> 4]
  //---- disk in FPIX  [4 --> 20 [14?] ??]
  //----
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<20; ilayer++) {
    layerId.push_back(ilayer);
  }
  
  
  
  
  
  
  std::cout << " eta_edges :: " << eta_edges.size() << std::endl;
  
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    std::cout << " eta_edges[" << iEdge << "] = " << eta_edges.at(iEdge) << std::endl;
  }
  
  std::cout << " name_input_file_data = " << name_input_file_data << std::endl;
  std::cout << " name_input_file_mc   = " << name_input_file_mc << std::endl;
  
  TFile* inputFile_data = new TFile (name_input_file_data.c_str(), "READ");   
  TTree* inputTree_data = (TTree*) ((TTree*) inputFile_data -> Get ("tree")) -> Clone ("tree_data");
  
  TFile* inputFile_mc = new TFile (name_input_file_mc.c_str(), "READ");   
  TTree* inputTree_mc = (TTree*) ((TTree*) inputFile_mc -> Get ("tree")) -> Clone ("tree_mc");
  
  std::cout << " data = " << inputTree_data->GetEntries() << std::endl;
  std::cout << " mc   = " << inputTree_mc->GetEntries()   << std::endl;
  
  gStyle->SetOptStat(0);
  
  
//   
//   IsoTrack_sizeXbyLayer2[0]:IsoTrack_subDetIdByLayer2[0]
//   
//   sizeXbyLayer is 0 for strips
//                is != 0 for pixels
//
//   subDetIdByLayer is filled for strips and for pixels
//                values: 0, 1, ... 5, 6, 7
//
  
  
  //---- best track
  
  int best_track;
  inputTree_data->SetBranchAddress("best_track",    &best_track);
  inputTree_mc  ->SetBranchAddress("best_track",    &best_track);
  
  
  //---- muon
  const Int_t kMaxLepGood = 10;
  Float_t LepGood_pt[kMaxLepGood];
  Float_t LepGood_eta[kMaxLepGood];
  Float_t LepGood_phi[kMaxLepGood];
  Int_t LepGood_tightId[kMaxLepGood];
  Int_t   LepGood_pdgId[kMaxLepGood];
  Int_t nLepGood;
  
  
  inputTree_data->SetBranchAddress("LepGood_pt",  LepGood_pt);
  inputTree_mc  ->SetBranchAddress("LepGood_pt",  LepGood_pt);
  inputTree_data->SetBranchAddress("LepGood_eta",  LepGood_eta);
  inputTree_mc  ->SetBranchAddress("LepGood_eta",  LepGood_eta);
  inputTree_data->SetBranchAddress("LepGood_phi",  LepGood_phi);
  inputTree_mc  ->SetBranchAddress("LepGood_phi",  LepGood_phi);
  inputTree_data->SetBranchAddress("LepGood_tightId",  LepGood_tightId);
  inputTree_mc  ->SetBranchAddress("LepGood_tightId",  LepGood_tightId);
  inputTree_data->SetBranchAddress("LepGood_pdgId",  LepGood_pdgId);
  inputTree_mc  ->SetBranchAddress("LepGood_pdgId",  LepGood_pdgId);
  inputTree_data->SetBranchAddress("nLepGood",    &nLepGood);
  inputTree_mc  ->SetBranchAddress("nLepGood",    &nLepGood);
  
//   
//   30 < pT < 50 GeV ; |η| < 2.4 
//   Passes tight ID selection ; rel. iso (Δβ corrected) < 0.15
//   
  
  
  //   IsoTrack_dedxByLayer0
  const Int_t kMaxTracks = 1000;
  
  Float_t IsoTrack_layerPixelByLayer0[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer1[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer2[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer3[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer4[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer5[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer6[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer7[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer8[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer9[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer10[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer11[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer12[kMaxTracks];
  Float_t IsoTrack_layerPixelByLayer13[kMaxTracks];
  
  
  Float_t IsoTrack_diskPixelByLayer0[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer1[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer2[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer3[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer4[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer5[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer6[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer7[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer8[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer9[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer10[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer11[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer12[kMaxTracks];
  Float_t IsoTrack_diskPixelByLayer13[kMaxTracks];
  


  
  
  
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

  Int_t IsoTrack_sizeXbyLayer0[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer1[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer2[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer3[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer4[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer5[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer6[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer7[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer8[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer9[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer10[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer11[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer12[kMaxTracks];
  Int_t IsoTrack_sizeXbyLayer13[kMaxTracks];
  
  Int_t IsoTrack_subDetIdByLayer0[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer1[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer2[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer3[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer4[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer5[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer6[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer7[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer8[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer9[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer10[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer11[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer12[kMaxTracks];
  Int_t IsoTrack_subDetIdByLayer13[kMaxTracks];
  
  
  
  Float_t IsoTrack_pt[kMaxTracks];
  Float_t IsoTrack_eta[kMaxTracks];
  Float_t IsoTrack_phi[kMaxTracks];
  Float_t IsoTrack_dxy[kMaxTracks];
  Float_t IsoTrack_dz[kMaxTracks];
  Int_t IsoTrack_highPurity[kMaxTracks];
  Int_t nIsoTrack;

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer0",  IsoTrack_dedxByLayer0);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer0",  IsoTrack_dedxByLayer0);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer1",  IsoTrack_dedxByLayer1);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer1",  IsoTrack_dedxByLayer1);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer2",  IsoTrack_dedxByLayer2);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer2",  IsoTrack_dedxByLayer2);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer3",  IsoTrack_dedxByLayer3);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer3",  IsoTrack_dedxByLayer3);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer4",  IsoTrack_dedxByLayer4);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer4",  IsoTrack_dedxByLayer4);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer5",  IsoTrack_dedxByLayer5);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer5",  IsoTrack_dedxByLayer5);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer6",  IsoTrack_dedxByLayer6);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer6",  IsoTrack_dedxByLayer6);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer7",  IsoTrack_dedxByLayer7);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer7",  IsoTrack_dedxByLayer7);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer8",  IsoTrack_dedxByLayer8);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer8",  IsoTrack_dedxByLayer8);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer9",  IsoTrack_dedxByLayer9);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer9",  IsoTrack_dedxByLayer9);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer10",  IsoTrack_dedxByLayer10);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer10",  IsoTrack_dedxByLayer10);               
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer11",  IsoTrack_dedxByLayer11);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer11",  IsoTrack_dedxByLayer11);               
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer12",  IsoTrack_dedxByLayer12);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer12",  IsoTrack_dedxByLayer12);               
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer13",  IsoTrack_dedxByLayer13);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer13",  IsoTrack_dedxByLayer13);               
  
  
  
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer0",  IsoTrack_sizeXbyLayer0);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer0",  IsoTrack_sizeXbyLayer0);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer1",  IsoTrack_sizeXbyLayer1);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer1",  IsoTrack_sizeXbyLayer1);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer2",  IsoTrack_sizeXbyLayer2);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer2",  IsoTrack_sizeXbyLayer2);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer3",  IsoTrack_sizeXbyLayer3);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer3",  IsoTrack_sizeXbyLayer3);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer4",  IsoTrack_sizeXbyLayer4);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer4",  IsoTrack_sizeXbyLayer4);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer5",  IsoTrack_sizeXbyLayer5);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer5",  IsoTrack_sizeXbyLayer5);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer6",  IsoTrack_sizeXbyLayer6);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer6",  IsoTrack_sizeXbyLayer6);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer7",  IsoTrack_sizeXbyLayer7);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer7",  IsoTrack_sizeXbyLayer7);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer8",  IsoTrack_sizeXbyLayer8);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer8",  IsoTrack_sizeXbyLayer8);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer9",  IsoTrack_sizeXbyLayer9);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer9",  IsoTrack_sizeXbyLayer9);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer10",  IsoTrack_sizeXbyLayer10);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer10",  IsoTrack_sizeXbyLayer10);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer11",  IsoTrack_sizeXbyLayer11);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer11",  IsoTrack_sizeXbyLayer11);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer12",  IsoTrack_sizeXbyLayer12);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer12",  IsoTrack_sizeXbyLayer12);
  
  inputTree_data->SetBranchAddress("IsoTrack_sizeXbyLayer13",  IsoTrack_sizeXbyLayer13);
  inputTree_mc  ->SetBranchAddress("IsoTrack_sizeXbyLayer13",  IsoTrack_sizeXbyLayer13);
  
  
  
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer0",  IsoTrack_layerPixelByLayer0);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer0",  IsoTrack_layerPixelByLayer0);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer1",  IsoTrack_layerPixelByLayer1);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer1",  IsoTrack_layerPixelByLayer1);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer2",  IsoTrack_layerPixelByLayer2);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer2",  IsoTrack_layerPixelByLayer2);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer3",  IsoTrack_layerPixelByLayer3);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer3",  IsoTrack_layerPixelByLayer3);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer4",  IsoTrack_layerPixelByLayer4);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer4",  IsoTrack_layerPixelByLayer4);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer5",  IsoTrack_layerPixelByLayer5);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer5",  IsoTrack_layerPixelByLayer5);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer6",  IsoTrack_layerPixelByLayer6);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer6",  IsoTrack_layerPixelByLayer6);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer7",  IsoTrack_layerPixelByLayer7);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer7",  IsoTrack_layerPixelByLayer7);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer8",  IsoTrack_layerPixelByLayer8);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer8",  IsoTrack_layerPixelByLayer8);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer9",  IsoTrack_layerPixelByLayer9);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer9",  IsoTrack_layerPixelByLayer9);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer10",  IsoTrack_layerPixelByLayer10);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer10",  IsoTrack_layerPixelByLayer10);               
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer11",  IsoTrack_layerPixelByLayer11);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer11",  IsoTrack_layerPixelByLayer11);               
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer12",  IsoTrack_layerPixelByLayer12);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer12",  IsoTrack_layerPixelByLayer12);               
  
  inputTree_data->SetBranchAddress("IsoTrack_layerPixelByLayer13",  IsoTrack_layerPixelByLayer13);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerPixelByLayer13",  IsoTrack_layerPixelByLayer13);               
  
  
  
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer0",  IsoTrack_diskPixelByLayer0);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer0",  IsoTrack_diskPixelByLayer0);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer1",  IsoTrack_diskPixelByLayer1);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer1",  IsoTrack_diskPixelByLayer1);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer2",  IsoTrack_diskPixelByLayer2);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer2",  IsoTrack_diskPixelByLayer2);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer3",  IsoTrack_diskPixelByLayer3);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer3",  IsoTrack_diskPixelByLayer3);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer4",  IsoTrack_diskPixelByLayer4);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer4",  IsoTrack_diskPixelByLayer4);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer5",  IsoTrack_diskPixelByLayer5);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer5",  IsoTrack_diskPixelByLayer5);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer6",  IsoTrack_diskPixelByLayer6);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer6",  IsoTrack_diskPixelByLayer6);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer7",  IsoTrack_diskPixelByLayer7);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer7",  IsoTrack_diskPixelByLayer7);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer8",  IsoTrack_diskPixelByLayer8);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer8",  IsoTrack_diskPixelByLayer8);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer9",  IsoTrack_diskPixelByLayer9);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer9",  IsoTrack_diskPixelByLayer9);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer10",  IsoTrack_diskPixelByLayer10);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer10",  IsoTrack_diskPixelByLayer10);               
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer11",  IsoTrack_diskPixelByLayer11);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer11",  IsoTrack_diskPixelByLayer11);               
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer12",  IsoTrack_diskPixelByLayer12);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer12",  IsoTrack_diskPixelByLayer12);               
  
  inputTree_data->SetBranchAddress("IsoTrack_diskPixelByLayer13",  IsoTrack_diskPixelByLayer13);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_diskPixelByLayer13",  IsoTrack_diskPixelByLayer13);               
  
  
  
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer0",  IsoTrack_subDetIdByLayer0);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer0",  IsoTrack_subDetIdByLayer0);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer1",  IsoTrack_subDetIdByLayer1);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer1",  IsoTrack_subDetIdByLayer1);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer2",  IsoTrack_subDetIdByLayer2);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer2",  IsoTrack_subDetIdByLayer2);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer3",  IsoTrack_subDetIdByLayer3);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer3",  IsoTrack_subDetIdByLayer3);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer4",  IsoTrack_subDetIdByLayer4);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer4",  IsoTrack_subDetIdByLayer4);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer5",  IsoTrack_subDetIdByLayer5);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer5",  IsoTrack_subDetIdByLayer5);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer6",  IsoTrack_subDetIdByLayer6);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer6",  IsoTrack_subDetIdByLayer6);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer7",  IsoTrack_subDetIdByLayer7);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer7",  IsoTrack_subDetIdByLayer7);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer8",  IsoTrack_subDetIdByLayer8);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer8",  IsoTrack_subDetIdByLayer8);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer9",  IsoTrack_subDetIdByLayer9);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer9",  IsoTrack_subDetIdByLayer9);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer10",  IsoTrack_subDetIdByLayer10);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer10",  IsoTrack_subDetIdByLayer10);               
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer11",  IsoTrack_subDetIdByLayer11);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer11",  IsoTrack_subDetIdByLayer11);               
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer12",  IsoTrack_subDetIdByLayer12);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer12",  IsoTrack_subDetIdByLayer12);               
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer13",  IsoTrack_subDetIdByLayer13);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_subDetIdByLayer13",  IsoTrack_subDetIdByLayer13);               
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
 
  inputTree_data->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  inputTree_mc  ->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  
  inputTree_data->SetBranchAddress("IsoTrack_phi",  IsoTrack_phi);
  inputTree_mc  ->SetBranchAddress("IsoTrack_phi",  IsoTrack_phi);
  
  inputTree_data->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);
  inputTree_mc  ->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);

  inputTree_data->SetBranchAddress("IsoTrack_dxy",  IsoTrack_dxy);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dxy",  IsoTrack_dxy);

  inputTree_data->SetBranchAddress("IsoTrack_dz",  IsoTrack_dz);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dz",  IsoTrack_dz);
  
  inputTree_data->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  inputTree_mc  ->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  
//   
//   p T > 50 GeV ; |η| < 2.4 ; High purity track
//   |d xy | < 0.02 ; |d z | < 0.5
//   miniPFIsolation().chargedHadronIso() / p T < 1.0
//   EM energy around the track < 10 GeV ; Had energy around the track < 10 GeV
//   Mass(μ, track) between 86 and 106 GeV
//   
  
  
  UInt_t run;
  inputTree_data->SetBranchAddress("run",    &run);
  
  
  
  //---- a vector for the different run-ranges
  std::vector< std::map < int, std::map< std::pair<int, int> , TH1F*> > >  vector_map_h_dedxById_data;
  
  for (int iRun =0; iRun < (num_run_intervals+1); iRun++) {
  
  //----     layer                   eta   det
  std::map < int, std::map< std::pair<int, int> , TH1F*> > map_h_dedxById_data;
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    std::map< std::pair<int, int> , TH1F*> mini_map_h_dedxById_data;
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int idet = 0; idet<detId.size(); idet++) {     
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
        TString name;      
        name = Form ("h_%d_%d_%d_%d_dedxById_data" , iRun, ilayer, edge_det.first , edge_det.second);   
        TH1F* temp = new TH1F (name.Data(), "data", 100, 0, 10);  
        setupHisto(temp, iRun);
        
        mini_map_h_dedxById_data[edge_det] = temp;
      }
    }
    map_h_dedxById_data[ilayer] = mini_map_h_dedxById_data;
  }
  
  vector_map_h_dedxById_data.push_back (map_h_dedxById_data);
  }
  
  
  int minRun = inputTree_data->GetMinimum ("run");
  int maxRun = inputTree_data->GetMaximum ("run") + 1;
  int deltaRun = (maxRun-minRun) / num_run_intervals;
  
  std::cout << " minRun = " << minRun << std::endl;
  std::cout << " maxRun = " << maxRun << std::endl;
  std::cout << " deltaRun = " << deltaRun << std::endl;
  std::cout << " vector_map_h_dedxById_data.size() = " << vector_map_h_dedxById_data.size() << std::endl;
  
  
  
  for (int iEntry=0; iEntry<inputTree_data->GetEntries(); iEntry++) {
//   for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_data->GetEntry(iEntry);
  
    
    int iRun = FindInterval(run, minRun, deltaRun);
    //---- safe check
    if (iRun >= num_run_intervals) {
      std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
      continue;      
    }
    
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
      //
      //       best_track read from tree
      //
      
      if (best_track != -1) {
    
        int iEdge = FindEdge (IsoTrack_eta[best_track], eta_edges);
        
        if (iEdge != -1) {
          
          //
          //   sizeXbyLayer is 0 for strips
          //                is != 0 for pixels
          //
          
          
          std::pair<int, int> edge_det;
          edge_det.first = iEdge;
          
          if (IsoTrack_sizeXbyLayer0[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer0[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_layerPixelByLayer0[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer0 [best_track]    ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_diskPixelByLayer0[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer0 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer1[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer1[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_layerPixelByLayer1[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer1 [best_track]    ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_diskPixelByLayer1[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer1 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer2[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer2[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_layerPixelByLayer2[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer2 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_diskPixelByLayer2[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer2 [best_track]  ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer3[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer3[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_layerPixelByLayer3[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer3 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_diskPixelByLayer3[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer3 [best_track]  ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer4[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer4[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_layerPixelByLayer4[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer4 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_diskPixelByLayer4[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer4 [best_track]  ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer5[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer5[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_layerPixelByLayer5[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer5 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_diskPixelByLayer5[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer5 [best_track]  ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer6[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer6[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_layerPixelByLayer6[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer6 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              ((vector_map_h_dedxById_data[iRun])[ IsoTrack_diskPixelByLayer6[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer6 [best_track]  ); 
            }
          }
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);          
        }
      }
    }
  }
  
  
  
  
  
  
  
  
  
  
  
  std::map < int, std::map< std::pair<int, int> , TH1F*> > map_h_dedxById_mc;
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    std::map< std::pair<int, int> , TH1F*> mini_map_h_dedxById_mc;
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int idet = 0; idet<detId.size(); idet++) {     
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
        TString name;      
        name = Form ("h_%d_%d_%d_dedxById_mc" , ilayer, edge_det.first , edge_det.second);   
        TH1F* temp = new TH1F (name.Data(), "mc", 100, 0, 10);  
        setupHisto(temp, 11);
        
        mini_map_h_dedxById_mc[edge_det] = temp;
      }
    }
    map_h_dedxById_mc[ilayer] = mini_map_h_dedxById_mc;
  }
  
  
  for (int iEntry=0; iEntry<inputTree_mc->GetEntries(); iEntry++) {
    //   for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_mc->GetEntry(iEntry);
    
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
      //---- tracks
      //
      //       best_track read from tree
      //

      if (best_track != -1) {
        
        int iEdge = FindEdge (IsoTrack_eta[best_track], eta_edges);
        
        if (iEdge != -1) {
          
          //
          //   sizeXbyLayer is 0 for strips
          //                is != 0 for pixels
          //
          
          
          std::pair<int, int> edge_det;
          edge_det.first = iEdge;
          
          if (IsoTrack_sizeXbyLayer0[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer0[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              (map_h_dedxById_mc[ IsoTrack_layerPixelByLayer0[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer0 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              (map_h_dedxById_mc[ IsoTrack_diskPixelByLayer0[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer0 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer1[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer1[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              (map_h_dedxById_mc[ IsoTrack_layerPixelByLayer1[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer1 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              (map_h_dedxById_mc[ IsoTrack_diskPixelByLayer1[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer1 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer2[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer2[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              (map_h_dedxById_mc[ IsoTrack_layerPixelByLayer2[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer2 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              (map_h_dedxById_mc[ IsoTrack_diskPixelByLayer2[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer2 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer3[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer3[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              (map_h_dedxById_mc[ IsoTrack_layerPixelByLayer3[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer3 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              (map_h_dedxById_mc[ IsoTrack_diskPixelByLayer3[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer3 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer4[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer4[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              (map_h_dedxById_mc[ IsoTrack_layerPixelByLayer4[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer4 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              (map_h_dedxById_mc[ IsoTrack_diskPixelByLayer4[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer4 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer5[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer5[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              (map_h_dedxById_mc[ IsoTrack_layerPixelByLayer5[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer5 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              (map_h_dedxById_mc[ IsoTrack_diskPixelByLayer5[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer5 [best_track]   ); 
            }
          }
          
          if (IsoTrack_sizeXbyLayer6[best_track] != 0) {  
            if (IsoTrack_layerPixelByLayer6[best_track] > -10) {
              //---- BPIX
              edge_det.second = 0;
              (map_h_dedxById_mc[ IsoTrack_layerPixelByLayer6[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer6 [best_track]   ); 
            }
            else {
              //---- FPIX
              edge_det.second = 1;
              (map_h_dedxById_mc[ IsoTrack_diskPixelByLayer6[best_track] ])[edge_det] ->Fill(IsoTrack_dedxByLayer6 [best_track]   ); 
            }
          }
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);
          
        }
      }
    }
  }
  
  
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int idet = 0; idet<detId.size(); idet++) {  
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
          Normalize((vector_map_h_dedxById_data[iRun])[ilayer][edge_det]);
        }  
        Normalize(map_h_dedxById_mc[ilayer][edge_det]);
      }
    }
  }
  
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    
    TString name;
    
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
      
      name = Form ("cc_summary_layer_%d_eta_%d" , ilayer, iEdge); 
      TCanvas* cc_summary_ieta = new TCanvas (name.Data(),"",1400,700);
      cc_summary_ieta->Divide(detId.size(), 1);
      
      for (int idet = 0; idet<detId.size(); idet++) {     
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
     
        TLegend* leg = new TLegend(0.50,0.70,0.90,0.90);
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
          std::string name = " data [" + std::to_string(minRun+iRun*deltaRun) + " , " + std::to_string(minRun+(iRun+1)*deltaRun) + "] "; 
          leg->AddEntry((vector_map_h_dedxById_data[iRun])[ilayer][edge_det],name.c_str(),"pl");
        }
        leg->AddEntry(map_h_dedxById_mc[ilayer][edge_det], "mc",  "pl");
        
        
        name = Form ("cc_bin_%d_%d_%d" , ilayer, iEdge, idet); 
        
        TCanvas* cc_summary = new TCanvas (name.Data(),"",1000,1000);
        
        map_h_dedxById_mc[ilayer][edge_det]  ->Draw("PL");
        for (int iRun =0; iRun < num_run_intervals; iRun++) { 
          (vector_map_h_dedxById_data[iRun])[ilayer][edge_det]->Draw("PL same");
        }
        map_h_dedxById_mc[ilayer][edge_det]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
        leg->Draw();
        
//         cc_summary->Write();
        
        
        cc_summary_ieta->cd(idet+1);
        map_h_dedxById_mc[ilayer][edge_det]  ->Draw("PL");
        for (int iRun =0; iRun < num_run_intervals; iRun++) { 
          (vector_map_h_dedxById_data[iRun])[ilayer][edge_det]->Draw("PL same");
        }
        
        map_h_dedxById_mc[ilayer][edge_det]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
        leg->Draw();
          
      }
      
//       cc_summary_ieta->Write();
      name = Form ("plots_run/cc_summary_layer_%d_eta_%d.png" , ilayer, iEdge); 
      cc_summary_ieta->SaveAs(name.Data());
      
    }
  }
  
    
  
}







