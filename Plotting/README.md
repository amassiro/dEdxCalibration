Generic plotting utilities
====

    g++ -o draw_integral.exe draw_integral.cpp `root-config --cflags --glibs`

    ./filterTree.exe Data/22Mar2019/DYJetsM50_2018.root    Data/22Mar2019/tree_filtered_DYJetsM50_2018.root  
    
    ./draw_integral.exe    data_calibration/22Mar2019/tree_filtered_DYJetsM50_2018.root    data_calibration/22Mar2019/tree_filtered_DYJetsM50_2018.root   
    
    ./draw_integral.exe    tree_filtered_DYJetsM50_2018.root    tree_filtered_DYJetsM50_2018.root   
    

    data_calibration/22Mar2019/tree_filtered_DYJetsM50_2018.root


    
    
    
    g++ -o draw_integral_ttree.exe draw_integral_ttree.cpp `root-config --cflags --glibs`

    ./draw_integral_ttree.exe    ../PixelGeometry/Data/8Feb2019/tree_filtered_data_SingleMuon_31Mar2018.root    data_calibration/22Mar2019/tree_filtered_DYJetsM50_2018.root   
    
    ./draw_integral_ttree.exe    tree_filtered_data_SingleMuon_31Mar2018.root    tree_filtered_DYJetsM50_2018.root     outplots.root

    
                                                                                                                             max       run    layer  hit ladder    by_what
    ./draw_integral_ttree.exe    tree_filtered_data_SingleMuon_31Mar2018.root    tree_filtered_DYJetsM50_2018.root     outplots.root    1      2      2     3        0 ---> just to test
    ./draw_integral_ttree.exe    tree_filtered_data_SingleMuon_31Mar2018.root    tree_filtered_DYJetsM50_2018.root     outplots.root    1      5      4     10       0
    
    
    
    
    /eos/cms/store/group/phys_exotica/xtracks/23April2019_Samples2018_Hadded/DYJetsM50_HT100to200/treeProducerXtracks/tree.root
    ../PixelGeometry/filterTree.exe    data_calibration/29Apr2019/MC2018/tree_DYJetsM50_HT100to200.root   data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root

    ../PixelGeometry/filterTree.exe    data_calibration/29Apr2019/MC2018/tree_DYJetsM50_HT100to200_simpleHadd.root   data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200_simpleHadd.root
    
    
    ./draw_integral_ttree.exe    data_calibration/29Apr2019/Data2019/tree_filtered_SingleMuon_Run2018A.root    data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data.root    1      5      4     10     1
    
     
Get 2018 data:

    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/phys_exotica/xtracks/1Apr2019-Hadded-2018/SingleMuon_Run2018A/treeProducerXtracks/tree.root   data_calibration/29Apr2019/Data2019/tree_SingleMuon_Run2018A.root
    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/phys_exotica/xtracks/1Apr2019-Hadded-2018/SingleMuon_Run2018B/treeProducerXtracks/tree.root   data_calibration/29Apr2019/Data2019/tree_SingleMuon_Run2018B.root
    scp amassiro@lxplus.cern.ch:/eos/cms/store/group/phys_exotica/xtracks/1Apr2019-Hadded-2018/SingleMuon_Run2018C/treeProducerXtracks/tree.root   data_calibration/29Apr2019/Data2019/tree_SingleMuon_Run2018C.root

    
    ../PixelGeometry/filterTree.exe    data_calibration/29Apr2019/Data2019/tree_SingleMuon_Run2018A.root   data_calibration/29Apr2019/Data2019/tree_filtered_SingleMuon_Run2018A.root
    ../PixelGeometry/filterTree.exe    data_calibration/29Apr2019/Data2019/tree_SingleMuon_Run2018B.root   data_calibration/29Apr2019/Data2019/tree_filtered_SingleMuon_Run2018B.root
    ../PixelGeometry/filterTree.exe    data_calibration/29Apr2019/Data2019/tree_SingleMuon_Run2018C.root   data_calibration/29Apr2019/Data2019/tree_filtered_SingleMuon_Run2018C.root
    
    
    
10_4_X CMSSW release:
    
    data_calibration/1May2019/
    
    scp -r amassiro@lxplus.cern.ch:/eos/cms/store/group/phys_exotica/xtracks/1May2019/MC-CR-2018-Hadded/ data_calibration/1May2019/
    scp -r amassiro@lxplus.cern.ch:/eos/cms/store/group/phys_exotica/xtracks/1May2019/DATA-CR-2018-Hadded/ data_calibration/1May2019/

    
    ../PixelGeometry/filterTree.exe    data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered.root
    ../PixelGeometry/filterTree.exe    data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered.root
    ../PixelGeometry/filterTree.exe    data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered.root
    ../PixelGeometry/filterTree.exe    data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root
    
    ../PixelGeometry/filterTree.exe   data_calibration/1May2019/MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.root     data_calibration/1May2019/MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree_filtered.root


    
    
    g++ -o draw_integral_ttree.exe draw_integral_ttree.cpp `root-config --cflags --glibs`
    
                                               num_run_intervals       num_max_layer(min_layer+this number)     num_max_hit   num_max_labberblade    new_by_what(1=byHit,0=byLayer)       min_layer
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data.root    1      4      4     65     1
    
    
    IsoTrack_pixByHit0   1 -> BPIX
                         2 -> FPIX
                         
                         
    tree->Draw("IsoTrack_ladderOrBladeByHit0:IsoTrack_layerOrSideByHit0", "IsoTrack_pixByHit0==1", "colz")
    tree->Draw("IsoTrack_ladderOrBladeByHit0:IsoTrack_layerOrSideByHit0", "IsoTrack_pixByHit0==2", "colz")
    
    tree->Draw("IsoTrack_ladderOrBladeByHit3:IsoTrack_layerOrSideByHit3", "IsoTrack_pixByHit3==1", "colz")
    tree->Draw("IsoTrack_ladderOrBladeByHit3:IsoTrack_layerOrSideByHit3", "IsoTrack_pixByHit3==2", "colz")
    
    
    BPIX:
    IsoTrack_ladderOrBladeByHit0: [1 .. 12], [1 .. 28], [1 .. 44], [1 .. 64]
    IsoTrack_layerOrSideByHit0 : 1, 2, 3, 4
    
    
    FPIX: 
    IsoTrack_ladderOrBladeByHit0: [1 .. 56]
    IsoTrack_layerOrSideByHit0 : 1, 2, 3
    
    
    
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data.root    1      1      1     65     1     0
    
    
    
    
    
    
    
    
    
    
    
    
    