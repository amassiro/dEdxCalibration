

TH1F * ConvertOverflow(TH1F *h) {
  // This function paint the histogram h with an extra bin for overflows
  UInt_t nx = h->GetNbinsX()+1;
  Double_t *xbins= new Double_t[nx+1];
  for (UInt_t i=0;i<nx;i++)
    xbins[i]=h->GetBinLowEdge(i+1);
  xbins[nx]=xbins[nx-1]+h->GetBinWidth(nx);
  char *tempName= new char[strlen(h->GetName())+10];
  sprintf(tempName,"%swtOverFlow",h->GetName());
  // Book a temporary histogram having ab extra bin for overflows
  TH1F *htmp = new TH1F(tempName, h->GetTitle(), nx, xbins);
  //---- style
  htmp->SetLineColor(h->GetLineColor());
  htmp->SetLineWidth(h->GetLineWidth());
  htmp->SetLineStyle(h->GetLineStyle());
  // Reset the axis labels
  htmp->SetXTitle(h->GetXaxis()->GetTitle());
  htmp->SetYTitle(h->GetYaxis()->GetTitle());
  // Fill the new hitogram including the extra bin for overflows
  for (UInt_t i=1; i<=nx; i++)
    htmp->SetBinContent(i, h->GetBinContent(i));
  // Fill the underflows
  htmp->SetBinContent(0, h->GetBinContent(0));
  // Restore the number of entries
  htmp->SetEntries(h->GetEntries());
  // FillStyle and color
  htmp->SetFillStyle(h->GetFillStyle());
  htmp->SetFillColor(h->GetFillColor());
  return htmp;
}




void setupHisto(TH1F* histo, int icolor, std::string var) {
  
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
  
  
  histo->SetLineWidth(2);
  histo->SetLineColor(color[icolor]);
  histo->SetMarkerColor(color[icolor]);
  histo->SetMarkerSize(1);
  histo->SetMarkerStyle(20+icolor);
  
  histo->GetXaxis()->SetTitle(var.c_str());
  
}


void Normalize(TH1F* histo) {

  float integral = histo->Integral();
  if (integral != 0) {
    histo->Scale(1./integral);
  }
  
}
  


void DrawTracker( std::string var = "ciao", int NBIN = 1000, float MIN = 0, float MAX = 1000, std::string cut = "1") {
  
 
  TFile* inputFile_bkg = new TFile ("Data/../calibration/11Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root", "READ");   
  TTree* inputTree_bkg = (TTree*) ((TTree*) inputFile_bkg -> Get ("tree")) -> Clone ("flatTree_bkg");
  
  TFile* inputFile_data = new TFile ("tree_filtered_data_SingleMuon_Run2017E_31Mar2018.root", "READ");   
  TTree* inputTree_data = (TTree*) ((TTree*) inputFile_data -> Get ("tree")) -> Clone ("flatTree_data");
 
  
  TString name;
  TString toDraw;
  TString weight;

  weight = Form ("%s", cut.c_str());
  
  TH1F* h_bkg = new TH1F("h_bkg","DY",NBIN,MIN,MAX);
  
  TH1F* h_data = new TH1F("h_data","data",NBIN,MIN,MAX);
  
  toDraw = Form ("%s >> h_bkg",var.c_str());
  inputTree_bkg->Draw(toDraw.Data(),weight.Data(),"goff");
  
  toDraw = Form ("%s >> h_data",var.c_str());
  inputTree_data->Draw(toDraw.Data(),weight.Data(),"goff");
  
    
  
  h_bkg = ConvertOverflow(h_bkg);
  h_data = ConvertOverflow(h_data);
  
  setupHisto(h_bkg, 10, var);
  setupHisto(h_data, 0, var);
  
  Normalize(h_bkg);
  Normalize(h_data);
  
  
  TCanvas* cc = new TCanvas ("cc", "", 800, 600);
  h_bkg->Draw("");
  h_data->Draw("same");
  
  cc->BuildLegend();
  
  
}