//
// Scale and smear
//
//
//   g++ -o calibratePixelTimeNew.exe calibratePixelTimeNew.cpp `root-config --cflags --glibs`
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
  //   eta_edges.push_back(-2.5);           FindEdge  -> FindEdgeAbs
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
  
  
  //---- 
  //---- layer 
  //----
  std::vector<int> layerId;
  for (int ilayer = 0; ilayer<20; ilayer++) {
    layerId.push_back(ilayer);
  }
  
  
  //---- 
  //---- ladderblade 
  //----
  std::vector<int> ladderbladeId;
  for (int iladderblade = 0; iladderblade<12; iladderblade++) {
    //     for (int iladderblade = 0; iladderblade<40; iladderblade++) {
    ladderbladeId.push_back(iladderblade);
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  //---- a vector for the different run-ranges
  
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_BPIX_data;
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_FPIX_data;
  
  
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_scale_data;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_scale_data;

  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_gaus_data;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_gaus_data;

  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_land_data;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_land_data;

  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_like_data;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_like_data;
  
  
  
  
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_best;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_best;
  
  
  
  
  
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
    map_calibration_BPIX_scale_data.push_back(v_1);
    map_calibration_FPIX_scale_data.push_back(v_1);
    
    map_calibration_BPIX_gaus_data.push_back(v_1);
    map_calibration_FPIX_gaus_data.push_back(v_1);
    
    map_calibration_BPIX_land_data.push_back(v_1);
    map_calibration_FPIX_land_data.push_back(v_1);
    
    map_calibration_BPIX_like_data.push_back(v_1);
    map_calibration_FPIX_like_data.push_back(v_1);

    map_calibration_BPIX_best.push_back(v_1);
    map_calibration_FPIX_best.push_back(v_1);
    
  }
  
  
  
  
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_BPIX;
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_FPIX;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      std::vector < std::vector  < TH1F* > > v_2_BPIX;
      std::vector < std::vector  < TH1F* > > v_2_FPIX;
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        std::vector < TH1F* > v_BPIX;
        std::vector < TH1F* > v_FPIX;
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          TString name;      
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_data", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp = (TH1F*) fileIn->Get(name.Data());
          setupHisto(temp, iRun);
          v_BPIX.push_back ( temp );
          
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_data", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp2 = (TH1F*) fileIn->Get(name.Data());
          setupHisto(temp2, iRun+10);
          v_FPIX.push_back ( temp2 );
 
          
        }
        v_2_BPIX.push_back(v_BPIX);
        v_2_FPIX.push_back(v_FPIX);
      }
      v_1_BPIX.push_back(v_2_BPIX);
      v_1_FPIX.push_back(v_2_FPIX);
    }
    map_h_BPIX_data.push_back(v_1_BPIX);
    map_h_FPIX_data.push_back(v_1_FPIX);  
  }
  
  
  
  
  
  
  
  
  
  
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_BPIX_mc;
  std::vector < std::vector < std::vector  < std::vector < TH1F* > > > >  map_h_FPIX_mc;
  
  
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_scale_mc;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_scale_mc;
  
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_gaus_mc;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_gaus_mc;
  
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_land_mc;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_land_mc;
  
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_BPIX_like_mc;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_calibration_FPIX_like_mc;
  
  
  //----                mc only 1 run range
  for (int iRun = 0; iRun<1; iRun++) {
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
    map_calibration_BPIX_scale_mc.push_back(v_1);
    map_calibration_FPIX_scale_mc.push_back(v_1);
    
    map_calibration_BPIX_gaus_mc.push_back(v_1);
    map_calibration_FPIX_gaus_mc.push_back(v_1);
    
    map_calibration_BPIX_land_mc.push_back(v_1);
    map_calibration_FPIX_land_mc.push_back(v_1);
    
    map_calibration_BPIX_like_mc.push_back(v_1);
    map_calibration_FPIX_like_mc.push_back(v_1);
    
  }
  
  
  
  
  //----                mc only 1 run range
  for (int iRun = 0; iRun<1; iRun++) {
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_BPIX;
    std::vector < std::vector < std::vector  < TH1F* > > > v_1_FPIX;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      std::vector < std::vector  < TH1F* > > v_2_BPIX;
      std::vector < std::vector  < TH1F* > > v_2_FPIX;
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        std::vector < TH1F* > v_BPIX;
        std::vector < TH1F* > v_FPIX;
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          TString name;      
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp = (TH1F*) fileIn->Get(name.Data());
          setupHisto(temp, iRun);
          v_BPIX.push_back ( temp );
          
          name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX_mc", iRun, ilayer, iEdge, iladderblade);   
          TH1F* temp2 = (TH1F*) fileIn->Get(name.Data());
          setupHisto(temp2, iRun);
          v_FPIX.push_back ( temp2 );
          
          
        }
        v_2_BPIX.push_back(v_BPIX);
        v_2_FPIX.push_back(v_FPIX);
      }
      v_1_BPIX.push_back(v_2_BPIX);
      v_1_FPIX.push_back(v_2_FPIX);
    }
    map_h_BPIX_mc.push_back(v_1_BPIX);
    map_h_FPIX_mc.push_back(v_1_FPIX);  
  }
  
  
  
  
  
  
  
  
  
  outputCanvas.mkdir ("test/");
  
  
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < TCanvas* > > > >  vector_map_canvas_all_BPIX;
  std::vector < std::vector < std::vector  < std::vector < TCanvas* > > > >  vector_map_canvas_all_FPIX;
  //   canvas with:   |  data/mc    |      entries    |     likelihood scan  |    closure likelihood   | 
  
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
    std::vector < std::vector < std::vector  < TCanvas* > > > v_1_BPIX;
    std::vector < std::vector < std::vector  < TCanvas* > > > v_1_FPIX;
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      std::vector < std::vector  < TCanvas* > > v_2_BPIX;
      std::vector < std::vector  < TCanvas* > > v_2_FPIX;
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        std::vector < TCanvas* > v_BPIX;
        std::vector < TCanvas* > v_FPIX;
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          TString name;      
          name = Form ("canvas_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX", iRun, ilayer, iEdge, iladderblade);   
          TCanvas* temp = new TCanvas (name.Data(),"",800,800);
          temp -> Divide (2, 2);
          v_BPIX.push_back ( temp );
          
          name = Form ("canvas_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX", iRun, ilayer, iEdge, iladderblade);   
          TCanvas* temp2 = new TCanvas (name.Data(),"",800,800);
          temp2 -> Divide (2, 2);
          v_FPIX.push_back ( temp2 );
          
          
        }
        v_2_BPIX.push_back(v_BPIX);
        v_2_FPIX.push_back(v_FPIX);
      }
      v_1_BPIX.push_back(v_2_BPIX);
      v_1_FPIX.push_back(v_2_FPIX);
    }
    vector_map_canvas_all_BPIX.push_back(v_1_BPIX);
    vector_map_canvas_all_FPIX.push_back(v_1_FPIX);  
  }
  
  
  
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
   
    for (int iRun = 0; iRun<num_run_intervals; iRun++) {
      for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
        //---- BPIX
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          f_gauss->SetParameter(0, 0);
          f_gauss->SetParameter(2, 2);
          
          f_landau->SetParameter(0, 0);
          f_landau->SetParameter(2, 1);
          
          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> cd (1);
          
          map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->DrawNormalized("hist");
          
          //---- save time if empty
          if (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral() == 0) continue;
          
          f_gauss->SetParameter(1, sqrt(map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_gauss->SetParameter(3, 3.0);  
          f_gauss->SetParameter(2, 2.0);  
          f_landau->SetParameter(1, sqrt(map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_landau->SetParameter(3, 3);  
          f_landau->SetParameter(2, 2.0);  
          map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
          
          map_calibration_BPIX_gaus_data[iRun][ilayer][iEdge][iladderblade] = f_gauss->GetParameter(3);
          
          map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
          map_calibration_BPIX_land_data[iRun][ilayer][iEdge][iladderblade] = f_landau->GetParameter(3);
          
          f_landau->DrawClone("same");
          f_gauss->DrawClone("same");
          
        }

        
        //---- FPIX
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          f_gauss->SetParameter(0, 0);
          f_gauss->SetParameter(2, 2);
          
          f_landau->SetParameter(0, 0);
          f_landau->SetParameter(2, 1);
          
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> cd (1);
          
          map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->DrawNormalized("hist");
          
          //---- save time if empty
          if (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral() == 0) continue;
          
          f_gauss->SetParameter(1, sqrt(map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_gauss->SetParameter(3, 3.0);  
          f_gauss->SetParameter(2, 2.0);  
          f_landau->SetParameter(1, sqrt(map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_landau->SetParameter(3, 3);  
          f_landau->SetParameter(2, 2.0);  
          map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
          
          map_calibration_FPIX_gaus_data[iRun][ilayer][iEdge][iladderblade] = f_gauss->GetParameter(3);
          
          map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
          map_calibration_FPIX_land_data[iRun][ilayer][iEdge][iladderblade] = f_landau->GetParameter(3);
          
          f_landau->DrawClone("same");
          f_gauss->DrawClone("same");
          
        }
        
        
      }
    }
  }
  
  
  
  
  
  
  //---- mc 
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    TString name;  
    name = Form ("eta_%d" , iEdge); 
    
    outputCanvas.cd();
    outputCanvas.cd(name.Data());
    
    for (int iRun = 0; iRun<1; iRun++) {
      for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
        //---- BPIX
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          f_gauss->SetParameter(0, 0);
          f_gauss->SetParameter(2, 2);
          
          f_landau->SetParameter(0, 0);
          f_landau->SetParameter(2, 1);
          
          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> cd (1);
          
          map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade]->DrawNormalized("hist same");
          
          //---- save time if empty
          if (map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade]->Integral() == 0) continue;
          
          f_gauss->SetParameter(1, sqrt(map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_gauss->SetParameter(3, 3.0);  
          f_gauss->SetParameter(2, 2.0);  
          f_landau->SetParameter(1, sqrt(map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_landau->SetParameter(3, 3);  
          f_landau->SetParameter(2, 2.0);  
          map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
          
          map_calibration_BPIX_gaus_mc[iRun][ilayer][iEdge][iladderblade] = f_gauss->GetParameter(3);
          
          map_h_BPIX_mc[iRun][ilayer][iEdge][iladderblade]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
          map_calibration_BPIX_land_mc[iRun][ilayer][iEdge][iladderblade] = f_landau->GetParameter(3);
          
          f_landau->DrawClone("same");
          f_gauss->DrawClone("same");
          
        }
        
        
        //---- FPIX
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          f_gauss->SetParameter(0, 0);
          f_gauss->SetParameter(2, 2);
          
          f_landau->SetParameter(0, 0);
          f_landau->SetParameter(2, 1);
          
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> cd (1);
          
          map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade]->DrawNormalized("hist same");
          
          //---- save time if empty
          if (map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade]->Integral() == 0) continue;
          
          f_gauss->SetParameter(1, sqrt(map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_gauss->SetParameter(3, 3.0);  
          f_gauss->SetParameter(2, 2.0);  
          f_landau->SetParameter(1, sqrt(map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade]->Integral()));
          f_landau->SetParameter(3, 3);  
          f_landau->SetParameter(2, 2.0);  
          map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade]->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
          
          map_calibration_FPIX_gaus_mc[iRun][ilayer][iEdge][iladderblade] = f_gauss->GetParameter(3);
          
          map_h_FPIX_mc[iRun][ilayer][iEdge][iladderblade]->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
          map_calibration_FPIX_land_mc[iRun][ilayer][iEdge][iladderblade] = f_landau->GetParameter(3);
          
          f_landau->DrawClone("same");
          f_gauss->DrawClone("same");
          
        }
        
        
      }
    }
  }
  
  
  
  
  
  //---- now likelihood scan
  
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    TString name;  
    name = Form ("eta_%d" , iEdge); 
    
    outputCanvas.cd();
    outputCanvas.cd(name.Data());
    
    for (int iRun = 0; iRun<num_run_intervals; iRun++) {
      for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
        //---- BPIX
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          
          //---- save time if empty
          if (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral() == 0) continue;
          
          
          int npoint = 100;
          
          //---- template fit
          TemplateFit myFit;
          //---- define the reference histogram 
          //---> first check bias in data vs data
          myFit.set_reference_histogram(map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]);
          myFit.set_min_max( 0.0,    8.0 );
          
          
          //   canvas with:   |  data/mc    |      entries    |     likelihood scan  |    closure likelihood   | 
          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> cd (4);
          
          TGraph* likelihoodScan = new TGraph();
          TGraph* entriesScan = new TGraph();
          
          if (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral() > 500 ) {  
            for (int ipoint=0; ipoint<npoint; ipoint++) {
              float likelihood = 1;
              float loglikelihood = 0;
              float entries = 0;
              
              float scale_value = 0.95 + 0.10/npoint * ipoint;
              myFit.set_scale( scale_value );
              
              for (int ibin=0; ibin<map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetNbinsX(); ibin++) {
                if ( (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) >= min_histo && (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) <= max_histo) {
                  if (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1) > 0) {
                    
                    float value = myFit.evaluate (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1));
                    if (value != 0) {
                      likelihood *= ( pow( value , (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1))) ) ;
                      loglikelihood += ( (log ( value )) * (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1)) ) ;
                      entries += (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1));
                    }
                  }
                }
              }
              
              likelihoodScan -> SetPoint ( ipoint, scale_value, -2 * loglikelihood  ); 
              entriesScan -> SetPoint ( ipoint, scale_value, entries ); 
              
            }
          }
          
          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> cd (4);
          
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
          
          //---- canvas counting: 
          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> cd (2);
          entriesScan->DrawClone("APL");
          
          
          //---- now do the mc to data fit
          myFit.set_reference_histogram(map_h_BPIX_mc[0][ilayer][iEdge][iladderblade]);
          
          //---- canvas likelihood
          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> cd (3);
          TGraph* likelihoodScan_mc_data = new TGraph();
          
          if (map_h_BPIX_data[0][ilayer][iEdge][iladderblade]->Integral() > 500 ) {
            for (int ipoint=0; ipoint<npoint; ipoint++) {
              float likelihood = 1;
              float loglikelihood = 0;
              float entries = 0;
              
              float scale_value = 0.95 + 0.10/npoint * ipoint;
              myFit.set_scale( scale_value );
              
              for (int ibin=0; ibin<map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade]->GetNbinsX(); ibin++) {
                if ( (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) >= min_histo && (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) <= max_histo) {
                  if (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1) > 0) {
                    
                    float value = myFit.evaluate (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1));
                    if (value != 0) {
                      likelihood *= ( pow( value , (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1))) ) ;
                      loglikelihood += ( (log ( value )) * (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1)) ) ;
                      entries += (map_h_BPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1));
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
          map_calibration_BPIX_like_data[iRun][ilayer][iEdge][iladderblade] = final_scale;
          
        }
      }
    }
  }
  
  
  
  
  
  
  
  
  for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
    TString name;  
    name = Form ("eta_%d" , iEdge); 
    
    outputCanvas.cd();
    outputCanvas.cd(name.Data());
    
    for (int iRun = 0; iRun<num_run_intervals; iRun++) {
      for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
        //---- FPIX
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          //---- save time if empty
          if (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral() == 0) continue;
          
          int npoint = 100;
          
          //---- template fit
          TemplateFit myFit;
          //---- define the reference histogram 
          //---> first check bias in data vs data
          myFit.set_reference_histogram(map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]);
          myFit.set_min_max( 0.0,    8.0 );
          
          
          //   canvas with:   |  data/mc    |      entries    |     likelihood scan  |    closure likelihood   | 
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> cd (4);
          
          TGraph* likelihoodScan = new TGraph();
          TGraph* entriesScan = new TGraph();
          
          if (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->Integral() > 500 ) {  
            for (int ipoint=0; ipoint<npoint; ipoint++) {
              float likelihood = 1;
              float loglikelihood = 0;
              float entries = 0;
              
              float scale_value = 0.95 + 0.10/npoint * ipoint;
              myFit.set_scale( scale_value );
              
              for (int ibin=0; ibin<map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetNbinsX(); ibin++) {
                if ( (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) >= min_histo && (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) <= max_histo) {
                  if (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1) > 0) {
                    
                    float value = myFit.evaluate (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1));
                    if (value != 0) {
                      likelihood *= ( pow( value , (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1))) ) ;
                      loglikelihood += ( (log ( value )) * (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1)) ) ;
                      entries += (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1));
                    }
                  }
                }
              }
              
              likelihoodScan -> SetPoint ( ipoint, scale_value, -2 * loglikelihood  ); 
              entriesScan -> SetPoint ( ipoint, scale_value, entries ); 
              
            }
          }
          
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> cd (4);
          
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
          
          //---- canvas counting: 
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> cd (2);
          entriesScan->DrawClone("APL");
          
          
          //---- now do the mc to data fit
          myFit.set_reference_histogram(map_h_FPIX_mc[0][ilayer][iEdge][iladderblade]);
          
          //---- canvas likelihood
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> cd (3);
          TGraph* likelihoodScan_mc_data = new TGraph();
          
          if (map_h_FPIX_data[0][ilayer][iEdge][iladderblade]->Integral() > 500 ) {
            for (int ipoint=0; ipoint<npoint; ipoint++) {
              float likelihood = 1;
              float loglikelihood = 0;
              float entries = 0;
              
              float scale_value = 0.95 + 0.10/npoint * ipoint;
              myFit.set_scale( scale_value );
              
              for (int ibin=0; ibin<map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade]->GetNbinsX(); ibin++) {
                if ( (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) >= min_histo && (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1)) <= max_histo) {
                  if (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1) > 0) {
                    
                    float value = myFit.evaluate (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinCenter (ibin+1));
                    if (value != 0) {
                      likelihood *= ( pow( value , (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1))) ) ;
                      loglikelihood += ( (log ( value )) * (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1)) ) ;
                      entries += (map_h_FPIX_data[iRun][ilayer][iEdge][iladderblade] -> GetBinContent(ibin+1));
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
          map_calibration_FPIX_like_data[iRun][ilayer][iEdge][iladderblade] = final_scale;
          
        }
      }
    }
  }
  
  
  
  
  
  
  //---- save output 
  
  std::cout << " save output ... " << std::endl;
  
  outputCanvas.cd();
  outputCanvas.mkdir ("all");
  outputCanvas.cd("all");
  
  
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     

          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> Write();
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> Write();
          
          TString name;      
          name = Form ("plot_calibration_run/canvas_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX.png", iRun, ilayer, iEdge, iladderblade);   
          vector_map_canvas_all_BPIX[iRun][ilayer][iEdge][iladderblade] -> SaveAs( name.Data() );
          name = Form ("plot_calibration_run/canvas_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_FPIX.png", iRun, ilayer, iEdge, iladderblade);   
          vector_map_canvas_all_FPIX[iRun][ilayer][iEdge][iladderblade] -> SaveAs( name.Data() );
          
        }
      }
    }
  }
  
  
  
  
  //---- now get the values and transform into historical dependence
   
   
  //---- iRun       layer         eta        ladderblade     
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_scale_BPIX;
  std::vector < std::vector < std::vector  < std::vector < float > > > >  map_scale_FPIX;
   
 
  
  
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
    map_scale_BPIX.push_back(v_1);
    map_scale_FPIX.push_back(v_1);
  }
  
  
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          myfile << " |" << iEdge << " " << ilayer << " " << iladderblade << " " << iRun << "|";
          myfile << "    " << map_calibration_BPIX_like_data[iRun][ilayer][iEdge][iladderblade];
          
          myfile << "    " << map_calibration_BPIX_gaus_mc[0][ilayer][iEdge][iladderblade] / map_calibration_BPIX_gaus_data[iRun][ilayer][iEdge][iladderblade];
          myfile  << " [ " << map_calibration_BPIX_gaus_mc[0][ilayer][iEdge][iladderblade] << " / " << map_calibration_BPIX_gaus_data[iRun][ilayer][iEdge][iladderblade] << " ]" ;
          
          myfile << "    " << map_calibration_BPIX_land_mc[0][ilayer][iEdge][iladderblade] / map_calibration_BPIX_land_data[iRun][ilayer][iEdge][iladderblade];
          myfile  << " [ " << map_calibration_BPIX_land_mc[0][ilayer][iEdge][iladderblade] << " / " << map_calibration_BPIX_land_data[iRun][ilayer][iEdge][iladderblade] << " ]" ;
          
          
          
          myfile << "    " << map_calibration_FPIX_like_data[iRun][ilayer][iEdge][iladderblade];
          
          myfile << "    " << map_calibration_FPIX_gaus_mc[0][ilayer][iEdge][iladderblade] / map_calibration_FPIX_gaus_data[iRun][ilayer][iEdge][iladderblade];
          myfile  << " [ " << map_calibration_FPIX_gaus_mc[0][ilayer][iEdge][iladderblade] << " / " << map_calibration_FPIX_gaus_data[iRun][ilayer][iEdge][iladderblade] << " ]" ;
          
          myfile << "    " << map_calibration_FPIX_land_mc[0][ilayer][iEdge][iladderblade] / map_calibration_FPIX_land_data[iRun][ilayer][iEdge][iladderblade];
          myfile  << " [ " << map_calibration_FPIX_land_mc[0][ilayer][iEdge][iladderblade] << " / " << map_calibration_FPIX_land_data[iRun][ilayer][iEdge][iladderblade] << " ]" ;
          
          
          
          myfile << "    "  << std::endl;
          
          
        }
      }
    }
  }
  
  
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {
    for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
      for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
        for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
          
          float best_value = 1.;
          
          float value_1;
          if (map_calibration_BPIX_like_data[iRun][ilayer][iEdge][iladderblade] != 0 ) value_1 =  map_calibration_BPIX_land_mc[0][ilayer][iEdge][iladderblade] / map_calibration_BPIX_land_data[iRun][ilayer][iEdge][iladderblade];
          float value_2;
          if (map_calibration_BPIX_gaus_data[iRun][ilayer][iEdge][iladderblade] != 0 ) value_2 = map_calibration_BPIX_gaus_mc[0][ilayer][iEdge][iladderblade] / map_calibration_BPIX_gaus_data[iRun][ilayer][iEdge][iladderblade];
          float value_3 =  map_calibration_BPIX_like_data[iRun][ilayer][iEdge][iladderblade];
          
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
          
          myfile_reduced << " |" << iEdge << " " << ilayer << " " << iladderblade << " " << iRun << "|";
          myfile_reduced << "    " << best_value;
          
          map_calibration_BPIX_best[iRun][ilayer][iEdge][iladderblade] = best_value;
          
          
          
          best_value = 1.;
          
          value_1 = 0;
          if (map_calibration_FPIX_like_data[iRun][ilayer][iEdge][iladderblade] != 0 ) value_1 =  map_calibration_FPIX_land_mc[0][ilayer][iEdge][iladderblade] / map_calibration_FPIX_land_data[iRun][ilayer][iEdge][iladderblade];
          value_2 = 0;
          if (map_calibration_FPIX_gaus_data[iRun][ilayer][iEdge][iladderblade] != 0 ) value_2 = map_calibration_FPIX_gaus_mc[0][ilayer][iEdge][iladderblade] / map_calibration_FPIX_gaus_data[iRun][ilayer][iEdge][iladderblade];
          value_3 =  map_calibration_FPIX_like_data[iRun][ilayer][iEdge][iladderblade];
          
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
          
          
          myfile_reduced << "    " << best_value;
          myfile_reduced << "    "  << std::endl;
          
          map_calibration_FPIX_best[iRun][ilayer][iEdge][iladderblade] = best_value;
          
          
        }
      }
    }
  }
  
  
  
  
  
  
  for (int ilayer = 0; ilayer<layerId.size(); ilayer++) {
    for (int iEdge = 0; iEdge<eta_edges.size()-1; iEdge++) {
      for (int iladderblade = 0; iladderblade<ladderbladeId.size(); iladderblade++) {     
        
        TString name;
        name = Form ("cc_scale__eta_%d__iladderblade_%d__ilayer_%d" , iEdge, iladderblade, ilayer); 
        TCanvas* temp_canvas = new TCanvas (name.Data(), "", 800, 600);
        
        TGraph* evolution_scale = new TGraph();
        
        for (int iRun = 0; iRun<num_run_intervals; iRun++) {
          evolution_scale->SetPoint(iRun, iRun,  map_calibration_BPIX_best[iRun][ilayer][iEdge][iladderblade]);
        }
        
        evolution_scale->SetMarkerSize(2);
        evolution_scale->SetMarkerStyle(21);
        evolution_scale->SetMarkerColor(kRed);
        evolution_scale->SetLineColor(kRed);
        
        evolution_scale->Draw("APL");
        
        name = Form ("plot_calibration_run/cc_scale__eta_%d__iladderblade_%d__ilayer_%d.png" , iEdge, iladderblade, ilayer); 
        temp_canvas -> SaveAs (name.Data());
        
        
        
      }
    }
  }

 
 
 /*
  
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
  
  
  */
  
  outputCanvas.Close();
  
  myfile.close(); 
  myfile_reduced.close();
  
}


