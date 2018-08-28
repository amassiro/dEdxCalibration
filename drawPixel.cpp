//
// drawPixel
//
//
//   g++ -o drawPixel.exe drawPixel.cpp `root-config --cflags --glibs`
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
  
  
  std::vector<float> eta_edges;
  eta_edges.push_back(0.0);
  eta_edges.push_back(1.3);
  eta_edges.push_back(1.6);
  eta_edges.push_back(2.1);
  eta_edges.push_back(2.5);
  
  
  
  //---- read calibration values
  std::string fileCalibration = "calibration_eta.txt";
  if (argc>=4) {
    fileCalibration = argv[3];
  }
  
  std::vector< std::vector<float> > calibration_values;
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    std::vector<float> temp_calibration_values;
    for (int i=0; i<14; i++) {
      temp_calibration_values.push_back(1.0);
    }
    calibration_values.push_back (temp_calibration_values);
  }
  
  std::ifstream file (fileCalibration); 
  std::string buffer;
  float value;
  
  if(!file.is_open()) {
    std::cerr << "** ERROR: Can't open '" << fileCalibration << "' for input" << std::endl;
    return false;
  }
  
  int num_layer = 0;
  while(!file.eof()) {
    getline(file,buffer);
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end!
      std::stringstream line( buffer );      
      for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
      line >> value; 
      (calibration_values.at(iEdge)).at(num_layer) = value;
      }
      num_layer++;
    } 
  }
  
  
  for (int i=0; i<calibration_values.size(); i++) {
    for (int j=0; j<calibration_values.at(i).size(); j++) {
      std::cout << " [" << i << ", " << j << "] = " << calibration_values.at(i).at(j) << std::endl;
    }
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
  
  
  std::vector<int> detId;
  for (int idet = 0; idet<10; idet++) {
    detId.push_back(idet);
  }
  
  
  std::map< std::pair<int, int> , TH1F*> map_h_dedxById_data;

  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    for (int idet = 0; idet<detId.size(); idet++) {     
      std::pair<int, int> edge_det;
      edge_det.first = iEdge;
      edge_det.second = idet;
      
      TString name;      
      name = Form ("h_%d_%d_dedxById_data" , edge_det.first , edge_det.second);   
      TH1F* temp = new TH1F (name.Data(), "data", 400, 0, 10);  
      setupHisto(temp, 10);
      
      map_h_dedxById_data[edge_det] = temp;
    }
  }
  
  
  TH1F* h_mass_data [eta_edges.size()-1];
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    TString name;    
    name = Form ("h_%d_mass_data", iEdge);  
    h_mass_data[iEdge] = new TH1F (name.Data(), "data", 100, 86, 106);
    setupHisto(h_mass_data[iEdge], 10);  
  }
  
    
  for (int iEntry=0; iEntry<inputTree_data->GetEntries(); iEntry++) {
//   for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_data->GetEntry(iEntry);
    
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
      int best_track = -1;
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
    
        int iEdge = FindEdge (IsoTrack_eta[best_track], eta_edges);
        
        if (iEdge != -1) {
          
          //
          //   sizeXbyLayer is 0 for strips
          //                is != 0 for pixels
          //
          //   subDetIdByLayer is filled for strips and for pixels
          //                values: 0, 1, ... 5, 6, 7
          //
          
          
          std::pair<int, int> edge_det;
          edge_det.first = iEdge;
         
          if (IsoTrack_sizeXbyLayer0[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer0[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer0 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer1[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer1[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer1 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer2[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer2[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer2 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer3[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer3[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer3 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer4[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer4[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer4 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer5[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer5[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer5 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer6[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer6[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer6 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer7[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer7[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer7 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer8[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer8[best_track];
            map_h_dedxById_data[edge_det] ->Fill(IsoTrack_dedxByLayer8 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);
          h_mass_data[iEdge] -> Fill((track+muon).M());
          
        }
      }
    }
  }
  
  

  

  
  
  
  
  
  std::map< std::pair<int, int> , TH1F*> map_h_dedxById_mc;
  
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    for (int idet = 0; idet<detId.size(); idet++) {     
      std::pair<int, int> edge_det;
      edge_det.first = iEdge;
      edge_det.second = idet;
      
      TString name;      
      name = Form ("h_%d_%d_dedxById_mc" , edge_det.first , edge_det.second);   
      TH1F* temp = new TH1F (name.Data(), "mc", 400, 0, 10);  
      setupHisto(temp, 11);
      
      map_h_dedxById_mc[edge_det] = temp;
    }
  }
  
  
  TH1F* h_mass_mc [eta_edges.size()-1];
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    TString name;    
    name = Form ("h_%d_mass_mc", iEdge);  
    h_mass_mc[iEdge] = new TH1F (name.Data(), "mc", 100, 86, 106);
    setupHisto(h_mass_mc[iEdge], 11);  
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
      max_pt = 0;   
      int best_track = -1;
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
        
        int iEdge = FindEdge (IsoTrack_eta[best_track], eta_edges);
        
        if (iEdge != -1) {
          
          //
          //   sizeXbyLayer is 0 for strips
          //                is != 0 for pixels
          //
          //   subDetIdByLayer is filled for strips and for pixels
          //                values: 0, 1, ... 5, 6, 7
          //
          
          
          std::pair<int, int> edge_det;
          edge_det.first = iEdge;
          
          if (IsoTrack_sizeXbyLayer0[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer0[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer0 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer1[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer1[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer1 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer2[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer2[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer2 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer3[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer3[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer3 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer4[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer4[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer4 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer5[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer5[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer5 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer6[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer6[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer6 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer7[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer7[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer7 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          if (IsoTrack_sizeXbyLayer8[best_track] != 0) {           
            edge_det.second = IsoTrack_subDetIdByLayer8[best_track];
            map_h_dedxById_mc[edge_det] ->Fill(IsoTrack_dedxByLayer8 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  ); 
          }
          
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);
          h_mass_mc[iEdge] -> Fill((track+muon).M());
          
        }
      }
    }
  }
  
  
  
  
  
   
  
  
  
  TFile* fileOut = new TFile ("tocalibrate_complete_eta_edges_idet.root", "RECREATE");
 
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    for (int idet = 0; idet<detId.size(); idet++) {     
      std::pair<int, int> edge_det;
      edge_det.first = iEdge;
      edge_det.second = idet;
      map_h_dedxById_data[edge_det] -> Write();
      map_h_dedxById_mc[edge_det]   -> Write();
    }
  }
      
      
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      h_mass_data[iEdge]->Write();                                h_mass_mc[iEdge]->Write();
  }
  
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    
    TLegend* leg = new TLegend(0.70,0.70,0.90,0.90);
    leg->AddEntry(h_mass_data[iEdge],"data","pl");
    leg->AddEntry(h_mass_mc  [iEdge],"mc",  "pl");
    
    TString name;
    
    for (int idet = 0; idet<detId.size(); idet++) {     
      std::pair<int, int> edge_det;
      edge_det.first = iEdge;
      edge_det.second = idet;
      
      
      name = Form ("cc_summary_%d_%d" , iEdge, idet); 
      
      TCanvas* cc_summary = new TCanvas (name.Data(),"",1000,1000);
      
      map_h_dedxById_data[edge_det]->Draw("PL");
      map_h_dedxById_mc[edge_det]  ->Draw("PL same");
      
      map_h_dedxById_data[edge_det]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
      leg->Draw();
      
      cc_summary->Write();
    }
  }
  
    
  
  
  fileOut->Close();
  
}






