//
// Scale and smear
//
//
//   g++ -o calibrate.exe calibrate.cpp `root-config --cflags --glibs`
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
    if (_min_histo > x || _max_histo < x) return 0.;
    else {
      return ( (_reference_histogram -> GetBinContent ( _reference_histogram->GetXaxis()->FindBin(x_scaled) )) / _integral );
    }
  }
  
};




int main(int argc, char** argv) {
  
  std::string fileIn_name = "";
  
  if (argc>=2) {
    fileIn_name = argv[1];
  }
  
  TFile* fileIn = new TFile (fileIn_name.c_str(), "READ");
  
  std::vector<TH1F*> h_dedxByLayer_data;
  std::vector<TH1F*> h_dedxByLayer_mc;
  
  for (int i=0; i<14; i++) {
    TString name;
    
    name = Form ("h_dedxByLayer%d_data", i);
    h_dedxByLayer_data.push_back((TH1F*) fileIn -> Get (name.Data()));

    name = Form ("h_dedxByLayer%d_mc", i);
    h_dedxByLayer_mc.push_back((TH1F*) fileIn -> Get (name.Data()));
    
  }
  
  std::vector< float > calibration_values_result;
  std::vector< float > calibration_values_data;
  std::vector< float > calibration_values_mc;

  TCanvas* cc_summary_likelihood_scan = new TCanvas ("cc_summary_likelihood_scan","",1000,1000);
  cc_summary_likelihood_scan->Divide(4,4);
  
  TCanvas* cc_summary_result = new TCanvas ("cc_summary_result","",1000,1000);
  cc_summary_result->Divide(4,4);
 
  TCanvas* cc_summary_data = new TCanvas ("cc_summary_data","",1000,1000);
  cc_summary_data->Divide(4,4);
  
  TCanvas* cc_summary_mc = new TCanvas ("cc_summary_mc","",1000,1000);
  cc_summary_mc->Divide(4,4);
  
  
  float min_landau = 2.15;
  float max_landau = 4.4;
  
  float min_histo = 0.0;
  float max_histo = 10.0;
  
  
  TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 1.5, 6.5);
  TF1* f_landau = new TF1 ("f_landau", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1)", min_landau, max_landau);
  
  
  f_gauss->SetParameter(0, 0);
  f_gauss->SetParameter(2, 2);

  f_landau->SetParameter(0, 0);
  f_landau->SetParameter(2, 2);
  
  
  for (int i=0; i<14; i++) {
    cc_summary_data->cd(i+1);
    h_dedxByLayer_data.at(i)->Draw("hist");
    
    f_gauss->SetParameter(1, sqrt(h_dedxByLayer_data.at(i)->Integral()));
    f_gauss->SetParameter(3, h_dedxByLayer_data.at(i)->GetMean());  
    f_landau->SetParameter(1, sqrt(h_dedxByLayer_data.at(i)->Integral()));
    f_landau->SetParameter(3, h_dedxByLayer_data.at(i)->GetMean());  
    h_dedxByLayer_data.at(i)->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
    h_dedxByLayer_data.at(i)->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
    calibration_values_data.push_back (f_landau->GetParameter(3));
    f_landau->DrawClone("same");
    
    cc_summary_mc->cd(i+1);
    h_dedxByLayer_mc.at(i)->Draw("hist");
    f_gauss->SetParameter(1, sqrt(h_dedxByLayer_mc.at(i)->Integral()));
    f_gauss->SetParameter(3, h_dedxByLayer_mc.at(i)->GetMean());  
    f_landau->SetParameter(1, sqrt(h_dedxByLayer_mc.at(i)->Integral()));
    f_landau->SetParameter(3, h_dedxByLayer_mc.at(i)->GetMean());  
    h_dedxByLayer_mc.at(i)->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
    h_dedxByLayer_mc.at(i)->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
    calibration_values_mc.push_back (f_landau->GetParameter(3));
    f_landau->DrawClone("same");
    
    
    
    
    
    cc_summary_result->cd(i+1);
    
    h_dedxByLayer_data.at(i)->Draw("hist");
    
    //---- template fit
    TemplateFit myFit;
    //---- define the reference histogram
    myFit.set_reference_histogram(h_dedxByLayer_mc.at(i));
    myFit.set_min_max( 0.0,    8.0 );

    
    cc_summary_likelihood_scan->cd(i+1);
    TGraph* likelihoodScan = new TGraph();
    TGraph* entriesScan = new TGraph();
    
    for (int ipoint=0; ipoint<20; ipoint++) {
      float likelihood = 1;
      float loglikelihood = 0;
      int entries = 0;
      
      float scale_value = 0.9 + 0.01 * ipoint;
      myFit.set_scale( scale_value );
      
      for (int ibin=0; ibin<h_dedxByLayer_data.at(i)->GetNbinsX(); ibin++) {
        if ( (h_dedxByLayer_data.at(i) -> GetBinCenter (ibin+1)) > min_histo && (h_dedxByLayer_data.at(i) -> GetBinCenter (ibin+1)) < max_histo) {
          if (h_dedxByLayer_data.at(i) -> GetBinContent(ibin+1) != 0) {
            
            float value = myFit.evaluate (h_dedxByLayer_data.at(i) -> GetBinCenter (ibin+1));
            if (value != 0) {
              likelihood *= (  value * h_dedxByLayer_data.at(i) -> GetBinContent(ibin+1) ) ;
              loglikelihood += log (( value * h_dedxByLayer_data.at(i) -> GetBinContent(ibin+1) ) );
              entries += h_dedxByLayer_data.at(i) -> GetBinContent(ibin+1);
            }
          }
        }
      }
      
//       likelihoodScan -> SetPoint ( ipoint, scale_value, likelihood  ); 
      likelihoodScan -> SetPoint ( ipoint, scale_value, -2 * loglikelihood  ); 
      entriesScan -> SetPoint ( ipoint, scale_value, entries ); 
      
//       std::cout << " scale_value, likelihood = " << scale_value << " , " << likelihood << std::endl;
      std::cout << " scale_value, loglikelihood = " << scale_value << " , " << loglikelihood << std::endl;
      
    }
    
    likelihoodScan->SetLineColor (kBlue);
    likelihoodScan->SetLineWidth (2);
    likelihoodScan->SetMarkerSize (2);
    likelihoodScan->SetMarkerStyle (20);
    
    likelihoodScan->DrawClone("APL");
    
  }
  
  
  
  
  
  TCanvas* cc_summary_data_mc = new TCanvas ("cc_summary_data_mc","",1000,1000);
  cc_summary_data_mc->Divide(4,4);
  
  
  for (int i=0; i<14; i++) {
    cc_summary_data_mc->cd(i+1);
    h_dedxByLayer_data.at(i)->DrawNormalized("hist");
    h_dedxByLayer_mc.at(i)->DrawNormalized("hist SAME");
   }
  
  
  
  TFile outputCanvas ("outputCanvas2.root", "RECREATE");
  
  cc_summary_result->Write();
  cc_summary_data->Write();
  cc_summary_mc->Write();
  cc_summary_data_mc->Write();
  cc_summary_likelihood_scan->Write();
  
  outputCanvas.Close();
  
  
}


