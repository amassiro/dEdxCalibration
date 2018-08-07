//
// Scale and smear
//
//
//   g++ -o toyCalibrate.exe toyCalibrate.cpp `root-config --cflags --glibs`
//
//

#include <iostream>

#include "TTree.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"



class TemplateFit {
  
  TH1F* _reference_histogram;
  float _min_histo;
  float _max_histo;
  float _integral;
  
  float _scale_value;
  
public:
  
  TemplateFit () {
    _min_histo = 0;
    _max_histo = 10;
  };
  void set_reference_histogram (TH1F* function_in) { 
    _reference_histogram = function_in; 
    _integral = _reference_histogram->Integral();
  };
  
  void set_min_max (float min, float max) { _min_histo = min; _max_histo = max; };
  
  void set_scale (float scale) { _scale_value = scale; };
  
  Double_t evaluate (Double_t x) {
    Double_t x_scaled = 0;
    x_scaled = (x) * _scale_value;
    
    int bin_number = _reference_histogram->GetXaxis()->FindBin(x_scaled);
    //     int bin_number_noscale = _reference_histogram->GetXaxis()->FindBin(x);
    
    //---- fix overflow and underflow
    if (bin_number >  _reference_histogram->GetNbinsX()) bin_number = _reference_histogram->GetNbinsX();
    if (bin_number == 0) bin_number = 1;
    
    while ( ( (_reference_histogram -> GetBinContent ( bin_number )) / _integral ) == 0) {
      if (bin_number != _reference_histogram->GetNbinsX()) bin_number += 1;
      else bin_number -=1;
    }
    
//     return ( (_reference_histogram -> GetBinContent (bin_number)) / _integral ) ;
    return ( (_reference_histogram -> GetBinContent (bin_number)) / _integral ) * _scale_value ;
    
  }
  
};




int main(int argc, char** argv) {
  
  
  std::vector <int> num_events;
  num_events.push_back(1000);
//   num_events.push_back(1000);
//   num_events.push_back(1000);
  
  num_events.push_back(10000);
  num_events.push_back(100000);
  num_events.push_back(1000000);
//   num_events.push_back(10000000);
//   num_events.push_back(100000000);
  
  float min_scan = 0.90;
  float max_scan = 1.10;
  std::vector <int> num_points;
  num_points.push_back(50);
  num_points.push_back(100);
  num_points.push_back(200);
  num_points.push_back(400);
  
  
  TFile outputCanvas ("outputToys.root", "RECREATE");
  
  
  TCanvas* cc_summary_likelihood_scan = new TCanvas ("cc_summary_likelihood_scan","",1000,1000);
  cc_summary_likelihood_scan->Divide (num_points.size(), num_events.size());
  
  
  for (int itoys = 0; itoys<num_events.size(); itoys++) {
    
    std::cout << " itoys = " << itoys << " --> " << num_events.at(itoys) << std::endl;
    
    TString name = Form ("toys_%d.root", num_events.at(itoys));
    
    TFile* fileIn = new TFile (name.Data(), "READ");
    
    TH1F* histo = (TH1F*) fileIn->Get ("histo");
    
    
    float min_histo = 0.8;
    float max_histo = 1.2;
    
    //---- template fit
    TemplateFit myFit;
    //---- define the reference histogram 
    //---> first check bias in data vs data
    myFit.set_reference_histogram(histo);
    myFit.set_min_max( 0.0,    8.0 );
    
    
    
    for (int numpoints = 0; numpoints<num_points.size(); numpoints++) {

      std::cout << "    numpoints = " << numpoints << " -> " << num_points.at(numpoints) << " delta = " << (max_scan - min_scan)/num_points.at(numpoints) << std::endl;
      
      cc_summary_likelihood_scan->cd(itoys*num_points.size() + numpoints + 1);
      
      outputCanvas.cd();
      TGraph* likelihoodScan = new TGraph();
      
      for (int ipoint=0; ipoint<num_points.at(numpoints); ipoint++) {
//         std::cout << "          ipoint = " << ipoint << " [" << num_points.at(numpoints) << "]" << std::endl;
        float likelihood = 1;
        float loglikelihood = 0;
        float entries = 0;
        
        float scale_value = min_scan + (max_scan - min_scan)/num_points.at(numpoints) * ipoint;
        myFit.set_scale( scale_value );
        
        for (int ibin=0; ibin<histo->GetNbinsX(); ibin++) {
          if ( (histo -> GetBinCenter (ibin+1)) >= min_histo && (histo -> GetBinCenter (ibin+1)) <= max_histo) {
            if (histo -> GetBinContent(ibin+1) > 0) {
              
              float value = myFit.evaluate (histo -> GetBinCenter (ibin+1));
              if (value != 0) {
                likelihood *= ( pow( value , (histo -> GetBinContent(ibin+1))) ) ;
                loglikelihood += ( (log ( value )) * (histo -> GetBinContent(ibin+1)) ) ;
                entries += (histo -> GetBinContent(ibin+1));
              }
            }
          }
        }
        
        likelihoodScan -> SetPoint ( ipoint, scale_value, -2 * loglikelihood  ); 
      }
      
      likelihoodScan->SetLineColor (kBlue);
      likelihoodScan->SetLineWidth (2);
      likelihoodScan->SetMarkerSize (0.5);
      likelihoodScan->SetMarkerStyle (20);
      
      likelihoodScan->DrawClone("APL");
      
    }
    
    
  }
  
  outputCanvas.cd();
  cc_summary_likelihood_scan->Write();
  outputCanvas.Close();
  
  
}


