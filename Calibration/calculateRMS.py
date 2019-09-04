import os

# example of file name:
#    plots_run/cc_add_layer_3_eta_5_BPIX.root

list_files = []

#name_folder_input = "../Plotting/plots_summary_calibrated/"
name_folder_input = "../Plotting/plots_summary_calibrated_2018data_RunD/"
#name_folder_input = "../Plotting/plots_summary_calibrated_2018data_RunC/"
#name_folder_input = "../Plotting/plots_summary_calibrated_2018data_RunB/"
#name_folder_input = "../Plotting/plots_summary_calibrated_2018data_RunA/"



#for root, dirs, files in os.walk("plots_run/"):  
for root, dirs, files in os.walk(name_folder_input):  
  for filename in files:
    #if "cc_add_" in filename and ".root" in filename :
    if "cc_summary_" in filename and ".root" in filename :
        #print(filename)
        list_files.append(filename)
        
#print "list_files = " , list_files


eta_edges = {}
#eta_edges[0] = [0.0, 0.3]
#eta_edges[1] = [0.3, 0.6]
#eta_edges[2] = [0.6, 1.0]
#eta_edges[3] = [1.0, 1.3]
#eta_edges[4] = [1.3, 1.6]
#eta_edges[5] = [1.6, 2.1]
#eta_edges[6] = [2.1, 2.5]


# reduced eta ranges
eta_edges[0] = [0.0, 1.3]
eta_edges[1] = [1.3, 2.1]
eta_edges[2] = [2.1, 2.5]



print " writing results into : ", "smear_for_cmssw.txt"

file_bpix_out = open("smear_for_cmssw_bpix.txt","w") 
file_fpix_out = open("smear_for_cmssw_fpix.txt","w") 

file_bpix_out.write("#  " + "\n")
file_bpix_out.write("# iEdge      num_layerId       (rms_data / rms_mc - 1)           rms_data         rms_mc   " + "\n")
file_bpix_out.write("#  " + "\n")
file_fpix_out.write("#  " + "\n")
file_fpix_out.write("# iEdge      num_layerId       (rms_data / rms_mc - 1)           rms_data         rms_mc   " + "\n")
file_fpix_out.write("#  " + "\n")

  


file_out = open("smear_for_cmssw.txt","w") 
file_out.write("#  " + "\n")
file_out.write("# pix layerorside   etaMin etaMax       value      iedge   " + "\n")
file_out.write("#  " + "\n")

import ROOT

for name_file in list_files:
  f = ROOT.TFile.Open(name_folder_input + name_file)
  #f = ROOT.TFile.Open("plots_run/" + name_file)
  print " name_file = ", name_folder_input + name_file
  canvas_name = name_file.replace('.root', '')
  
  canvas_name = "summary"; 
  
  canvas = f.Get(canvas_name)
  #print " histograms = ", canvas.GetListOfPrimitives()
  histograms = canvas.GetListOfPrimitives()
  rms_mc = 0.0
  rms_data = 0.0
  scale_rms = -1
  
  ilayer = -1
  iedge = -1
  isBPIX = -1
  
  for histo in histograms:
    #print histo.GetName()
    
    
    if "_mc" in histo.GetName(): 
      #
      # to get a more reasonable RMS, in particular for BPIX layer 1
      histo.GetXaxis().SetRangeUser (0.5, 4.0);
      #histo.GetXaxis().SetRangeUser (1.0, 4.0);
      #
      # this is the MC histogram 
      if histo.GetEntries() > 10:
        rms_mc = histo.GetRMS()
    if "_data" in histo.GetName(): 
      #
      # to get a more reasonable RMS, in particular for BPIX layer 1
      histo.GetXaxis().SetRangeUser (0.5, 4.0);
      #histo.GetXaxis().SetRangeUser (1.0, 4.0);
      #
      if histo.GetEntries() > 10:
        rms_data = histo.GetRMS()

      # example name histogram:   h_ilayer_1__iEdge_2__dedxById_BPIX_data
      name_histo = histo.GetName()
      " ilayer_1 --> 1"
      position_layer = name_histo.find("ilayer")
      if position_layer != -1 :
        #print " name_histo = ", name_histo, " --> position_layer = ", position_layer
        ilayer = name_histo[position_layer+7]
        #print " name_histo = ", name_histo, " --> ", ilayer
      
      position_edge = name_histo.find("iEdge")
      if position_edge != -1 :
        iedge = name_histo[position_edge+6]
      
      isBPIX = name_histo.find("BPIX")
      if isBPIX == -1 : 
        isBPIX = 2   # FPIX = 2 !
      else :
        isBPIX = 1
  
  
  # pix = 1 (BPIX), 2 (FPIX)
    
  if rms_mc != 0 and rms_data != 0:
    scale_rms = rms_data/rms_mc - 1.0
    print " file = ", name_folder_input + name_file, "     name_histo = ", name_histo, " -->  data = ", rms_data, " ; mc = ", rms_mc
    
    #print " name_histo = ", name_histo, " --> ", ilayer, " ; ", iedge, " : ", isBPIX
    #print " ---> " + " " + str(isBPIX) + "      " + str(ilayer) + "      " + str(eta_edges[iedge][0]) + "      " + str(eta_edges[iedge][1]) + "      " + str(scale_rms) + "      " + str(iedge) + "\n"
    #print " ---> iedge = ", iedge, " => ", eta_edges[iedge]
    #print " iedge = ", iedge
    #print eta_edges[int(iedge)][1]
    file_out.write(" " + str(isBPIX) + "      " + str(ilayer) + "      " + str(eta_edges[int(iedge)][0]) + "      " + str(eta_edges[int(iedge)][1]) + "      " + str(scale_rms) + "      " + str(iedge) + "\n") 
  
    if isBPIX==1 :
      file_bpix_out.write("       " + str(iedge)  + "      " + str(ilayer)  + "      " + str(round(scale_rms,3)) + "      " + str(round(rms_data,3)) + "     "  + str(round(rms_mc,3))  +  "\n") 
    else:                                                                  
      file_fpix_out.write("       " + str(iedge)  + "      " + str(ilayer)  + "      " + str(round(scale_rms,3)) + "      " + str(round(rms_data,3)) + "     "  + str(round(rms_mc,3))  +  "\n") 
  
  
#print eta_edges
#print eta_edges[0]
#print eta_edges[0][1]
#print str(eta_edges[0][1])


# pix layerorside   etaMin etaMax       value 
#  
#  1      1        0.000      0.300      0.01
#


 
file_out.close() 

file_bpix_out.close()
file_fpix_out.close()



