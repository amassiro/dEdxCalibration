
  
  
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
  
  
  //---- muon
  const Int_t kMaxLepGood = 10;
  Float_t LepGood_pt[kMaxLepGood];
  Int_t   LepGood_pdgId[kMaxLepGood];
  Int_t nLepGood;
  
  
  inputTree_data->SetBranchAddress("LepGood_pt",  LepGood_pt);
  inputTree_mc  ->SetBranchAddress("LepGood_pt",  LepGood_pt);
  inputTree_data->SetBranchAddress("LepGood_pdgId",  LepGood_pdgId);
  inputTree_mc  ->SetBranchAddress("LepGood_pdgId",  LepGood_pdgId);
  inputTree_data->SetBranchAddress("nLepGood",    &nLepGood);
  inputTree_mc  ->SetBranchAddress("nLepGood",    &nLepGood);
  
  
  //   IsoTrack_dedxByLayer0
  const Int_t kMaxTracks = 1000;
 
  Float_t IsoTrack_dedxByLayer0[kMaxTracks];
  Float_t IsoTrack_pt[kMaxTracks];
  Int_t IsoTrack_highPurity[kMaxTracks];
  Int_t nIsoTrack;

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer0",  IsoTrack_dedxByLayer0);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer0",  IsoTrack_dedxByLayer0);
  
  inputTree_data->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
  
  inputTree_data->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);
  inputTree_mc  ->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);
  
  inputTree_data->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  inputTree_mc  ->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  
  TH1F* h_data = new TH1F ("h_data", "data", 100, 0, 20);
  TH1F* h_ntracks_data = new TH1F ("h_ntracks_data", "data", 100, 0, 50000);
  TH1F* h_LepGood_pt_data = new TH1F ("h_LepGood_pt_data", "data", 100, 0, 100);
  
  setupHisto(h_data, 1);
  setupHisto(h_ntracks_data, 1);
  setupHisto(h_LepGood_pt_data, 1);
  
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
    
    
    //---- muon
    max_pt = 0;
    for (int iMuon = 0; iMuon < std::min(kMaxLepGood, nLepGood); iMuon++) {
      if (LepGood_pt[iMuon] > max_pt && LepGood_pdgId[iMuon] == 13) {
        max_pt = LepGood_pt[iMuon];
      }
    }
    if (max_pt != 0) h_LepGood_pt_data->Fill(max_pt);
  }
  
  
  
  
  
  
  
  
  
  
  TH1F* h_mc = new TH1F ("h_mc", "mc", 100, 0, 20);
  TH1F* h_ntracks_mc = new TH1F ("h_ntracks_mc", "mc", 100, 0, 50000);
  TH1F* h_LepGood_pt_mc = new TH1F ("h_LepGood_pt_mc", "mc", 100, 0, 100);
  
  setupHisto(h_mc, 3);
  setupHisto(h_ntracks_mc, 3);
  setupHisto(h_LepGood_pt_mc, 3);
  
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
 
    //---- muon
    max_pt = 0;
//     std::cout << " nLepGood = " << nLepGood << std::endl;    
    for (int iMuon = 0; iMuon < std::min(kMaxLepGood, nLepGood); iMuon++) {
//       std::cout << "    >> LepGood_pdgId[" << iMuon << "] = " << LepGood_pdgId[iMuon];
//       std::cout << "    >> LepGood_pt[" << iMuon << "] = " << LepGood_pt[iMuon] << std::endl;
      if (LepGood_pt[iMuon] > max_pt && LepGood_pdgId[iMuon] == 13) {
        max_pt = LepGood_pt[iMuon];
      }
    }
    if (max_pt != 0) h_LepGood_pt_mc->Fill(max_pt);
    
  }  
  
  h_data->Scale(1./h_data->Integral());
  h_mc  ->Scale(1./h_mc  ->Integral());
  
  h_ntracks_data->Scale(1./h_ntracks_data->Integral());
  h_ntracks_mc  ->Scale(1./h_ntracks_mc  ->Integral());
 
  h_LepGood_pt_data->Scale(1./h_LepGood_pt_data->Integral());
  h_LepGood_pt_mc  ->Scale(1./h_LepGood_pt_mc  ->Integral());
  
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


  
  TCanvas* cc_MuonPt = new TCanvas ("cc_MuonPt","",800,600);
  
  h_LepGood_pt_data->Draw("APL");
  h_LepGood_pt_mc->Draw("PL");
  
  h_LepGood_pt_data->GetYaxis()->SetTitle("#mu p_{T}");
  
  leg->Draw();
  
}
