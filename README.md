# dEdxCalibration

Calibration of dE/dx for pixel

- scale for data
- smearing for MC



Inputs:

    /eos/cms/store/cmst3/user/avartak/XTracks/
    
    
Where:

    /home/amassiro/Cern/Code/CMG/DisappearingTracks/dEdxCalibration
    
    
    
Test draw:

    r99t draw.cxx\(\"../XTracks/CR_Data/SingleMuon_Run2017B_17Nov2017/treeProducerXtracks/tree.root\",\"../XTracks/CR_MC/DYJetsToLL_M50/treeProducerXtracks/tree.root\"\)
    
    r99t draw.cxx\(\"../XTracks/CR_Data/SingleMuon_Run2017B_17Nov2017/treeProducerXtracks/tree.root\",\"../XTracks/CR_Data/SingleMuon_Run2017B_17Nov2017/treeProducerXtracks/tree.root\"\)
    r99t draw.cxx\(\"../XTracks/CR_MC/DYJetsToLL_M50/treeProducerXtracks/tree.root\",\"../XTracks/CR_MC/DYJetsToLL_M50/treeProducerXtracks/tree.root\"\)
    
    
Calibrate:

    r99t calibrate.cxx\(\"tocalibrate.root\"\)
    r99t calibrateAuto.cxx\(\"tocalibrate.root\"\)
    
    
    
    
    