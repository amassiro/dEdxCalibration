//
//   draw_integral
//
//
//   g++ -o draw_integral_ttree.exe draw_integral_ttree.cpp `root-config --cflags --glibs`
//
//

// #include <ROOT/RDataFrame.hxx>


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
  
  TFile* inputFile_data = new TFile (name_input_file_data.c_str(), "READ");   
  TTree* inputTree_data = (TTree*) ((TTree*) inputFile_data -> Get ("tree")) -> Clone ("tree_data");
  
  std::string name_input_file_mc = "out.root";
  if (argc>=3) {
    name_input_file_mc = argv[2];
  }
  
  std::cout << " name_input_file_mc = " << name_input_file_mc << std::endl;
 
  TFile* inputFile_mc = new TFile (name_input_file_mc.c_str(), "READ");   
  TTree* inputTree_mc = (TTree*) ((TTree*) inputFile_mc -> Get ("tree")) -> Clone ("tree_mc");
  
  
  
  
  std::string name_output_file_plots = "outplots.root";
  if (argc>=4) {
    name_output_file_plots = argv[3];
  }
  
  
  TFile* output_file_plots = new TFile (name_output_file_plots.c_str(), "RECREATE");
  
  //----
  //---- Now define the cuts, first the common ones, then the specific
  //----
  
  
  
  
  std::vector<float> eta_edges;
  
//   eta_edges.push_back(0.0);
//   eta_edges.push_back(0.3);  //--- exclude
//   eta_edges.push_back(0.6);  //--- exclude
//   eta_edges.push_back(1.0);  //--- exclude
//   eta_edges.push_back(1.3);
//   eta_edges.push_back(1.6);  //--- exclude
//   eta_edges.push_back(2.1);
//   eta_edges.push_back(2.5);



//   eta_edges.push_back(0.0);
// //   eta_edges.push_back(0.3);  //--- exclude
// //   eta_edges.push_back(0.6);  //--- exclude
// //   eta_edges.push_back(1.0);  //--- exclude
//   eta_edges.push_back(1.3);
// //   eta_edges.push_back(1.6);  //--- exclude
//   eta_edges.push_back(2.1);
//   eta_edges.push_back(2.5);
  
  
  eta_edges.push_back(0.0);
  eta_edges.push_back(2.5);
  
  
  
  int num_run_intervals = 10;
  if (argc>=5) {
    num_run_intervals = atoi(argv[4]);
  }
  std::cout << " num_run_intervals = " << num_run_intervals << std::endl;
  
  int num_max_layer = 5; // 20
  if (argc>=6) {
    num_max_layer = atoi(argv[5]);
  }
  std::cout << " num_max_layer = " << num_max_layer << std::endl;
  

  int num_max_hit = 10;
  if (argc>=7) {
    num_max_hit = atoi(argv[6]);
  }
  std::cout << " num_max_hit = " << num_max_hit << std::endl;
  
  
  int num_max_labberblade = 40;
  if (argc>=8) {
    num_max_labberblade = atoi(argv[7]);
  }
  std::cout << " num_max_labberblade = " << num_max_labberblade << std::endl;


  int new_by_what = 0;
  if (argc>=9) {
    new_by_what = atoi(argv[8]);
  }
  
  std::string by_what;
  
  if (new_by_what == 1) by_what = "ByHit";
  else                  by_what = "ByLayer";
  
  std::cout << " new_by_what = " << new_by_what;
  std::cout << "   --> by_what = " << by_what << std::endl;
  
  
  
  int minRun = inputTree_data->GetMinimum ("run");
  int maxRun = inputTree_data->GetMaximum ("run") + 1;
  int deltaRun = ceil( 1. * (maxRun-minRun) / num_run_intervals );
  
  std::cout << "        minRun   " << minRun << std::endl;
  std::cout << "        maxRun   " << maxRun << std::endl;
  std::cout << "        deltaRun " << deltaRun << std::endl;
  std::cout << "        maxRun*  " << minRun+deltaRun*num_run_intervals << std::endl;
  
  
  
  //---- 
  //---- layer 
  //----
  
  int min_layer = 0; //---- start from the first layer!
  if (argc>=10) {
    min_layer = atoi(argv[9]);
  }
  
  std::cout << " min_layer = " << min_layer << std::endl;  
  
  
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<num_max_layer; ilayer++) {
    layerId.push_back(ilayer+1 + min_layer); // counting starts from 1
  }
  
  
  //---- 
  //---- ladderblade 
  //----
  std::vector<int> ladderbladeId;
  for (int iladderblade = 0; iladderblade<num_max_labberblade; iladderblade++) {
    ladderbladeId.push_back(iladderblade+1); // counting starts from 1
  }
  
  
  
//   
//   NBIN, minBIN, maxBIN
//   

  int NBIN = 50;
  float minBIN = 0;
  float maxBIN = 10;
  
  
  // it is useless to have many ladders in first layers, while removing ladders in last layers
  //
  //    BPIX:
  //    IsoTrack_ladderOrBladeByHit0: [1 .. 12], [1 .. 28], [1 .. 44], [1 .. 64]
  //    IsoTrack_layerOrSideByHit0 : 1, 2, 3, 4
  //    
  //    
  //    FPIX: 
  //    IsoTrack_ladderOrBladeByHit0: [1 .. 56]
  //    IsoTrack_layerOrSideByHit0 : 1, 2, 3
  //    
  std::map<int, int> map_layer_max_ladders_BPIX;
  std::map<int, int> map_layer_max_ladders_FPIX;
  map_layer_max_ladders_BPIX[1] = 12;
  map_layer_max_ladders_BPIX[2] = 28;
  map_layer_max_ladders_BPIX[3] = 44;
  map_layer_max_ladders_BPIX[4] = 64;

  map_layer_max_ladders_FPIX[1] = 56;
  map_layer_max_ladders_FPIX[2] = 56;
  map_layer_max_ladders_FPIX[3] = 56;
  map_layer_max_ladders_FPIX[4] = 0;
  
  
       
  
  
  
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
          
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_data", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
          TH1F* temp = new TH1F (name.Data(), "data", NBIN, minBIN, maxBIN);  
          setupHisto(temp, iRun);
          v_h_BPIX.push_back ( temp );
          
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_data", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
          TH1F* temp2 = new TH1F (name.Data(), "data", NBIN, minBIN, maxBIN);  
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
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_data", layerId.at(ilayer), iEdge);   
      TH1F* temp = new TH1F (name.Data(), "data", NBIN, minBIN, maxBIN);  
      setupHisto(temp, iEdge);
      v_h_BPIX.push_back ( temp );
      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_data", layerId.at(ilayer), iEdge);   
      TH1F* temp2 = new TH1F (name.Data(), "data", NBIN, minBIN, maxBIN);  
      setupHisto(temp2, iEdge);
      v_h_FPIX.push_back ( temp2 );
      
    }
    map_h_BPIX_reduced_data.push_back( v_h_BPIX );
    map_h_FPIX_reduced_data.push_back( v_h_FPIX );
  }
  
  
  
  
  
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
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
          TH1F* temp = new TH1F (name.Data(), "mc", NBIN, minBIN, maxBIN);  
          setupHisto(temp, iRun);
          v_h_BPIX.push_back ( temp );
          
          
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_mc", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
          TH1F* temp2 = new TH1F (name.Data(), "mc", NBIN, minBIN, maxBIN);  
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
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_mc", layerId.at(ilayer), iEdge);   
      TH1F* temp = new TH1F (name.Data(), "mc", NBIN, minBIN, maxBIN);  
      setupHisto(temp, iEdge +1 );
      v_h_BPIX.push_back ( temp );
      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_mc", layerId.at(ilayer), iEdge);   
      TH1F* temp2 = new TH1F (name.Data(), "mc", NBIN, minBIN, maxBIN);  
      setupHisto(temp2, iEdge +1 );
      v_h_FPIX.push_back ( temp2 );
      
    }
    map_h_BPIX_reduced_mc.push_back( v_h_BPIX );
    map_h_FPIX_reduced_mc.push_back( v_h_FPIX );
  }
  
  
  
  
  //---- 
  //---- variables definition
  //---- 
  
  
//   std::string variable_dedx         = "IsoTrack_dedxUnSmeared" + by_what ;
  std::string variable_dedx         = "IsoTrack_dedx" + by_what ;
  
  std::string variable_layer        = "IsoTrack_layerOrSide" + by_what ;
  std::string variable_ladder_blade = "IsoTrack_ladderOrBlade" + by_what;
  
  std::string variable_eta          = "IsoTrack_eta";
  std::string variable_pt           = "IsoTrack_pt";
  
  std::string variable_pix           = "IsoTrack_pix" + by_what;
  
  
  
  output_file_plots->cd();
 
  //---- iterate over the hits
  for (int iHit = 0; iHit<num_max_hit; iHit++) {
    std::cout << " iHit = " << iHit << " :: " << num_max_hit << std::endl;
    //---- iterate over the hits
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      std::cout << " layerId.at(ilayer) = " << layerId.at(ilayer) << std::endl;
      //---- iterate over the eta regions
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        std::cout << " iEdge = " << iEdge << std::endl;
        //---- iterate over the run
        for (int iRun = 0; iRun<num_run_intervals; iRun++) {
          //---- iterate over the ladder (BPIX) and blade (FPIX)
          for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
            std::cout << " ladderbladeId.at(iladderblade) = " << ladderbladeId.at(iladderblade) << std::endl;
            std::string whatToDraw;
            TString name;   
            std::string cutToDraw ;
            
            if ( ladderbladeId.at(iladderblade) <= map_layer_max_ladders_BPIX[layerId.at(ilayer)] ) {  // optimization
              //
              // Data
              //
              // BPIX
              cutToDraw  = "(" + variable_layer + std::to_string(iHit) + "[best_track] == " + std::to_string(layerId.at(ilayer)) + ") && " + \
                           "(" + variable_ladder_blade + std::to_string(iHit) + "[best_track] == " + std::to_string(ladderbladeId.at(iladderblade)) + ") && " + \
                           "(" + variable_pix + std::to_string(iHit) + "[best_track] == 1 ) && " + \
                           "( (run >= " + std::to_string(minRun+iRun*deltaRun) + ") && (run < " + std::to_string(minRun+(iRun+1)*deltaRun) + ")  ) && " + \
                           "( (  abs(" + variable_eta  + "[best_track] ) >="  + std::to_string( eta_edges.at(iEdge) ) + ") && (  abs(" + variable_eta  + "[best_track] ) <"  + std::to_string( eta_edges.at(iEdge+1) ) + ")   )" + \
                           " ";
  
              name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_data", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
              whatToDraw = variable_dedx+ std::to_string(iHit) + "[best_track] >>+ " + name.Data();
              
              std::cout << " whatToDraw = " << whatToDraw << std::endl;
              std::cout << " cutToDraw  = " << cutToDraw << std::endl;
              inputTree_data -> Draw(whatToDraw.c_str(), cutToDraw.c_str(), "goff");
              
              std::cout << " > Get Entries: " << inputTree_data -> GetEntries(cutToDraw.c_str()) << std::endl;
              
              //
              // MC
              //
              // BPIX
              cutToDraw  = "(" + variable_layer + std::to_string(iHit) + "[best_track] == " + std::to_string(layerId.at(ilayer)) + ") && " + \
                           "(" + variable_ladder_blade + std::to_string(iHit) + "[best_track] == " + std::to_string(ladderbladeId.at(iladderblade)) + ") && " + \
                           "(" + variable_pix + std::to_string(iHit) + "[best_track] == 1 ) && " + \
                           "( (  abs(" + variable_eta  + "[best_track] ) >="  + std::to_string( eta_edges.at(iEdge) ) + ") && (  abs(" + variable_eta  + "[best_track] ) <"  + std::to_string( eta_edges.at(iEdge+1) ) + ")   )" + \
                           " ";
  
              name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", 0, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
              whatToDraw = variable_dedx+ std::to_string(iHit) + "[best_track] >>+ " + name.Data();
              
              std::cout << " whatToDraw = " << whatToDraw << std::endl;
              inputTree_mc -> Draw(whatToDraw.c_str(), cutToDraw.c_str(), "goff");  
  
            }
            
            if ( ladderbladeId.at(iladderblade) <= map_layer_max_ladders_FPIX[layerId.at(ilayer)] ) {  // optimization  
              //
              // Data
              //
              // FPIX
              cutToDraw  = "(" + variable_layer + std::to_string(iHit) + "[best_track] == " + std::to_string(layerId.at(ilayer)) + ") && " + \
                           "(" + variable_ladder_blade + std::to_string(iHit) + "[best_track] == " + std::to_string(ladderbladeId.at(iladderblade)) + ") && " + \
                           "(" + variable_pix + std::to_string(iHit) + "[best_track] == 2 ) && " + \
                           "( (run >= " + std::to_string(minRun+iRun*deltaRun) + ") && (run < " + std::to_string(minRun+(iRun+1)*deltaRun) + ")  ) && " + \
                           "( (  abs(" + variable_eta  + "[best_track] ) >="  + std::to_string( eta_edges.at(iEdge) ) + ") && (  abs(" + variable_eta  + "[best_track] ) <"  + std::to_string( eta_edges.at(iEdge+1) ) + ")   )" + \
                           " ";
  
              name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_data", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
              whatToDraw = variable_dedx+ std::to_string(iHit) + "[best_track] >>+ " + name.Data();
              
              std::cout << " whatToDraw = " << whatToDraw << std::endl;
              std::cout << " cutToDraw  = " << cutToDraw << std::endl;
              inputTree_data -> Draw(whatToDraw.c_str(), cutToDraw.c_str(), "goff");
              
              
              //
              // MC
              //
              // FPIX
              cutToDraw  = "(" + variable_layer + std::to_string(iHit) + "[best_track] == " + std::to_string(layerId.at(ilayer)) + ") && " + \
                           "(" + variable_ladder_blade + std::to_string(iHit) + "[best_track] == " + std::to_string(ladderbladeId.at(iladderblade)) + ") && " + \
                           "(" + variable_pix + std::to_string(iHit) + "[best_track] == 2 ) && " + \
                           "( (  abs(" + variable_eta  + "[best_track] ) >="  + std::to_string( eta_edges.at(iEdge) ) + ") && (  abs(" + variable_eta  + "[best_track] ) <"  + std::to_string( eta_edges.at(iEdge+1) ) + ")   )" + \
                           " ";
  
              name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_mc", 0, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade));   
              whatToDraw = variable_dedx+ std::to_string(iHit) + "[best_track] >>+ " + name.Data();
              
              std::cout << " whatToDraw = " << whatToDraw << std::endl;
              inputTree_mc -> Draw(whatToDraw.c_str(), cutToDraw.c_str(), "goff");
  
            }
            
          } // ladder
        } // run 
      } // edge eta
    } // layer
  } // hit
  
  
  
  
  //---- save in output file
  output_file_plots->cd();
  
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
  
  TCanvas* cc_summary = new TCanvas ("summary","",800,600);
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {    
      map_h_BPIX_reduced_data[ilayer][iEdge] -> Write ();
      map_h_FPIX_reduced_data[ilayer][iEdge] -> Write ();
      map_h_BPIX_reduced_mc[ilayer][iEdge]   -> Write ();
      map_h_FPIX_reduced_mc[ilayer][iEdge]   -> Write ();

      TString name;
      
      map_h_BPIX_reduced_data[ilayer][iEdge]->DrawNormalized();
      map_h_BPIX_reduced_mc[ilayer][iEdge]->DrawNormalized("same E");
      name = Form ("plots_summary/cc_summary_layer_%d_eta_%d_BPIX.png" , layerId.at(ilayer), iEdge); 
      cc_summary->SaveAs(name.Data());
      name = Form ("plots_summary/cc_summary_layer_%d_eta_%d_BPIX.root" , layerId.at(ilayer), iEdge); 
      cc_summary->SaveAs(name.Data());
      
      
      map_h_FPIX_reduced_data[ilayer][iEdge]->DrawNormalized();
      map_h_FPIX_reduced_mc[ilayer][iEdge]->DrawNormalized("same E");
      name = Form ("plots_summary/cc_summary_layer_%d_eta_%d_FPIX.png" , layerId.at(ilayer), iEdge); 
      cc_summary->SaveAs(name.Data());
      name = Form ("plots_summary/cc_summary_layer_%d_eta_%d_FPIX.root" , layerId.at(ilayer), iEdge); 
      cc_summary->SaveAs(name.Data());
      
      
    }
  }
  
  std::cout << " name_output_file_plots = " << name_output_file_plots << std::endl;
 
}






