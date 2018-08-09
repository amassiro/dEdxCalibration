//
// draw
//
//
//   g++ -o draw.exe draw.cpp `root-config --cflags --glibs`
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
  
  
  TH1F* h_dedxByLayer0_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer1_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer2_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer3_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer4_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer5_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer6_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer7_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer8_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer9_data  [eta_edges.size()-1];
  TH1F* h_dedxByLayer10_data [eta_edges.size()-1];
  TH1F* h_dedxByLayer11_data [eta_edges.size()-1];
  TH1F* h_dedxByLayer12_data [eta_edges.size()-1];
  TH1F* h_dedxByLayer13_data [eta_edges.size()-1];
  
  TH1F* h_mass_data [eta_edges.size()-1];
  
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    
    TString name;
    
    name = Form ("h_%d_dedxByLayer0_data" , iEdge);      h_dedxByLayer0_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer0_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer1_data" , iEdge);      h_dedxByLayer1_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer1_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer2_data" , iEdge);      h_dedxByLayer2_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer2_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer3_data" , iEdge);      h_dedxByLayer3_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer3_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer4_data" , iEdge);      h_dedxByLayer4_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer4_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer5_data" , iEdge);      h_dedxByLayer5_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer5_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer6_data" , iEdge);      h_dedxByLayer6_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer6_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer7_data" , iEdge);      h_dedxByLayer7_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer7_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer8_data" , iEdge);      h_dedxByLayer8_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer8_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer9_data" , iEdge);      h_dedxByLayer9_data [iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer9_data [iEdge], 10);
    name = Form ("h_%d_dedxByLayer10_data", iEdge);      h_dedxByLayer10_data[iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer10_data[iEdge], 10);
    name = Form ("h_%d_dedxByLayer11_data", iEdge);      h_dedxByLayer11_data[iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer11_data[iEdge], 10);
    name = Form ("h_%d_dedxByLayer12_data", iEdge);      h_dedxByLayer12_data[iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer12_data[iEdge], 10);
    name = Form ("h_%d_dedxByLayer13_data", iEdge);      h_dedxByLayer13_data[iEdge] = new TH1F (name.Data(), "data", 2000, 0, 10);         setupHisto(h_dedxByLayer13_data[iEdge], 10);
      
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
          
          h_dedxByLayer0_data [iEdge]->Fill(IsoTrack_dedxByLayer0 [best_track]      *   (calibration_values.at(iEdge)).at(0 )  );
          h_dedxByLayer1_data [iEdge]->Fill(IsoTrack_dedxByLayer1 [best_track]      *   (calibration_values.at(iEdge)).at(1 )  );
          h_dedxByLayer2_data [iEdge]->Fill(IsoTrack_dedxByLayer2 [best_track]      *   (calibration_values.at(iEdge)).at(2 )  );
          h_dedxByLayer3_data [iEdge]->Fill(IsoTrack_dedxByLayer3 [best_track]      *   (calibration_values.at(iEdge)).at(3 )  );
          h_dedxByLayer4_data [iEdge]->Fill(IsoTrack_dedxByLayer4 [best_track]      *   (calibration_values.at(iEdge)).at(4 )  );
          h_dedxByLayer5_data [iEdge]->Fill(IsoTrack_dedxByLayer5 [best_track]      *   (calibration_values.at(iEdge)).at(5 )  );
          h_dedxByLayer6_data [iEdge]->Fill(IsoTrack_dedxByLayer6 [best_track]      *   (calibration_values.at(iEdge)).at(6 )  );
          h_dedxByLayer7_data [iEdge]->Fill(IsoTrack_dedxByLayer7 [best_track]      *   (calibration_values.at(iEdge)).at(7 )  );
          h_dedxByLayer8_data [iEdge]->Fill(IsoTrack_dedxByLayer8 [best_track]      *   (calibration_values.at(iEdge)).at(8 )  );
          h_dedxByLayer9_data [iEdge]->Fill(IsoTrack_dedxByLayer9 [best_track]      *   (calibration_values.at(iEdge)).at(9 )  );
          h_dedxByLayer10_data[iEdge]->Fill(IsoTrack_dedxByLayer10[best_track]      *   (calibration_values.at(iEdge)).at(10)  );
          h_dedxByLayer11_data[iEdge]->Fill(IsoTrack_dedxByLayer11[best_track]      *   (calibration_values.at(iEdge)).at(11)  );
          h_dedxByLayer12_data[iEdge]->Fill(IsoTrack_dedxByLayer12[best_track]      *   (calibration_values.at(iEdge)).at(12)  );
          h_dedxByLayer13_data[iEdge]->Fill(IsoTrack_dedxByLayer13[best_track]      *   (calibration_values.at(iEdge)).at(13)  );
          
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);
          h_mass_data[iEdge] -> Fill((track+muon).M());
          
        }
      }
    }
  }
  
  

  
  
  
  
  TH1F* h_dedxByLayer0_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer1_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer2_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer3_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer4_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer5_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer6_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer7_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer8_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer9_mc  [eta_edges.size()-1];
  TH1F* h_dedxByLayer10_mc [eta_edges.size()-1];
  TH1F* h_dedxByLayer11_mc [eta_edges.size()-1];
  TH1F* h_dedxByLayer12_mc [eta_edges.size()-1];
  TH1F* h_dedxByLayer13_mc [eta_edges.size()-1];
  
  TH1F* h_mass_mc [eta_edges.size()-1];
  
  for (int iEdge = 0; iEdge<eta_edges.size(); iEdge++) {
    
    TString name;
    
    name = Form ("h_%d_dedxByLayer0_mc" , iEdge);      h_dedxByLayer0_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer0_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer1_mc" , iEdge);      h_dedxByLayer1_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer1_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer2_mc" , iEdge);      h_dedxByLayer2_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer2_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer3_mc" , iEdge);      h_dedxByLayer3_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer3_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer4_mc" , iEdge);      h_dedxByLayer4_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer4_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer5_mc" , iEdge);      h_dedxByLayer5_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer5_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer6_mc" , iEdge);      h_dedxByLayer6_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer6_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer7_mc" , iEdge);      h_dedxByLayer7_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer7_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer8_mc" , iEdge);      h_dedxByLayer8_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer8_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer9_mc" , iEdge);      h_dedxByLayer9_mc [iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer9_mc [iEdge], 11);
    name = Form ("h_%d_dedxByLayer10_mc", iEdge);      h_dedxByLayer10_mc[iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer10_mc[iEdge], 11);
    name = Form ("h_%d_dedxByLayer11_mc", iEdge);      h_dedxByLayer11_mc[iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer11_mc[iEdge], 11);
    name = Form ("h_%d_dedxByLayer12_mc", iEdge);      h_dedxByLayer12_mc[iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer12_mc[iEdge], 11);
    name = Form ("h_%d_dedxByLayer13_mc", iEdge);      h_dedxByLayer13_mc[iEdge] = new TH1F (name.Data(), "mc", 2000, 0, 10);         setupHisto(h_dedxByLayer13_mc[iEdge], 11);
    
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
          
          h_dedxByLayer0_mc [iEdge]->Fill(IsoTrack_dedxByLayer0 [best_track]);
          h_dedxByLayer1_mc [iEdge]->Fill(IsoTrack_dedxByLayer1 [best_track]);
          h_dedxByLayer2_mc [iEdge]->Fill(IsoTrack_dedxByLayer2 [best_track]);
          h_dedxByLayer3_mc [iEdge]->Fill(IsoTrack_dedxByLayer3 [best_track]);
          h_dedxByLayer4_mc [iEdge]->Fill(IsoTrack_dedxByLayer4 [best_track]);
          h_dedxByLayer5_mc [iEdge]->Fill(IsoTrack_dedxByLayer5 [best_track]);
          h_dedxByLayer6_mc [iEdge]->Fill(IsoTrack_dedxByLayer6 [best_track]);
          h_dedxByLayer7_mc [iEdge]->Fill(IsoTrack_dedxByLayer7 [best_track]);
          h_dedxByLayer8_mc [iEdge]->Fill(IsoTrack_dedxByLayer8 [best_track]);
          h_dedxByLayer9_mc [iEdge]->Fill(IsoTrack_dedxByLayer9 [best_track]);
          h_dedxByLayer10_mc[iEdge]->Fill(IsoTrack_dedxByLayer10[best_track]);
          h_dedxByLayer11_mc[iEdge]->Fill(IsoTrack_dedxByLayer11[best_track]);
          h_dedxByLayer12_mc[iEdge]->Fill(IsoTrack_dedxByLayer12[best_track]);
          h_dedxByLayer13_mc[iEdge]->Fill(IsoTrack_dedxByLayer13[best_track]);
          
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);
          h_mass_mc[iEdge] -> Fill((track+muon).M());
          
        }
      }
    }
  }
  
  
  
  TFile* fileOut = new TFile ("tocalibrate_complete_eta_edges.root", "RECREATE");
 
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    h_dedxByLayer0_data [iEdge]->Write();                       h_dedxByLayer0_mc [iEdge]->Write();
    h_dedxByLayer1_data [iEdge]->Write();                       h_dedxByLayer1_mc [iEdge]->Write();
    h_dedxByLayer2_data [iEdge]->Write();                       h_dedxByLayer2_mc [iEdge]->Write();
    h_dedxByLayer3_data [iEdge]->Write();                       h_dedxByLayer3_mc [iEdge]->Write();
    h_dedxByLayer4_data [iEdge]->Write();                       h_dedxByLayer4_mc [iEdge]->Write();
    h_dedxByLayer5_data [iEdge]->Write();                       h_dedxByLayer5_mc [iEdge]->Write();
    h_dedxByLayer6_data [iEdge]->Write();                       h_dedxByLayer6_mc [iEdge]->Write();
    h_dedxByLayer7_data [iEdge]->Write();                       h_dedxByLayer7_mc [iEdge]->Write();
    h_dedxByLayer8_data [iEdge]->Write();                       h_dedxByLayer8_mc [iEdge]->Write();
    h_dedxByLayer9_data [iEdge]->Write();                       h_dedxByLayer9_mc [iEdge]->Write();
    h_dedxByLayer10_data[iEdge]->Write();                       h_dedxByLayer10_mc[iEdge]->Write();
    h_dedxByLayer11_data[iEdge]->Write();                       h_dedxByLayer11_mc[iEdge]->Write();
    h_dedxByLayer12_data[iEdge]->Write();                       h_dedxByLayer12_mc[iEdge]->Write();
    h_dedxByLayer13_data[iEdge]->Write();                       h_dedxByLayer13_mc[iEdge]->Write(); 
    
    h_mass_data[iEdge]->Write();                                h_mass_mc[iEdge]->Write();
    
  }
  
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    
    TLegend* leg = new TLegend(0.70,0.70,0.90,0.90);
    leg->AddEntry(h_dedxByLayer0_data[iEdge],"data","pl");
    leg->AddEntry(h_dedxByLayer0_mc[iEdge]  ,"mc",  "pl");
    
    TString name;
    
    name = Form ("cc_summary_%d" , iEdge); 
    
    TCanvas* cc_summary = new TCanvas (name.Data(),"",1000,1000);
    
    cc_summary->Divide(4,4);
    
    cc_summary->cd(1);
    h_dedxByLayer0_data[iEdge]->Draw("PL");
    h_dedxByLayer0_mc[iEdge]->Draw("PL same");
    h_dedxByLayer0_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(2);
    h_dedxByLayer1_data[iEdge]->Draw("PL");
    h_dedxByLayer1_mc[iEdge]->Draw("PL same");
    h_dedxByLayer1_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(3);
    h_dedxByLayer2_data[iEdge]->Draw("PL");
    h_dedxByLayer2_mc[iEdge]->Draw("PL same");
    h_dedxByLayer2_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(4);
    h_dedxByLayer3_data[iEdge]->Draw("PL");
    h_dedxByLayer3_mc[iEdge]->Draw("PL same");
    h_dedxByLayer3_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(5);
    h_dedxByLayer4_data[iEdge]->Draw("PL");
    h_dedxByLayer4_mc[iEdge]->Draw("PL same");
    h_dedxByLayer4_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(6);
    h_dedxByLayer5_data[iEdge]->Draw("PL");
    h_dedxByLayer5_mc[iEdge]->Draw("PL same");
    h_dedxByLayer5_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(7);
    h_dedxByLayer6_data[iEdge]->Draw("PL");
    h_dedxByLayer6_mc[iEdge]->Draw("PL same");
    h_dedxByLayer6_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(8);
    h_dedxByLayer7_data[iEdge]->Draw("PL");
    h_dedxByLayer7_mc[iEdge]->Draw("PL same");
    h_dedxByLayer7_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(9);
    h_dedxByLayer8_data[iEdge]->Draw("PL");
    h_dedxByLayer8_mc[iEdge]->Draw("PL same");
    h_dedxByLayer8_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(10);
    h_dedxByLayer9_data[iEdge]->Draw("PL");
    h_dedxByLayer9_mc[iEdge]->Draw("PL same");
    h_dedxByLayer9_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(11);
    h_dedxByLayer10_data[iEdge]->Draw("PL");
    h_dedxByLayer10_mc[iEdge]->Draw("PL same");
    h_dedxByLayer10_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(12);
    h_dedxByLayer11_data[iEdge]->Draw("PL");
    h_dedxByLayer11_mc[iEdge]->Draw("PL same");
    h_dedxByLayer11_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(13);
    h_dedxByLayer12_data[iEdge]->Draw("PL");
    h_dedxByLayer12_mc[iEdge]->Draw("PL same");
    h_dedxByLayer12_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    cc_summary->cd(14);
    h_dedxByLayer13_data[iEdge]->Draw("PL");
    h_dedxByLayer13_mc[iEdge]->Draw("PL same");
    h_dedxByLayer13_data[iEdge]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
    leg->Draw();
    
    
    cc_summary->Write();
  
  }
  
  
  
  fileOut->Close();
  
}






