//
// drawPixelFromRootToPNG
//
//
//   g++ -o drawPixelFromRootToPNG.exe drawPixelFromRootToPNG.cpp.cpp `root-config --cflags --glibs`
//
//   Extract from root file and save in canvas
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
  
  std::string name_input_file = "out.root";
  
  if (argc>=2) {
    name_input_file = argv[1];
  }
  
  std::string name_output_folder = "bla/";
  
  if (argc>=3) {
    name_output_folder = argv[2];
  }

//   
  system ( ( "mkdir " + name_output_folder ).c_str());
// 
  
  
  TFile* input_file = new TFile (name_input_file.c_str(), "READ");
  
  //   
  //   name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_mc", ilayer, iEdge);   
  //   name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_data", ilayer, iEdge);   
  //   name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_mc", ilayer, iEdge);   
  //   name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_data", ilayer, iEdge);   
  //   
  
  int max_num_iEdge = 10;
  int max_num_ilayer = 10;
  
  TString name;
  
  for (int ilayer = 0; ilayer<max_num_ilayer; ilayer++) {
    for (int iEdge = 0; iEdge<max_num_iEdge; iEdge++) {
      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_mc", ilayer, iEdge);   
      
      if ( input_file -> Get (name.Data()) ) {
        
        name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_mc", ilayer, iEdge);   
        TH1F* BPIX_mc = (TH1F*) input_file -> Get (name.Data());
        
        name = Form ("h_ilayer_%d__iEdge_%d__dedxById_BPIX_data", ilayer, iEdge);   
        TH1F* BPIX_data = (TH1F*) input_file -> Get (name.Data());
        
        name = Form ("cc_add_layer_%d_eta_%d_BPIX" , ilayer, iEdge); 
        TCanvas* cc_add_iEdge_iladder_BPIX = new TCanvas (name.Data(),"",800,600);
        BPIX_mc   -> DrawNormalized("P");
        BPIX_data -> DrawNormalized("same");
        
        name = Form ("%s/cc_add_layer_%d_eta_%d_BPIX.png" , name_output_folder.c_str(), ilayer, iEdge); 
        cc_add_iEdge_iladder_BPIX->SaveAs(name.Data());
        name = Form ("%s/cc_add_layer_%d_eta_%d_BPIX.root" , name_output_folder.c_str(), ilayer, iEdge); 
        cc_add_iEdge_iladder_BPIX->SaveAs(name.Data());
        
      }
      
      name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_mc", ilayer, iEdge);   
      
      if ( input_file -> Get (name.Data()) ) {
        
        name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_mc", ilayer, iEdge);   
        TH1F* FPIX_mc = (TH1F*) input_file -> Get (name.Data());
        
        name = Form ("h_ilayer_%d__iEdge_%d__dedxById_FPIX_data", ilayer, iEdge);   
        TH1F* FPIX_data = (TH1F*) input_file -> Get (name.Data());
        
        name = Form ("cc_add_layer_%d_eta_%d_FPIX" , ilayer, iEdge); 
        TCanvas* cc_add_iEdge_iladder_FPIX = new TCanvas (name.Data(),"",800,600);
        FPIX_mc   -> DrawNormalized("P");
        FPIX_data -> DrawNormalized("same");
        
        name = Form ("%s/cc_add_layer_%d_eta_%d_FPIX.png" , name_output_folder.c_str(), ilayer, iEdge); 
        cc_add_iEdge_iladder_FPIX->SaveAs(name.Data());
        name = Form ("%s/cc_add_layer_%d_eta_%d_FPIX.root" , name_output_folder.c_str(), ilayer, iEdge); 
        cc_add_iEdge_iladder_FPIX->SaveAs(name.Data());
        
      }
      
      
    }
  }
  
  
}







