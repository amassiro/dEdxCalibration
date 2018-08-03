//
// Scale and smear
//


void calibrate(std::string fileIn_name) {
  
  TFile* fileIn = new TFile (fileIn_name.c_str(), "READ");
  
  TH1F* h_dedxByLayer0_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer0_data");                       TH1F* h_dedxByLayer0_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer0_mc");
  TH1F* h_dedxByLayer1_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer1_data");                       TH1F* h_dedxByLayer1_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer1_mc");
  TH1F* h_dedxByLayer2_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer2_data");                       TH1F* h_dedxByLayer2_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer2_mc");
  TH1F* h_dedxByLayer3_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer3_data");                       TH1F* h_dedxByLayer3_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer3_mc");
  TH1F* h_dedxByLayer4_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer4_data");                       TH1F* h_dedxByLayer4_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer4_mc");
  TH1F* h_dedxByLayer5_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer5_data");                       TH1F* h_dedxByLayer5_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer5_mc");
  TH1F* h_dedxByLayer6_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer6_data");                       TH1F* h_dedxByLayer6_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer6_mc");
  TH1F* h_dedxByLayer7_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer7_data");                       TH1F* h_dedxByLayer7_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer7_mc");
  TH1F* h_dedxByLayer8_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer8_data");                       TH1F* h_dedxByLayer8_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer8_mc");
  TH1F* h_dedxByLayer9_data  = (TH1F*) fileIn -> Get ("h_dedxByLayer9_data");                       TH1F* h_dedxByLayer9_mc  = (TH1F*) fileIn -> Get ("h_dedxByLayer9_mc");
  TH1F* h_dedxByLayer10_data = (TH1F*) fileIn -> Get ("h_dedxByLayer10_data");                      TH1F* h_dedxByLayer10_mc = (TH1F*) fileIn -> Get ("h_dedxByLayer10_mc");
  TH1F* h_dedxByLayer11_data = (TH1F*) fileIn -> Get ("h_dedxByLayer11_data");                      TH1F* h_dedxByLayer11_mc = (TH1F*) fileIn -> Get ("h_dedxByLayer11_mc");
  TH1F* h_dedxByLayer12_data = (TH1F*) fileIn -> Get ("h_dedxByLayer12_data");                      TH1F* h_dedxByLayer12_mc = (TH1F*) fileIn -> Get ("h_dedxByLayer12_mc");
  TH1F* h_dedxByLayer13_data = (TH1F*) fileIn -> Get ("h_dedxByLayer13_data");                      TH1F* h_dedxByLayer13_mc = (TH1F*) fileIn -> Get ("h_dedxByLayer13_mc");
  
 
  std::vector< float > calibration_values_data;
  std::vector< float > calibration_values_mc;
 
  TCanvas* cc_summary_data = new TCanvas ("cc_summary_data","",1000,1000);
  cc_summary_data->Divide(4,4);
  
  TCanvas* cc_summary_mc = new TCanvas ("cc_summary_mc","",1000,1000);
  cc_summary_mc->Divide(4,4);
  
  
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [4]*x + [5]*x*x  + [1]*[1]/(sqrt(2)*3.14*[2])*exp(-0.5 * (x-[3])*(x-[3])) / ([2]*[2])", 1.5, 4.5);
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1) + [6] * [6] * TMath::Gaus(x,[4],[5]) ", 1.5, 6.5);
  //   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1)", 1.5, 6.5);
  
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.2, 3.5);
  TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.2, 3.7);
  
  
  
  
  f_gauss->SetParameter(0, 0);
  f_gauss->SetParameter(2, 2);
//   f_gauss->SetParameter(4, 3);
//   f_gauss->SetParameter(5, 10);
//   f_gauss->SetParameter(6, 10);
  
  
  cc_summary_data->cd(1);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer0_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer0_data->GetMean());  
  h_dedxByLayer0_data->Fit("f_gauss", "RMIQ", "", 2.0, 3.5);
  calibration_values_data.push_back (f_gauss->GetParameter(3));
 
  cc_summary_data->cd(2);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer1_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer1_data->GetMean());  
  h_dedxByLayer1_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));
  
  cc_summary_data->cd(3);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer2_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer2_data->GetMean());  
  h_dedxByLayer2_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));
  
  cc_summary_data->cd(4);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer3_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer3_data->GetMean());  
  h_dedxByLayer3_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(5);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer4_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer4_data->GetMean());  
  h_dedxByLayer4_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(6);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer5_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer5_data->GetMean());  
  h_dedxByLayer5_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(7);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer6_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer6_data->GetMean());  
  h_dedxByLayer6_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(8);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer7_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer7_data->GetMean());  
  h_dedxByLayer7_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(9);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer8_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer8_data->GetMean());  
  h_dedxByLayer8_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(10);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer9_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer9_data->GetMean());  
  h_dedxByLayer9_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(11);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer10_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer10_data->GetMean());  
  h_dedxByLayer10_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(12);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer11_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer11_data->GetMean());  
  h_dedxByLayer11_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(13);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer12_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer12_data->GetMean());  
  h_dedxByLayer12_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));

  cc_summary_data->cd(14);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer13_data->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer13_data->GetMean());  
  h_dedxByLayer13_data->Fit("f_gauss", "RMIQ");
  calibration_values_data.push_back (f_gauss->GetParameter(3));
  
  
  
  
  
  
  
  
  
  
  
  
  cc_summary_mc->cd(1);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer0_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer0_mc->GetMean());  
  h_dedxByLayer0_mc->Fit("f_gauss", "RMIQ", "", 2.3, 3.6);
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(2);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer1_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer1_mc->GetMean());  
  h_dedxByLayer1_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(3);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer2_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer2_mc->GetMean());  
  h_dedxByLayer2_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(4);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer3_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer3_mc->GetMean());  
  h_dedxByLayer3_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(5);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer4_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer4_mc->GetMean());  
  h_dedxByLayer4_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(6);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer5_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer5_mc->GetMean());  
  h_dedxByLayer5_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(7);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer6_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer6_mc->GetMean());  
  h_dedxByLayer6_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(8);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer7_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer7_mc->GetMean());  
  h_dedxByLayer7_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(9);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer8_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer8_mc->GetMean());  
  h_dedxByLayer8_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(10);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer9_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer9_mc->GetMean());  
  h_dedxByLayer9_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(11);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer10_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer10_mc->GetMean());  
  h_dedxByLayer10_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(12);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer11_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer11_mc->GetMean());  
  h_dedxByLayer11_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(13);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer12_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer12_mc->GetMean());  
  h_dedxByLayer12_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  cc_summary_mc->cd(14);
  f_gauss->SetParameter(1, sqrt(h_dedxByLayer13_mc->Integral()));
  f_gauss->SetParameter(3, h_dedxByLayer13_mc->GetMean());  
  h_dedxByLayer13_mc->Fit("f_gauss", "RMIQ");
  calibration_values_mc.push_back (f_gauss->GetParameter(3));
  
  
  
  for (int iLayer = 0; iLayer<calibration_values_mc.size(); iLayer++) {
    std::cout << " [" << iLayer << "] = " << calibration_values_mc.at(iLayer) / calibration_values_data.at(iLayer) << " = " << calibration_values_mc.at(iLayer) << " / " << calibration_values_data.at(iLayer) << std::endl;
  }
  
}


