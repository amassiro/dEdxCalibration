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
    