//
//   draw_integral
//
//
//   g++ -o draw_integral.exe draw_integral.cpp `root-config --cflags --glibs`
//
//

#include <ROOT/RDataFrame.hxx>


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
int FindEdge (float eta, std::vector<float>& eta_edges) {
  
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
  
  std::cout << " ================================ " << std::endl;
  std::cout << " Plot all time periods together " << std::endl;
  std::cout << " ================================ " << std::endl;
  
  //----
  //---- get the two root files with the two trees
  //----  
  
  std::string name_input_file_data = "out.root"; 
  if (argc>=2) {
    name_input_file_data = argv[1];
  }
  
  std::cout << " name_input_file_data = " << name_input_file_data << std::endl;
  
  ROOT::RDataFrame dataframe_data ("tree", name_input_file_data.c_str());
  
  std::string name_input_file_mc = "out.root";
  if (argc>=3) {
    name_input_file_mc = argv[2];
  }
  
  std::cout << " name_input_file_mc = " << name_input_file_mc << std::endl;
  ROOT::RDataFrame dataframe_mc ("tree", name_input_file_mc.c_str());
  
  
  
  
  std::string name_output_file_plots = "outplots.root";
  if (argc>=4) {
    name_output_file_plots = argv[3];
  }
  
  
  TFile* output_file_plots = new TFile (name_output_file_plots.c_str(), "RECREATE");
  
  
  //----
  //---- Now define the cuts, first the common ones, then the specific
  //----
  
  
  
  
  std::vector<float> eta_edges;
  
  eta_edges.push_back(0.0);
  eta_edges.push_back(0.3);  //--- exclude
  eta_edges.push_back(0.6);  //--- exclude
  eta_edges.push_back(1.0);  //--- exclude
  eta_edges.push_back(1.3);
  eta_edges.push_back(1.6);  //--- exclude
  eta_edges.push_back(2.1);
  eta_edges.push_back(2.5);
  
  
  
  
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
  
  
  
  
  
  //---- 
  //---- layer 
  //----
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<num_max_layer; ilayer++) {
    layerId.push_back(ilayer);
  }
  
  
  //---- 
  //---- ladderblade 
  //----
  std::vector<int> ladderbladeId;
  for (int iladderblade = 0; iladderblade<40; iladderblade++) {
    ladderbladeId.push_back(iladderblade);
  }
  
  
  
  //---- 
  //---- variables definition
  //---- 
  
  
//   std::string by_what = "ByHit";
  std::string by_what = "ByLayer";
  
  std::string variable_dedx         = "IsoTrack_dedxUnSmeared" + by_what ;
//   std::string variable_dedx         = "IsoTrack_dedx" + by_what ;
  
  std::string variable_layer        = "IsoTrack_layerOrSide" + by_what ;
  std::string variable_ladder_blade = "IsoTrack_ladderOrBlade" + by_what;
  
  std::string variable_eta          = "IsoTrack_eta";
  std::string variable_pt           = "IsoTrack_pt";
  
  
  auto cutGreater = [](float b2, float b1) { return b2 >  b1; };
  auto cutEqual   = [](float b2, float b1) { return b2 == b1; };
  auto cutBetween = [](float b,  float min, float max) { return (b <= max) && (b > min); };
  
  int iEdgeTotal;
//   auto cutFindEdgeAbs = [&](float eta[], int best_track) { return (iEdgeTotal == FindEdgeAbs (eta[best_track], eta_edges)); };
//   auto cutFindEdgeAbs = [&](float eta[], int best_track) { return (FindEdgeAbs (eta[best_track], eta_edges) == 10); };
  auto cutFindEdgeAbs = [](float eta[], int best_track) { return (eta[best_track] <10); };
  
  int iLayerTotal;
//   auto cutEqualLayer  = [&](int layer[], int best_track) { return layer[best_track] == iLayerTotal; };
  auto cutEqualLayer  = [&](int layer) { return layer == iLayerTotal; };
  
  int iBadderOrBladeTotal;
  auto cutEqualBadderOrBlade  = [&](int badderorblade[], int best_track) { return badderorblade[best_track] == iBadderOrBladeTotal; };
  
  
  //---- iterate over the hits
  for (int iHit = 0; iHit<14; iHit++) {
    
    //---- iterate over the layers
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      iLayerTotal = ilayer;
//       auto dataframe_data_layer = dataframe_data.Filter( cutEqualLayer, { variable_layer + std::to_string(iHit), "best_track" } );      
//       auto dataframe_mc_layer   = dataframe_mc.Filter  ( cutEqualLayer, { variable_layer + std::to_string(iHit), "best_track" } );      
      
      //---> it works but not what I want
//       auto dataframe_data_layer = dataframe_data.Filter( variable_layer + std::to_string(iHit) + "[best_track] == 1" );      
//       auto dataframe_mc_layer   = dataframe_mc.Filter  ( variable_layer + std::to_string(iHit) + "[best_track] == 1" );  
      
      auto dataframe_data_layer = dataframe_data.Define( variable_layer + std::to_string(iHit) + "_best_track", variable_layer + std::to_string(iHit) + "[best_track]" ).Filter( cutEqualLayer, { variable_layer + std::to_string(iHit) + "_best_track" } );      
      auto dataframe_mc_layer   = dataframe_mc.Define  ( variable_layer + std::to_string(iHit) + "_best_track", variable_layer + std::to_string(iHit) + "[best_track]" ).Filter( cutEqualLayer, { variable_layer + std::to_string(iHit) + "_best_track" } );      

//       auto dataframe_data_layer = dataframe_data.Define( variable_layer + std::to_string(iHit) + "_best_track", variable_layer + std::to_string(iHit) + "[best_track]" ).Filter( variable_layer + std::to_string(iHit) + "_best_track == 1"  );      
//       auto dataframe_mc_layer   = dataframe_mc.Define  ( variable_layer + std::to_string(iHit) + "_best_track", variable_layer + std::to_string(iHit) + "[best_track]" ).Filter( variable_layer + std::to_string(iHit) + "_best_track == 1"  );      
      
      
      //---- iterate over the eta regions
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        iEdgeTotal = iEdge;
//         auto dataframe_data_layer_eta = dataframe_data_layer.Filter( cutFindEdgeAbs, { variable_eta , "best_track" } );      
//         auto dataframe_mc_layer_eta   = dataframe_mc_layer.Filter  ( cutFindEdgeAbs, { variable_eta , "best_track" } );      
//         auto dataframe_data_layer_eta = dataframe_data_layer.Filter( variable_eta + "[best_track]<3" );      
//         auto dataframe_mc_layer_eta   = dataframe_mc_layer.Filter  ( variable_eta + "[best_track]<3" );      
        
        //---- iterate over the ladder (BPIX) and blade (FPIX)
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     

          iBadderOrBladeTotal = iladderblade;
//           auto dataframe_data_layer_eta_ladderblade = dataframe_data_layer_eta.Filter( cutEqualBadderOrBlade, { variable_ladder_blade + std::to_string(iHit), "best_track" } );      
//           auto dataframe_mc_layer_eta_ladderblade   = dataframe_mc_layer_eta.Filter  ( cutEqualBadderOrBlade, { variable_ladder_blade + std::to_string(iHit), "best_track" } );      
          
          //---- https://root-forum.cern.ch/t/rdataframe-histo1d-to-extract-histogram-from-an-indexed-vector-branch/31066
          
//           auto h_data = dataframe_data_layer_eta_ladderblade
//                                                     .Define(variable_dedx+ std::to_string(iHit) + "_best_track", variable_dedx+ std::to_string(iHit) + "[best_track]")
//                                                     .Histo1D(variable_dedx+ std::to_string(iHit) + "_best_track");
//           auto h_mc   = dataframe_data_layer_eta_ladderblade
//                                                     .Define(variable_dedx+ std::to_string(iHit) + "_best_track", variable_dedx+ std::to_string(iHit) + "[best_track]")
//                                                     .Histo1D(variable_dedx+ std::to_string(iHit) + "_best_track");
// 
         
          output_file_plots->cd();
//           h_data->Write();
//           h_mc->Write();
          
          //           std::cout << "ciao" << std::endl;
        }
      }
    }
  }
  
  
  
  
  
//   auto h_data = dataframe_data.Filter("IsoTrack_layerOrSideByHit0==1").Histo1D("IsoTrack_layerOrSideByHit0");
//   auto h_mc = dataframe_mc.Filter("IsoTrack_layerOrSideByHit0==1").Histo1D("IsoTrack_layerOrSideByHit0");
   
  
 
}






