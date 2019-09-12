# 
# Directly from cmssw, scale and smear already applied 
# 
# 
#     int want_to_use_the_smeared = 1; //----  1 = use "dedx" ;    0 = use "dedxUnSmeared"
# 
# 
# 
# 
    
    
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunD_layer1_from_cmssw.root    1      1      4     65     1     0       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunD_layer2_from_cmssw.root    1      1      4     65     1     1       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunD_layer3_from_cmssw.root    1      1      4     65     1     2       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018D_PromptReco_v2/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunD_layer4_from_cmssw.root    1      1      4     65     1     3       1

    
cp -r  plots_summary      plots_summary_from_cmssw_2018data_RunD
    
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunC_layer1_from_cmssw.root    1      1      4     65     1     0       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunC_layer2_from_cmssw.root    1      1      4     65     1     1       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunC_layer3_from_cmssw.root    1      1      4     65     1     2       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018C_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunC_layer4_from_cmssw.root    1      1      4     65     1     3       1

    
cp -r  plots_summary      plots_summary_from_cmssw_2018data_RunC


./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunB_layer1_from_cmssw.root    1      1      4     65     1     0       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunB_layer2_from_cmssw.root    1      1      4     65     1     1       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunB_layer3_from_cmssw.root    1      1      4     65     1     2       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018B_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunB_layer4_from_cmssw.root    1      1      4     65     1     3       1

    
cp -r  plots_summary      plots_summary_from_cmssw_2018data_RunB


./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunA_layer1_from_cmssw.root    1      1      4     65     1     0       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunA_layer2_from_cmssw.root    1      1      4     65     1     1       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunA_layer3_from_cmssw.root    1      1      4     65     1     2       1
    
./draw_integral_ttree.exe  data_calibration/7Sep2019/Calibrated-DATA-CR-2018-Hadded/SingleMuon_Run2018A_17Sep2018/treeProducerXtracks/tree.filtered.skimmed.root  \
    data_calibration/7Sep2019/Calibrated-MC-CR-2018-Hadded/DYJetsToLL_M50_HT100to200/treeProducerXtracks/tree.filtered.skimmed.root    outplots_2018data_RunA_layer4_from_cmssw.root    1      1      4     65     1     3       1
    
cp -r  plots_summary      plots_summary_from_cmssw_2018data_RunA



