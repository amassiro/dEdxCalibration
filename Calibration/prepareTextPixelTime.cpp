//
// prepareTextPixelTime
//
//
//   g++ -o prepareTextPixelTime.exe prepareTextPixelTime.cpp `root-config --cflags --glibs`
//
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "TTree.h"
#include "TFile.h"



int main(int argc, char** argv) {
  
  std::string name_output_file = "test.txt";
  
  if (argc>=2) {
    name_output_file = argv[1];
  }
  
  int num_run_intervals = 10;
  if (argc>=3) {
    num_run_intervals = atoi(argv[2]);
  }
  std::cout << " num_run_intervals = " << num_run_intervals << std::endl;
  
  int num_max_layer = 5; // 20
  if (argc>=4) {
    num_max_layer = atoi(argv[3]);
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
  
//   eta_edges.push_back(0.3);  //--- exclude
//   eta_edges.push_back(0.6);  //--- exclude
//   eta_edges.push_back(1.0);  //--- exclude
  eta_edges.push_back(1.3);
//   eta_edges.push_back(1.6);  //--- exclude
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
  std::string fileCalibration_BPIX = "scale_BPIX_pixels_run_ranges.txt";
  fileCalibration_BPIX = argv[4];
  std::cout << " fileCalibration BPIX = " << fileCalibration_BPIX << std::endl;
  
  std::ifstream file_BPIX (fileCalibration_BPIX); 
  std::string buffer;
  float value;
  
  if(!file_BPIX.is_open()) {
    std::cerr << "** ERROR: Can't open '" << fileCalibration_BPIX << "' for input" << std::endl;
    return false;
  }
  
  while(!file_BPIX.eof()) {
    getline(file_BPIX,buffer);
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
  
  
  std::string fileCalibration_FPIX = argv[5];
  
  std::cout << " fileCalibration FPIX = " << fileCalibration_FPIX << std::endl;
  
  std::ifstream file_FPIX (fileCalibration_FPIX); 
  
  if(!file_FPIX.is_open()) {
    std::cerr << "** ERROR: Can't open '" << fileCalibration_FPIX << "' for input" << std::endl;
    return false;
  }
  
  while(!file_FPIX.eof()) {
    getline(file_FPIX,buffer);
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
  
  
  
  
//   std::string name_input_file_data = "Data/tree_filtered_data.root";
//   std::string name_input_file_data = "Data/tree_filtered_data_calibrated_cmssw.root";
//   std::string name_input_file_data = "Data/tree_filtered_data_calibrated_cmssw_firstRound.root";
//   std::string name_input_file_data = "Data/7Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root";

  std::string name_input_file_data = "data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root";
  
  
  

  std::cout << " template run ranges from : " << name_input_file_data << std::endl;
  
  TFile* inputFile_data = new TFile (name_input_file_data.c_str(), "READ");   
  TTree* inputTree_data = (TTree*) ((TTree*) inputFile_data -> Get ("tree")) -> Clone ("tree_data");
  
  int minRun = inputTree_data->GetMinimum ("run");
  int maxRun = inputTree_data->GetMaximum ("run") + 1;
  int deltaRun = ceil( 1. * (maxRun-minRun) / num_run_intervals );
  
  std::cout << " minRun = " << minRun << std::endl;
  std::cout << " maxRun = " << maxRun << std::endl;
  std::cout << " deltaRun = " << deltaRun << std::endl;
  
  
  
  
  std::ofstream myfile_output;
  myfile_output.open (name_output_file);
  
  myfile_output << "#  " << std::endl;
  myfile_output << "# pix layerorside ladderorblade etaMin etaMax  irunMin irunMax  value " << std::endl;
  myfile_output << "#  " << std::endl;
  
  //---- print calibration map
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        for (int iRun = 0; iRun < num_run_intervals; iRun++) {
          
          //---- 1 = bpix, 2 = fpix
          
          //---- 2 = FPIX
          if (map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade] != 1) {
            myfile_output << 2;
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << ilayer;
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << iladderblade;
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << eta_edges[iEdge];
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << eta_edges[iEdge+1];
            myfile_output << "     " << int(minRun + iRun     * deltaRun);
            myfile_output << "     " << int(minRun + (iRun+1) * deltaRun);          
            myfile_output << "     " << std::fixed << std::setprecision(5) << " " << map_calibration_FPIX[iRun][ilayer][iEdge][iladderblade];
            myfile_output << std::endl;
          }
          
          //---- 1 = BPIX
          if (map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade] != 1) {
            myfile_output << 1;
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << ilayer;
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << iladderblade;
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << eta_edges[iEdge];
            myfile_output << "     " << std::fixed << std::setprecision(3) << " " << eta_edges[iEdge+1];
            myfile_output << "     " << int(minRun + iRun     * deltaRun);
            myfile_output << "     " << int(minRun + (iRun+1) * deltaRun);          
            myfile_output << "     " << std::fixed << std::setprecision(5) << " " << map_calibration_BPIX[iRun][ilayer][iEdge][iladderblade];
            myfile_output << std::endl;
          }
          
        }
      }
    }
  }
  
  
  
  myfile_output.close();
  
  
  
  
}







