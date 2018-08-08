  
void toySimulate(int Ntoys=1000000, int nbin = 1000){
  
  TString name = Form ("toys_%d_%d.root", Ntoys, nbin);
  
  TFile* fileOut = new TFile (name.Data(), "RECREATE");
  
  TF1* gauss = new TF1 ("gauss", "gaus", 0, 2);  
  gauss->SetParameter(0, 1);
  gauss->SetParameter(1, 1);
  gauss->SetParameter(2, 0.1);
  
  
  float min = 0;
  float max = 2;
  
  TH1F histo ("histo", "", nbin, min, max);
  histo.FillRandom("gauss", Ntoys);
  
  histo.Write(); 
  gauss->Write();
  
  fileOut->Close();
  
}




  
  