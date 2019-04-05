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
  
  std::cout << " ================================ " << std::endl;
  std::cout << " Plot all time periods together " << std::endl;
  std::cout << " ================================ " << std::endl;
  
  
  std::string name_input_file_data = "out.root"; 
  if (argc>=2) {
    name_input_file_data = argv[1];
  }
  
  std::cout << " name_input_file_data = " << name_input_file_data << std::endl;
  
  ROOT::RDataFrame dataframe_data ("tree", name_input_file_data.c_str());
  
//   myHisto = d.Histo1D("Branch_A");
  
  //   ROOT::RDF::RResultPtr<TH1D>
//   auto h_data = dataframe_data.Filter("IsoTrack_layerOrSideByHit0==1").Histo1D("IsoTrack_layerOrSideByHit0");
//   
//   h_data->SaveAs("mytest_data.root");

  
  std::string name_input_file_mc = "out.root";
  if (argc>=3) {
    name_input_file_mc = argv[2];
  }
  
  std::cout << " name_input_file_mc = " << name_input_file_mc << std::endl;
  ROOT::RDataFrame dataframe_mc ("tree", name_input_file_mc.c_str());
  
  
  
  
  
  
  
  
  
  
  auto h_data = dataframe_data.Filter("IsoTrack_layerOrSideByHit0==1").Histo1D("IsoTrack_layerOrSideByHit0");
  auto h_mc = dataframe_mc.Filter("IsoTrack_layerOrSideByHit0==1").Histo1D("IsoTrack_layerOrSideByHit0");
    
  
}






