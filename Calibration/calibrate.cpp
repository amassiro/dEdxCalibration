
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




int main(int argc, char** argv) {
  
  std::ofstream myfile_BPIX;
  myfile_BPIX.open ("scale_BPIX_pixels_run_ranges.txt");
  std::ofstream myfile_FPIX;
  myfile_FPIX.open ("scale_FPIX_pixels_run_ranges.txt");
  
  
  std::ofstream myfile_RMS_BPIX;
  myfile_RMS_BPIX.open ("smear_BPIX_pixels_run_ranges.txt");
  std::ofstream myfile_RMS_FPIX;
  myfile_RMS_FPIX.open ("smear_FPIX_pixels_run_ranges.txt");


  
  std::string name_input_file_data = "out.root"; 
  if (argc>=2) {
    name_input_file_data = argv[1];
  }
  
  TFile* inputFile_data = new TFile (name_input_file_data.c_str(), "READ");   
  
  TList* list = inputFile_data->GetListOfKeys() ;
  TIter next(list) ;
  TKey* key ;
  TObject* obj ;
  
  while ( key = (TKey*) next() ) {
    obj = key->ReadObj() ;
    if (strcmp(obj->IsA()->GetName(),"TH1")!=0) {
      // std::cout << " found: " << obj->GetName() << " ---> " << obj->GetTitle() << std::endl;
      //       "mc" or "data"
      
      if (std::string(obj->GetTitle()) == "mc") {
        
        //---- get the "coordinates"
        
        int iRun;
        int num_layerId;
        int iEdge;
        int num_ladderbladeId;
        
//         name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, layerId.at(layerId), iEdge, ladderbladeId.at(iladderblade))
//         name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, num_layerId        , iEdge, num_ladderbladeId             )
        
        std::string name = obj->GetName();
        
        std::cout << " name = " << name << std::endl;
        std::size_t found_iRun = name.find("h_iRun_");
        int position_end_iRun;
        if (found_iRun!=std::string::npos) {
//           std::cout << "   > found_iRun = " << found_iRun << std::endl;
          position_end_iRun = name.find("__");
//           std::cout << "         >> " << name.substr(found_iRun + 7, position_end_iRun - found_iRun - 7) << std::endl;
          iRun = std::stoi( name.substr(found_iRun + 7, position_end_iRun - found_iRun - 7) );  // 7 is the length of "h_iRun_"
//           std::cout << "           -> iRun = " << iRun << std::endl;
        }
        else {
          //---- if not a "good" histogram
          continue;
        }
        
        std::size_t found_num_layerId = name.find("ilayer_");
        int position_end_num_layerId;
        if (found_num_layerId!=std::string::npos) {
//           std::cout << "   > found_num_layerId = " << found_num_layerId << std::endl;
          position_end_num_layerId = name.find("__", position_end_iRun + 2);
          num_layerId = std::stoi( name.substr(found_num_layerId + 7, position_end_num_layerId - found_num_layerId - 7) );  // 7 is the length of "ilayer_"
//           std::cout << "           -> num_layerId = " << num_layerId << std::endl;
        }
        
        std::size_t found_iEdge = name.find("iEdge_");
        int position_end_iEdge;
        if (found_iEdge!=std::string::npos) {
//           std::cout << "   > found_iEdge = " << found_iEdge << std::endl;
          position_end_iEdge = name.find("__", position_end_num_layerId + 2);
          iEdge = std::stoi( name.substr(found_iEdge + 6, position_end_iEdge - found_iEdge - 6) );  // 6 is the length of "iEdge_"
//           std::cout << "           -> iEdge = " << iEdge << std::endl;
        }
        
        std::size_t found_num_ladderbladeId = name.find("ladderblade_");
        int position_end_num_ladderbladeId;
        if (found_num_ladderbladeId!=std::string::npos) {
//           std::cout << "   > found_num_ladderbladeId = " << found_num_ladderbladeId << std::endl;
          position_end_num_ladderbladeId = name.find("__", position_end_iEdge + 2);
          num_ladderbladeId = std::stoi( name.substr(found_num_ladderbladeId + 12, position_end_num_ladderbladeId - found_num_ladderbladeId - 12) );  // 12 is the length of "ladderblade_"
//           std::cout << "           -> num_ladderbladeId = " << num_ladderbladeId << std::endl;
        }
        
        
        std::cout << " :: " << iRun << " - " << num_layerId << " - " << iEdge << " - " << num_ladderbladeId << std::endl;

        
        //----
        //---- now get the values
        //----
        
        float mean_mc   = ((TH1F*) obj ) -> GetMean();
        float rms_mc   = ((TH1F*) obj )  -> GetRMS();
        
        std::size_t found_BPIX = name.find("_BPIX_");
        std::string isBPIX = "BPIX";
        if (found_BPIX!=std::string::npos) {
          isBPIX = "BPIX";
        }
        else {
          isBPIX = "FPIX";          
        }
        
        TString name_data = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_%s_data", iRun, num_layerId, iEdge, num_ladderbladeId, isBPIX.c_str());
        float mean_data = ((TH1F*) inputFile_data->Get(name_data.Data()) ) -> GetMean();
        
        std::cout << " data : mc = " << mean_data << " ; " << mean_mc << std::endl;
        
        if (mean_data != 0) {
          if (found_BPIX!=std::string::npos) {
            myfile_BPIX << " " << iEdge << " " << num_layerId << " " << num_ladderbladeId << "     "  << iRun << "     " ;
            myfile_BPIX << "          " << mean_mc / mean_data << "        " << mean_data << "        " << mean_mc;
            myfile_BPIX << std::endl;
          }
          else {
            myfile_FPIX << " " << iEdge << " " << num_layerId << " " << num_ladderbladeId << "     "  << iRun << "     " ;
            myfile_FPIX << "          " << mean_mc / mean_data << "        " << mean_data << "        " << mean_mc;
            myfile_FPIX << std::endl;
          }
        }
        
        
        //---- rms for smearing
        float rms_data = ((TH1F*) inputFile_data->Get(name_data.Data()) ) -> GetRMS();
        
        if (rms_data != 0) {
          if ( fabs(rms_mc / rms_data -1) > 0.05) { //---- only if smearing is > 5%
            if (found_BPIX!=std::string::npos) {
              myfile_RMS_BPIX << " " << iEdge << " " << num_layerId << " " << num_ladderbladeId << "     "  << iRun << "     " ;
              myfile_RMS_BPIX << "          " << rms_mc / rms_data << "        " << rms_data << "        " << rms_mc;
              myfile_RMS_BPIX << std::endl;
            }
            else {
              myfile_RMS_FPIX << " " << iEdge << " " << num_layerId << " " << num_ladderbladeId << "     "  << iRun << "     " ;
              myfile_RMS_FPIX << "          " << rms_mc / rms_data << "        " << rms_data << "        " << rms_mc;
              myfile_RMS_FPIX << std::endl;
            }
          }
        }
        
      }
      
    }
  }
  
  
//   name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade))
  
  
  myfile_BPIX.close();
  myfile_FPIX.close();
  
  myfile_RMS_BPIX.close();
  myfile_RMS_FPIX.close();
  
  
  
}