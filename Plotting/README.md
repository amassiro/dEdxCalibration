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

    
                                                                                                                             max       run    layer  hit ladder
    ./draw_integral_ttree.exe    tree_filtered_data_SingleMuon_31Mar2018.root    tree_filtered_DYJetsM50_2018.root     outplots.root    1      2      2     3
    

    
    
     cutToDraw  = (IsoTrack_layerOrSideByLayer0[best_track] == 0) && (IsoTrack_ladderOrBladeByLayer0[best_track] == 0) && (IsoTrack_pixByLayer0[best_track] == 1 ) && ( (run >= 297050) && (run < 306461)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <0.300000)   ) 

     (IsoTrack_ladderOrBladeByLayer0[best_track] == 0) && (IsoTrack_pixByLayer0[best_track] == 1 ) && ( (run >= 297050) && (run < 306461)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <0.300000)   )
     
     (IsoTrack_ladderOrBladeByLayer0[best_track] == 1) && (IsoTrack_pixByLayer0[best_track] == 1 ) && ( (run >= 297050) && (run < 306461)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <0.300000)   )
     
     (IsoTrack_pixByLayer0[best_track] == 1 ) && ( (run >= 297050) && (run < 306461)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <0.300000)   )
     