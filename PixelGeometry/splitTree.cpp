//
// splitTree
//
//
//   g++ -o splitTree.exe splitTree.cpp `root-config --cflags --glibs`
//
//

#include <iostream>
#include <fstream>

#include "TTree.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TStyle.h"
  


int main(int argc, char** argv) {
  
  std::string name_input_file = "out.root";
  
  if (argc>=2) {
    name_input_file = argv[1];
  }
  
  
  int runNumber = 0;
  if (argc>=3) {
    runNumber = atoi(argv[2]);
  }
  
  std::string name_output_file_before = name_input_file + "_before_" + std::to_string(runNumber) + ".root";
  std::string name_output_file_after  = name_input_file + "_after_"  + std::to_string(runNumber) + ".root";
  
  std::cout << " name_output_file_before = " << name_output_file_before << std::endl;
  std::cout << " name_output_file_after = " << name_output_file_after << std::endl;
  
  
  TFile* inputFile = new TFile (name_input_file.c_str(), "READ");   
  TTree* inputTree = (TTree*) ((TTree*) inputFile -> Get ("tree")) -> Clone ("tree");
  
  std::cout << " entries = " << inputTree->GetEntries() << std::endl;
  
  UInt_t run;
  inputTree->SetBranchAddress("run",    &run);

  
  TFile* outputFile_before = new TFile (name_output_file_before.c_str(), "RECREATE");   
  TTree *outputTree_before = inputTree->CloneTree(0);

  TFile* outputFile_after = new TFile (name_output_file_after.c_str(), "RECREATE");   
  TTree *outputTree_after = inputTree->CloneTree(0);

  
  
  
      
  for (int iEntry=0; iEntry<inputTree->GetEntries(); iEntry++) {
    if (!(iEntry%50000)) std::cout << "   " << iEntry << " ; run = "  << run << std::endl;
    inputTree->GetEntry(iEntry);
     
    if (run < runNumber) {
      outputTree_before->Fill();
    }
    else {
      outputTree_after->Fill();      
    }
    
  }
  
  std::cout << " before entries = " << outputTree_before->GetEntries() << " out of: " << inputTree->GetEntries() << std::endl;
  std::cout << " after entries = " << outputTree_after->GetEntries() << " out of: " << inputTree->GetEntries() << std::endl;
  
  outputTree_before->AutoSave();
  outputTree_after->AutoSave();
  
  outputFile_before->Close();
  outputFile_after->Close();
  
}






