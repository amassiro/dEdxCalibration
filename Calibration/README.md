Calibration
====

Use the output of the "Plotting" folder to measure calibration values.

E.g.

    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer1.root    1      1      4     65     1     0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer2.root    1      1      4     65     1     1
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer3.root    1      1      4     65     1     2
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer4.root    1      1      4     65     1     3
    

    
Hadd:

    hadd outplots_2018data_all.root  outplots_2018data_layer*.root
    
    
    hadd outplots_2018data_RunA_all.root  outplots_2018data_RunA_layer*.root
    hadd outplots_2018data_RunB_all.root  outplots_2018data_RunB_layer*.root
    hadd outplots_2018data_RunC_all.root  outplots_2018data_RunC_layer*.root
    hadd outplots_2018data_RunD_all.root  outplots_2018data_RunD_layer*.root
    
    
    
    hadd outplots_2018data_RunA_all_smeared_but_not_calibrated.root outplots_2018data_RunA_layer?_scaled_and_smeared.root
    hadd outplots_2018data_RunB_all_smeared_but_not_calibrated.root outplots_2018data_RunB_layer?_scaled_and_smeared.root
    hadd outplots_2018data_RunC_all_smeared_but_not_calibrated.root outplots_2018data_RunC_layer?_scaled_and_smeared.root
    hadd outplots_2018data_RunD_all_smeared_but_not_calibrated.root outplots_2018data_RunD_layer?_scaled_and_smeared.root
    
    
Calibrate. The code will automatically read the histograms, and save the calibration constant for each region/time slice, exploiting the name of the histogram

    name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade))
    
Compile:

    g++ -o calibrate.exe calibrate.cpp `root-config --cflags --glibs`
    
Run:

    ./calibrate.exe  ../Plotting/outplots_2018data_all.root
    
    ./calibrate.exe  ../Plotting/outplots_2018data_many_eta_bins.root
    

    ./calibrate.exe  ../Plotting/outplots_2018data_RunA_all.root
    ./calibrate.exe  ../Plotting/outplots_2018data_RunB_all.root
    ./calibrate.exe  ../Plotting/outplots_2018data_RunC_all.root
    ./calibrate.exe  ../Plotting/outplots_2018data_RunD_all.root

    ./calibrate.exe  ../Plotting/outplots_2018data_RunA_all_smeared_but_not_calibrated.root
    ./calibrate.exe  ../Plotting/outplots_2018data_RunB_all_smeared_but_not_calibrated.root
    ./calibrate.exe  ../Plotting/outplots_2018data_RunC_all_smeared_but_not_calibrated.root
    ./calibrate.exe  ../Plotting/outplots_2018data_RunD_all_smeared_but_not_calibrated.root

    cp *.txt Run2018A/
    cp *.txt Run2018B/
    cp *.txt Run2018C/
    cp *.txt Run2018D/
    
    
    
Prepare for lxplus/cmssw (old version)

    g++ -o prepareTextPixelTime.exe prepareTextPixelTime.cpp `root-config --cflags --glibs`
    ./prepareTextPixelTime.exe    scale_for_cmssw.txt    30       5    scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    ./prepareTextPixelTime.exe    scale_for_cmssw_runA.txt    1   5    Run2018A/scale_BPIX_pixels_run_ranges.txt  Run2018A/scale_FPIX_pixels_run_ranges.txt
    ./prepareTextPixelTime.exe    scale_for_cmssw_runB.txt    1   5    Run2018B/scale_BPIX_pixels_run_ranges.txt  Run2018B/scale_FPIX_pixels_run_ranges.txt
    ./prepareTextPixelTime.exe    scale_for_cmssw_runC.txt    1   5    Run2018C/scale_BPIX_pixels_run_ranges.txt  Run2018C/scale_FPIX_pixels_run_ranges.txt
    ./prepareTextPixelTime.exe    scale_for_cmssw_runD.txt    1   5    Run2018D/scale_BPIX_pixels_run_ranges.txt  Run2018D/scale_FPIX_pixels_run_ranges.txt

    
    

    g++ -o prepareTextPixel.exe prepareTextPixel.cpp `root-config --cflags --glibs`
    ./prepareTextPixel.exe    scale_for_cmssw.txt    4    scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    
    

Get smearing (new and faster):

    python calculateRMS.py 

    
     0.052 / 0.045  -> 16% additional


 
    
    
