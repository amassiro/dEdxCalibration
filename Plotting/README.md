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


    
Filter and skim


    g++ -o filterTreeSkim.exe filterTreeSkim.cpp `root-config --cflags --glibs`
 
    ../PixelGeometry/filterTreeSkim.exe data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root
    ../PixelGeometry/filterTreeSkim.exe data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root
    ../PixelGeometry/filterTreeSkim.exe data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root
    ../PixelGeometry/filterTreeSkim.exe data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.root  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root
    
    ../PixelGeometry/filterTreeSkim.exe data_calibration/1May2019/MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.root     data_calibration/1May2019/MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree_filtered_skimmed.root

    ../PixelGeometry/filterTreeSkim.exe  data_calibration/29Apr2019/MC2018/tree_DYJetsM50_HT100to200.root   data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root

      
      
    
    
    
    ../PixelGeometry/filterTreeSkim.exe  data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.root  data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root

    ../PixelGeometry/filterTreeSkim.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.root  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root
    ../PixelGeometry/filterTreeSkim.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.root  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root
    ../PixelGeometry/filterTreeSkim.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.root  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root
    ../PixelGeometry/filterTreeSkim.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.root  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.filtered.skimmed.root
    



    

Plot


    
    g++ -o draw_integral_ttree.exe draw_integral_ttree.cpp `root-config --cflags --glibs`
    
                                               num_run_intervals       num_max_layer(min_layer+this number)     num_max_hit   num_max_labberblade    new_by_what(1=byHit,0=byLayer)       min_layer    want_to_use_the_smeared
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
    
    
    
Draw 1 layer at a time (before calibration):
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer1.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer2.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer3.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root        data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer4.root    1      1      4     65     1     3       0
    
    

    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root   \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunD_layer1.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunD_layer2.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunD_layer3.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root     \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunD_layer4.root    1      1      4     65     1     3       0

    

    
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root   \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunC_layer1.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunC_layer2.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunC_layer3.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root     \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunC_layer4.root    1      1      4     65     1     3       0

    
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root   \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunB_layer1.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunB_layer2.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunB_layer3.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root     \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunB_layer4.root    1      1      4     65     1     3       0
    
    

    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root   \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunA_layer1.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunA_layer2.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root    \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunA_layer3.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root     \
                               data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root   \
                               outplots_2018data_RunA_layer4.root    1      1      4     65     1     3       0

                               
                               
                               
    
    tree->Draw ("IsoTrack_dedxByHit1[best_track]", "(IsoTrack_layerOrSideByHit1[best_track] == 1) && (IsoTrack_ladderOrBladeByHit1[best_track] == 1) && (IsoTrack_pixByHit1[best_track] == 1 ) && ( (run >= 320673) && (run < 325173)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <2.500000)   ) " )
    
    tree->Draw ("IsoTrack_dedxByHit2[best_track]", "(IsoTrack_layerOrSideByHit2[best_track] == 1) && (IsoTrack_ladderOrBladeByHit2[best_track] == 1) && (IsoTrack_pixByHit2[best_track] == 1 ) && ( (run >= 320673) && (run < 325173)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <2.500000)   ) " )

    tree->Draw ("IsoTrack_dedxByHit3[best_track]", "(IsoTrack_layerOrSideByHit3[best_track] == 1) && (IsoTrack_ladderOrBladeByHit3[best_track] == 1) && (IsoTrack_pixByHit3[best_track] == 1 ) && ( (run >= 320673) && (run < 325173)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <2.500000)   ) " )
    
    tree->Draw ("IsoTrack_dedxByHit0[best_track]", "(IsoTrack_layerOrSideByHit0[best_track] == 1) && (IsoTrack_ladderOrBladeByHit0[best_track] == 1) && (IsoTrack_pixByHit0[best_track] == 1 ) && ( (run >= 320673) && (run < 325173)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <2.500000)   ) " )
                 
    whatToDraw = IsoTrack_dedxByHit0[best_track] >> h_iRun_0__ilayer_1__iEdge_0__ladderblade_1__dedxById_BPIX_data
    cutToDraw  = (IsoTrack_layerOrSideByHit0[best_track] == 1) && (IsoTrack_ladderOrBladeByHit0[best_track] == 1) && (IsoTrack_pixByHit0[best_track] == 1 ) && ( (run >= 320673) && (run < 325173)  ) && ( (  abs(IsoTrack_eta[best_track] ) >=0.000000) && (  abs(IsoTrack_eta[best_track] ) <2.500000)   ) 

 
 
 
    tree->Draw ("IsoTrack_dedxByHit1[best_track]/IsoTrack_dedxUnSmearedByHit1[best_track]", "" )
    
 

Draw after calibration
====

Two text files needed as input, from the "Calibration" folder.
    
    

    g++ -o draw_integral_ttree_calibrated.exe draw_integral_ttree_calibrated.cpp `root-config --cflags --glibs`
    
                   BPIX_calib     FPIX_calib              num_run_intervals       num_max_layer(min_layer+this number)     num_max_hit   num_max_labberblade    new_by_what(1=byHit,0=byLayer)       min_layer   want_to_use_the_smeared
 
    
Draw 1 layer at a time:
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer1_scaled.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer2_scaled.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer3_scaled.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer4_scaled.root    1      1      4     65     1     3       0
    
    

    
    
    
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018D/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018D/scale_FPIX_pixels_run_ranges.txt     \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunD_layer1_scaled.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018D/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018D/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunD_layer2_scaled.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018D/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018D/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunD_layer3_scaled.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018D/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018D/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunD_layer4_scaled.root    1      1      4     65     1     3       0

    
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018C/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018C/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunC_layer1_scaled.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018C/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018C/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunC_layer2_scaled.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018C/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018C/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunC_layer3_scaled.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018C/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018C/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunC_layer4_scaled.root    1      1      4     65     1     3       0

    
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018B/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018B/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunB_layer1_scaled.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018B/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018B/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunB_layer2_scaled.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018B/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018B/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunB_layer3_scaled.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018B/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018B/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunB_layer4_scaled.root    1      1      4     65     1     3       0

    
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018A/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018A/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunA_layer1_scaled.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018A/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018A/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunA_layer2_scaled.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018A/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018A/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunA_layer3_scaled.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree_filtered_skimmed.root  \
    ../Calibration/Run2018A/scale_BPIX_pixels_run_ranges.txt   ../Calibration/Run2018A/scale_FPIX_pixels_run_ranges.txt      \
    data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root    outplots_2018data_RunA_layer4_scaled.root    1      1      4     65     1     3       0
    
    
    
    
    
Split in run ranges without applying calibration:

    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer1_scaled.root    1      1      4     65     1     0       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer2_scaled.root    1      1      4     65     1     1       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer3_scaled.root    1      1      4     65     1     2       0
    
    ./draw_integral_ttree_calibrated.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  ../Calibration/scale_BPIX_pixels_run_ranges.txt   ../Calibration/scale_FPIX_pixels_run_ranges.txt      data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer4_scaled.root    1      1      4     65     1     3       0
    

    


Smear the MC
====

Smear the MC according to RMS ratio
    
    g++ -o smear_tree.exe smear_tree.cpp `root-config --cflags --glibs`
    
Run:

    ./smear_tree.exe   data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root      data_calibration/29Apr2019/MC2018/tree_filtered_smeared_DYJetsM50_HT100to200.root
    ./smear_tree.exe   data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root      data_calibration/29Apr2019/MC2018/tree_filtered_smeared_DEFAULT_DYJetsM50_HT100to200.root


    ./smear_tree.exe   data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root     data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_smeared_DYJetsM50_HT100to200.root 
    
    
Test:

    r99t ../Plotting/data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_smeared_DYJetsM50_HT100to200.root ../Plotting/data_calibration/29Apr2019/MC2018/tree_filtered_skimmed_DYJetsM50_HT100to200.root


    TTree* tree1 = (TTree*) _file1->Get("tree")
    TTree* tree0 = (TTree*) _file0->Get("tree")
    tree1->Draw("IsoTrack_dedxUnSmearedByHit1[best_track]", "IsoTrack_layerOrSideByHit1[best_track] == 1 && (IsoTrack_pixByHit1[best_track] == 1 ) ")
    tree0->Draw("IsoTrack_dedxUnSmearedByHit1[best_track]", "IsoTrack_layerOrSideByHit1[best_track] == 1 && (IsoTrack_pixByHit1[best_track] == 1 ) ", "same")

    TTree* tree1 = (TTree*) _file1->Get("tree")
    TTree* tree0 = (TTree*) _file0->Get("tree")
    tree1->Draw("IsoTrack_dedxUnSmearedByHit0[best_track]", "IsoTrack_layerOrSideByHit0[best_track] == 1 && (IsoTrack_pixByHit0[best_track] == 1 ) ")
    tree0->Draw("IsoTrack_dedxUnSmearedByHit0[best_track]", "IsoTrack_layerOrSideByHit0[best_track] == 1 && (IsoTrack_pixByHit0[best_track] == 1 ) ", "same")

    TTree* tree1 = (TTree*) _file1->Get("tree")
    TTree* tree0 = (TTree*) _file0->Get("tree")
    tree1->Draw("IsoTrack_dedxUnSmearedByHit5[best_track]", "IsoTrack_layerOrSideByHit5[best_track] == 1 && (IsoTrack_pixByHit5[best_track] == 1 ) ")
    tree0->Draw("IsoTrack_dedxUnSmearedByHit5[best_track]", "IsoTrack_layerOrSideByHit5[best_track] == 1 && (IsoTrack_pixByHit5[best_track] == 1 ) ", "same")

    TTree* tree1 = (TTree*) _file1->Get("tree")
    TTree* tree0 = (TTree*) _file0->Get("tree")
    tree1->Draw("IsoTrack_dedxUnSmearedByHit6[best_track]", "IsoTrack_layerOrSideByHit6[best_track] == 1 && (IsoTrack_pixByHit6[best_track] == 1 ) ")
    tree0->Draw("IsoTrack_dedxUnSmearedByHit6[best_track]", "IsoTrack_layerOrSideByHit6[best_track] == 1 && (IsoTrack_pixByHit6[best_track] == 1 ) ", "same")

    
    
And plot:


    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer1_scaled_mc_not_smeared_many_run_ranges.root    10      1      4     65     1     0       0
 
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer2_scaled_mc_not_smeared_many_run_ranges.root    10      1      4     65     1     1       0
    
    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer3_scaled_mc_not_smeared_many_run_ranges.root    10      1      4     65     1     2       0

    ./draw_integral_ttree.exe  data_calibration/1May2019/DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree_filtered.root  data_calibration/29Apr2019/MC2018/tree_filtered_DYJetsM50_HT100to200.root    outplots_2018data_layer4_scaled_mc_not_smeared_many_run_ranges.root    10      1      4     65     1     3       0
    

    
    
Automatic plotting:

    sh script_post_smearing.sh
    sh script_post_smearing_no_scale.sh
    sh script_pre_smearing_no_scale.sh

    > plot directly from cmssw, scale and smear already applied
    sh script_from_cmsssw.sh

    
    
    
For web:

    ls -alrth plots_summary_calibrated_smeared_2018data_Run?/plots_summary_calibrated/*.png | tr "/" " " | awk '{print "cp "$9"/"$10"/"$11" plots_summary_calibrated_smeared_2018data_forWeb/"$9"_"$11}'
    
    ls -alrth plots_summary_no_calibrated_smeared_2018data_Run?/*.png | tr "/" " " | awk '{print "cp "$9"/"$10" plots_summary_no_calibrated_smeared_2018data_forWeb/"$9"_"$10}'
    
    ls -alrth plots_summary_no_calibrated_no_smear_2018data_Run?/*.png | tr "/" " " | awk '{print "cp "$9"/"$10" plots_summary_no_calibrated_no_smear_2018data_Run_forWeb/"$9"_"$10}'
    
    
    ls -alrth plots_summary_from_cmssw_2018data_Run?/*.png | tr "/" " " | awk '{print "cp "$9"/"$10" plots_summary_from_cmssw_2018data_Run_forWeb/"$9"_"$10}'
    
    
    
    
    
    
    
    
    
    
    