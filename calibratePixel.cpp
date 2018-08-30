//
// Scale and smear
//
//
//   g++ -o calibratePixel.exe calibratePixel.cpp `root-config --cflags --glibs`
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
    
    if (_integral == 0) return 1;
    
    Double_t x_scaled = 0;
    x_scaled = (x) * _scale_value;
    
    int bin_number = _reference_histogram->GetXaxis()->FindBin(x_scaled);
//     int bin_number_noscale = _reference_histogram->GetXaxis()->FindBin(x);
    
    //---- fix overflow and underflow
    if (bin_number >  _reference_histogram->GetNbinsX()) bin_number = _reference_histogram->GetNbinsX();
    if (bin_number == 0) bin_number = 1;
      
    //----
//     while ( ( ( (_reference_histogram -> GetBinContent ( bin_number )) / _integral ) == 0 )    &&    bin_number<(_reference_histogram->GetNbinsX()+1)  ) {
//       if (bin_number != _reference_histogram->GetNbinsX()) bin_number += 1;
//       else bin_number -=1;
//     }
        
    int max_reached = 0;
    while ( ( (_reference_histogram -> GetBinContent ( bin_number )) / _integral ) == 0 ) {
      if ( bin_number != _reference_histogram->GetNbinsX() && (max_reached ==0) ) bin_number += 1;
      else {
        bin_number -=1;
        max_reached = 1;
      }
    }
    
//     return ( (_reference_histogram -> GetBinContent (bin_number)) / _integral ) ;
    return ( (_reference_histogram -> GetBinContent (bin_number)) / _integral ) * _scale_value ;
  }
  
};




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





int main(int argc, char** argv) {
  
  std::string fileIn_name = "";
  
  if (argc>=2) {
    fileIn_name = argv[1];
  }
  
  TFile* fileIn = new TFile (fileIn_name.c_str(), "READ");
  
  
  TFile outputCanvas ("outputCanvas_Calibration.root", "RECREATE");
  
  std::ofstream myfile;
  myfile.open ("scale_pixels.txt");
 
  std::ofstream myfile_reduced;
  myfile_reduced.open ("scale_pixels_reduced.txt");
  
  
  std::vector<float> eta_edges;
  eta_edges.push_back(0.0);
  eta_edges.push_back(0.3);
  eta_edges.push_back(0.6);
  eta_edges.push_back(1.0);
  eta_edges.push_back(1.3);
  eta_edges.push_back(1.6);
  eta_edges.push_back(2.1);
  eta_edges.push_back(2.5);
  
  
  std::vector<int> detId;
  for (int idet = 0; idet<4; idet++) {
    detId.push_back(idet);
  }
  
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<6; ilayer++) {
    layerId.push_back(ilayer);
  }
  
  
  //----     layer                   eta   det
  std::map < int, std::map< std::pair<int, int> , TH1F*> > map_h_dedxById_data;
  std::map < int, std::map< std::pair<int, int> , TH1F*> > map_h_dedxById_mc;
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int idet = 0; idet<detId.size(); idet++) {     
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
        TString name;      
        name = Form ("h_%d_%d_%d_dedxById_data" , ilayer, edge_det.first , edge_det.second);   
        map_h_dedxById_data[ilayer][edge_det] = (TH1F*) fileIn->Get(name.Data());
        name = Form ("h_%d_%d_%d_dedxById_mc" , ilayer, edge_det.first , edge_det.second);   
        map_h_dedxById_mc  [ilayer][edge_det] = (TH1F*) fileIn->Get(name.Data());
      }
    }
  }
  
  
  
  
  
  
  
  outputCanvas.mkdir ("test/");
  
  
  TCanvas* cc_summary_entries_scan = new TCanvas ("cc_summary_entries_scan","",1000,1000);
  cc_summary_entries_scan->Divide(4,4);
  
  TCanvas* cc_summary_likelihood_scan_closure = new TCanvas ("cc_summary_likelihood_scan_closure","",1000,1000);
  cc_summary_likelihood_scan_closure->Divide(4,4);
  
  TCanvas* cc_summary_likelihood_scan = new TCanvas ("cc_summary_likelihood_scan","",1000,1000);
  cc_summary_likelihood_scan->Divide(4,4);
  
  TCanvas* cc_summary_result = new TCanvas ("cc_summary_result","",1000,1000);
  cc_summary_result->Divide(4,4);
  
  TCanvas* cc_summary_data = new TCanvas ("cc_summary_data","",1000,1000);
  cc_summary_data->Divide(4,4);
  
  TCanvas* cc_summary_mc = new TCanvas ("cc_summary_mc","",1000,1000);
  cc_summary_mc->Divide(4,4);
  
  
  
  //   float min_landau = 2.15;
  //   float max_landau = 4.4;
  float min_landau = 2.0;
  float max_landau = 6.5;
  
  float min_histo = 0.1; //---- remove peak at 0
  float max_histo = 10.0;
  
  
  //   TF1* f_gauss = new TF1 ("f_gauss", "[0] + x*[4] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.0, 4.0);
  //   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.0, 4.0);
  TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.2, 4.0);
  TF1* f_landau = new TF1 ("f_landau", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1)", min_landau, max_landau);
  
  f_gauss->SetLineColor (kOrange+2);
  f_landau->SetLineColor (kMagenta);
  
  
  TF1 parabola ("parabola", "[0]*x*x + [1]*x + [2]", 0.90, 1.10);
  
  TF1 parabola_result ("parabola_result", "[0]*x*x + [1]*x + [2]", 0.90, 1.10);
  
  
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    TString name;  
    name = Form ("eta_%d" , iEdge); 
    
    outputCanvas.cd();
    outputCanvas.mkdir (name.Data());
    outputCanvas.cd(name.Data());
    
    
    std::vector< float > calibration_values_likelihood_result;
    std::vector< float > calibration_values_result;
    std::vector< float > calibration_values_data;
    std::vector< float > calibration_values_mc;
    std::vector< float > calibration_values_gauss_data;
    std::vector< float > calibration_values_gauss_mc;
    
    
    int iterator_pad = 0;
    
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
      
      for (int idet = 0; idet<detId.size(); idet++) { 
        
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
        
        f_gauss->SetParameter(0, 0);
        f_gauss->SetParameter(2, 2);
        
        f_landau->SetParameter(0, 0);
        f_landau->SetParameter(2, 1);
        
        
        
        
        cc_summary_data->cd(iterator_pad+1);
        map_h_dedxById_data[ilayer][edge_det]->Draw("hist");
        
        f_gauss->SetParameter(1, sqrt(map_h_dedxById_data[ilayer][edge_det]->Integral()));
//         f_gauss->SetParameter(1, sqrt(1000));
        //     f_gauss->SetParameter(3, map_h_dedxById_data[ilayer][edge_det]->GetMean());  
        f_gauss->SetParameter(3, 3.0);  
        f_gauss->SetParameter(2, 2.0);  
        f_landau->SetParameter(1, sqrt(map_h_dedxById_data[ilayer][edge_det]->Integral()));
        //     f_landau->SetParameter(3, map_h_dedxById_data[ilayer][edge_det]->GetMean());  
        f_landau->SetParameter(3, 3);  
        f_landau->SetParameter(2, 2.0);  
        map_h_dedxById_data[ilayer][edge_det]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
        calibration_values_gauss_data.push_back (f_gauss->GetParameter(3));
        map_h_dedxById_data[ilayer][edge_det]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
        calibration_values_data.push_back (f_landau->GetParameter(3));
        f_landau->DrawClone("same");
        f_gauss->DrawClone("same");
        
        cc_summary_mc->cd(iterator_pad+1);
        map_h_dedxById_mc[ilayer][edge_det]->Draw("hist");
        f_gauss->SetParameter(1, sqrt(map_h_dedxById_mc[ilayer][edge_det]->Integral()));
//         f_gauss->SetParameter(1, sqrt(1000));
        //     f_gauss->SetParameter(3, map_h_dedxById_mc[ilayer][edge_det]->GetMean());  
        f_gauss->SetParameter(3, 3.0);  
        f_gauss->SetParameter(2, 2.0);  
        f_landau->SetParameter(1, sqrt(map_h_dedxById_mc[ilayer][edge_det]->Integral()));
        //     f_landau->SetParameter(3, map_h_dedxById_mc[ilayer][edge_det]->GetMean());  
        f_landau->SetParameter(3, 3);  
        f_landau->SetParameter(2, 2.0);  
        map_h_dedxById_mc[ilayer][edge_det]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
        calibration_values_gauss_mc.push_back (f_gauss->GetParameter(3));
        map_h_dedxById_mc[ilayer][edge_det]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
        calibration_values_mc.push_back (f_landau->GetParameter(3));
        f_landau->DrawClone("same");
        f_gauss->DrawClone("same");
        
        
        
        
        
        int npoint = 100;
        
        cc_summary_result->cd(iterator_pad+1);
        
        map_h_dedxById_data[ilayer][edge_det]->Draw("hist");
        map_h_dedxById_mc  [ilayer][edge_det]->Draw("hist same");
        
        
        //---- template fit
        TemplateFit myFit;
        //---- define the reference histogram 
        //---> first check bias in data vs data
        myFit.set_reference_histogram(map_h_dedxById_data[ilayer][edge_det]);
        myFit.set_min_max( 0.0,    8.0 );
        
        
        cc_summary_likelihood_scan_closure->cd(iterator_pad+1);
        TGraph* likelihoodScan = new TGraph();
        TGraph* entriesScan = new TGraph();
        
        if (map_h_dedxById_data[ilayer][edge_det]->Integral() > 500 ) {  
          for (int ipoint=0; ipoint<npoint; ipoint++) {
            float likelihood = 1;
            float loglikelihood = 0;
            float entries = 0;
            
            float scale_value = 0.95 + 0.10/npoint * ipoint;
            myFit.set_scale( scale_value );
            
            for (int ibin=0; ibin<map_h_dedxById_data[ilayer][edge_det]->GetNbinsX(); ibin++) {
              if ( (map_h_dedxById_data[ilayer][edge_det] -> GetBinCenter (ibin+1)) >= min_histo && (map_h_dedxById_data[ilayer][edge_det] -> GetBinCenter (ibin+1)) <= max_histo) {
                if (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1) > 0) {
                  
                  float value = myFit.evaluate (map_h_dedxById_data[ilayer][edge_det] -> GetBinCenter (ibin+1));
                  if (value != 0) {
                    likelihood *= ( pow( value , (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1))) ) ;
                    loglikelihood += ( (log ( value )) * (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1)) ) ;
                    entries += (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1));
                  }
                }
              }
            }
            
            //       likelihoodScan -> SetPoint ( ipoint, scale_value, likelihood  ); 
            likelihoodScan -> SetPoint ( ipoint, scale_value, -2 * loglikelihood  ); 
            entriesScan -> SetPoint ( ipoint, scale_value, entries ); 
            
          }
        }
        
        likelihoodScan->SetLineColor (kBlue);
        likelihoodScan->SetLineWidth (2);
        likelihoodScan->SetMarkerSize (0.5);
        likelihoodScan->SetMarkerStyle (20);
        
        likelihoodScan->DrawClone("APL");
        
        
        parabola.SetLineColor (kRed);
        likelihoodScan->Fit("parabola", "Q");
        parabola.DrawClone ("same");
        float bias_min_value = - parabola.GetParameter (1) / (2. *  parabola.GetParameter (0) );
        std::cout << " min = " << bias_min_value << std::endl;
        bias_min_value = (1. - bias_min_value);
        
        
        
        
        
        
        
        
        //---- FIX bias deactivated
        //       bias_min_value = 0;
        //----
        
        
        cc_summary_entries_scan->cd(iterator_pad+1);
        entriesScan->DrawClone("APL");
        
        
        //---- now do the mc to data fit
        myFit.set_reference_histogram(map_h_dedxById_mc[ilayer][edge_det]);
        
        cc_summary_likelihood_scan->cd(iterator_pad+1);
        TGraph* likelihoodScan_mc_data = new TGraph();
        
        if (map_h_dedxById_mc[ilayer][edge_det]->Integral() > 500 ) {
          for (int ipoint=0; ipoint<npoint; ipoint++) {
            float likelihood = 1;
            float loglikelihood = 0;
            float entries = 0;
            
            float scale_value = 0.95 + 0.10/npoint * ipoint;
            myFit.set_scale( scale_value );
            
            for (int ibin=0; ibin<map_h_dedxById_data[ilayer][edge_det]->GetNbinsX(); ibin++) {
              if ( (map_h_dedxById_data[ilayer][edge_det] -> GetBinCenter (ibin+1)) >= min_histo && (map_h_dedxById_data[ilayer][edge_det] -> GetBinCenter (ibin+1)) <= max_histo) {
                if (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1) > 0) {
                  
                  float value = myFit.evaluate (map_h_dedxById_data[ilayer][edge_det] -> GetBinCenter (ibin+1));
                  if (value != 0) {
                    likelihood *= ( pow( value , (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1))) ) ;
                    loglikelihood += ( (log ( value )) * (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1)) ) ;
                    entries += (map_h_dedxById_data[ilayer][edge_det] -> GetBinContent(ibin+1));
                  }
                }
              }
            }
            
            //---                                               add the bias obtained in the data 2 data
            likelihoodScan_mc_data -> SetPoint ( ipoint, scale_value + bias_min_value, -2 * loglikelihood  ); 
            
          }
        }
        
        likelihoodScan_mc_data->SetLineColor (kBlue);
        likelihoodScan_mc_data->SetLineWidth (2);
        likelihoodScan_mc_data->SetMarkerSize (0.5);
        likelihoodScan_mc_data->SetMarkerStyle (20);
        
        likelihoodScan_mc_data->DrawClone("APL");
        
        
        
        likelihoodScan_mc_data->Fit("parabola_result", "Q");
        parabola_result.SetLineColor (kRed);
        parabola_result.DrawClone ("same");
        float final_scale = - parabola_result.GetParameter (1) / (2. *  parabola_result.GetParameter (0) );
        std::cout << " Scale [ " << iterator_pad << "] = " << final_scale << std::endl;
        calibration_values_likelihood_result.push_back(final_scale);
        
        
        
        //--- 
        iterator_pad ++;
        //--- 
        
      }
    }
    
    
    
    
    TCanvas* cc_summary_scale = new TCanvas ("cc_summary_scale","",1000,1000);
    
    TGraph* gr_likelihood = new TGraph ();
    TGraph* gr_landau     = new TGraph ();
    TGraph* gr_gauss      = new TGraph ();
    
    iterator_pad = 0;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
      for (int idet = 0; idet<detId.size(); idet++) { 
        
        //----      |     eta             layer            det   |
        myfile << " |" << iEdge << " " << ilayer << " " << idet << "|";
        myfile << "    " << calibration_values_mc.at(iterator_pad) / calibration_values_data.at(iterator_pad);
        myfile  << " [ " << calibration_values_mc.at(iterator_pad) << " / " << calibration_values_data.at(iterator_pad) << " ]" ;
        
        myfile  << "    " << calibration_values_gauss_mc.at(iterator_pad) / calibration_values_gauss_data.at(iterator_pad) ;
        myfile  << " [ " << calibration_values_gauss_mc.at(iterator_pad) << " / " << calibration_values_gauss_data.at(iterator_pad) << " ]";
        
        myfile << "    " << calibration_values_likelihood_result.at(iterator_pad)  << std::endl;
        
        
        
        
        myfile_reduced << iEdge << " " << ilayer << " " << idet << "               ";
        float best_value = 1.;
        
        float value_1;
        if (calibration_values_data.at(iterator_pad) != 0 ) value_1 = calibration_values_mc.at(iterator_pad) / calibration_values_data.at(iterator_pad);
        float value_2;
        if (calibration_values_gauss_data.at(iterator_pad) != 0 ) value_2 = calibration_values_gauss_mc.at(iterator_pad) / calibration_values_gauss_data.at(iterator_pad);
        float value_3 = calibration_values_likelihood_result.at(iterator_pad);
        
        if (fabs(value_1-1.0) > 2) {
          if (fabs(value_2-1.0) > 2) {
            best_value = value_3;
          }
          else {
            best_value = value_2;
          }
        }
        else {
          best_value = value_1;
        }
        
        myfile_reduced << best_value << std::endl;
        std::cout << " best_value = " << best_value << std::endl;
        
        gr_likelihood->SetPoint (iterator_pad, iterator_pad, calibration_values_likelihood_result.at(iterator_pad));
        float data = calibration_values_data.at(iterator_pad);
        float mc   = calibration_values_mc  .at(iterator_pad);
        float scale = mc/data;
        if ( (fabs(scale)) >10 ) {
          scale = 0;
        }
        calibration_values_result.push_back(scale);
        gr_landau->SetPoint (iterator_pad, iterator_pad, scale);
        
        
        data = calibration_values_gauss_data.at(iterator_pad);
        mc   = calibration_values_gauss_mc  .at(iterator_pad);
        scale = mc/data;
        if ( (fabs(scale)) >10 ) {
          scale = 0;
        }
        gr_gauss->SetPoint (iterator_pad, iterator_pad, scale);
        
        
        iterator_pad++;
        
      }
    }
    
    setupTGraph(gr_likelihood, 0);
    setupTGraph(gr_landau,     1);
    setupTGraph(gr_gauss,      2);
    
    gr_likelihood->SetTitle ("likelihood");
    gr_landau    ->SetTitle ("landau");
    gr_gauss     ->SetTitle ("gauss");
    
    TMultiGraph mg;
    mg.Add(gr_likelihood);
    mg.Add(gr_landau);
    mg.Add(gr_gauss);
    mg.Draw("APL");
    cc_summary_scale->BuildLegend();
    
    
    
    cc_summary_result->Write();
    cc_summary_data->Write();
    cc_summary_mc->Write();
    //   cc_summary_data_mc->Write();
    cc_summary_likelihood_scan->Write();
    cc_summary_likelihood_scan_closure->Write();
    cc_summary_entries_scan->Write();
    cc_summary_scale->Write();
    
    
  }
  
  
  
  /*
  
    
    TCanvas* cc_summary_data_mc = new TCanvas ("cc_summary_data_mc","",1000,1000);
    cc_summary_data_mc->Divide(4,4);
    
    
    for (int i=0; i<14; i++) {
      cc_summary_data_mc->cd(i+1);
      map_h_dedxById_data[ilayer][edge_det]->Scale (1./(map_h_dedxById_data[ilayer][edge_det])->Integral() * ((map_h_dedxById_data[ilayer][edge_det])->GetNbinsX()) );
      h_dedxByLayer_mc.at(i)  ->Scale (1./(h_dedxByLayer_mc.at(i))  ->Integral() * ((h_dedxByLayer_mc.at(i))->GetNbinsX())   );
      
//       map_h_dedxById_data[ilayer][edge_det]->DrawNormalized("hist");
//       h_dedxByLayer_mc.at(i)->DrawNormalized("hist SAME");

      map_h_dedxById_data[ilayer][edge_det]->Draw("hist");
      h_dedxByLayer_mc.at(i)->Draw("hist SAME");
      
    }
    
    
    
    TCanvas* cc_summary_scale = new TCanvas ("cc_summary_scale","",1000,1000);
    
    TGraph* gr_likelihood = new TGraph ();
    TGraph* gr_landau     = new TGraph ();
    TGraph* gr_gauss      = new TGraph ();
    
    std::cout << " ~~~~ " << std::endl;
    
    for (int i=0; i<14; i++) {
      gr_likelihood->SetPoint (i, i, calibration_values_likelihood_result.at(i));
      float data = calibration_values_data.at(i);
      float mc   = calibration_values_mc  .at(i);
      float scale = mc/data;
      if ( (fabs(scale)) >10 ) {
        scale = 0;
      }
      calibration_values_result.push_back(scale);
      gr_landau->SetPoint (i, i, scale);
      std::cout << " [" << i << "] = " << scale;
      
      
      data = calibration_values_gauss_data.at(i);
      mc   = calibration_values_gauss_mc  .at(i);
      scale = mc/data;
      if ( (fabs(scale)) >10 ) {
        scale = 0;
      }
      gr_gauss->SetPoint (i, i, scale);
      std::cout << "     " << scale;
      
      std::cout << "     " << calibration_values_likelihood_result.at(i);
      
      std::cout << std::endl;
      
    }
    
    setupTGraph(gr_likelihood, 0);
    setupTGraph(gr_landau,     1);
    setupTGraph(gr_gauss,      2);
    
    gr_likelihood->SetTitle ("likelihood");
    gr_landau    ->SetTitle ("landau");
    gr_gauss     ->SetTitle ("gauss");
    
    TMultiGraph mg;
    mg.Add(gr_likelihood);
    mg.Add(gr_landau);
    mg.Add(gr_gauss);
    mg.Draw("APL");
    cc_summary_scale->BuildLegend();
    
    */
    
    
  
  outputCanvas.Close();
  
  myfile.close(); 
  myfile_reduced.close();
  
}


