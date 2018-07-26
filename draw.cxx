void draw(std::string name_input_file_data = "out.root", std::string name_input_file_mc = "out.root"){
  
  TFile* inputFile_data = new TFile (name_input_file_data.c_str(), "READ");   
  TTree* inputTree_data = (TTree*) ((TTree*) inputFile_data -> Get ("tree")) -> Clone ("tree_data");
  
  TFile* inputFile_mc = new TFile (name_input_file_mc.c_str(), "READ");   
  TTree* inputTree_mc = (TTree*) ((TTree*) inputFile_mc -> Get ("tree")) -> Clone ("tree_mc");
  
  std::cout << " data = " << inputTree_data->GetEntries() << std::endl;
  std::cout << " mc   = " << inputTree_mc->GetEntries()   << std::endl;
  
  gStyle->SetOptStat(0);
  
  
  //   IsoTrack_dedxByLayer0
  const Int_t kMaxTracks = 1000;
 
  Float_t IsoTrack_dedxByLayer0[kMaxTracks];
  Float_t IsoTrack_pt[kMaxTracks];
  Int_t IsoTrack_highPurity[kMaxTracks];
  Int_t nIsoTrack;

  inputTree_data->Branch("IsoTrack_dedxByLayer0",  &IsoTrack_dedxByLayer0, "IsoTrack_dedxByLayer0[nIsoTrack]/F");
  inputTree_mc  ->Branch("IsoTrack_dedxByLayer0",  &IsoTrack_dedxByLayer0, "IsoTrack_dedxByLayer0[nIsoTrack]/F");
  
  inputTree_data->Branch("IsoTrack_pt",  &IsoTrack_pt  , "IsoTrack_pt[nIsoTrack]/F");
  inputTree_mc  ->Branch("IsoTrack_pt",  &IsoTrack_pt  , "IsoTrack_pt[nIsoTrack]/F");
  
  inputTree_data->Branch("IsoTrack_highPurity",  &IsoTrack_highPurity, "IsoTrack_highPurity[nIsoTrack]/I");
  inputTree_mc  ->Branch("IsoTrack_highPurity",  &IsoTrack_highPurity, "IsoTrack_highPurity[nIsoTrack]/I");
  
  inputTree_data->Branch("nIsoTrack",  &nIsoTrack, "nIsoTrack/I");
  inputTree_mc  ->Branch("nIsoTrack",  &nIsoTrack, "nIsoTrack/I");
  
  TH1F* h_data = new TH1F ("h_data", "data", 100, 0, 20);
  //   for (int iEntry=0; iEntry<inputTree_data->GetEntries(); iEntry++) {
  for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_data->GetEntry(iEntry);
    float max_pt = 0;
    int best_track = -1;
    for (int iTrack = 0; iTrack < std::min(kMaxTracks, nIsoTrack); iTrack++) {
      if (IsoTrack_pt[iTrack] > max_pt && IsoTrack_highPurity[iTrack] == 1) {
        best_track = iTrack;
        max_pt = IsoTrack_pt[iTrack];
      }
    }
    if (best_track != -1) {
      h_data->Fill(IsoTrack_dedxByLayer0[best_track]);
      std::cout << " best dE/dx = " << IsoTrack_dedxByLayer0[best_track] << " [ best_track = " << best_track << " , pt = " << max_pt << "]" << std::endl;
    }
  }
  
  
  TH1F* h_mc = new TH1F ("h_mc", "mc", 100, 0, 20);
  //   for (int iEntry=0; iEntry<inputTree_mc->GetEntries(); iEntry++) {
  for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_mc->GetEntry(iEntry);
    float max_pt = 0;
    int best_track = -1;
    for (int iTrack = 0; iTrack < std::min(kMaxTracks, nIsoTrack); iTrack++) {
      if (IsoTrack_pt[iTrack] > max_pt && IsoTrack_highPurity[iTrack] == 1) {
        best_track = iTrack;
        max_pt = IsoTrack_pt[iTrack];
      }
    }
    if (best_track != -1) h_mc->Fill(IsoTrack_dedxByLayer0[best_track]);
  }  
  
  h_data->Scale(1./h_data->Integral());
  h_mc  ->Scale(1./h_mc  ->Integral());
  
  TLegend* leg = new TLegend(0.20,0.70,0.50,0.90);
  leg->AddEntry(h_data,"data","pl");
  leg->AddEntry(h_mc, "mc","pl");
  
  
  TCanvas* cc = new TCanvas ("cc","",800,600);
  
  h_data->Draw("APL");
  h_mc->Draw("PL");
  
  h_data->GetYaxis()->SetTitle("dE/dx (GeV/cm)");
  
  leg->Draw();
  
  cc->SaveAs("dedx.png");
  cc->SaveAs("dedx.root");
  
  
}
