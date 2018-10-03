//
// Scale and smear
//
//
//   g++ -o calibratePixelTime.exe calibratePixelTime.cpp `root-config --cflags --glibs`
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





int main(int argc, char** argv) {
  
  std::string fileIn_name = "";
  
  if (argc>=2) {
    fileIn_name = argv[1];
  }
  
  
  int num_run_intervals = 10;
  if (argc>=3) {
    num_run_intervals = atoi(argv[2]);
  }
  
  std::cout << " num_run_intervals = " << num_run_intervals << std::endl;
  
  
  TFile* fileIn = new TFile (fileIn_name.c_str(), "READ");
  
  
  TFile outputCanvas ("outputCanvas_run_ranges_Calibration.root", "RECREATE");
  
  std::ofstream myfile;
  myfile.open ("scale_pixels_run_ranges.txt");
 
  std::ofstream myfile_reduced;
  myfile_reduced.open ("scale_pixels_run_ranges_reduced.txt");
  
  
  
  std::vector<float> eta_edges;
//   eta_edges.push_back(-2.5);
//   eta_edges.push_back(-2.1);
//   eta_edges.push_back(-1.6);
//   eta_edges.push_back(-1.3);
//   eta_edges.push_back(-1.0);
//   eta_edges.push_back(-0.6);
//   eta_edges.push_back(-0.3);
  
  eta_edges.push_back(0.0);
  
//   eta_edges.push_back(0.3);
//   eta_edges.push_back(0.6);
//   eta_edges.push_back(1.0);
  eta_edges.push_back(1.3);
  eta_edges.push_back(1.6);
  eta_edges.push_back(2.1);
  eta_edges.push_back(2.5);
  
  
  
  //---- BPIX vs FPIX
  std::vector<int> detId;
  for (int idet = 0; idet<2; idet++) {
    detId.push_back(idet);
  }
  
  //---- 
  //---- layer in BPIX [0 --> 4]
  //---- disk in FPIX  [4 --> 20 [14?] ??]
  //----
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<20; ilayer++) {
    layerId.push_back(ilayer);
  }
  
  
  
  //---- a vector for the different run-ranges
  //---- run             layer                   eta   det   
  std::vector< std::map < int, std::map< std::pair<int, int> , TH1F*> > >  vector_map_h_dedxById_data;
  std::vector< std::map < int, std::map< std::pair<int, int> , float> > >  vector_map_scale_data;
  std::vector< std::map < int, std::map< std::pair<int, int> , float> > >  vector_map_gaus_data;
  std::vector< std::map < int, std::map< std::pair<int, int> , float> > >  vector_map_land_data;
  std::vector< std::map < int, std::map< std::pair<int, int> , float> > >  vector_map_like_data;
  
  for (int iRun =0; iRun < num_run_intervals; iRun++) {
    
    //----     layer                   eta   det
    std::map < int, std::map< std::pair<int, int> , TH1F*> > map_h_dedxById_data;
    std::map < int, std::map< std::pair<int, int> , float> > map_scale_data;
    
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        for (int idet = 0; idet<detId.size(); idet++) {     
          std::pair<int, int> edge_det;
          edge_det.first = iEdge;
          edge_det.second = idet;
          
          TString name;      
          name = Form ("h_irun_%d__ilayer_%d__ieta_%d__bpixfpix_%d__dedxById_data" , iRun, ilayer, edge_det.first , edge_det.second);   
          map_h_dedxById_data[ilayer][edge_det] = (TH1F*) fileIn->Get(name.Data());
          setupHisto(map_h_dedxById_data[ilayer][edge_det], iRun);
          
          map_scale_data[ilayer][edge_det] = 1.0;
        }
      }
    }
    
    vector_map_h_dedxById_data.push_back (map_h_dedxById_data);
    vector_map_scale_data.push_back (map_scale_data);
    vector_map_gaus_data.push_back (map_scale_data);
    vector_map_land_data.push_back (map_scale_data);
    vector_map_like_data.push_back (map_scale_data);
  }
  
  
  
  //----     layer                   eta   det   
  std::map < int, std::map< std::pair<int, int> , TH1F*> > map_h_dedxById_mc;
  //----         layer                   eta   det   
  std::map < int, std::map< std::pair<int, int> , float> > map_gaus_mc;
  std::map < int, std::map< std::pair<int, int> , float> > map_land_mc;
  
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int idet = 0; idet<detId.size(); idet++) {     
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
        TString name;      
        name = Form ("h_ilayer_%d__ieta_%d__bpixfpix_%d__dedxById_mc" , ilayer, edge_det.first , edge_det.second);   
        map_h_dedxById_mc  [ilayer][edge_det] = (TH1F*) fileIn->Get(name.Data());
        setupHisto(map_h_dedxById_mc[ilayer][edge_det], 20); //---- kRed
        
        map_gaus_mc[ilayer][edge_det] = -1.0;
        map_land_mc[ilayer][edge_det] = -1.0;
        
      }
    }
  }
  
  
  
  
  
  
  
  
  
  outputCanvas.mkdir ("test/");
  
//   TCanvas* cc_summary_result = new TCanvas ("cc_summary_result","",1000,1000);
//   cc_summary_result->Divide(2, eta_edges.size());
//   
//   TCanvas* cc_summary_data = new TCanvas ("cc_summary_data","",1000,1000);
//   cc_summary_data->Divide(2, eta_edges.size());
//   
//   TCanvas* cc_summary_mc = new TCanvas ("cc_summary_mc","",1000,1000);
//   cc_summary_mc->Divide(2, eta_edges.size());
//   
 
  
  //----  run                     layer   det   
  std::vector< std::map < std::pair<int, int> , TCanvas*> >  vector_map_canvas_entries;
  std::vector< std::map < std::pair<int, int> , TCanvas*> >  vector_map_canvas_like_closure;
  std::vector< std::map < std::pair<int, int> , TCanvas*> >  vector_map_canvas_like_scan;
  std::vector< std::map < std::pair<int, int> , TCanvas*> >  vector_map_canvas_histo;
  
  for (int iRun =0; iRun < num_run_intervals; iRun++) {
    std::pair<int, int> layer_det;
    //----            layer   det   
    std::map< std::pair<int, int> , TCanvas*> mini_map_canvas_entries;
    std::map< std::pair<int, int> , TCanvas*> mini_map_canvas_like_closure;
    std::map< std::pair<int, int> , TCanvas*> mini_map_canvas_like_scan;
    std::map< std::pair<int, int> , TCanvas*> mini_map_canvas_histo;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
      for (int idet = 0; idet<detId.size(); idet++) { 
        layer_det.first = ilayer;
        layer_det.second = idet;
      
        TString name;  
        
        name = Form ("cc_entries__iRun_%d__idet_%d__ilayer_%d" , iRun, idet, ilayer); 
        mini_map_canvas_entries[layer_det] = new TCanvas (name.Data(),"",800,1800);
        mini_map_canvas_entries[layer_det]->Divide(2, eta_edges.size());

        name = Form ("cc_like_closure__iRun_%d__idet_%d__ilayer_%d" , iRun, idet, ilayer); 
        mini_map_canvas_like_closure[layer_det] = new TCanvas (name.Data(),"",800,1800);
        mini_map_canvas_like_closure[layer_det]->Divide(2, eta_edges.size());

        name = Form ("cc_like_scan__iRun_%d__idet_%d__ilayer_%d" , iRun, idet, ilayer); 
        mini_map_canvas_like_scan[layer_det] = new TCanvas (name.Data(),"",800,1800);
        mini_map_canvas_like_scan[layer_det]->Divide(2, eta_edges.size());
        
        name = Form ("cc_histo__iRun_%d__idet_%d__ilayer_%d" , iRun, idet, ilayer); 
        mini_map_canvas_histo[layer_det] = new TCanvas (name.Data(),"",800,1800);
        mini_map_canvas_histo[layer_det]->Divide(2, eta_edges.size());
        
      }
    }
    vector_map_canvas_entries.push_back(mini_map_canvas_entries);
    vector_map_canvas_like_closure.push_back(mini_map_canvas_like_closure);
    vector_map_canvas_like_scan.push_back(mini_map_canvas_like_scan);
    vector_map_canvas_histo.push_back(mini_map_canvas_histo);
  }
  
  
  
  
  //   float min_landau = 2.15;
  //   float max_landau = 4.4;
  float min_landau = 2.0;
  float max_landau = 6.5;
  
  float min_histo = 0.1; //---- remove peak at 0
  float max_histo = 10.0;
  
  
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
    
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
      
      for (int idet = 0; idet<detId.size(); idet++) { 
        
//         std::cout << " iEdge = " << iEdge << " ilayer = " << ilayer << " idet = " << idet << std::endl;
        
        
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;
        
        
        f_gauss->SetParameter(0, 0);
        f_gauss->SetParameter(2, 2);
        
        f_landau->SetParameter(0, 0);
        f_landau->SetParameter(2, 1);
        
        
        std::pair<int, int> layer_det;
        layer_det.first = ilayer;
        layer_det.second = idet;
        
        //---- plot and fit data
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
//           std::cout << "   -> iRun = " << iRun << std::endl;
          
          //---- canvas histo:   (ieta *2) + idet + 1
          vector_map_canvas_histo[iRun][layer_det] -> cd (iEdge*2 + idet + 1);
          
          if (iRun==0) vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Draw("hist");
          else  vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Draw("hist same");
          
          //---- save time if empty
          if (vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Integral() == 0) continue;
          
          f_gauss->SetParameter(1, sqrt(vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Integral()));
          f_gauss->SetParameter(3, 3.0);  
          f_gauss->SetParameter(2, 2.0);  
          f_landau->SetParameter(1, sqrt(vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Integral()));
          f_landau->SetParameter(3, 3);  
          f_landau->SetParameter(2, 2.0);  
          vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
          
          vector_map_gaus_data[iRun][ilayer][edge_det] = f_gauss->GetParameter(3);
          
          vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
          vector_map_land_data[iRun][ilayer][edge_det] = f_landau->GetParameter(3);
          
          f_landau->DrawClone("same");
          f_gauss->DrawClone("same");
        }
        
        //---- plot and fit also MC
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
          vector_map_canvas_histo[iRun][layer_det] -> cd(iEdge*2 + idet + 1);
          map_h_dedxById_mc[ilayer][edge_det]->Draw("hist same");
       
          if (iRun == 0) {
            f_gauss->SetParameter(1, sqrt(map_h_dedxById_mc[ilayer][edge_det]->Integral()));
            f_gauss->SetParameter(3, 3.0);  
            f_gauss->SetParameter(2, 2.0);  
            f_landau->SetParameter(1, sqrt(map_h_dedxById_mc[ilayer][edge_det]->Integral()));
            f_landau->SetParameter(3, 3);  
            f_landau->SetParameter(2, 2.0);  
            
            //---- save time if empty
            if (map_h_dedxById_mc[ilayer][edge_det]->Integral() == 0) continue;
            
            map_h_dedxById_mc[ilayer][edge_det]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
            map_gaus_mc[ilayer][edge_det] = f_gauss->GetParameter(3);
            
            map_h_dedxById_mc[ilayer][edge_det]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
            map_land_mc[ilayer][edge_det] = f_landau->GetParameter(3);
            
            f_landau->DrawClone("same");
            f_gauss->DrawClone("same");
          }
        }
        
        
        
        
        int npoint = 100;
        
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
          
          //---- template fit
          TemplateFit myFit;
          //---- define the reference histogram 
          //---> first check bias in data vs data
          myFit.set_reference_histogram(vector_map_h_dedxById_data[iRun][ilayer][edge_det]);
          myFit.set_min_max( 0.0,    8.0 );
          
          
          //---- canvas closure:   (ieta *2) + idet + 1
          vector_map_canvas_like_closure[iRun][layer_det] -> cd (iEdge*2 + idet + 1);
          
          TGraph* likelihoodScan = new TGraph();
          TGraph* entriesScan = new TGraph();
          
          if (vector_map_h_dedxById_data[iRun][ilayer][edge_det]->Integral() > 500 ) {  
            for (int ipoint=0; ipoint<npoint; ipoint++) {
              float likelihood = 1;
              float loglikelihood = 0;
              float entries = 0;
              
              float scale_value = 0.95 + 0.10/npoint * ipoint;
              myFit.set_scale( scale_value );
              
              for (int ibin=0; ibin<vector_map_h_dedxById_data[iRun][ilayer][edge_det]->GetNbinsX(); ibin++) {
                if ( (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinCenter (ibin+1)) >= min_histo && (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinCenter (ibin+1)) <= max_histo) {
                  if (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1) > 0) {
                    
                    float value = myFit.evaluate (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinCenter (ibin+1));
                    if (value != 0) {
                      likelihood *= ( pow( value , (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1))) ) ;
                      loglikelihood += ( (log ( value )) * (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1)) ) ;
                      entries += (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1));
                    }
                  }
                }
              }
              
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
//           std::cout << " min = " << bias_min_value << std::endl;
          bias_min_value = (1. - bias_min_value);
          
        
          
          
          //---- FIX bias deactivated
          //       bias_min_value = 0;
          //----
          
          //---- canvas counting:   (ieta *2) + idet + 1
          vector_map_canvas_entries[iRun][layer_det] -> cd (iEdge*2 + idet + 1);
          entriesScan->DrawClone("APL");
          
          
          //---- now do the mc to data fit
          myFit.set_reference_histogram(map_h_dedxById_mc[ilayer][edge_det]);
          
          //---- canvas likelihood:   (ieta *2) + idet + 1
          vector_map_canvas_like_scan[iRun][layer_det] -> cd (iEdge*2 + idet + 1);
          TGraph* likelihoodScan_mc_data = new TGraph();
          
          if (map_h_dedxById_mc[ilayer][edge_det]->Integral() > 500 ) {
            for (int ipoint=0; ipoint<npoint; ipoint++) {
              float likelihood = 1;
              float loglikelihood = 0;
              float entries = 0;
              
              float scale_value = 0.95 + 0.10/npoint * ipoint;
              myFit.set_scale( scale_value );
              
              for (int ibin=0; ibin<vector_map_h_dedxById_data[iRun][ilayer][edge_det]->GetNbinsX(); ibin++) {
                if ( (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinCenter (ibin+1)) >= min_histo && (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinCenter (ibin+1)) <= max_histo) {
                  if (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1) > 0) {
                    
                    float value = myFit.evaluate (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinCenter (ibin+1));
                    if (value != 0) {
                      likelihood *= ( pow( value , (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1))) ) ;
                      loglikelihood += ( (log ( value )) * (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1)) ) ;
                      entries += (vector_map_h_dedxById_data[iRun][ilayer][edge_det] -> GetBinContent(ibin+1));
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
          std::cout << " Scale [ " << iRun << ", " << ilayer << ", " << iEdge << ", " << idet << "] = " << final_scale << std::endl;
          vector_map_like_data[iRun][ilayer][edge_det] = final_scale;
          
        }
        
      }
    }
  }
  
  
  //---- save output 
  
  std::cout << " save output ... " << std::endl;
  
  outputCanvas.cd();
  outputCanvas.mkdir ("all");
  outputCanvas.cd("all");
  
  for (int iRun =0; iRun < num_run_intervals; iRun++) {
    std::pair<int, int> layer_det;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
      for (int idet = 0; idet<detId.size(); idet++) {
        layer_det.first = ilayer;
        layer_det.second = idet;
        vector_map_canvas_entries      [iRun][layer_det]->Write();
        vector_map_canvas_histo        [iRun][layer_det]->Write();
        vector_map_canvas_like_closure [iRun][layer_det]->Write();
        vector_map_canvas_like_scan    [iRun][layer_det]->Write();
        
        TString name;
        
        name = Form ("plot_calibration_run/cc_entries__iRun_%d__idet_%d__ilayer_%d.png" , iRun, idet, ilayer); 
        vector_map_canvas_entries      [iRun][layer_det]->SaveAs( name.Data() );
        
        name = Form ("plot_calibration_run/cc_like_closure__iRun_%d__idet_%d__ilayer_%d.png" , iRun, idet, ilayer); 
        vector_map_canvas_like_closure [iRun][layer_det]->SaveAs( name.Data() );
        
        name = Form ("plot_calibration_run/cc_like_scan__iRun_%d__idet_%d__ilayer_%d.png" , iRun, idet, ilayer); 
        vector_map_canvas_like_scan    [iRun][layer_det]->SaveAs( name.Data() );
        
        name = Form ("plot_calibration_run/cc_histo__iRun_%d__idet_%d__ilayer_%d.png" , iRun, idet, ilayer); 
        vector_map_canvas_histo        [iRun][layer_det]->SaveAs( name.Data() );
                
      }
    }
  }
  
  
  
  //---- now get the values and transform into historical dependence
      
  //----     iRun           eta                      layer  det   
  std::map < int, std::map< int, std::map < std::pair<int, int> , float> > > map_scale;
    
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int idet = 0; idet<detId.size(); idet++) {
        std::pair<int, int> edge_det;
        edge_det.first = iEdge;
        edge_det.second = idet;      
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
          //----      |     eta             layer            det            iRun     |
          myfile << " |" << iEdge << " " << ilayer << " " << idet << " " << iRun << "|";
          myfile << "    " << map_land_mc[ilayer][edge_det] / vector_map_land_data[iRun][ilayer][edge_det];
          myfile  << " [ " << map_land_mc[ilayer][edge_det] << " / " << vector_map_land_data[iRun][ilayer][edge_det] << " ]" ;
          
          myfile << "    " << map_gaus_mc[ilayer][edge_det] / vector_map_gaus_data[iRun][ilayer][edge_det];
          myfile  << " [ " << map_gaus_mc[ilayer][edge_det] << " / " << vector_map_gaus_data[iRun][ilayer][edge_det] << " ]" ;
          
          myfile << "    " << vector_map_like_data[iRun][ilayer][edge_det]  << std::endl;
          
          
          
          myfile_reduced << iEdge << " " << ilayer << " " << idet << "               ";
          float best_value = 1.;
          
          float value_1;
          if (vector_map_land_data[iRun][ilayer][edge_det] != 0 ) value_1 = map_land_mc[ilayer][edge_det] / vector_map_land_data[iRun][ilayer][edge_det];
          float value_2;
          if (vector_map_gaus_data[iRun][ilayer][edge_det] != 0 ) value_2 = map_gaus_mc[ilayer][edge_det] / vector_map_gaus_data[iRun][ilayer][edge_det];
          float value_3 =  vector_map_like_data[iRun][ilayer][edge_det];
          
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
         
          std::pair<int, int> layer_det;
          layer_det.first = ilayer;
          layer_det.second = idet; 
          
          map_scale[iRun][iEdge][layer_det] = best_value;
           
        }
      }
    }
    
  }
  
  
  //---- now plot

  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {  
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int idet = 0; idet<detId.size(); idet++) {
        std::pair<int, int> layer_det;
        layer_det.first = ilayer;
        layer_det.second = idet; 
        
        TString name;
        name = Form ("cc_scale__eta_%d__idet_%d__ilayer_%d" , iEdge, idet, ilayer); 
        TCanvas* temp_canvas = new TCanvas (name.Data(), "", 800, 600);
        
        TGraph* evolution_scale = new TGraph();
        
        for (int iRun =0; iRun < num_run_intervals; iRun++) {
          evolution_scale->SetPoint(iRun, iRun, map_scale[iRun][iEdge][layer_det]);
        }
        
        evolution_scale->SetMarkerSize(2);
        evolution_scale->SetMarkerStyle(21);
        evolution_scale->SetMarkerColor(kRed);
        evolution_scale->SetLineColor(kRed);
        
        evolution_scale->Draw("APL");
        
        name = Form ("plot_calibration_run/cc_scale__eta_%d__idet_%d__ilayer_%d.png" , iEdge, idet, ilayer); 
        temp_canvas -> SaveAs (name.Data());
        
      }
    }
  }
  
  
  
  
  outputCanvas.Close();
  
  myfile.close(); 
  myfile_reduced.close();
  
}


