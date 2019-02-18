

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



void DrawTimeEvolution( std::string BPIXorFPIX = "BPIX", int num_run_intervals = 30, int ilayer = 0, int iEdge = 0, int iladderblade = 0) {
  
  TFile* inputFileHistos = new TFile ("tocalibrate_complete_eta_edges_iladderblade_timeRanges.root", "READ");   
  
  std::cout << " BPIXorFPIX, ilayer, iEdge, iladderblade = " << BPIXorFPIX << "  " << ilayer << "  " << iEdge << "  " << iladderblade << std::endl;
  
  std::vector<TH1F*> v_histo; 
  
  TString name;
  
  
  for (int iRun = 0; iRun<num_run_intervals; iRun++) {

    name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_%s_data", iRun, ilayer, iEdge, iladderblade, BPIXorFPIX.c_str());   
    TH1F* temp = (TH1F*) inputFileHistos->Get(name.Data());
    Normalize(temp);
    setupHisto(temp, iRun, "dE/dx");
    
    //---- rebin the histogram for graphic motivation
    temp->Rebin(5);
   
    //---- draw only one histogram every 3
    if (!(iRun%3))  v_histo.push_back ( temp );

  }
  
 
 
//   h_bkg = ConvertOverflow(h_bkg);
//   h_data = ConvertOverflow(h_data);
//   setupHisto(h_bkg, 10, var);
//   setupHisto(h_data, 0, var);
//   Normalize(h_bkg);
//   Normalize(h_data);
  
 
  TCanvas* cc = new TCanvas ("cc", "", 800, 600);
 
  for (int iRun = 0; iRun<v_histo.size(); iRun++) {
//     if (iRun==0) v_histo.at(iRun) -> Draw("histo");
//     else         v_histo.at(iRun) -> Draw("histo same");

    if (iRun==0) v_histo.at(iRun) -> Draw("");
    else         v_histo.at(iRun) -> Draw("same");
    
  }
  
//   cc->BuildLegend();
  
}