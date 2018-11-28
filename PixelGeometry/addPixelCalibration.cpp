//
// addPixelCalibration
//
//
//   g++ -o addPixelCalibration.exe addPixelCalibration.cpp `root-config --cflags --glibs`
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
  
  std::string name_output_file_data = "outmc.root";
  
  if (argc>=3) {
    name_output_file_data = argv[2];
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

  eta_edges.push_back(0.3);  //--- exclude
  eta_edges.push_back(0.6);  //--- exclude
  eta_edges.push_back(1.0);  //--- exclude
  eta_edges.push_back(1.3);
  eta_edges.push_back(1.6);  //--- exclude
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
  
  
  
  std::cout << " name_input_file_data = " << name_input_file_data << std::endl;
  std::cout << " name_output_file_data   = " << name_output_file_data << std::endl;
  
  TFile* inputFile_data = new TFile (name_input_file_data.c_str(), "READ");   
  TTree* inputTree_data = (TTree*) ((TTree*) inputFile_data -> Get ("tree")) -> Clone ("tree_data");
  
  TFile* outputFile_data = new TFile (name_output_file_data.c_str(), "RECREATE");   
  TTree *outputTree_data = inputTree_data->CloneTree(0);
  
  
  std::cout << " data = " << inputTree_data->GetEntries() << std::endl;
  
  gStyle->SetOptStat(0);
   
  
  //---- muon
  
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
  


  //---- calibration
  Float_t IsoTrack_calibrationdedxByLayer0[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer1[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer2[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer3[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer4[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer5[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer6[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer7[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer8[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer9[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer10[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer11[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer12[kMaxTracks];
  Float_t IsoTrack_calibrationdedxByLayer13[kMaxTracks];
  
  
  
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
  
  
  Float_t IsoTrack_pt[kMaxTracks];
  Float_t IsoTrack_eta[kMaxTracks];
  Float_t IsoTrack_phi[kMaxTracks];
  Float_t IsoTrack_dxy[kMaxTracks];
  Float_t IsoTrack_dz[kMaxTracks];
  Int_t IsoTrack_highPurity[kMaxTracks];
  Int_t nIsoTrack;

  //---- calibration                                                                                                                  kMaxTracks
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer0",   IsoTrack_calibrationdedxByLayer0  , "IsoTrack_calibrationdedxByLayer0[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer1",   IsoTrack_calibrationdedxByLayer1  , "IsoTrack_calibrationdedxByLayer1[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer2",   IsoTrack_calibrationdedxByLayer2  , "IsoTrack_calibrationdedxByLayer2[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer3",   IsoTrack_calibrationdedxByLayer3  , "IsoTrack_calibrationdedxByLayer3[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer4",   IsoTrack_calibrationdedxByLayer4  , "IsoTrack_calibrationdedxByLayer4[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer5",   IsoTrack_calibrationdedxByLayer5  , "IsoTrack_calibrationdedxByLayer5[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer6",   IsoTrack_calibrationdedxByLayer6  , "IsoTrack_calibrationdedxByLayer6[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer7",   IsoTrack_calibrationdedxByLayer7  , "IsoTrack_calibrationdedxByLayer7[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer8",   IsoTrack_calibrationdedxByLayer8  , "IsoTrack_calibrationdedxByLayer8[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer9",   IsoTrack_calibrationdedxByLayer9  , "IsoTrack_calibrationdedxByLayer9[1000]/F"  );                 
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer10",  IsoTrack_calibrationdedxByLayer10 , "IsoTrack_calibrationdedxByLayer10[1000]/F" );               
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer11",  IsoTrack_calibrationdedxByLayer11 , "IsoTrack_calibrationdedxByLayer11[1000]/F" );               
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer12",  IsoTrack_calibrationdedxByLayer12 , "IsoTrack_calibrationdedxByLayer12[1000]/F" );               
  outputTree_data->Branch("IsoTrack_calibrationdedxByLayer13",  IsoTrack_calibrationdedxByLayer13 , "IsoTrack_calibrationdedxByLayer13[1000]/F" );               
  
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer0",  IsoTrack_dedxByLayer0);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer1",  IsoTrack_dedxByLayer1);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer2",  IsoTrack_dedxByLayer2);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer3",  IsoTrack_dedxByLayer3);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer4",  IsoTrack_dedxByLayer4);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer5",  IsoTrack_dedxByLayer5);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer6",  IsoTrack_dedxByLayer6);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer7",  IsoTrack_dedxByLayer7);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer8",  IsoTrack_dedxByLayer8);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer9",  IsoTrack_dedxByLayer9);                 
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer10",  IsoTrack_dedxByLayer10);               
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer11",  IsoTrack_dedxByLayer11);               
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer12",  IsoTrack_dedxByLayer12);               
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer13",  IsoTrack_dedxByLayer13);               
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer0",  IsoTrack_pixByLayer0);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer1",  IsoTrack_pixByLayer1);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer2",  IsoTrack_pixByLayer2);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer3",  IsoTrack_pixByLayer3);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer4",  IsoTrack_pixByLayer4);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer5",  IsoTrack_pixByLayer5);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer6",  IsoTrack_pixByLayer6);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer7",  IsoTrack_pixByLayer7);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer8",  IsoTrack_pixByLayer8);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer9",  IsoTrack_pixByLayer9);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer10",  IsoTrack_pixByLayer10);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer11",  IsoTrack_pixByLayer11);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer12",  IsoTrack_pixByLayer12);
  inputTree_data->SetBranchAddress("IsoTrack_pixByLayer13",  IsoTrack_pixByLayer13);
  
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer0",  IsoTrack_layerOrSideByLayer0);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer1",  IsoTrack_layerOrSideByLayer1);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer2",  IsoTrack_layerOrSideByLayer2);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer3",  IsoTrack_layerOrSideByLayer3);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer4",  IsoTrack_layerOrSideByLayer4);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer5",  IsoTrack_layerOrSideByLayer5);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer6",  IsoTrack_layerOrSideByLayer6);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer7",  IsoTrack_layerOrSideByLayer7);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer8",  IsoTrack_layerOrSideByLayer8);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer9",  IsoTrack_layerOrSideByLayer9);                 
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer10",  IsoTrack_layerOrSideByLayer10);               
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer11",  IsoTrack_layerOrSideByLayer11);               
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer12",  IsoTrack_layerOrSideByLayer12);               
  inputTree_data->SetBranchAddress("IsoTrack_layerOrSideByLayer13",  IsoTrack_layerOrSideByLayer13);               
  
  
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer0",  IsoTrack_ladderOrBladeByLayer0);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer1",  IsoTrack_ladderOrBladeByLayer1);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer2",  IsoTrack_ladderOrBladeByLayer2);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer3",  IsoTrack_ladderOrBladeByLayer3);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer4",  IsoTrack_ladderOrBladeByLayer4);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer5",  IsoTrack_ladderOrBladeByLayer5);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer6",  IsoTrack_ladderOrBladeByLayer6);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer7",  IsoTrack_ladderOrBladeByLayer7);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer8",  IsoTrack_ladderOrBladeByLayer8);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer9",  IsoTrack_ladderOrBladeByLayer9);                 
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer10",  IsoTrack_ladderOrBladeByLayer10);               
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer11",  IsoTrack_ladderOrBladeByLayer11);               
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer12",  IsoTrack_ladderOrBladeByLayer12);               
  inputTree_data->SetBranchAddress("IsoTrack_ladderOrBladeByLayer13",  IsoTrack_ladderOrBladeByLayer13);               
  
  
  
  
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer0",  IsoTrack_subDetIdByLayer0);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer1",  IsoTrack_subDetIdByLayer1);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer2",  IsoTrack_subDetIdByLayer2);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer3",  IsoTrack_subDetIdByLayer3);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer4",  IsoTrack_subDetIdByLayer4);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer5",  IsoTrack_subDetIdByLayer5);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer6",  IsoTrack_subDetIdByLayer6);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer7",  IsoTrack_subDetIdByLayer7);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer8",  IsoTrack_subDetIdByLayer8);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer9",  IsoTrack_subDetIdByLayer9);                 
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer10",  IsoTrack_subDetIdByLayer10);               
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer11",  IsoTrack_subDetIdByLayer11);               
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer12",  IsoTrack_subDetIdByLayer12);               
  inputTree_data->SetBranchAddress("IsoTrack_subDetIdByLayer13",  IsoTrack_subDetIdByLayer13);               
  
  
  
  inputTree_data->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
  inputTree_data->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  inputTree_data->SetBranchAddress("IsoTrack_phi",  IsoTrack_phi);
  inputTree_data->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);
  inputTree_data->SetBranchAddress("IsoTrack_dxy",  IsoTrack_dxy);
  inputTree_data->SetBranchAddress("IsoTrack_dz",  IsoTrack_dz);
  inputTree_data->SetBranchAddress("nIsoTrack",  &nIsoTrack);

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
  
  
  int minRun = inputTree_data->GetMinimum ("run");
  int maxRun = inputTree_data->GetMaximum ("run") + 1;
  int deltaRun = (maxRun-minRun) / num_run_intervals;
  
  std::cout << " minRun = " << minRun << std::endl;
  std::cout << " maxRun = " << maxRun << std::endl;
  std::cout << " deltaRun = " << deltaRun << std::endl;
  
  
  for (int iEntry=0; iEntry<inputTree_data->GetEntries(); iEntry++) {
    inputTree_data->GetEntry(iEntry);

    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
  
//     std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    
    
    int iRun = FindInterval(run, minRun, deltaRun);
    //---- safe check
    if (iRun >= num_run_intervals) {
//       std::cout << " iRun = " << iRun << " :: " << num_run_intervals << std::endl;
      continue;      
    }
    
    int iEdge = -1;
    int ilayer = -1; // IsoTrack_layerOrSideByLayer0[iTrack];
    int iladderblade = -1; // IsoTrack_ladderOrBladeByLayer0[iTrack];
    
    
    for (int iTrack = 0; iTrack < std::min(kMaxTracks, nIsoTrack); iTrack++) {
    
      iEdge = FindEdgeAbs (IsoTrack_eta[iTrack], eta_edges);
      
      IsoTrack_calibrationdedxByLayer0[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer1[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer2[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer3[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer4[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer5[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer6[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer7[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer8[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer9[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer10[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer11[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer12[iTrack] = 1.;
      IsoTrack_calibrationdedxByLayer13[iTrack] = 1.;
      
      if (iEdge != -1) {
        
        if (IsoTrack_pixByLayer0[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer0[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer0[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer0[iTrack] != 0) {  
            if (IsoTrack_pixByLayer0[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer0[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer0[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }      
        
        
        if (IsoTrack_pixByLayer1[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer1[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer1[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer1[iTrack] != 0) {  
            if (IsoTrack_pixByLayer1[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer1[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer1[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer2[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer2[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer2[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer2[iTrack] != 0) {  
            if (IsoTrack_pixByLayer2[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer2[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer2[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        
        if (IsoTrack_pixByLayer3[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer3[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer3[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer3[iTrack] != 0) {  
            if (IsoTrack_pixByLayer3[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer3[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer3[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer4[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer4[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer4[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer4[iTrack] != 0) {  
            if (IsoTrack_pixByLayer4[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer4[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer4[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer5[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer5[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer5[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer5[iTrack] != 0) {  
            if (IsoTrack_pixByLayer5[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer5[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer5[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer6[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer6[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer6[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer6[iTrack] != 0) {  
            if (IsoTrack_pixByLayer6[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer6[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer6[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer7[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer7[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer7[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer7[iTrack] != 0) {  
            if (IsoTrack_pixByLayer7[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer7[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer7[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer8[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer8[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer8[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer8[iTrack] != 0) {  
            if (IsoTrack_pixByLayer8[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer8[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer8[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer9[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer9[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer9[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer9[iTrack] != 0) {  
            if (IsoTrack_pixByLayer9[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer9[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer9[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer10[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer10[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer10[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer10[iTrack] != 0) {  
            if (IsoTrack_pixByLayer10[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer10[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer10[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer11[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer11[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer11[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer11[iTrack] != 0) {  
            if (IsoTrack_pixByLayer11[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer11[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer11[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer12[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer12[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer12[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer12[iTrack] != 0) {  
            if (IsoTrack_pixByLayer12[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer12[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer12[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
        
        if (IsoTrack_pixByLayer0[iTrack] != 0) {  
          ilayer = IsoTrack_layerOrSideByLayer0[iTrack];
          iladderblade = IsoTrack_ladderOrBladeByLayer0[iTrack];   
        }  
        if ((ilayer >=0 && ilayer<layerId.size()) && (iladderblade>=0 && iladderblade<ladderbladeId.size())) {
          if (IsoTrack_pixByLayer13[iTrack] != 0) {  
            if (IsoTrack_pixByLayer13[iTrack] == 1) {
              //---- BPIX
              IsoTrack_calibrationdedxByLayer13[iTrack] = map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
            else {
              //---- FPIX
              IsoTrack_calibrationdedxByLayer13[iTrack] = map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade]; 
            }
          }
        }
      
      }
      
    }
    
    outputTree_data->Fill();     
    
  }
  
  
  
  std::cout << " minRun = " << minRun << std::endl;
  std::cout << " maxRun = " << maxRun << std::endl;
  std::cout << " deltaRun = " << deltaRun << std::endl;
 
  std::cout << std::endl;
  std::cout << " name_input_file_data = " << name_input_file_data << std::endl;
  std::cout << " name_output_file_data   = " << name_output_file_data << std::endl;
  
  
  outputTree_data->AutoSave();
  outputFile_data->Close();
  
}







