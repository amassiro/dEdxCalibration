
  
  
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
  Float_t LepGood_eta[kMaxLepGood];
  Float_t LepGood_phi[kMaxLepGood];
  Int_t LepGood_tightId[kMaxLepGood];
  Int_t   LepGood_pdgId[kMaxLepGood];
  Int_t nLepGood;
  
  
  inputTree_data->SetBranchAddress("LepGood_pt",  LepGood_pt);
  inputTree_mc  ->SetBranchAddress("LepGood_pt",  LepGood_pt);
  inputTree_data->SetBranchAddress("LepGood_eta",  LepGood_eta);
  inputTree_mc  ->SetBranchAddress("LepGood_eta",  LepGood_eta);
  inputTree_data->SetBranchAddress("LepGood_phi",  LepGood_phi);
  inputTree_mc  ->SetBranchAddress("LepGood_phi",  LepGood_phi);
  inputTree_data->SetBranchAddress("LepGood_tightId",  LepGood_tightId);
  inputTree_mc  ->SetBranchAddress("LepGood_tightId",  LepGood_tightId);
  inputTree_data->SetBranchAddress("LepGood_pdgId",  LepGood_pdgId);
  inputTree_mc  ->SetBranchAddress("LepGood_pdgId",  LepGood_pdgId);
  inputTree_data->SetBranchAddress("nLepGood",    &nLepGood);
  inputTree_mc  ->SetBranchAddress("nLepGood",    &nLepGood);
  
//   
//   30 < pT < 50 GeV ; |η| < 2.4 
//   Passes tight ID selection ; rel. iso (Δβ corrected) < 0.15
//   
  
  
  //   IsoTrack_dedxByLayer0
  const Int_t kMaxTracks = 1000;
 
  Float_t IsoTrack_dedxByLayer0[kMaxTracks];
  Float_t IsoTrack_dedxByLayer1[kMaxTracks];
  Float_t IsoTrack_dedxByLayer2[kMaxTracks];
  Float_t IsoTrack_dedxByLayer3[kMaxTracks];
  Float_t IsoTrack_dedxByLayer4[kMaxTracks];
  Float_t IsoTrack_dedxByLayer5[kMaxTracks];
  Float_t IsoTrack_dedxByLayer6[kMaxTracks];
  Float_t IsoTrack_dedxByLayer7[kMaxTracks];
  Float_t IsoTrack_dedxByLayer8[kMaxTracks];
  Float_t IsoTrack_dedxByLayer9[kMaxTracks];
  Float_t IsoTrack_dedxByLayer10[kMaxTracks];
  Float_t IsoTrack_dedxByLayer11[kMaxTracks];
  Float_t IsoTrack_dedxByLayer12[kMaxTracks];
  Float_t IsoTrack_dedxByLayer13[kMaxTracks];
  
  Float_t IsoTrack_pt[kMaxTracks];
  Float_t IsoTrack_eta[kMaxTracks];
  Float_t IsoTrack_phi[kMaxTracks];
  Float_t IsoTrack_dxy[kMaxTracks];
  Float_t IsoTrack_dz[kMaxTracks];
  Int_t IsoTrack_highPurity[kMaxTracks];
  Int_t nIsoTrack;

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer0",  IsoTrack_dedxByLayer0);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer0",  IsoTrack_dedxByLayer0);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer1",  IsoTrack_dedxByLayer1);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer1",  IsoTrack_dedxByLayer1);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer2",  IsoTrack_dedxByLayer2);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer2",  IsoTrack_dedxByLayer2);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer3",  IsoTrack_dedxByLayer3);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer3",  IsoTrack_dedxByLayer3);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer4",  IsoTrack_dedxByLayer4);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer4",  IsoTrack_dedxByLayer4);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer5",  IsoTrack_dedxByLayer5);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer5",  IsoTrack_dedxByLayer5);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer6",  IsoTrack_dedxByLayer6);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer6",  IsoTrack_dedxByLayer6);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer7",  IsoTrack_dedxByLayer7);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer7",  IsoTrack_dedxByLayer7);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer8",  IsoTrack_dedxByLayer8);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer8",  IsoTrack_dedxByLayer8);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer9",  IsoTrack_dedxByLayer9);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer9",  IsoTrack_dedxByLayer9);

  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer10",  IsoTrack_dedxByLayer10);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer10",  IsoTrack_dedxByLayer10);
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer11",  IsoTrack_dedxByLayer11);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer11",  IsoTrack_dedxByLayer11);
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer12",  IsoTrack_dedxByLayer12);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer12",  IsoTrack_dedxByLayer12);
  
  inputTree_data->SetBranchAddress("IsoTrack_dedxByLayer13",  IsoTrack_dedxByLayer13);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dedxByLayer13",  IsoTrack_dedxByLayer13);
  
  
  inputTree_data->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
  inputTree_mc  ->SetBranchAddress("IsoTrack_pt",  IsoTrack_pt);
 
  inputTree_data->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  inputTree_mc  ->SetBranchAddress("IsoTrack_eta",  IsoTrack_eta);
  
  inputTree_data->SetBranchAddress("IsoTrack_phi",  IsoTrack_phi);
  inputTree_mc  ->SetBranchAddress("IsoTrack_phi",  IsoTrack_phi);
  
  inputTree_data->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);
  inputTree_mc  ->SetBranchAddress("IsoTrack_highPurity",  IsoTrack_highPurity);

  inputTree_data->SetBranchAddress("IsoTrack_dxy",  IsoTrack_dxy);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dxy",  IsoTrack_dxy);

  inputTree_data->SetBranchAddress("IsoTrack_dz",  IsoTrack_dz);
  inputTree_mc  ->SetBranchAddress("IsoTrack_dz",  IsoTrack_dz);
  
  inputTree_data->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  inputTree_mc  ->SetBranchAddress("nIsoTrack",  &nIsoTrack);
  
//   
//   p T > 50 GeV ; |η| < 2.4 ; High purity track
//   |d xy | < 0.02 ; |d z | < 0.5
//   miniPFIsolation().chargedHadronIso() / p T < 1.0
//   EM energy around the track < 10 GeV ; Had energy around the track < 10 GeV
//   Mass(μ, track) between 86 and 106 GeV
//   
  
  
  TH1F* h_dedxByLayer0_data  = new TH1F ("h_dedxByLayer0_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer1_data  = new TH1F ("h_dedxByLayer1_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer2_data  = new TH1F ("h_dedxByLayer2_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer3_data  = new TH1F ("h_dedxByLayer3_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer4_data  = new TH1F ("h_dedxByLayer4_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer5_data  = new TH1F ("h_dedxByLayer5_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer6_data  = new TH1F ("h_dedxByLayer6_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer7_data  = new TH1F ("h_dedxByLayer7_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer8_data  = new TH1F ("h_dedxByLayer8_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer9_data  = new TH1F ("h_dedxByLayer9_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer10_data = new TH1F ("h_dedxByLayer10_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer11_data = new TH1F ("h_dedxByLayer11_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer12_data = new TH1F ("h_dedxByLayer12_data", "data", 100, 0, 10);
  TH1F* h_dedxByLayer13_data = new TH1F ("h_dedxByLayer13_data", "data", 100, 0, 10);

  TH1F* h_ntracks_data = new TH1F ("h_ntracks_data", "data", 100, 0, 100);
  TH1F* h_LepGood_pt_data = new TH1F ("h_LepGood_pt_data", "data", 100, 0, 100);
  TH1F* h_mass_data = new TH1F ("h_mass_data", "data", 100, 86, 106);
  
  setupHisto(h_dedxByLayer0_data , 10);
  setupHisto(h_dedxByLayer1_data , 10);
  setupHisto(h_dedxByLayer2_data , 10);
  setupHisto(h_dedxByLayer3_data , 10);
  setupHisto(h_dedxByLayer4_data , 10);
  setupHisto(h_dedxByLayer5_data , 10);
  setupHisto(h_dedxByLayer6_data , 10);
  setupHisto(h_dedxByLayer7_data , 10);
  setupHisto(h_dedxByLayer8_data , 10);
  setupHisto(h_dedxByLayer9_data , 10);
  setupHisto(h_dedxByLayer10_data, 10);
  setupHisto(h_dedxByLayer11_data, 10);
  setupHisto(h_dedxByLayer12_data, 10);
  setupHisto(h_dedxByLayer13_data, 10);  
  
  setupHisto(h_ntracks_data, 10);
  setupHisto(h_LepGood_pt_data, 10);
  setupHisto(h_mass_data, 10);
  
  for (int iEntry=0; iEntry<inputTree_data->GetEntries(); iEntry++) {
//   for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_data->GetEntry(iEntry);
    
    float max_pt = 0;
    int best_iMuon = -1;
    //---- muon
    for (int iMuon = 0; iMuon < std::min(kMaxLepGood, nLepGood); iMuon++) {
      if (LepGood_pdgId[iMuon] == 13 && LepGood_tightId[iMuon] == 1 && LepGood_pt[iMuon] > max_pt && fabs(LepGood_eta[iMuon])<2.4) {
        max_pt = LepGood_pt[iMuon];
        best_iMuon = iMuon;
      }
    }
    if (max_pt != 0) h_LepGood_pt_data->Fill(max_pt);
    
    if (best_iMuon != -1) {
      TLorentzVector muon;
      muon.SetPtEtaPhiM(LepGood_pt[best_iMuon], LepGood_eta[best_iMuon], LepGood_phi[best_iMuon], 0);
       
      //---- tracks
      max_pt = 0;   
      int best_track = -1;
      h_ntracks_data->Fill(nIsoTrack);
      for (int iTrack = 0; iTrack < std::min(kMaxTracks, nIsoTrack); iTrack++) {
        if (
          IsoTrack_pt[iTrack] > max_pt &&
          IsoTrack_highPurity[iTrack] == 1 && 
          fabs(IsoTrack_dxy[iTrack]) < 0.02 &&
          fabs(IsoTrack_dz[iTrack]) < 0.5
        ) {
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[iTrack], IsoTrack_eta[iTrack], IsoTrack_phi[iTrack], 0);
          
          float mass_mu_track = (track+muon).M();
          
          if (mass_mu_track > 86 && mass_mu_track < 106) {
            best_track = iTrack;
            max_pt = IsoTrack_pt[iTrack];
          }
        }
      }
      if (best_track != -1) {
    
        h_dedxByLayer0_data ->Fill(IsoTrack_dedxByLayer0 [best_track]);
        h_dedxByLayer1_data ->Fill(IsoTrack_dedxByLayer1 [best_track]);
        h_dedxByLayer2_data ->Fill(IsoTrack_dedxByLayer2 [best_track]);
        h_dedxByLayer3_data ->Fill(IsoTrack_dedxByLayer3 [best_track]);
        h_dedxByLayer4_data ->Fill(IsoTrack_dedxByLayer4 [best_track]);
        h_dedxByLayer5_data ->Fill(IsoTrack_dedxByLayer5 [best_track]);
        h_dedxByLayer6_data ->Fill(IsoTrack_dedxByLayer6 [best_track]);
        h_dedxByLayer7_data ->Fill(IsoTrack_dedxByLayer7 [best_track]);
        h_dedxByLayer8_data ->Fill(IsoTrack_dedxByLayer8 [best_track]);
        h_dedxByLayer9_data ->Fill(IsoTrack_dedxByLayer9 [best_track]);
        h_dedxByLayer10_data->Fill(IsoTrack_dedxByLayer10[best_track]);
        h_dedxByLayer11_data->Fill(IsoTrack_dedxByLayer11[best_track]);
        h_dedxByLayer12_data->Fill(IsoTrack_dedxByLayer12[best_track]);
        h_dedxByLayer13_data->Fill(IsoTrack_dedxByLayer13[best_track]);
        
        //       std::cout << " best dE/dx = " << IsoTrack_dedxByLayer0[best_track] << " [ best_track = " << best_track << " , pt = " << max_pt << "]" << std::endl;
        
        TLorentzVector track;
        track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);
        h_mass_data -> Fill((track+muon).M());
        
      }
      
      
    }
    
  }
  
  
  
  
  
  
  
  
  
  TH1F* h_dedxByLayer0_mc = new TH1F ("h_dedxByLayer0_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer1_mc = new TH1F ("h_dedxByLayer1_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer2_mc = new TH1F ("h_dedxByLayer2_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer3_mc = new TH1F ("h_dedxByLayer3_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer4_mc = new TH1F ("h_dedxByLayer4_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer5_mc = new TH1F ("h_dedxByLayer5_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer6_mc = new TH1F ("h_dedxByLayer6_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer7_mc = new TH1F ("h_dedxByLayer7_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer8_mc = new TH1F ("h_dedxByLayer8_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer9_mc = new TH1F ("h_dedxByLayer9_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer10_mc = new TH1F ("h_dedxByLayer10_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer11_mc = new TH1F ("h_dedxByLayer11_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer12_mc = new TH1F ("h_dedxByLayer12_mc", "mc", 100, 0, 10);
  TH1F* h_dedxByLayer13_mc = new TH1F ("h_dedxByLayer13_mc", "mc", 100, 0, 10);

  TH1F* h_ntracks_mc = new TH1F ("h_ntracks_mc", "mc", 100, 0, 100);
  TH1F* h_LepGood_pt_mc = new TH1F ("h_LepGood_pt_mc", "mc", 100, 0, 100);
  TH1F* h_mass_mc = new TH1F ("h_mass_mc", "mc", 100, 86, 106);
  
  setupHisto(h_dedxByLayer0_mc , 11);
  setupHisto(h_dedxByLayer1_mc , 11);
  setupHisto(h_dedxByLayer2_mc , 11);
  setupHisto(h_dedxByLayer3_mc , 11);
  setupHisto(h_dedxByLayer4_mc , 11);
  setupHisto(h_dedxByLayer5_mc , 11);
  setupHisto(h_dedxByLayer6_mc , 11);
  setupHisto(h_dedxByLayer7_mc , 11);
  setupHisto(h_dedxByLayer8_mc , 11);
  setupHisto(h_dedxByLayer9_mc , 11);
  setupHisto(h_dedxByLayer10_mc, 11);
  setupHisto(h_dedxByLayer11_mc, 11);
  setupHisto(h_dedxByLayer12_mc, 11);
  setupHisto(h_dedxByLayer13_mc, 11);  

  setupHisto(h_ntracks_mc, 11);
  setupHisto(h_LepGood_pt_mc, 11);
  setupHisto(h_mass_mc, 11);
  
  for (int iEntry=0; iEntry<inputTree_mc->GetEntries(); iEntry++) {
//   for (int iEntry=0; iEntry<5000; iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; nIsoTrack = "  << nIsoTrack << std::endl;
    inputTree_mc->GetEntry(iEntry);
    
    float max_pt = 0;
    int best_iMuon = -1;
    //---- muon
    for (int iMuon = 0; iMuon < std::min(kMaxLepGood, nLepGood); iMuon++) {
      if (LepGood_pdgId[iMuon] == 13 && LepGood_tightId[iMuon] == 1 && LepGood_pt[iMuon] > max_pt && fabs(LepGood_eta[iMuon])<2.4) {
        max_pt = LepGood_pt[iMuon];
        best_iMuon = iMuon;
      }
    }
    if (max_pt != 0) h_LepGood_pt_mc->Fill(max_pt);
    
    if (best_iMuon != -1) {
      TLorentzVector muon;
      muon.SetPtEtaPhiM(LepGood_pt[best_iMuon], LepGood_eta[best_iMuon], LepGood_phi[best_iMuon], 0);
      
      //---- tracks
      max_pt = 0;   
      int best_track = -1;
      h_ntracks_mc->Fill(nIsoTrack);
      for (int iTrack = 0; iTrack < std::min(kMaxTracks, nIsoTrack); iTrack++) {
        if (
          IsoTrack_pt[iTrack] > max_pt &&
          IsoTrack_highPurity[iTrack] == 1 && 
          fabs(IsoTrack_dxy[iTrack]) < 0.02 &&
          fabs(IsoTrack_dz[iTrack]) < 0.5
        ) {
          
          TLorentzVector track;
          track.SetPtEtaPhiM(IsoTrack_pt[iTrack], IsoTrack_eta[iTrack], IsoTrack_phi[iTrack], 0);
          
          float mass_mu_track = (track+muon).M();
          
          if (mass_mu_track > 86 && mass_mu_track < 106) {
            best_track = iTrack;
            max_pt = IsoTrack_pt[iTrack];
          }
        }
      }
      if (best_track != -1) {
        
        h_dedxByLayer0_mc ->Fill(IsoTrack_dedxByLayer0 [best_track]);
        h_dedxByLayer1_mc ->Fill(IsoTrack_dedxByLayer1 [best_track]);
        h_dedxByLayer2_mc ->Fill(IsoTrack_dedxByLayer2 [best_track]);
        h_dedxByLayer3_mc ->Fill(IsoTrack_dedxByLayer3 [best_track]);
        h_dedxByLayer4_mc ->Fill(IsoTrack_dedxByLayer4 [best_track]);
        h_dedxByLayer5_mc ->Fill(IsoTrack_dedxByLayer5 [best_track]);
        h_dedxByLayer6_mc ->Fill(IsoTrack_dedxByLayer6 [best_track]);
        h_dedxByLayer7_mc ->Fill(IsoTrack_dedxByLayer7 [best_track]);
        h_dedxByLayer8_mc ->Fill(IsoTrack_dedxByLayer8 [best_track]);
        h_dedxByLayer9_mc ->Fill(IsoTrack_dedxByLayer9 [best_track]);
        h_dedxByLayer10_mc->Fill(IsoTrack_dedxByLayer10[best_track]);
        h_dedxByLayer11_mc->Fill(IsoTrack_dedxByLayer11[best_track]);
        h_dedxByLayer12_mc->Fill(IsoTrack_dedxByLayer12[best_track]);
        h_dedxByLayer13_mc->Fill(IsoTrack_dedxByLayer13[best_track]);
        
        //       std::cout << " best dE/dx = " << IsoTrack_dedxByLayer0[best_track] << " [ best_track = " << best_track << " , pt = " << max_pt << "]" << std::endl;
        TLorentzVector track;
        track.SetPtEtaPhiM(IsoTrack_pt[best_track], IsoTrack_eta[best_track], IsoTrack_phi[best_track], 0);
        h_mass_mc -> Fill((track+muon).M());
      }
      
      
    }
    
  }
  
  
  
  
  
  
  
  
  
  
  
  
  h_dedxByLayer0_data->Scale(1./h_dedxByLayer0_data->Integral());
  h_dedxByLayer0_mc  ->Scale(1./h_dedxByLayer0_mc  ->Integral());
  
  h_ntracks_data->Scale(1./h_ntracks_data->Integral());
  h_ntracks_mc  ->Scale(1./h_ntracks_mc  ->Integral());
  
  h_LepGood_pt_data->Scale(1./h_LepGood_pt_data->Integral());
  h_LepGood_pt_mc  ->Scale(1./h_LepGood_pt_mc  ->Integral());
  
  h_mass_data->Scale(1./h_mass_data->Integral());
  h_mass_mc  ->Scale(1./h_mass_mc  ->Integral());
  
  
  
  
  
  TLegend* leg = new TLegend(0.70,0.70,0.90,0.90);
  leg->AddEntry(h_dedxByLayer0_data,"data","pl");
  leg->AddEntry(h_dedxByLayer0_mc, "mc","pl");
  
  
  TCanvas* cc = new TCanvas ("cc","",800,600);
  
  h_dedxByLayer0_data->Draw("PL");
  h_dedxByLayer0_mc->Draw("PL same");
  
  h_dedxByLayer0_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  
  leg->Draw();
  
  cc->SaveAs("dedx.png");
  cc->SaveAs("dedx.root");
  
  
  
  TCanvas* cc_ntracks = new TCanvas ("cc_ntracks","",800,600);
  
  h_ntracks_data->Draw("PL");
  h_ntracks_mc->Draw("PL same");
  
  h_ntracks_data->GetXaxis()->SetTitle("# tracks");
  
  leg->Draw();


  
  TCanvas* cc_MuonPt = new TCanvas ("cc_MuonPt","",800,600);
  
  h_LepGood_pt_data->Draw("PL");
  h_LepGood_pt_mc->Draw("PL same");
  
  h_LepGood_pt_data->GetXaxis()->SetTitle("#mu p_{T}");
  
  leg->Draw();

  
  
  

  TCanvas* cc_mass = new TCanvas ("cc_mass","",800,600);
  
  h_mass_data->Draw("PL");
  h_mass_mc  ->Draw("PL same");
  
  h_mass_data->GetXaxis()->SetTitle("Mass [GeV]");
  
  leg->Draw();
  
  
  
  
  
  TCanvas* cc_summary = new TCanvas ("cc_summary","",1000,1000);
  
  cc_summary->Divide(4,4);
  
  cc_summary->cd(1);
  h_dedxByLayer0_data->Draw("PL");
  h_dedxByLayer0_mc->Draw("PL same");
  h_dedxByLayer0_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(2);
  h_dedxByLayer1_data->Draw("PL");
  h_dedxByLayer1_mc->Draw("PL same");
  h_dedxByLayer1_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(3);
  h_dedxByLayer2_data->Draw("PL");
  h_dedxByLayer2_mc->Draw("PL same");
  h_dedxByLayer2_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(4);
  h_dedxByLayer3_data->Draw("PL");
  h_dedxByLayer3_mc->Draw("PL same");
  h_dedxByLayer3_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(5);
  h_dedxByLayer4_data->Draw("PL");
  h_dedxByLayer4_mc->Draw("PL same");
  h_dedxByLayer4_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(6);
  h_dedxByLayer5_data->Draw("PL");
  h_dedxByLayer5_mc->Draw("PL same");
  h_dedxByLayer5_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(7);
  h_dedxByLayer6_data->Draw("PL");
  h_dedxByLayer6_mc->Draw("PL same");
  h_dedxByLayer6_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(8);
  h_dedxByLayer7_data->Draw("PL");
  h_dedxByLayer7_mc->Draw("PL same");
  h_dedxByLayer7_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(9);
  h_dedxByLayer8_data->Draw("PL");
  h_dedxByLayer8_mc->Draw("PL same");
  h_dedxByLayer8_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(10);
  h_dedxByLayer9_data->Draw("PL");
  h_dedxByLayer9_mc->Draw("PL same");
  h_dedxByLayer9_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(11);
  h_dedxByLayer10_data->Draw("PL");
  h_dedxByLayer10_mc->Draw("PL same");
  h_dedxByLayer10_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(12);
  h_dedxByLayer11_data->Draw("PL");
  h_dedxByLayer11_mc->Draw("PL same");
  h_dedxByLayer11_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(13);
  h_dedxByLayer12_data->Draw("PL");
  h_dedxByLayer12_mc->Draw("PL same");
  h_dedxByLayer12_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  cc_summary->cd(14);
  h_dedxByLayer13_data->Draw("PL");
  h_dedxByLayer13_mc->Draw("PL same");
  h_dedxByLayer13_data->GetXaxis()->SetTitle("dE/dx (GeV/cm)");
  leg->Draw();
  
  

  
  
  
  
}




