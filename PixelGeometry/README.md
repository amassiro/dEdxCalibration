
Copy files:
====

    scp amassiro@lxplus.cern.ch:/afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/Test/Wino_M_300_cTau_3_Chunk12/treeProducerXtracks/tree.root data/
    scp amassiro@lxplus.cern.ch:/afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/tree_DY.root data/
    scp amassiro@lxplus.cern.ch:/afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/tree_DY_new.root data/
    scp amassiro@lxplus.cern.ch:/afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/tree_data.root data/
    
    cd /afs/cern.ch/user/a/amassiro/work/CMG/DisappearingTracks/test_geometry/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/
    hadd /tmp/amassiro/tree_data.root MYBATCH/SingleMuon_Run201*/treeProducerXtracksSUPER/tree.root 
    scp amassiro@lxplus.cern.ch:/tmp/amassiro/tree_data.root Data/



Filter:
====

    g++ -o filterTree.exe filterTree.cpp `root-config --cflags --glibs`
     
    ./filterTree.exe data/tree.root   data/tree_out.root  
    ./filterTree.exe ../../XTracks/CR_MC/DYJetsToLL_M50/treeProducerXtracks/tree.root   data/tree_mc.root  
    ./filterTree.exe data/tree_DY.root   data/tree_filtered_DY.root  
    ./filterTree.exe data/tree_DY_new.root   data/tree_filtered_DY.root  
    ./filterTree.exe data/tree_data.root   data/tree_filtered_data.root  
 
    ./filterTree.exe Data/tree_data.root   Data/tree_filtered_data.root  
    ./filterTree.exe Data/tree_dy.root     Data/tree_filtered_mc.root  

    ./filterTree.exe Data/4Feb2019/tree_DYJetsM50_HT100to200.root     Data/4Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root  
    ./filterTree.exe Data/4Feb2019/tree_SingleMuon_Run2017B_31Mar2018.root     Data/4Feb2019/tree_filtered_data_SingleMuon_Run2017B_31Mar2018.root  
    ./filterTree.exe Data/4Feb2019/tree_SingleMuon_Run2017C_31Mar2018.root     Data/4Feb2019/tree_filtered_data_SingleMuon_Run2017C_31Mar2018.root  
    ./filterTree.exe Data/4Feb2019/tree_SingleMuon_Run2017D_31Mar2018.root     Data/4Feb2019/tree_filtered_data_SingleMuon_Run2017D_31Mar2018.root  
    ./filterTree.exe Data/4Feb2019/tree_SingleMuon_Run2017E_31Mar2018.root     Data/4Feb2019/tree_filtered_data_SingleMuon_Run2017E_31Mar2018.root  
    ./filterTree.exe Data/4Feb2019/tree_SingleMuon_Run2017F_31Mar2018.root     Data/4Feb2019/tree_filtered_data_SingleMuon_Run2017F_31Mar2018.root  
    
    hadd Data/4Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root Data/4Feb2019/tree_filtered_data_SingleMuon_Run2017*_31Mar2018.root

    
    ./filterTree.exe Data/7Feb2019/tree_DYJetsM50_HT100to200.root     Data/7Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root  
    ./filterTree.exe Data/7Feb2019/tree_SingleMuon_Run2017B_31Mar2018.root     Data/7Feb2019/tree_filtered_data_SingleMuon_Run2017B_31Mar2018.root  
    ./filterTree.exe Data/7Feb2019/tree_SingleMuon_Run2017C_31Mar2018.root     Data/7Feb2019/tree_filtered_data_SingleMuon_Run2017C_31Mar2018.root  
    ./filterTree.exe Data/7Feb2019/tree_SingleMuon_Run2017D_31Mar2018.root     Data/7Feb2019/tree_filtered_data_SingleMuon_Run2017D_31Mar2018.root  
    ./filterTree.exe Data/7Feb2019/tree_SingleMuon_Run2017E_31Mar2018.root     Data/7Feb2019/tree_filtered_data_SingleMuon_Run2017E_31Mar2018.root  
    ./filterTree.exe Data/7Feb2019/tree_SingleMuon_Run2017F_31Mar2018.root     Data/7Feb2019/tree_filtered_data_SingleMuon_Run2017F_31Mar2018.root  
    
    hadd Data/7Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root Data/7Feb2019/tree_filtered_data_SingleMuon_Run2017*_31Mar2018.root

    
    
    ./filterTree.exe Data/8Feb2019/tree_DYJetsM50_HT100to200.root     Data/8Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root  
    ./filterTree.exe Data/8Feb2019/tree_SingleMuon_Run2017B_31Mar2018.root     Data/8Feb2019/tree_filtered_data_SingleMuon_Run2017B_31Mar2018.root  
    ./filterTree.exe Data/8Feb2019/tree_SingleMuon_Run2017C_31Mar2018.root     Data/8Feb2019/tree_filtered_data_SingleMuon_Run2017C_31Mar2018.root  
    ./filterTree.exe Data/8Feb2019/tree_SingleMuon_Run2017D_31Mar2018.root     Data/8Feb2019/tree_filtered_data_SingleMuon_Run2017D_31Mar2018.root  
    ./filterTree.exe Data/8Feb2019/tree_SingleMuon_Run2017E_31Mar2018.root     Data/8Feb2019/tree_filtered_data_SingleMuon_Run2017E_31Mar2018.root  
    ./filterTree.exe Data/8Feb2019/tree_SingleMuon_Run2017F_31Mar2018.root     Data/8Feb2019/tree_filtered_data_SingleMuon_Run2017F_31Mar2018.root  
    
    hadd Data/8Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root Data/8Feb2019/tree_filtered_data_SingleMuon_Run2017*_31Mar2018.root

    
    ./filterTree.exe Data/11Feb2019/tree_DYJetsM50_HT100to200.root     Data/11Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root  
    ./filterTree.exe Data/11Feb2019/tree_SingleMuon_Run2017B_31Mar2018.root     Data/11Feb2019/tree_filtered_data_SingleMuon_Run2017B_31Mar2018.root  
    ./filterTree.exe Data/11Feb2019/tree_SingleMuon_Run2017C_31Mar2018.root     Data/11Feb2019/tree_filtered_data_SingleMuon_Run2017C_31Mar2018.root  
    ./filterTree.exe Data/11Feb2019/tree_SingleMuon_Run2017D_31Mar2018.root     Data/11Feb2019/tree_filtered_data_SingleMuon_Run2017D_31Mar2018.root  
    ./filterTree.exe Data/11Feb2019/tree_SingleMuon_Run2017E_31Mar2018.root     Data/11Feb2019/tree_filtered_data_SingleMuon_Run2017E_31Mar2018.root  
    ./filterTree.exe Data/11Feb2019/tree_SingleMuon_Run2017F_31Mar2018.root     Data/11Feb2019/tree_filtered_data_SingleMuon_Run2017F_31Mar2018.root  
    
    hadd Data/11Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root Data/11Feb2019/tree_filtered_data_SingleMuon_Run2017*_31Mar2018.root
    
    
 
 
 
    ./filterTree.exe Data/22Mar2019/DYJetsM50_2018.root    Data/22Mar2019/tree_filtered_DYJetsM50_2018.root  
    
    ./drawPixel.exe     Data/22Mar2019/tree_filtered_DYJetsM50_2018.root        Data/11Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root

    
    
    
    
    ls --color=never  Data/11Feb2019-SR/ | awk '{print "./filterTree.exe Data/11Feb2019-SR/"$1"   Data/11Feb2019-SR/tree_filtered_"$1}'
    
    
    
    
    ./filterTree.exe Data/tree_data_calibrated_cmssw_firstRound.root   Data/tree_filtered_data_calibrated_cmssw_firstRound.root 


    
    
Draw:
====

    g++ -o drawPixel.exe drawPixel.cpp `root-config --cflags --glibs`
     
    ./drawPixel.exe data/tree.root   data/tree.root  
    
    ./drawPixel.exe data/tree_filtered_DY.root   data/tree_filtered_DY.root

    ./drawPixel.exe data/tree_filtered_data.root   data/tree_filtered_DY.root

    
    
    ./drawPixel.exe data/tree_filtered_data.root_before_300850.root  data/tree_filtered_data.root_after_300850.root

    ./drawPixel.exe data/tree_filtered_data.root_before_300850.root_before_300000.root  data/tree_filtered_data.root_before_300850.root_after_300000.root
    
    ./drawPixel.exe data/tree_filtered_data.root_after_300850.root_before_301500.root  data/tree_filtered_data.root_after_300850.root_after_301500.root


    

    g++ -o drawPixelTime.exe drawPixelTime.cpp `root-config --cflags --glibs`
    
                                                                                   number of run intervals
    ./drawPixelTime.exe data/tree_filtered_data.root    data/tree_filtered_DY.root    10
    ./drawPixelTime.exe data/tree_filtered_data.root    data/tree_filtered_DY.root     4
    
    
    ./drawPixelTime.exe data/tree_filtered_data.root    data/tree_filtered_DY.root    10     scale_pixels_run_ranges_reduced.txt
    
    
    
    g++ -o drawPixelTimeNew.exe drawPixelTimeNew.cpp `root-config --cflags --glibs`
    
    ./drawPixelTimeNew.exe Data/tree_filtered_data.root    Data/tree_filtered_mc.root    10   

                                                                               num_run_intervals   num_max_layer
    ./drawPixelTimeNew.exe Data/tree_filtered_data.root    Data/tree_filtered_mc.root    10       5

    ./drawPixelTimeNew.exe Data/tree_filtered_data.root    Data/tree_filtered_mc.root    30       5

    ./drawPixelTimeNew.exe Data/tree_filtered_data.root    Data/tree_filtered_mc.root    60       5


    g++ -o drawPixelTimeUncorrected.exe drawPixelTimeUncorrected.cpp `root-config --cflags --glibs`
    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw.root    Data/tree_filtered_mc.root    60       5
    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw.root    Data/tree_filtered_mc.root    30       5

    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw_firstRound.root     Data/tree_filtered_mc.root    30       5

    
    
    
    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw.root    Data/tree_filtered_mc.root    60       5         scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt
    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw.root    Data/tree_filtered_mc.root    30       5         scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    
    
    
    New geometry
    
    
    ./drawPixelTimeUncorrected.exe Data/4Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root     Data/4Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root        30       5         
    
    ./drawPixelTimeUncorrected.exe Data/4Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root     Data/4Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root     30       5     scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

     minRun = 297050
     maxRun = 306461
     deltaRun = 314

    ./drawPixelTimeUncorrected.exe Data/4Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root     Data/4Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root     30       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt   smear_for_cmssw.txt

    ./prepareTextPixelTime.exe    scale_for_cmssw.txt    30       5    scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    python calculateRMS.py
    
    
    
    ./drawPixelTimeNew.exe Data/7Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root     Data/7Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root        30       5         
    
     minRun = 297050
     maxRun = 306461
     deltaRun = 314

 
    ./drawPixelTimeNew.exe Data/8Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root     Data/8Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root        30       5         
    
    ./drawPixelTimeUncorrected.exe  Data/8Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root     Data/8Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root   30       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt   smear_for_cmssw.txt

    
    ./drawPixelTimeNew.exe Data/11Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root     Data/11Feb2019/tree_filtered_mc_DYJetsM50_HT100to200.root        30       5         
    
    
Draw time evolution
====

    void DrawTimeEvolution( std::string BPIXorFPIX = "BPIX", int num_run_intervals = 30, int ilayer = 0, int iEdge = 0, int iladderblade = 0) 
    
    r99t DrawTimeEvolution.cxx\(\"BPIX\",30,1,0,1\)
    
    r99t DrawTimeEvolution.cxx\(\"BPIX\",5,1,0,1\)
    r99t DrawTimeEvolution.cxx\(\"BPIX\",5,1,1,1\)
    
    
Complete procedure
====

Copy from lxplus uncalibrated.

Filter the tree

    ./filterTree.exe Data/tree_data_calibrated_cmssw_firstRound.root   Data/tree_filtered_data_calibrated_cmssw_firstRound.root 

    hadd Data/25Jan2019/Data-CR1L/tree_SingleMuon_all.root Data/25Jan2019/Data-CR1L/tree_SingleMuon_Run2017*
    ./filterTree.exe   Data/25Jan2019/Data-CR1L/tree_SingleMuon_all.root   Data/25Jan2019/Data-CR1L/tree_filtered_SingleMuon_all.root
    
then draw uncalibrated 
    
    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw_firstRound.root     Data/tree_filtered_mc.root    30       5
    
then calibrate
    
    ./calibratePixelTimeNew.exe    tocalibrate_complete_eta_edges_iladderblade_timeRanges.root      30              5 

then draw calibrated in local
    
    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw_firstRound.root     Data/tree_filtered_mc.root    30       5     scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

prepare for lxplus/cmssw

    g++ -o prepareTextPixelTime.exe prepareTextPixelTime.cpp `root-config --cflags --glibs`
    ./prepareTextPixelTime.exe    scale_for_cmssw.txt    30       5    scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

copy to lxplus (in folder "data") and run again over condor

    heppy_batch.py  run_susyDeDx_cfg.py       -o  /afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/test_geometry_Giovanni/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/MYBATCH3/  --option region=cr1l --option run=data   \
             -b 'run_condor_simple.sh -t 480 ./batchScript.sh' -B
    

Check that worked. Filter the tree
    
    ./filterTree.exe   Data/tree_data_calibrated_cmssw_it_should_be_calibrated.root  Data/tree_filtered_data_calibrated_cmssw_it_should_be_calibrated.root
    
Plot:

    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw_it_should_be_calibrated.root     Data/tree_filtered_mc.root    30       5
    ./drawPixelTimeNew.exe Data/tree_filtered_data_calibrated_cmssw_it_should_be_calibrated.root     Data/tree_filtered_mc.root    30       5
    
 
Get smearing:

    python calculateRMS.py
    
Test smearing:

    ./drawPixelTimeUncorrected.exe Data/tree_filtered_data_calibrated_cmssw_it_should_be_calibrated.root     Data/tree_filtered_mc.root    30       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt   smear_for_cmssw.txt

 
Add pixel calibration:

    g++ -o addPixelCalibration.exe addPixelCalibration.cpp `root-config --cflags --glibs`

    ./addPixelCalibration.exe  Data/tree_filtered_data_calibrated_cmssw_it_should_be_calibrated.root    Data/tree_filtered_data_calibrated_cmssw_it_should_be_calibrated_weight_added.root       30       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt
    
    
Create text file for CMSSW 
====

    g++ -o prepareTextPixelTime.exe prepareTextPixelTime.cpp `root-config --cflags --glibs`

    ./prepareTextPixelTime.exe    scale_for_cmssw.txt    60       5    scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt
    
    ./prepareTextPixelTime.exe    scale_for_cmssw.txt    30       5    scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt
    
    
    ./filterTree.exe Data/tree_data_calibrated_cmssw.root   Data/tree_filtered_data_calibrated_cmssw.root  

    
    
 
    
Split:
====

    g++ -o splitTree.exe splitTree.cpp `root-config --cflags --glibs`
    
    ./splitTree.exe  data/tree_filtered_data.root     300850
    
    Run half ~ 300850
    
    
    ./splitTree.exe  data/tree_filtered_data.root     300850
    
    
    ./splitTree.exe  data/tree_filtered_data.root_before_300850.root     300000
    
    ./splitTree.exe  data/tree_filtered_data.root_after_300850.root      301500
    
    
 
Calibrate:
====


    g++ -o calibratePixel.exe calibratePixel.cpp `root-config --cflags --glibs`
 
    ./calibratePixel.exe    tocalibrate_complete_eta_edges_idet.root
    
 
    Draw calibrated 
    ./drawPixel.exe  data/tree_filtered_data.root   data/tree_filtered_DY.root   scale_pixels_reduced.txt
 
 
 
 
 
    g++ -o calibratePixelTime.exe calibratePixelTime.cpp `root-config --cflags --glibs`

                                                                                    num_run_intervals
    ./calibratePixelTime.exe    tocalibrate_complete_eta_edges_idet_timeRanges.root       4
    ./calibratePixelTime.exe    tocalibrate_complete_eta_edges_idet_timeRanges.root      10
    
    
    
    g++ -o calibratePixelTimeNew.exe calibratePixelTimeNew.cpp `root-config --cflags --glibs`

                                                                                               num_run_intervals   num_max_layer
    ./calibratePixelTimeNew.exe    tocalibrate_complete_eta_edges_iladderblade_timeRanges.root      10              5 

    ./calibratePixelTimeNew.exe    tocalibrate_complete_eta_edges_iladderblade_timeRanges.root      30              5 

    ./calibratePixelTimeNew.exe    tocalibrate_complete_eta_edges_iladderblade_timeRanges.root      60              5 

    //---- draw calibrated
    ./drawPixelTimeNew.exe Data/tree_filtered_data.root    Data/tree_filtered_mc.root    30       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    ./drawPixelTimeNew.exe Data/tree_filtered_data.root    Data/tree_filtered_mc.root    60       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    
Add calibration as a weight:
====

    g++ -o addPixelCalibration.exe addPixelCalibration.cpp `root-config --cflags --glibs`

    ./addPixelCalibration.exe  Data/tree_filtered_data.root   Data/tree_filtered_data_calibrated.root       30       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    ./addPixelCalibration.exe  Data/tree_filtered_data.root   Data/tree_filtered_data_calibrated_new_many_eta_regions.root       30       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt

    ./addPixelCalibration.exe  Data/tree_filtered_data.root   Data/tree_filtered_data_calibrated_new_many_eta_regions_30iov.root       60       5       scale_BPIX_pixels_run_ranges.txt     scale_FPIX_pixels_run_ranges.txt


    r99t  Data/tree_filtered_data.root 
    r99t  Data/tree_filtered_data_calibrated.root    
    r99t  Data/tree_filtered_mc.root
    
    r99t  Data/tree_filtered_data_calibrated_new_many_eta_regions.root 
    
    r99t  Data/tree_filtered_data_calibrated_new_many_eta_regions_30iov.root
    
    
    
    tree = (TTree*)  _file0 -> Get ("tree");
    tree = (TTree*)  _file0 -> Get ("tree_data");
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]==1", "colz")    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]==1", "colz")    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:run", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]==1", "colz")    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]:run", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]==1", "colz")    
    
    
    
    tree->Draw("IsoTrack_dedxByLayer1[best_track]*IsoTrack_calibrationdedxByLayer1[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer1[best_track]==1 && IsoTrack_dedxByLayer1[best_track]*IsoTrack_calibrationdedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer1[best_track]==1", "colz")    
    
    tree->Draw("IsoTrack_dedxByLayer2[best_track]*IsoTrack_calibrationdedxByLayer2[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer2[best_track]==1 && IsoTrack_dedxByLayer2[best_track]*IsoTrack_calibrationdedxByLayer2[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer2[best_track]==1", "colz")    
    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]==1", "")    
    
    tree->Draw("IsoTrack_dedxByLayer1[best_track]*IsoTrack_calibrationdedxByLayer1[best_track]", "IsoTrack_layerOrSideByLayer1[best_track]==1 && IsoTrack_dedxByLayer1[best_track]*IsoTrack_calibrationdedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer1[best_track]==1", "")    
    
    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]==2", "colz")    
    
    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_layerOrSideByLayer0[best_track]", "IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]==1", "colz")    

    
    
    
    
    
    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<3.0", "colz")    
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && (IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track])<10 && abs(IsoTrack_eta[best_track])<3.0", "colz")    

    
    tree->Draw("IsoTrack_ladderOrBladeByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    
    
    tree->Draw("IsoTrack_moduleByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<3.0", "colz")    
    
    

    //---- ladder 12 was not calibrated (by mistake)
    tree->Draw("IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerOrSideByLayer0[best_track]==1 && IsoTrack_dedxByLayer0[best_track]*IsoTrack_calibrationdedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_ladderOrBladeByLayer0[best_track]!=12", "colz")    
    
    
    
Draw dx and geometry
====

    tree->Draw("IsoTrack_dxByLayer0[0]:IsoTrack_eta[0]", "", "colz")


    
Draw phi modulation:
====

    r99t data/tree_filtered_data.root
    
    tree = (TTree*)  _file0 -> Get ("tree");
    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    

    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])>1.3", "colz")    

    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_dedxByLayer0[best_track]<10", "colz")    

    tree->Draw("IsoTrack_dedxByLayer1[best_track]:IsoTrack_phi[best_track]", "IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
     
     
    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerPixelByLayer0[best_track]==0 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    

    tree->Draw("IsoTrack_dedxByLayer1[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerPixelByLayer1[best_track]==1 && IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    

    tree->Draw("IsoTrack_dedxByLayer2[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerPixelByLayer2[best_track]==2 && IsoTrack_dedxByLayer2[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    
    
    
    tree->Draw("IsoTrack_layerPixelByLayer2[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerPixelByLayer2[best_track]>-10 && IsoTrack_dedxByLayer2[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    tree->Draw("IsoTrack_layerPixelByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_layerPixelByLayer0[best_track]>-10 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    
     
     
    r99t data/tree_filtered_DY.root
    
    tree = (TTree*)  _file0 -> Get ("tree");
    tree->Draw("IsoTrack_dedxByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    


    
    
    r99t data/tree_filtered_data.root
    tree = (TTree*)  _file0 -> Get ("tree");
    
    tree->Draw("IsoTrack_ladderPixelByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    tree->Draw("IsoTrack_modulePixelByLayer0[best_track]:IsoTrack_phi[best_track]", "IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    

    tree->Draw("IsoTrack_modulePixelByLayer0[best_track]:IsoTrack_ladderPixelByLayer0[best_track]", "IsoTrack_sizeXbyLayer0[best_track] != 0 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_layerPixelByLayer0[best_track]==0", "colz")    
    tree->Draw("IsoTrack_ladderPixelByLayer0[best_track]", "IsoTrack_sizeXbyLayer0[best_track] != 0 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_layerPixelByLayer0[best_track]==0", "colz")    
    
    tree->Draw("IsoTrack_ladderPixelByLayer0[best_track]", "IsoTrack_sizeXbyLayer0[best_track] != 0 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_layerPixelByLayer0[best_track]==0 && IsoTrack_diskPixelByLayer0[best_track]==-99", "colz")    
    
    
    tree->Draw("IsoTrack_ladderPixelByLayer1[best_track]", "IsoTrack_sizeXbyLayer1[best_track] != 0 && IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_layerPixelByLayer1[best_track]==1 && IsoTrack_diskPixelByLayer1[best_track]==-99", "colz")    
    
    
    tree->Draw("IsoTrack_ladderPixelByLayer1[best_track]", "IsoTrack_sizeXbyLayer1[best_track] != 0 && IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_layerPixelByLayer1[best_track]==0 && IsoTrack_diskPixelByLayer1[best_track]==-99", "colz")    
    
    tree->Draw("IsoTrack_ladderPixelByLayer1[best_track]", "IsoTrack_sizeXbyLayer1[best_track] != 0 && IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_layerPixelByLayer1[best_track]==2 && IsoTrack_diskPixelByLayer1[best_track]==-99", "colz")    
    
    
    tree->Draw("IsoTrack_layerPixelByLayer1[best_track]", "IsoTrack_sizeXbyLayer1[best_track] != 0 && IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_diskPixelByLayer1[best_track]==-99")    
    tree->Draw("IsoTrack_sizeXbyLayer1[best_track]:IsoTrack_layerPixelByLayer1[best_track]", "IsoTrack_sizeXbyLayer1[best_track] != 0 && IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_diskPixelByLayer1[best_track]==-99", "colz")    
    tree->Draw("IsoTrack_sizeXbyLayer2[best_track]:IsoTrack_layerPixelByLayer2[best_track]", "IsoTrack_sizeXbyLayer2[best_track] != 0 && IsoTrack_dedxByLayer2[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_diskPixelByLayer2[best_track]==-99", "colz")    
    tree->Draw("IsoTrack_layerPixelByLayer2[best_track]", "IsoTrack_sizeXbyLayer2[best_track] != 0 && IsoTrack_dedxByLayer2[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_diskPixelByLayer2[best_track]==-99")    
    
    tree->Draw("IsoTrack_modulePixelByLayer0[best_track]", "IsoTrack_sizeXbyLayer0[best_track] != 0 && IsoTrack_layerPixelByLayer0[best_track]==0  && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_diskPixelByLayer0[best_track]==-99")    
    tree->Draw("IsoTrack_modulePixelByLayer0[best_track]:IsoTrack_eta[best_track]", "IsoTrack_sizeXbyLayer0[best_track] != 0 && IsoTrack_layerPixelByLayer0[best_track]==0  && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3 && IsoTrack_diskPixelByLayer0[best_track]==-99", "colz")    
    
    
    
    tree->Draw("IsoTrack_modulePixelByLayer0[best_track]:IsoTrack_ladderPixelByLayer0[best_track]", "IsoTrack_sizeXbyLayer0[best_track] != 0 && IsoTrack_dedxByLayer0[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    tree->Draw("IsoTrack_modulePixelByLayer1[best_track]:IsoTrack_ladderPixelByLayer1[best_track]", "IsoTrack_sizeXbyLayer1[best_track] != 0 && IsoTrack_dedxByLayer1[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    tree->Draw("IsoTrack_modulePixelByLayer2[best_track]:IsoTrack_ladderPixelByLayer2[best_track]", "IsoTrack_sizeXbyLayer2[best_track] != 0 && IsoTrack_dedxByLayer2[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    
    tree->Draw("IsoTrack_modulePixelByLayer3[best_track]:IsoTrack_ladderPixelByLayer3[best_track]", "IsoTrack_sizeXbyLayer3[best_track] != 0 && IsoTrack_dedxByLayer3[best_track]<10 && abs(IsoTrack_eta[best_track])<1.3", "colz")    

     
 
 
Draw geometry:
====

    r99t data/tree_filtered_DY.root  
    
    tree = (TTree*)  _file0 -> Get ("tree");
    
    tree->Draw("IsoTrack_XbyLayer0[best_track]:IsoTrack_YbyLayer0[best_track]", "", "colz")    
    
    BPIX
    tree->Draw("IsoTrack_XbyLayer0[best_track]:IsoTrack_YbyLayer0[best_track]", "IsoTrack_ladderPixelByLayer0[best_track]>-10", "colz")    
    
    tree->Draw("IsoTrack_XbyLayer0[best_track]:IsoTrack_layerPixelByLayer0[best_track]", "IsoTrack_ladderPixelByLayer0[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_YbyLayer0[best_track]:IsoTrack_layerPixelByLayer0[best_track]", "IsoTrack_ladderPixelByLayer0[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_YbyLayer0[best_track]:IsoTrack_XbyLayer0[best_track]:IsoTrack_layerPixelByLayer0[best_track]", "IsoTrack_ladderPixelByLayer0[best_track]>-10", "")    
    tree->Draw("IsoTrack_YbyLayer1[best_track]:IsoTrack_XbyLayer1[best_track]:IsoTrack_layerPixelByLayer1[best_track]", "IsoTrack_ladderPixelByLayer1[best_track]>-11", "")    
    tree->Draw("IsoTrack_YbyLayer1[best_track]:IsoTrack_XbyLayer1[best_track]:IsoTrack_layerPixelByLayer1[best_track]:IsoTrack_dedxByLayer1[best_track]", "IsoTrack_ladderPixelByLayer1[best_track]>-11", "")    

    tree->Draw("IsoTrack_dedxByLayer1[best_track]:IsoTrack_YbyLayer1[best_track]:IsoTrack_XbyLayer1[best_track]", "(IsoTrack_layerPixelByLayer1[best_track] == 0) * (IsoTrack_ladderPixelByLayer1[best_track]>-11)", "")    

    
    FPIX
    tree->Draw("IsoTrack_XbyLayer0[best_track]:IsoTrack_YbyLayer0[best_track]", "IsoTrack_diskPixelByLayer0[best_track]>-10", "colz")    
    
    
    # BPIX
    
    tree->Draw("IsoTrack_layerPixelByLayer0[best_track]:IsoTrack_ladderPixelByLayer0[best_track]", "", "colz")    
    tree->Draw("IsoTrack_layerPixelByLayer0[best_track]:IsoTrack_ladderPixelByLayer0[best_track]", "IsoTrack_ladderPixelByLayer0[best_track]>-10", "colz")    
    
    tree->Draw("IsoTrack_layerPixelByLayer1[best_track]:IsoTrack_ladderPixelByLayer1[best_track]", "IsoTrack_ladderPixelByLayer1[best_track]>-10", "colz")    
    
    
    tree->Draw("IsoTrack_layerPixelByLayer0[best_track]:IsoTrack_modulePixelByLayer0[best_track]", "IsoTrack_layerPixelByLayer0[best_track]>-10", "colz")    




    tree->Draw("IsoTrack_layerOrSideByLayer0", "", "")    
    tree->Draw("IsoTrack_sideByLayer0", "", "")    
    
    tree->Draw("IsoTrack_ladderOrBladeByLayer0", "", "")    
    
    tree->Draw("IsoTrack_sizeXbyLayer0", "", "")    
    
    tree->Draw("IsoTrack_pixByLayer0", "", "")    
    
    bpix
    tree->Draw("IsoTrack_layerOrSideByLayer0", "IsoTrack_pixByLayer0==1")    
    tree->Draw("IsoTrack_layerOrSideByLayer1", "IsoTrack_pixByLayer1==1")    
    
    tree->Draw("IsoTrack_ladderOrBladeByLayer0", "IsoTrack_pixByLayer0==1 && IsoTrack_layerOrSideByLayer0==1")    
    
    tree->Draw("IsoTrack_moduleByLayer0", "IsoTrack_pixByLayer0==1 && IsoTrack_layerOrSideByLayer0==1")    
    tree->Draw("IsoTrack_moduleByLayer1", "IsoTrack_pixByLayer1==1 && IsoTrack_layerOrSideByLayer1==1")    
    
    
    

    # FPIX
    
    modulePixel
    sidePixel  
    diskPixel  
    bladePixel 
    panelPixel    
    
    tree->Draw("IsoTrack_diskPixelByLayer0[best_track]:IsoTrack_modulePixelByLayer0[best_track]", "IsoTrack_diskPixelByLayer0[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer1[best_track]:IsoTrack_modulePixelByLayer1[best_track]", "IsoTrack_diskPixelByLayer1[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer2[best_track]:IsoTrack_modulePixelByLayer2[best_track]", "IsoTrack_diskPixelByLayer2[best_track]>-10", "colz")    
    
    tree->Draw("IsoTrack_diskPixelByLayer0[best_track]:IsoTrack_bladePixelByLayer0[best_track]", "IsoTrack_diskPixelByLayer0[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer0[best_track]:IsoTrack_panelPixelByLayer0[best_track]", "IsoTrack_diskPixelByLayer0[best_track]>-10", "colz")    
     
    tree->Draw("IsoTrack_diskPixelByLayer1[best_track]:IsoTrack_panelPixelByLayer1[best_track]", "IsoTrack_diskPixelByLayer1[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer2[best_track]:IsoTrack_panelPixelByLayer2[best_track]", "IsoTrack_diskPixelByLayer2[best_track]>-10", "colz")    
    
    
    
    
Draw effect of smearing and scaling
====

    r99t Data/11Feb2019-SR/tree_Wino_M_1000_cTau_10.root
    tree->Draw("IsoTrack_dedxUnSmearedByLayer0[0]/IsoTrack_dedxByLayer0[0]")
    
    tree->Draw("IsoTrack_dedxUnSmearedByLayer0[0]")
    tree->Draw("IsoTrack_dedxByLayer0[0]", "", "same")

    tree->Draw("IsoTrack_dedxUnSmearedByLayer1[0]")
    tree->Draw("IsoTrack_dedxByLayer1[0]", "", "same")
    
    
    tree_Wino_M_1000_cTau_10.root
    tree_Wino_M_300_cTau_10.root
    tree_Wino_M_300_cTau_30.root
    tree_Wino_M_300_cTau_3.root
    tree_Wino_M_500_cTau_10.root
    tree_Wino_M_650_cTau_10.root
    tree_Wino_M_800_cTau_10.root
    
    
    
    
    
    
    