
  
  
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
  for (int i=0; i<30; i++) {
    color[i+10] = kBlue + i;
  }
  
  histo->SetLineColor(color[icolor]);
  histo->SetMarkerColor(color[icolor]);
  histo->SetMarkerSize(1);
  histo->SetMarkerStyle(20+icolor);
}


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
  TH1F* h_ntracks_data = new TH1F ("h_ntracks_data", "data", 100, 0, 50000);

  setupHisto(h_data, 1);
  setupHisto(h_ntracks_data, 1);
  
  //   for (int iEntry=0; iEntry<inputTree_data->GetEntries(); iEntry++) {
  for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_data->GetEntry(iEntry);
    float max_pt = 0;
    int best_track = -1;
    h_ntracks_data->Fill(nIsoTrack);
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
  TH1F* h_ntracks_mc = new TH1F ("h_ntracks_mc", "mc", 100, 0, 50000);
  
  setupHisto(h_mc, 3);
  setupHisto(h_ntracks_mc, 3);
  
  //   for (int iEntry=0; iEntry<inputTree_mc->GetEntries(); iEntry++) {
  for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_mc->GetEntry(iEntry);
    float max_pt = 0;
    int best_track = -1;
    h_ntracks_mc->Fill(nIsoTrack);
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
  
  h_ntracks_data->Scale(1./h_ntracks_data->Integral());
  h_ntracks_mc  ->Scale(1./h_ntracks_mc  ->Integral());
  
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
  
  
  
  TCanvas* cc_ntracks = new TCanvas ("cc_ntracks","",800,600);
  
  h_ntracks_data->Draw("APL");
  h_ntracks_mc->Draw("PL");
  
  h_ntracks_data->GetYaxis()->SetTitle("# tracks");
  
  leg->Draw();
  
}
