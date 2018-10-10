

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
  



void Draw( std::string var = "ciao", int NBIN = 1000, float MIN = 0, float MAX = 1000, std::string cut = "1") {
  
 
  TFile* inputFile_bkg = new TFile ("Data/flat_tree_Z.root", "READ");   
  TTree* inputTree_bkg = (TTree*) ((TTree*) inputFile_bkg -> Get ("flatTree")) -> Clone ("flatTree_bkg");
  
  TFile* inputFile_sig1 = new TFile ("Data/MoreData/Wino_M_1000_cTau_10/treeProducerXtracks/flat_tree.root", "READ");   
  TTree* inputTree_sig1 = (TTree*) ((TTree*) inputFile_sig1 -> Get ("flatTree")) -> Clone ("flatTree_sig1");
 
  TFile* inputFile_sig2 = new TFile ("Data/MoreData/Wino_M_1000_cTau_20/treeProducerXtracks/flat_tree.root", "READ");   
  TTree* inputTree_sig2 = (TTree*) ((TTree*) inputFile_sig2 -> Get ("flatTree")) -> Clone ("flatTree_sig2");

  TFile* inputFile_sig3 = new TFile ("Data/MoreData/Wino_M_300_cTau_10/treeProducerXtracks/flat_tree.root", "READ");   
  TTree* inputTree_sig3 = (TTree*) ((TTree*) inputFile_sig3 -> Get ("flatTree")) -> Clone ("flatTree_sig3");
  
  TFile* inputFile_sig4 = new TFile ("Data/MoreData/Wino_M_300_cTau_30/treeProducerXtracks/flat_tree.root", "READ");   
  TTree* inputTree_sig4 = (TTree*) ((TTree*) inputFile_sig4 -> Get ("flatTree")) -> Clone ("flatTree_sig4");
  
  
  
  TString name;
  TString toDraw;
  TString weight;

  weight = Form ("%s", cut.c_str());
  
  TH1F* h_bkg = new TH1F("h_bkg","DY",NBIN,MIN,MAX);
  
  TH1F* h_sig1 = new TH1F("h_sig1","m=1000 c#tau=10",NBIN,MIN,MAX);
  TH1F* h_sig2 = new TH1F("h_sig2","m=1000 c#tau=20",NBIN,MIN,MAX);
  TH1F* h_sig3 = new TH1F("h_sig3","m= 300 c#tau=10",NBIN,MIN,MAX);
  TH1F* h_sig4 = new TH1F("h_sig4","m= 300 c#tau=30",NBIN,MIN,MAX);
  
  toDraw = Form ("%s >> h_bkg",var.c_str());
  inputTree_bkg->Draw(toDraw.Data(),weight.Data(),"goff");
  
  toDraw = Form ("%s >> h_sig1",var.c_str());
  inputTree_sig1->Draw(toDraw.Data(),weight.Data(),"goff");
  
  toDraw = Form ("%s >> h_sig2",var.c_str());
  inputTree_sig2->Draw(toDraw.Data(),weight.Data(),"goff");

  toDraw = Form ("%s >> h_sig3",var.c_str());
  inputTree_sig3->Draw(toDraw.Data(),weight.Data(),"goff");

  toDraw = Form ("%s >> h_sig4",var.c_str());
  inputTree_sig4->Draw(toDraw.Data(),weight.Data(),"goff");
  
  
  
  h_bkg = ConvertOverflow(h_bkg);
  h_sig1 = ConvertOverflow(h_sig1);
  h_sig2 = ConvertOverflow(h_sig2);
  h_sig3 = ConvertOverflow(h_sig3);
  h_sig4 = ConvertOverflow(h_sig4);
  
  setupHisto(h_bkg, 10, var);
  setupHisto(h_sig1, 0, var);
  setupHisto(h_sig2, 1, var);
  setupHisto(h_sig3, 3, var);
  setupHisto(h_sig4, 4, var);
  
  Normalize(h_bkg);
  Normalize(h_sig1);
  Normalize(h_sig2);
  Normalize(h_sig3);
  Normalize(h_sig4);
  
  
  
  TCanvas* cc = new TCanvas ("cc", "", 800, 600);
  h_bkg->Draw("");
  h_sig1->Draw("same");
  h_sig2->Draw("same");
  h_sig3->Draw("same");
  h_sig4->Draw("same");
  
  cc->BuildLegend();
  
  
}