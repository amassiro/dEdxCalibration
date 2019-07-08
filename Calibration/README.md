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
    

    
Calibrate. The code will automatically read the histograms, and save the calibration constant for each region/time slice, exploiting the name of the histogram

    name = Form ("h_iRun_%d__ilayer_%d__iEdge_%d__ladderblade_%d__dedxById_BPIX_mc", iRun, layerId.at(ilayer), iEdge, ladderbladeId.at(iladderblade))
    
Compile:

    g++ -o calibrate.exe calibrate.cpp `root-config --cflags --glibs`
    
Run:

    ./calibrate.exe  ../Plotting/outplots_2018data_all.root
    
    ./calibrate.exe  ../Plotting/outplots_2018data_many_eta_bins.root
    
    
    RMS
    4.53758e-01 --> MC
    9.24676e-01 --> Data
 
 
 
Prepare for lxplus/cmssw

    g++ -o prepareTextPixelTime.exe prepareTextPixelTime.cpp `root-config --cflags --glibs`
    ./prepareTextPixelTime.exe    scale_for_cmssw.txt    30       5    scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt
 