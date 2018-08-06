//
// Scale and smear
//


void calibrateAuto(std::string fileIn_name) {
  
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
   
  std::vector< float > calibration_values_data;
  std::vector< float > calibration_values_mc;
 
  TCanvas* cc_summary_data = new TCanvas ("cc_summary_data","",1000,1000);
  cc_summary_data->Divide(4,4);
  
  TCanvas* cc_summary_mc = new TCanvas ("cc_summary_mc","",1000,1000);
  cc_summary_mc->Divide(4,4);
  
  
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [4]*x + [5]*x*x  + [1]*[1]/(sqrt(2)*3.14*[2])*exp(-0.5 * (x-[3])*(x-[3])) / ([2]*[2])", 1.5, 4.5);
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1) + [6] * [6] * TMath::Gaus(x,[4],[5]) ", 1.5, 6.5);
//     TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1)", 1.5, 6.5);
  
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.2, 3.5);

  
  float min_landau = 2.15;
  float max_landau = 4.4;
  
//   float min_landau = 2.2;
//   float max_landau = 4.4;
  
  TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 1.5, 6.5);
  TF1* f_landau = new TF1 ("f_landau", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1)", min_landau, max_landau);
  
  


  //   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1)", 1.5, 6.5);
  
  
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
    //     f_landau->SetParameter(1, f_gauss->GetParameter(1));
//     f_landau->SetParameter(3, f_gauss->GetParameter(3));  
//     f_landau->SetParameter(2, f_gauss->GetParameter(2));  
    h_dedxByLayer_data.at(i)->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
    //     calibration_values_data.push_back (f_gauss->GetParameter(3));
    calibration_values_data.push_back (f_landau->GetParameter(3));
    f_landau->DrawClone("same");
    
    
    cc_summary_mc->cd(i+1);
    h_dedxByLayer_mc.at(i)->Draw("hist");
    f_gauss->SetParameter(1, sqrt(h_dedxByLayer_mc.at(i)->Integral()));
    f_gauss->SetParameter(3, h_dedxByLayer_mc.at(i)->GetMean());  
    f_landau->SetParameter(1, sqrt(h_dedxByLayer_mc.at(i)->Integral()));
    f_landau->SetParameter(3, h_dedxByLayer_mc.at(i)->GetMean());  
    h_dedxByLayer_mc.at(i)->Fit("f_gauss", "RMIQ", "", 2.5, 3.4); //---- gauss
//     f_landau->SetParameter(1, f_gauss->GetParameter(1));
//     f_landau->SetParameter(3, f_gauss->GetParameter(3));  
//     f_landau->SetParameter(2, f_gauss->GetParameter(2));  
    h_dedxByLayer_mc.at(i)->Fit("f_landau", "RMIQ", "", min_landau, max_landau); //---- landau
    //     calibration_values_mc.push_back (f_gauss->GetParameter(3));
    calibration_values_mc.push_back (f_landau->GetParameter(3));
    f_landau->DrawClone("same");
    
    
    
  }
  
  
  
  
  std::cout << "       " << std::endl;
  
  for (int iLayer = 0; iLayer<calibration_values_mc.size(); iLayer++) {
    std::cout << " [" << iLayer << "] = " << calibration_values_mc.at(iLayer) / calibration_values_data.at(iLayer) << " = " << calibration_values_mc.at(iLayer) << " / " << calibration_values_data.at(iLayer) << std::endl;
  }
    
  std::cout << "       " << std::endl;
  
  
  
  TCanvas* cc_summary_data_mc = new TCanvas ("cc_summary_data_mc","",1000,1000);
  cc_summary_data_mc->Divide(4,4);
  
  
  for (int i=0; i<14; i++) {
    cc_summary_data_mc->cd(i+1);
    h_dedxByLayer_data.at(i)->DrawNormalized("hist");
    h_dedxByLayer_mc.at(i)->DrawNormalized("hist SAME");
   }
  
  
  
  
}


