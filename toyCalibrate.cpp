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
#include "TGraphErrors.h"
#include "TMultiGraph.h"



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




void setupTGraph(TGraph* graph, int icolor) {
  
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
  
  
  graph->SetLineColor(color[icolor]);
  graph->SetMarkerColor(color[icolor]);
  graph->SetMarkerSize(1);
  graph->SetMarkerStyle(20+icolor);
}


float sumQ (float a, float b) {
  return sqrt(a*a + b*b);
}


int main(int argc, char** argv) {
  
  int nbins = 1000;
  if (argc>=2) {
    nbins = atoi(argv[1]);
  }
  
  std::cout << " nbins = " << nbins << std::endl;
  
  
  std::vector <int> num_events;
  num_events.push_back(1000);
//   num_events.push_back(1000);
//   num_events.push_back(1000);
  
  num_events.push_back(10000);
  num_events.push_back(100000);
  num_events.push_back(1000000);
  num_events.push_back(10000000);
//   num_events.push_back(100000000);
  
  float min_scan = 0.90;
  float max_scan = 1.10;
  std::vector <int> num_points;
  num_points.push_back(50);
  num_points.push_back(100);
  num_points.push_back(200);
  num_points.push_back(400);
  
  TString titleOut = Form("outputToys_%d.root", nbins);
  TFile outputCanvas (titleOut.Data(), "RECREATE");

  TCanvas* cc_summary_results = new TCanvas ("cc_summary_results","",1000,1000);
  
  TCanvas* cc_summary_histo = new TCanvas ("cc_summary_histo","",1000,1000);
  cc_summary_histo->Divide (1, num_events.size());
  
  TCanvas* cc_summary_likelihood_scan = new TCanvas ("cc_summary_likelihood_scan","",1000,1000);
  cc_summary_likelihood_scan->Divide (num_points.size(), num_events.size());
  
  TGraphErrors* graph_fit[num_events.size()];

  
  for (int itoys = 0; itoys<num_events.size(); itoys++) {
    
    std::cout << " itoys = " << itoys << " --> " << num_events.at(itoys) << std::endl;
    
    graph_fit[itoys] = new TGraphErrors();
    
    TString name = Form ("toys_%d_%d.root", num_events.at(itoys), nbins);
    
    TFile* fileIn = new TFile (name.Data(), "READ");
    
    TH1F* histo = (TH1F*) fileIn->Get ("histo");
    
    cc_summary_histo->cd(itoys+1);
    histo->Draw("hist");
    
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
      
      TF1 parabola ("parabola", "[0]*x*x + [1]*x + [2]", 0.99, 1.01);
      likelihoodScan->Fit("parabola", "Q");
      parabola.SetLineColor(kRed);
      parabola.DrawClone("same");
      
      float bias_min_value = - parabola.GetParameter (1) / (2. *  parabola.GetParameter (0) );
      float bias_min_value_uncertainty = sumQ ( parabola.GetParError (1) / (2. *  parabola.GetParameter (0) ),      
                                                parabola.GetParameter (1) / (2. *  parabola.GetParameter (0)*  parabola.GetParameter (0) ) * parabola.GetParError (0)
      );
      
      graph_fit[itoys] -> SetPoint      (numpoints, num_points.at(numpoints), bias_min_value);
      graph_fit[itoys] -> SetPointError (numpoints, 0, bias_min_value_uncertainty);
      
    }
    
    
    TString title = Form("%d events", num_events.at(itoys));
    graph_fit[itoys] -> SetTitle (title.Data());
    setupTGraph(graph_fit[itoys], itoys);
    
  }

  
  cc_summary_results->cd();
  TMultiGraph mg;
  
  for (int itoys = 0; itoys<num_events.size(); itoys++) {
    mg.Add(graph_fit[itoys]);
  }
  mg.Draw("APL");
  cc_summary_results->BuildLegend();
  
  outputCanvas.cd();
  cc_summary_likelihood_scan->Write();
  cc_summary_histo->Write();
  cc_summary_results->Write();
  outputCanvas.Close();
  
  
}


