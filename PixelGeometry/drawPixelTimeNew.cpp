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
  color[11]= kRed + 2 ;
  color[12]= kRed + 4;
  for (int i=0; i<30; i++) {
    color[i+13] = kBlue + i;
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
  std::cout << " num_run_intervals = " << num_run_intervals << std::endl;
  
  int num_max_layer = 5; // 20
  if (argc>=5) {
    num_max_layer = atoi(argv[4]);
  }
  std::cout << " num_max_layer = " << num_max_layer << std::endl;
  
  
  
  
  std::vector<float> eta_edges;
//   eta_edges.push_back(-2.5);           FindEdge  -> FindEdgeAbs
//   eta_edges.push_back(-2.1);
//   eta_edges.push_back(-1.6);
//   eta_edges.push_back(-1.3);
//   eta_edges.push_back(-1.0);
//   eta_edges.push_back(-0.6);
//   eta_edges.push_back(-0.3);

  eta_edges.push_back(0.0);

//   eta_edges.push_back(0.3);
//   eta_edges.push_back(0.6);
//   eta_edges.push_back(1.0);
  eta_edges.push_back(1.3);
//   eta_edges.push_back(1.6);
  eta_edges.push_back(2.1);
  eta_edges.push_back(2.5);
  
   
  //---- 
  //---- layer 
  //----
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<num_max_layer; ilayer++) {
//     for (int ilayer = 0; ilayer<20; ilayer++) {
    layerId.push_back(ilayer);
  }
  
  
  //---- 
  //---- ladderblade 
  //----
  std::vector<int> ladderbladeId;
  for (int iladderblade = 0; iladderblade<40; iladderblade++) {
//     for (int iladderblade = 0; iladderblade<12; iladderblade++) {
      //     for (int iladderblade = 0; iladderblade<40; iladderblade++) {
    ladderbladeId.push_back(iladderblade);
  }
  
  
  
  
  
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX;
  
  
  //   map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]
  //   map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
    std::vector < std::vector < std::vector  < float > > > v_1;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      std::vector < std::vector  < float > > v_2;
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        std::vector < float > v_scale;
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          v_scale.push_back(1.0);
        }
        v_2.push_back(v_scale);
      }
      v_1.push_back(v_2);
    }
    map_calibration_BPIX.push_back(v_1);
    map_calibration_FPIX.push_back(v_1);
  }
  
    
    
  
  
  
  //---- read calibration values
  int apply_calibration = 0;
  std::string fileCalibration = "scale_pixels_run_ranges_reduced_BPIX.txt";
  if (argc>=6) {
    apply_calibration = 1;
    fileCalibration = argv[5];
    
    std::cout << " fileCalibration BPIX = " << fileCalibration << std::endl;
    
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
        
        int ilayer;
        int iladderblade;
        int iEdge;
        
        line >> iEdge;
        line >> ilayer;
        line >> iladderblade;
        
        float calibration_factor = 1.0;
        for (int iRun = 0; iRun < num_run_intervals; iRun++) {
          line >> calibration_factor;
          //---- fix
          if (calibration_factor < 0) calibration_factor = 1;
          map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] = calibration_factor;
        }
      } 
    }
  }
  
  
  if (argc>=7) {
    apply_calibration = 1;
    fileCalibration = argv[6];
  
    std::cout << " fileCalibration FPIX = " << fileCalibration << std::endl;
    
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
        
        int ilayer;
        int iladderblade;
        int iEdge;
        
        line >> iEdge;
        line >> ilayer;
        line >> iladderblade;
        
        float calibration_factor = 1.0;
        for (int iRun = 0; iRun < num_run_intervals; iRun++) {
          line >> calibration_factor;
          //---- fix
          if (calibration_factor < 0) calibration_factor = 1;
          map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] = calibration_factor;
        }
      } 
    }
  }
  
  
  
  
  
  //---- print calibration map
//  std::cout << " BPIX " << std::endl;
//  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
//    std::cout << " [ " << iRun << ", ";
//    std::cout << std::endl;
//    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
//      std::cout << "   | " << ilayer << "| ";
//      std::cout << std::endl;
//      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
//        std::cout << "      " << iEdge << "] = ";
//        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
//          std::cout << " :: " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade];
//        }
//      }
//    }
//  }
//  
//  std::cout << " FPIX " << std::endl;
//  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
//    std::cout << " [ " << iRun << ", ";
//    std::cout << std::endl;
//    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
//      std::cout << "   | " << ilayer << "| ";
//      std::cout << std::endl;
//      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
//        std::cout << "      " << iEdge << "] = ";
//        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
//          std::cout << " :: " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade];
//        }
//      }
//    }
//  }
  
  
  
  
  std::cout << " name_input_file_data = " << name_input_file_data << std::endl;
  std::cout << " name_input_file_mc   = " << name_input_file_mc << std::endl;
  
  TFile* inputFile_data = new TFile (name_input_file_data.c_str(), "READ");   
  TTree* inputTree_data = (TTree*) ((TTree*) inputFile_data -> Get ("tree")) -> Clone ("tree_data");
  
  TFile* inputFile_mc = new TFile (name_input_file_mc.c_str(), "READ");   
  TTree* inputTree_mc = (TTree*) ((TTree*) inputFile_mc -> Get ("tree")) -> Clone ("tree_mc");
  
  std::cout << " data = " << inputTree_data->GetEntries() << std::endl;
  std::cout << " mc   = " << inputTree_mc->GetEntries()   << std::endl;
  
  gStyle->SetOptStat(0);
   
  
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
  
  Int_t IsoTrack_layerOrSideByLayer0[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer1[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer2[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer3[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer4[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer5[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer6[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer7[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer8[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer9[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer10[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer11[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer12[kMaxTracks];
  Int_t IsoTrack_layerOrSideByLayer13[kMaxTracks];
  
  
  Int_t IsoTrack_ladderOrBladeByLayer0[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer1[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer2[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer3[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer4[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer5[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer6[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer7[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer8[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer9[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer10[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer11[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer12[kMaxTracks];
  Int_t IsoTrack_ladderOrBladeByLayer13[kMaxTracks];
  


  
  
  
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

  Int_t IsoTrack_pixByLayer0[kMaxTracks];
  Int_t IsoTrack_pixByLayer1[kMaxTracks];
  Int_t IsoTrack_pixByLayer2[kMaxTracks];
  Int_t IsoTrack_pixByLayer3[kMaxTracks];
  Int_t IsoTrack_pixByLayer4[kMaxTracks];
  Int_t IsoTrack_pixByLayer5[kMaxTracks];
  Int_t IsoTrack_pixByLayer6[kMaxTracks];
  Int_t IsoTrack_pixByLayer7[kMaxTracks];
  Int_t IsoTrack_pixByLayer8[kMaxTracks];
  Int_t IsoTrack_pixByLayer9[kMaxTracks];
  Int_t IsoTrack_pixByLayer10[kMaxTracks];
  Int_t IsoTrack_pixByLayer11[kMaxTracks];
  Int_t IsoTrack_pixByLayer12[kMaxTracks];
  Int_t IsoTrack_pixByLayer13[kMaxTracks];
  
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
  
  
  std::cout << " here " << std::endl;
  
  
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
  
  
  
  
  
  std::cout << " here 2 " << std::endl;
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer0",  IsoTrack_pixByLayer0);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer0",  IsoTrack_pixByLayer0);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer1",  IsoTrack_pixByLayer1);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer1",  IsoTrack_pixByLayer1);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer2",  IsoTrack_pixByLayer2);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer2",  IsoTrack_pixByLayer2);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer3",  IsoTrack_pixByLayer3);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer3",  IsoTrack_pixByLayer3);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer4",  IsoTrack_pixByLayer4);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer4",  IsoTrack_pixByLayer4);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer5",  IsoTrack_pixByLayer5);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer5",  IsoTrack_pixByLayer5);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer6",  IsoTrack_pixByLayer6);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer6",  IsoTrack_pixByLayer6);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer7",  IsoTrack_pixByLayer7);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer7",  IsoTrack_pixByLayer7);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer8",  IsoTrack_pixByLayer8);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer8",  IsoTrack_pixByLayer8);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer9",  IsoTrack_pixByLayer9);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer9",  IsoTrack_pixByLayer9);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer10",  IsoTrack_pixByLayer10);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer10",  IsoTrack_pixByLayer10);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer11",  IsoTrack_pixByLayer11);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer11",  IsoTrack_pixByLayer11);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer12",  IsoTrack_pixByLayer12);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer12",  IsoTrack_pixByLayer12);
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer13",  IsoTrack_pixByLayer13);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pixByLayer13",  IsoTrack_pixByLayer13);
  
  
  
  std::cout << " here 3 " << std::endl;
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer0",  IsoTrack_layerOrSideByLayer0);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer0",  IsoTrack_layerOrSideByLayer0);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer1",  IsoTrack_layerOrSideByLayer1);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer1",  IsoTrack_layerOrSideByLayer1);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer2",  IsoTrack_layerOrSideByLayer2);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer2",  IsoTrack_layerOrSideByLayer2);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer3",  IsoTrack_layerOrSideByLayer3);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer3",  IsoTrack_layerOrSideByLayer3);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer4",  IsoTrack_layerOrSideByLayer4);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer4",  IsoTrack_layerOrSideByLayer4);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer5",  IsoTrack_layerOrSideByLayer5);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer5",  IsoTrack_layerOrSideByLayer5);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer6",  IsoTrack_layerOrSideByLayer6);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer6",  IsoTrack_layerOrSideByLayer6);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer7",  IsoTrack_layerOrSideByLayer7);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer7",  IsoTrack_layerOrSideByLayer7);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer8",  IsoTrack_layerOrSideByLayer8);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer8",  IsoTrack_layerOrSideByLayer8);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer9",  IsoTrack_layerOrSideByLayer9);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer9",  IsoTrack_layerOrSideByLayer9);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer10",  IsoTrack_layerOrSideByLayer10);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer10",  IsoTrack_layerOrSideByLayer10);               
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer11",  IsoTrack_layerOrSideByLayer11);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer11",  IsoTrack_layerOrSideByLayer11);               
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer12",  IsoTrack_layerOrSideByLayer12);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer12",  IsoTrack_layerOrSideByLayer12);               
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer13",  IsoTrack_layerOrSideByLayer13);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_layerOrSideByLayer13",  IsoTrack_layerOrSideByLayer13);               
  
  
  
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer0",  IsoTrack_ladderOrBladeByLayer0);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer0",  IsoTrack_ladderOrBladeByLayer0);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer1",  IsoTrack_ladderOrBladeByLayer1);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer1",  IsoTrack_ladderOrBladeByLayer1);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer2",  IsoTrack_ladderOrBladeByLayer2);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer2",  IsoTrack_ladderOrBladeByLayer2);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer3",  IsoTrack_ladderOrBladeByLayer3);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer3",  IsoTrack_ladderOrBladeByLayer3);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer4",  IsoTrack_ladderOrBladeByLayer4);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer4",  IsoTrack_ladderOrBladeByLayer4);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer5",  IsoTrack_ladderOrBladeByLayer5);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer5",  IsoTrack_ladderOrBladeByLayer5);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer6",  IsoTrack_ladderOrBladeByLayer6);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer6",  IsoTrack_ladderOrBladeByLayer6);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer7",  IsoTrack_ladderOrBladeByLayer7);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer7",  IsoTrack_ladderOrBladeByLayer7);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer8",  IsoTrack_ladderOrBladeByLayer8);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer8",  IsoTrack_ladderOrBladeByLayer8);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer9",  IsoTrack_ladderOrBladeByLayer9);                 
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer9",  IsoTrack_ladderOrBladeByLayer9);                 
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer10",  IsoTrack_ladderOrBladeByLayer10);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer10",  IsoTrack_ladderOrBladeByLayer10);               
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer11",  IsoTrack_ladderOrBladeByLayer11);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer11",  IsoTrack_ladderOrBladeByLayer11);               
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer12",  IsoTrack_ladderOrBladeByLayer12);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer12",  IsoTrack_ladderOrBladeByLayer12);               
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer13",  IsoTrack_ladderOrBladeByLayer13);               
  inputTree_mc  ->SetBranchAddress("IsoTrack_ladderOrBladeByLayer13",  IsoTrack_ladderOrBladeByLayer13);               
  
  
  
  
  
  
  
  
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
  
  
  std::cout << " Prepare output ..." << std::endl;
  
  
  //---- output file
  TFile* fileOut;
  
  if (apply_calibration == 0)
    fileOut = new TFile ("tocalibrate_complete_eta_edges_iladderblade_timeRanges.root", "RECREATE");
  else 
    fileOut = new TFile ("tocalibrate_complete_eta_edges_iladderblade_timeRanges_calibrated.root", "RECREATE");
  
  
  std::cout << " file done ..." << std::endl;
  
  
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_BPIX_data;
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_FPIX_data;

  //---- layer         eta     
  std::vector  < std::vector < TH1F* > > map_h_BPIX_reduced_data;
  std::vector  < std::vector < TH1F* > > map_h_FPIX_reduced_data;
  
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_BPIX;
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_FPIX;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      std::vector < std::vector  < TH1F* > > v_2_BPIX;
      std::vector < std::vector  < TH1F* > > v_2_FPIX;
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        std::vector < TH1F* > v_h_BPIX;
        std::vector < TH1F* > v_h_FPIX;
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          TString name;      
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_data", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp = new TH1F (name.Data(), "data", 100, 0, 10);  
          setupHisto(temp, iRun);
          v_h_BPIX.push_back ( temp );
          
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_data", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp2 = new TH1F (name.Data(), "data", 100, 0, 10);  
          setupHisto(temp2, iRun);
          v_h_FPIX.push_back ( temp2 );
          
        }
        v_2_BPIX.push_back (v_h_BPIX);
        v_2_FPIX.push_back (v_h_FPIX);
      }
      v_1_BPIX.push_back (v_2_BPIX);
      v_1_FPIX.push_back (v_2_FPIX);
    }
    
    map_h_BPIX_data.push_back( v_1_BPIX );
    map_h_FPIX_data.push_back( v_1_FPIX );
    
  }
  
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    std::vector < TH1F* > v_h_BPIX;
    std::vector < TH1F* > v_h_FPIX;
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      
      TString name;      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_data", ilayer, iEdge);   
      TH1F* temp = new TH1F (name.Data(), "data", 100, 0, 10);  
      setupHisto(temp, iEdge);
      v_h_BPIX.push_back ( temp );
      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_data", ilayer, iEdge);   
      TH1F* temp2 = new TH1F (name.Data(), "data", 100, 0, 10);  
      setupHisto(temp2, iEdge);
      v_h_FPIX.push_back ( temp2 );
      
    }
    map_h_BPIX_reduced_data.push_back( v_h_BPIX );
    map_h_FPIX_reduced_data.push_back( v_h_FPIX );
  }
  

  
  

  std::cout << " now MC ..." << std::endl;
  
          
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_BPIX_mc;
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_FPIX_mc;
  
  //---- layer         eta     
  std::vector  < std::vector < TH1F* > > map_h_BPIX_reduced_mc;
  std::vector  < std::vector < TH1F* > > map_h_FPIX_reduced_mc;
  
  
  //                      1 -> just one run for MC
  for (int iRun = 0; iRun<1; iRun++) {
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_BPIX;
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_FPIX;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      std::vector < std::vector  < TH1F* > > v_2_BPIX;
      std::vector < std::vector  < TH1F* > > v_2_FPIX;
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        std::vector < TH1F* > v_h_BPIX;
        std::vector < TH1F* > v_h_FPIX;
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          TString name;      
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp = new TH1F (name.Data(), "mc", 100, 0, 10);  
          setupHisto(temp, iRun);
          v_h_BPIX.push_back ( temp );
          
          
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_mc", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp2 = new TH1F (name.Data(), "mc", 100, 0, 10);  
          setupHisto(temp2, iRun);
          v_h_FPIX.push_back ( temp2 );
          
        }
        v_2_BPIX.push_back (v_h_BPIX);
        v_2_FPIX.push_back (v_h_FPIX);
      }
      v_1_BPIX.push_back (v_2_BPIX);
      v_1_FPIX.push_back (v_2_FPIX);
    }
    
    map_h_BPIX_mc.push_back( v_1_BPIX );
    map_h_FPIX_mc.push_back( v_1_FPIX );
    
  }
  
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    std::vector < TH1F* > v_h_BPIX;
    std::vector < TH1F* > v_h_FPIX;
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      
      TString name;      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_mc", ilayer, iEdge);   
      TH1F* temp = new TH1F (name.Data(), "mc", 100, 0, 10);  
      setupHisto(temp, iEdge +1 );
      v_h_BPIX.push_back ( temp );
      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_mc", ilayer, iEdge);   
      TH1F* temp2 = new TH1F (name.Data(), "mc", 100, 0, 10);  
      setupHisto(temp2, iEdge +1 );
      v_h_FPIX.push_back ( temp2 );
      
    }
    map_h_BPIX_reduced_mc.push_back( v_h_BPIX );
    map_h_FPIX_reduced_mc.push_back( v_h_FPIX );
  }
  
       
       
       
       
  
  int minRun = inputTree_data->GetMinimum ("run");
  int maxRun = inputTree_data->GetMaximum ("run") + 1;
  int deltaRun = ceil( 1. * (maxRun-minRun) / num_run_intervals );
  
  std::cout << " minRun = " << minRun << std::endl;
  std::cout << " maxRun = " << maxRun << std::endl;
  std::cout << " deltaRun = " << deltaRun << std::endl;
  
  
//   for (int iEntry=0; iEntry<1000; iEntry++) {
  for (int iEntry=0; iEntry<inputTree_data->GetEntries(); iEntry++) {
    inputTree_data->GetEntry(iEntry);

    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
  
//     std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    
    
    int iRun = FindInterval(run, minRun, deltaRun);
    //---- safe check
    if (iRun >= num_run_intervals) {
      std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
      std::cout << "              -> " << run << ", " << minRun << ", " << deltaRun  << std::endl;
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
    
        int iEdge = FindEdgeAbs (IsoTrack_eta[best_track], eta_edges);
        
//         std::cout << " iEdge = " << iEdge << " :: " << eta_edges.size()-1 << std::endl;
        
        if (iEdge != -1) {
          
          //
          //   pixByLayer is 0 for strips
          //                is 1 for bpix, 2 for fpix (pixels)
          //
          
          int ilayer = -1; // IsoTrack_layerOrSideByLayer0[best_track];
          int iladderblade = -1; // IsoTrack_ladderOrBladeByLayer0[best_track];
          
          if (IsoTrack_pixByLayer0[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer0[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer0[best_track];   
     
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              
//               std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
//               std::cout << " iEdge = " << iEdge << " :: " << eta_edges.size()-1 << std::endl;
//               std::cout << " ilayer = " << ilayer << " :: " << 20 << std::endl;
//               std::cout << " iladderblade = " << iladderblade << " :: " << ladderbladeId.size() << std::endl;
//               std::cout << " map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " IsoTrack_dedxByLayer0 [" << best_track << "] = " << IsoTrack_dedxByLayer0 [best_track] << std::endl;
//               std::cout << " IsoTrack_pixByLayer0 [" << best_track << "] = " << IsoTrack_pixByLayer0 [best_track] << std::endl;
              
              if (IsoTrack_pixByLayer0[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer0 [best_track] * map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer0 [best_track] * map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
            }
          }
          
       
          if (IsoTrack_pixByLayer1[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer1[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer1[best_track];   
 
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              
//               std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
//               std::cout << " iEdge = " << iEdge << " :: " << eta_edges.size()-1 << std::endl;
//               std::cout << " ilayer = " << ilayer << " :: " << 20 << std::endl;
//               std::cout << " iladderblade = " << iladderblade << " :: " << ladderbladeId.size() << std::endl;
//               std::cout << " map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " IsoTrack_dedxByLayer1 [" << best_track << "] = " << IsoTrack_dedxByLayer1 [best_track] << std::endl;
//               std::cout << " IsoTrack_pixByLayer1 [" << best_track << "] = " << IsoTrack_pixByLayer1 [best_track] << std::endl;
              
              if (IsoTrack_pixByLayer1[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer1 [best_track] * map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer1 [best_track] * map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
            }
          }
          
          if (IsoTrack_pixByLayer2[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer2[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer2[best_track];   
           
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              
//               std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
//               std::cout << " iEdge = " << iEdge << " :: " << eta_edges.size()-1 << std::endl;
//               std::cout << " ilayer = " << ilayer << " :: " << 20 << std::endl;
//               std::cout << " iladderblade = " << iladderblade << " :: " << ladderbladeId.size() << std::endl;
//               std::cout << " map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " IsoTrack_dedxByLayer2 [" << best_track << "] = " << IsoTrack_dedxByLayer2 [best_track] << std::endl;
//               std::cout << " IsoTrack_pixByLayer2 [" << best_track << "] = " << IsoTrack_pixByLayer2 [best_track] << std::endl;
              
              if (IsoTrack_pixByLayer2[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer2 [best_track] * map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer2 [best_track] * map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
            }
          }
          
          if (IsoTrack_pixByLayer3[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer3[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer3[best_track];   
          
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              
//               std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
//               std::cout << " iEdge = " << iEdge << " :: " << eta_edges.size()-1 << std::endl;
//               std::cout << " ilayer = " << ilayer << " :: " << 20 << std::endl;
//               std::cout << " iladderblade = " << iladderblade << " :: " << ladderbladeId.size() << std::endl;
//               std::cout << " map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " IsoTrack_dedxByLayer3 [" << best_track << "] = " << IsoTrack_dedxByLayer3 [best_track] << std::endl;
//               std::cout << " IsoTrack_pixByLayer3 [" << best_track << "] = " << IsoTrack_pixByLayer3 [best_track] << std::endl;
              
              if (IsoTrack_pixByLayer3[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer3 [best_track] * map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer3 [best_track] * map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
            }
          }
          
          
          if (IsoTrack_pixByLayer4[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer4[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer4[best_track];   

            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              
//               std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
//               std::cout << " iEdge = " << iEdge << " :: " << eta_edges.size()-1 << std::endl;
//               std::cout << " ilayer = " << ilayer << " :: " << 20 << std::endl;
//               std::cout << " iladderblade = " << iladderblade << " :: " << ladderbladeId.size() << std::endl;
//               std::cout << " map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " IsoTrack_dedxByLayer4 [" << best_track << "] = " << IsoTrack_dedxByLayer4 [best_track] << std::endl;
//               std::cout << " IsoTrack_pixByLayer4 [" << best_track << "] = " << IsoTrack_pixByLayer4 [best_track] << std::endl;
              
              
              if (IsoTrack_pixByLayer4[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer4 [best_track] * map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer4 [best_track] * map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
            }
          }
          
          
          if (IsoTrack_pixByLayer5[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer5[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer5[best_track];   
     
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              
//               std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
//               std::cout << " iEdge = " << iEdge << " :: " << eta_edges.size()-5 << std::endl;
//               std::cout << " ilayer = " << ilayer << " :: " << 25 << std::endl;
//               std::cout << " iladderblade = " << iladderblade << " :: " << ladderbladeId.size() << std::endl;
//               std::cout << " map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] = " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] << " --> " << map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
//               std::cout << " map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] = " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] << std::endl;
//               std::cout << " IsoTrack_dedxByLayer5 [" << best_track << "] = " << IsoTrack_dedxByLayer5 [best_track] << std::endl;
//               std::cout << " IsoTrack_pixByLayer5 [" << best_track << "] = " << IsoTrack_pixByLayer5 [best_track] << std::endl;
              
              
              if (IsoTrack_pixByLayer5[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer5 [best_track] * map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer5 [best_track] * map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
            }
          }
          
          
          if (IsoTrack_pixByLayer6[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer6[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer6[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer6[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer6 [best_track] * map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer6 [best_track] * map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]); 
              }
            }
          }
          
//           std::cout << " I am done ... " << std::endl;
          
        }
      }
    }
  }
  
  
  
    
  for (int iEntry=0; iEntry<inputTree_mc->GetEntries(); iEntry++) {
    inputTree_mc->GetEntry(iEntry);
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    
    
    int iRun = 0;
        
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
        
        int iEdge = FindEdgeAbs (IsoTrack_eta[best_track], eta_edges);

//         std::cout << "  IsoTrack_eta[" << best_track << "]  = " << IsoTrack_eta[best_track] << " --> iEdge = " << iEdge << std::endl;
        
        if (iEdge != -1) {
          
          //
          //   pixByLayer is 0 for strips
          //                is 1 for bpix, 2 for fpix (pixels)
          //
          
          int ilayer = -1; // IsoTrack_layerOrSideByLayer0[best_track];
          int iladderblade = -1; // IsoTrack_ladderOrBladeByLayer0[best_track];
          
//           std::cout << "  IsoTrack_pixByLayer0[" << best_track << "]  = " << IsoTrack_pixByLayer0[best_track]  << std::endl;
          
          if (IsoTrack_pixByLayer0[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer0[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer0[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer0[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer0 [best_track]); 
                //               std::cout << "  map_h_BPIX_mc[" << iRun << "][" << ilayer << "][" << iEdge << "][" << iladderblade << "] entries = " << map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade]->GetEntries() << std::endl;
              }
              else {
                //---- FPIX
                map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer0 [best_track]); 
              }
            }
          }
          
          
          if (IsoTrack_pixByLayer1[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer1[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer1[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer1[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer1 [best_track]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer1 [best_track]); 
              }
            }
          }
          
          if (IsoTrack_pixByLayer2[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer2[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer2[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer2[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer2 [best_track]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer2 [best_track]); 
              }
            }
          }
          
          if (IsoTrack_pixByLayer3[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer3[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer3[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer3[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer3 [best_track]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer3 [best_track]); 
              }
            }
          }
          
          if (IsoTrack_pixByLayer4[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer4[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer4[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer4[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer4 [best_track]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer4 [best_track]); 
              }
            }
          }
          
          
          if (IsoTrack_pixByLayer5[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer5[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer5[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer5[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer5 [best_track]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer5 [best_track]); 
              }
            }
          }
          
          if (IsoTrack_pixByLayer6[best_track] != 0) {  
            ilayer = IsoTrack_layerOrSideByLayer6[best_track];
            iladderblade = IsoTrack_ladderOrBladeByLayer6[best_track];   
            if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
              if (IsoTrack_pixByLayer6[best_track] == 1) {
                //---- BPIX
                map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer6 [best_track]); 
              }
              else {
                //---- FPIX
                map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade] ->Fill(IsoTrack_dedxByLayer6 [best_track]); 
              }
            }
          }
          
        }
      }
    }
  }
  
  
  
  
  
  //---- save in output file
  fileOut->cd();
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
        for (int iRun = 0; iRun<num_run_intervals; iRun++) {
          map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> Write();
          map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> Write();
        }
        map_h_BPIX_mc[0][ilayer][iEdge][iladderblade] -> Write();
        map_h_FPIX_mc[0][ilayer][iEdge][iladderblade] -> Write();
      }
    }
  }
  
  //---- merge the histograms
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {    
      for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
        for (int iRun = 0; iRun<num_run_intervals; iRun++) {
          map_h_BPIX_reduced_data[ilayer][iEdge] -> Add( map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] , 1.0 );
          map_h_FPIX_reduced_data[ilayer][iEdge] -> Add( map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] , 1.0 );
        }
        map_h_BPIX_reduced_mc[ilayer][iEdge] -> Add( map_h_BPIX_mc[0][ilayer][iEdge][iladderblade] , 1.0 );
        map_h_FPIX_reduced_mc[ilayer][iEdge] -> Add( map_h_FPIX_mc[0][ilayer][iEdge][iladderblade] , 1.0 );
      }
    }
  }
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {    
      map_h_BPIX_reduced_data[ilayer][iEdge] -> Write ();
      map_h_FPIX_reduced_data[ilayer][iEdge] -> Write ();
      map_h_BPIX_reduced_mc[ilayer][iEdge]   -> Write ();
      map_h_FPIX_reduced_mc[ilayer][iEdge]   -> Write ();
    }
  }
  
  
  
  
  
  
  
  //---- now prepare to draw ...
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
        for (int iRun = 0; iRun<num_run_intervals; iRun++) {
          Normalize( map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] );
          Normalize( map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] );
        }
        Normalize( map_h_BPIX_mc[0][ilayer][iEdge][iladderblade] );
        Normalize( map_h_FPIX_mc[0][ilayer][iEdge][iladderblade] );
      }
    }
  }
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {    
      Normalize( map_h_BPIX_reduced_data[ilayer][iEdge] );
      Normalize( map_h_FPIX_reduced_data[ilayer][iEdge] );
      Normalize( map_h_BPIX_reduced_mc[ilayer][iEdge]   );
      Normalize( map_h_FPIX_reduced_mc[ilayer][iEdge]   );
    }
  }
  
  
  //---- ... and draw.
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    TString name;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      
      name = Form ("cc_summary_layer_%d_eta_%d" , ilayer, iEdge); 
      TCanvas* cc_summary_iEdge = new TCanvas (name.Data(),"",1400,400);
      cc_summary_iEdge->Divide(ladderbladeId.size(), 2);
 
      for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
        
      
        TLegend* leg = new TLegend(0.50,0.70,0.90,0.90);
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
          std::string name = " data [" + std::to_string(minRun+iRun*deltaRun) + " , " + std::to_string(minRun+(iRun+1)*deltaRun) + "] "; 
          leg->AddEntry(map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade], name.c_str(), "pl");
        }
        leg->AddEntry(map_h_BPIX_mc[0][ilayer][iEdge][iladderblade], "mc",  "pl");
        
        
//         name = Form ("cc_bin_BPIX_%d_%d_%d" , ilayer, iEdge, iladderblade); 
//         
//         TCanvas* cc_summary = new TCanvas (name.Data(),"",1000,1000);
//         
//         map_h_BPIX_mc[0][ilayer][iEdge][iladderblade]  ->Draw("PL");
//         for (int iRun =0; iRun < num_run_intervals; iRun++) { 
//           map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Draw("PL same");
//         }
//         map_h_BPIX_mc[0][ilayer][iEdge][iladderblade]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
//         leg->Draw();
        
        
//         cc_summary->Write();
       
        
        
        // BPIX
        
        cc_summary_iEdge->cd(iladderblade+1);
        map_h_BPIX_mc[0][ilayer][iEdge][iladderblade] ->Draw("PL");
        for (int iRun =0; iRun < num_run_intervals; iRun++) { 
          map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Draw("PL same");
        }
        
        map_h_BPIX_mc[0][ilayer][iEdge][iladderblade]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
        leg->Draw();
        
        
        
        // FPIX
        
        cc_summary_iEdge->cd(iladderblade+1+ladderbladeId.size());
        map_h_FPIX_mc[0][ilayer][iEdge][iladderblade] ->Draw("PL");
        for (int iRun =0; iRun < num_run_intervals; iRun++) { 
          map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Draw("PL same");
        }
        
        map_h_FPIX_mc[0][ilayer][iEdge][iladderblade]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
        leg->Draw();
        
        
        
        
        //---- single canvas
        
        name = Form ("cc_summary_layer_%d_eta_%d_ladder_%d_BPIX" , ilayer, iEdge, iladderblade); 
        TCanvas* cc_summary_iEdge_iladder_BPIX = new TCanvas (name.Data(),"",800,600);
        
        map_h_BPIX_mc[0][ilayer][iEdge][iladderblade] ->Draw("PL");
        for (int iRun =0; iRun < num_run_intervals; iRun++) { 
          map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Draw("PL same");
        }
        
        map_h_BPIX_mc[0][ilayer][iEdge][iladderblade]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
        leg->Draw();
    
        name = Form ("plots_run/cc_summary_layer_%d_eta_%d_ladder_%d_BPIX.png" , ilayer, iEdge, iladderblade); 
        cc_summary_iEdge_iladder_BPIX->SaveAs(name.Data());
        
        
        name = Form ("cc_summary_layer_%d_eta_%d_ladder_%d_FPIX" , ilayer, iEdge, iladderblade); 
        TCanvas* cc_summary_iEdge_iladder_FPIX = new TCanvas (name.Data(),"",800,600);
        
        map_h_FPIX_mc[0][ilayer][iEdge][iladderblade] ->Draw("PL");
        for (int iRun =0; iRun < num_run_intervals; iRun++) { 
          map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Draw("PL same");
        }
        
        map_h_FPIX_mc[0][ilayer][iEdge][iladderblade]->GetXaxis()->SetTitle("dE/dx (XX*GeV/cm)");
        leg->Draw();
        
        
        name = Form ("plots_run/cc_summary_layer_%d_eta_%d_ladder_%d_FPIX.png" , ilayer, iEdge, iladderblade); 
        cc_summary_iEdge_iladder_FPIX->SaveAs(name.Data());
        
        
        
        
      }
      
//       cc_summary_iEdge->Write();
      name = Form ("plots_run/cc_summary_layer_%d_eta_%d.png" , ilayer, iEdge); 
      cc_summary_iEdge->SaveAs(name.Data());
      
    }
  }
  
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {    
  
      TString name;
      name = Form ("cc_add_layer_%d_eta_%d_BPIX" , ilayer, iEdge); 
      TCanvas* cc_add_iEdge_iladder_BPIX = new TCanvas (name.Data(),"",800,600);
      map_h_BPIX_reduced_mc[ilayer][iEdge]   -> Draw();
      map_h_BPIX_reduced_data[ilayer][iEdge] -> Draw("same");
      name = Form ("plots_run/cc_add_layer_%d_eta_%d_BPIX.png" , ilayer, iEdge); 
      cc_add_iEdge_iladder_BPIX->SaveAs(name.Data());
      
      name = Form ("cc_add_layer_%d_eta_%d_FPIX" , ilayer, iEdge); 
      TCanvas* cc_add_iEdge_iladder_FPIX = new TCanvas (name.Data(),"",800,600);
      map_h_FPIX_reduced_mc[ilayer][iEdge]   -> Draw();
      map_h_FPIX_reduced_data[ilayer][iEdge] -> Draw("same");
      name = Form ("plots_run/cc_add_layer_%d_eta_%d_FPIX.png" , ilayer, iEdge); 
      cc_add_iEdge_iladder_FPIX->SaveAs(name.Data());
      
    }
  }
  
  std::cout << " minRun = " << minRun << std::endl;
  std::cout << " maxRun = " << maxRun << std::endl;
  std::cout << " deltaRun = " << deltaRun << std::endl;
  
  
}







