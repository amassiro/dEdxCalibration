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
    TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] * TMath::Landau(x,[3],[2],1)", 1.5, 6.5);
  
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.2, 3.5);
//   TF1* f_gauss = new TF1 ("f_gauss", "[0] + [1] * [1] *TMath::Gaus(x,[3],[2],1)", 2.2, 3.7);
  
  
  
  
  f_gauss->SetParameter(0, 0);
  f_gauss->SetParameter(2, 2);
  
  
  for (int i=0; i<14; i++) {
    cc_summary_data->cd(i+1);
    f_gauss->SetParameter(1, sqrt(h_dedxByLayer_data.at(i)->Integral()));
    f_gauss->SetParameter(3, h_dedxByLayer_data.at(i)->GetMean());  
    h_dedxByLayer_data.at(i)->Fit("f_gauss", "RMIQ", "", 2.0, 4.5);
    calibration_values_data.push_back (f_gauss->GetParameter(3));
    
    
    cc_summary_mc->cd(i+1);
    f_gauss->SetParameter(1, sqrt(h_dedxByLayer_mc.at(i)->Integral()));
    f_gauss->SetParameter(3, h_dedxByLayer_mc.at(i)->GetMean());  
    h_dedxByLayer_mc.at(i)->Fit("f_gauss", "RMIQ", "", 2.0, 4.5);
    calibration_values_mc.push_back (f_gauss->GetParameter(3));
    
    
    
  }
  
  
  
  
  std::cout << "       " << std::endl;
  
  for (int iLayer = 0; iLayer<calibration_values_mc.size(); iLayer++) {
    std::cout << " [" << iLayer << "] = " << calibration_values_mc.at(iLayer) / calibration_values_data.at(iLayer) << " = " << calibration_values_mc.at(iLayer) << " / " << calibration_values_data.at(iLayer) << std::endl;
  }
    
  std::cout << "       " << std::endl;
  
}


