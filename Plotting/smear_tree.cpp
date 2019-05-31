//
// smear_tree
//
//
//   g++ -o smear_tree.exe smear_tree.cpp `root-config --cflags --glibs`
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
  
  int num_max_layer = 5;
  int min_layer = 0;
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<num_max_layer; ilayer++) {
    layerId.push_back(ilayer+1 + min_layer); // counting starts from 1
  }
  
  
  
  
  std::vector<float> eta_edges;
  
  eta_edges.push_back(0.0);
  eta_edges.push_back(2.5);
  
  
  
  //---- layer         eta             
  std::vector  < std::vector < float > > map_smearing_BPIX;
  std::vector  < std::vector < float > > map_smearing_FPIX;
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    std::vector < float > v_smear;
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      v_smear.push_back(0.0);
    }
    map_smearing_BPIX.push_back(v_smear);
    map_smearing_FPIX.push_back(v_smear);
  }
  
  
  
  std::string buffer;
  float value;
  
  
  std::string fileSmear_BPIX = "../Calibration/smear_BPIX_pixels.txt";
  std::cout << " fileCalibration BPIX = " << fileSmear_BPIX << std::endl;
  
  std::ifstream file_BPIX (fileSmear_BPIX); 
  
  if(!file_BPIX.is_open()) {
    std::cerr << "** ERROR: Can't open '" << fileSmear_BPIX << "' for input" << " file_BPIX.is_open() = " << file_BPIX.is_open() << std::endl;
    return false;
  }
  
  while(!file_BPIX.eof()) {
    getline(file_BPIX,buffer);
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end!
      std::stringstream line( buffer );  
      
      //         iEdge << " " << num_layerId << " " << num_ladderbladeId << "     "  << iRun 
      
      int iEdge;
      int ilayer;
      
      line >> iEdge;
      line >> ilayer;
      
      //----
      // transform  "num_layerId" into "ilayer"
      ilayer = ilayer -1 - min_layer ; // counting starts from 1
      //----
      
      // needed fix because I should read only the layers that then I will use
      if (ilayer >=0 && ilayer<layerId.size()) {
        float smear_factor = 0.0;
        line >> smear_factor;
        //---- fix
        if (smear_factor < 0) smear_factor = 0;
        map_smearing_BPIX[ilayer][iEdge] = smear_factor;
      }
      
    } 
  }
  
  
  std::string fileSmear_FPIX = "../Calibration/smear_FPIX_pixels.txt";
  std::cout << " fileCalibration FPIX = " << fileSmear_FPIX << std::endl;
  
  std::ifstream file_FPIX (fileSmear_FPIX); 
  
  if(!file_FPIX.is_open()) {
    std::cerr << "** ERROR: Can't open '" << fileSmear_FPIX << "' for input" << std::endl;
    return false;
  }
  
  while(!file_FPIX.eof()) {
    getline(file_FPIX,buffer);
    if (buffer != "" && buffer.at(0) != '#'){ ///---> save from empty line at the end!
      std::stringstream line( buffer );  
      
      //         iEdge << " " << num_layerId << " " << num_ladderbladeId << "     "  << iRun 
      
      int iEdge;
      int ilayer;
      
      line >> iEdge;
      line >> ilayer;
      
      //----
      // transform  "num_layerId" into "ilayer"
      ilayer = ilayer -1 - min_layer ; // counting starts from 1
      //----
      
      // needed fix because I should read only the layers that then I will use
      if (ilayer >=0 && ilayer<layerId.size()) {
        float smear_factor = 0.0;
        line >> smear_factor;
        //---- fix
        if (smear_factor < 0) smear_factor = 0;
        map_smearing_FPIX[ilayer][iEdge] = smear_factor;
      }
      
    } 
  }
  
  
  
  TF1* f_smearing = new TF1 ("f_smearing", "gaus", 0, 2);
  f_smearing->SetParameter(0,1.0); // norm
  f_smearing->SetParameter(1,1.0); // mean
  f_smearing->SetParameter(2,1.0); // sigma
  
  
  
  
  std::string by_what;
  by_what = "ByHit";
//   by_what = "ByLayer";
  
  std::string variable_eta             = "IsoTrack_eta";
  std::string variable_layer           = "IsoTrack_layerOrSide" + by_what ;  
  std::string variable_pix             = "IsoTrack_pix" + by_what;
  std::string variable_dedxUnsmeared   = "IsoTrack_dedxUnSmeared" + by_what;
  
  
  
  const Int_t kMaxTracks = 1000;
  
  Float_t IsoTrack_eta[kMaxTracks];
  
  Int_t IsoTrack_layerOrSide_1[kMaxTracks];        Int_t IsoTrack_pix_1[kMaxTracks];      Float_t IsoTrack_dedxUnsmeared_1[kMaxTracks];
  Int_t IsoTrack_layerOrSide_2[kMaxTracks];        Int_t IsoTrack_pix_2[kMaxTracks];      Float_t IsoTrack_dedxUnsmeared_2[kMaxTracks];
  Int_t IsoTrack_layerOrSide_3[kMaxTracks];        Int_t IsoTrack_pix_3[kMaxTracks];      Float_t IsoTrack_dedxUnsmeared_3[kMaxTracks];
  Int_t IsoTrack_layerOrSide_4[kMaxTracks];        Int_t IsoTrack_pix_4[kMaxTracks];      Float_t IsoTrack_dedxUnsmeared_4[kMaxTracks];
  Int_t IsoTrack_layerOrSide_5[kMaxTracks];        Int_t IsoTrack_pix_5[kMaxTracks];      Float_t IsoTrack_dedxUnsmeared_5[kMaxTracks];
  Int_t IsoTrack_layerOrSide_6[kMaxTracks];        Int_t IsoTrack_pix_6[kMaxTracks];      Float_t IsoTrack_dedxUnsmeared_6[kMaxTracks];
 
  Int_t nIsoTrack;
  
  int best_track;

  
  inputTree->SetBranchAddress("best_track",  &best_track);
  
  inputTree->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  inputTree->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  
  inputTree->SetBranchAddress( (variable_layer + "1").c_str(),  IsoTrack_layerOrSide_1);
  inputTree->SetBranchAddress( (variable_layer + "2").c_str(),  IsoTrack_layerOrSide_2);
  inputTree->SetBranchAddress( (variable_layer + "3").c_str(),  IsoTrack_layerOrSide_3);
  inputTree->SetBranchAddress( (variable_layer + "4").c_str(),  IsoTrack_layerOrSide_4);
  inputTree->SetBranchAddress( (variable_layer + "5").c_str(),  IsoTrack_layerOrSide_5);
  inputTree->SetBranchAddress( (variable_layer + "6").c_str(),  IsoTrack_layerOrSide_6);
                                                
  inputTree->SetBranchAddress( (variable_pix + "1").c_str(),  IsoTrack_pix_1);
  inputTree->SetBranchAddress( (variable_pix + "2").c_str(),  IsoTrack_pix_2);
  inputTree->SetBranchAddress( (variable_pix + "3").c_str(),  IsoTrack_pix_3);
  inputTree->SetBranchAddress( (variable_pix + "4").c_str(),  IsoTrack_pix_4);
  inputTree->SetBranchAddress( (variable_pix + "5").c_str(),  IsoTrack_pix_5);
  inputTree->SetBranchAddress( (variable_pix + "6").c_str(),  IsoTrack_pix_6);
  
  inputTree->SetBranchAddress( (variable_dedxUnsmeared + "1").c_str(),  IsoTrack_dedxUnsmeared_1);
  inputTree->SetBranchAddress( (variable_dedxUnsmeared + "2").c_str(),  IsoTrack_dedxUnsmeared_2);
  inputTree->SetBranchAddress( (variable_dedxUnsmeared + "3").c_str(),  IsoTrack_dedxUnsmeared_3);
  inputTree->SetBranchAddress( (variable_dedxUnsmeared + "4").c_str(),  IsoTrack_dedxUnsmeared_4);
  inputTree->SetBranchAddress( (variable_dedxUnsmeared + "5").c_str(),  IsoTrack_dedxUnsmeared_5);
  inputTree->SetBranchAddress( (variable_dedxUnsmeared + "6").c_str(),  IsoTrack_dedxUnsmeared_6);

   

  //---- not to be saved in new ttree  
//   inputTree->SetBranchStatus((variable_dedxUnsmeared + "1").c_str(), 0 );
//   inputTree->SetBranchStatus((variable_dedxUnsmeared + "2").c_str(), 0 );
//   inputTree->SetBranchStatus((variable_dedxUnsmeared + "3").c_str(), 0 );
//   inputTree->SetBranchStatus((variable_dedxUnsmeared + "4").c_str(), 0 );
//   inputTree->SetBranchStatus((variable_dedxUnsmeared + "5").c_str(), 0 );
//   inputTree->SetBranchStatus((variable_dedxUnsmeared + "6").c_str(), 0 );
  
  
  TFile* outputFile = new TFile (name_output_file.c_str(), "RECREATE");   
  TTree *outputTree = inputTree->CloneTree(0);
 
  //---- to be changed
  outputTree->SetBranchAddress ( (variable_dedxUnsmeared + "1").c_str(),  IsoTrack_dedxUnsmeared_1);
  outputTree->SetBranchAddress ( (variable_dedxUnsmeared + "2").c_str(),  IsoTrack_dedxUnsmeared_2);
  outputTree->SetBranchAddress ( (variable_dedxUnsmeared + "3").c_str(),  IsoTrack_dedxUnsmeared_3);
  outputTree->SetBranchAddress ( (variable_dedxUnsmeared + "4").c_str(),  IsoTrack_dedxUnsmeared_4);
  outputTree->SetBranchAddress ( (variable_dedxUnsmeared + "5").c_str(),  IsoTrack_dedxUnsmeared_5);
  outputTree->SetBranchAddress ( (variable_dedxUnsmeared + "6").c_str(),  IsoTrack_dedxUnsmeared_6);

//  outputTree->Branch ( (variable_dedxUnsmeared + "1").c_str(),  IsoTrack_dedxUnsmeared_1, ( (variable_dedxUnsmeared + "1") + "[1000]" ) .c_str() );
//  outputTree->Branch ( (variable_dedxUnsmeared + "2").c_str(),  IsoTrack_dedxUnsmeared_2, ( (variable_dedxUnsmeared + "2") + "[1000]" ) .c_str() );
//  outputTree->Branch ( (variable_dedxUnsmeared + "3").c_str(),  IsoTrack_dedxUnsmeared_3, ( (variable_dedxUnsmeared + "3") + "[1000]" ) .c_str() );
//  outputTree->Branch ( (variable_dedxUnsmeared + "4").c_str(),  IsoTrack_dedxUnsmeared_4, ( (variable_dedxUnsmeared + "4") + "[1000]" ) .c_str() );
//  outputTree->Branch ( (variable_dedxUnsmeared + "5").c_str(),  IsoTrack_dedxUnsmeared_5, ( (variable_dedxUnsmeared + "5") + "[1000]" ) .c_str() );
//  outputTree->Branch ( (variable_dedxUnsmeared + "6").c_str(),  IsoTrack_dedxUnsmeared_6, ( (variable_dedxUnsmeared + "6") + "[1000]" ) .c_str() );
  
  
  for (int iEntry=0; iEntry<inputTree->GetEntries(); iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree->GetEntry(iEntry);
    
    int ilayer;
    int iEdge;
    iEdge  = FindEdgeAbs (IsoTrack_eta[best_track], eta_edges);
    
//     std::cout << " ilayer = " << ilayer << " iEdge = " << iEdge << " [IsoTrack_eta[" << best_track << "] = " << IsoTrack_eta[best_track] << " ]" << std::endl;
    
    float dedx_temp; 
    float additional_smearing = 1.0;
    
//     IsoTrack_pix
//     == 1 BPIX
//     == 2 FPIX
    
    ilayer = IsoTrack_layerOrSide_1[best_track] - 1;
    
    if (IsoTrack_pix_1[best_track] == 1) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_BPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }
    }
    
    if (IsoTrack_pix_1[best_track] == 2) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_FPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }  
    }
    
//     std::cout << " additional_smearing = " << additional_smearing << std::endl;
    dedx_temp = IsoTrack_dedxUnsmeared_1[best_track];
    IsoTrack_dedxUnsmeared_1[best_track] = dedx_temp * additional_smearing;
//     IsoTrack_dedxUnsmeared_1[best_track] = 5.0; // TEST
    


    //  Hit_2
    
    ilayer = IsoTrack_layerOrSide_2[best_track] - 1;
    
    if (IsoTrack_pix_2[best_track] == 1) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_BPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }
    }
    
    if (IsoTrack_pix_2[best_track] == 2) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_FPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }  
    }
    
    dedx_temp = IsoTrack_dedxUnsmeared_2[best_track];
    IsoTrack_dedxUnsmeared_2[best_track] = dedx_temp * additional_smearing;
    
 
    
    //  Hit_3
    
    ilayer = IsoTrack_layerOrSide_3[best_track] - 1;
    
    if (IsoTrack_pix_3[best_track] == 1) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_BPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }
    }
    
    if (IsoTrack_pix_3[best_track] == 2) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_FPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }  
    }
    
    dedx_temp = IsoTrack_dedxUnsmeared_3[best_track];
    IsoTrack_dedxUnsmeared_3[best_track] = dedx_temp * additional_smearing;
    
    
    //  Hit_4
    
    ilayer = IsoTrack_layerOrSide_4[best_track] - 1;
    
    if (IsoTrack_pix_4[best_track] == 1) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_BPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }
    }
    
    if (IsoTrack_pix_4[best_track] == 2) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_FPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }  
    }
    
    dedx_temp = IsoTrack_dedxUnsmeared_4[best_track];
    IsoTrack_dedxUnsmeared_4[best_track] = dedx_temp * additional_smearing;
    
    
    //  Hit_5
    
    ilayer = IsoTrack_layerOrSide_5[best_track] - 1;
    
    if (IsoTrack_pix_5[best_track] == 1) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_BPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }
    }
    
    if (IsoTrack_pix_5[best_track] == 2) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_FPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }  
    }
    
    dedx_temp = IsoTrack_dedxUnsmeared_5[best_track];
    IsoTrack_dedxUnsmeared_5[best_track] = dedx_temp * additional_smearing;
    
    
    //  Hit_6
    
    ilayer = IsoTrack_layerOrSide_6[best_track] - 1;
    
    if (IsoTrack_pix_6[best_track] == 1) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_BPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }
    }
    
    if (IsoTrack_pix_6[best_track] == 2) {
      if ( map_smearing_BPIX[ilayer][iEdge] != 0) {
        f_smearing->SetParameter(2, map_smearing_FPIX[ilayer][iEdge] );
        additional_smearing = f_smearing->GetRandom();
        if (additional_smearing <=0) additional_smearing = 1.0;
      }  
    }
    
    dedx_temp = IsoTrack_dedxUnsmeared_6[best_track];
    IsoTrack_dedxUnsmeared_6[best_track] = dedx_temp * additional_smearing;
    
    

    
    

    outputTree->Fill();     
    
  }
  
  std::cout << " saved entries = " << outputTree->GetEntries() << " out of: " << inputTree->GetEntries() << std::endl;
  
  outputTree->AutoSave();
  
  outputFile->Close();
  
}






