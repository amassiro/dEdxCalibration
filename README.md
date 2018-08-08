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
    
    
Compile:

    g++ -o calibrateAuto.exe calibrateAuto.cpp  `root-config --cflags --glibs`
    g++ -o calibrate.exe     calibrate.cpp      `root-config --cflags --glibs`
    
    ./calibrate.exe   tocalibrate.root
    

    
Toys likelihood fit:

    r99t -q toySimulate.cxx\(1000,1000\)       ;          r99t -q toySimulate.cxx\(1000,10000\)
    r99t -q toySimulate.cxx\(10000,1000\)      ;          r99t -q toySimulate.cxx\(10000,10000\)
    r99t -q toySimulate.cxx\(100000,1000\)     ;          r99t -q toySimulate.cxx\(100000,10000\)
    r99t -q toySimulate.cxx\(1000000,1000\)    ;          r99t -q toySimulate.cxx\(1000000,10000\)
    r99t -q toySimulate.cxx\(10000000,1000\)   ;          r99t -q toySimulate.cxx\(10000000,10000\)
    r99t -q toySimulate.cxx\(100000000,1000\)  ;          r99t -q toySimulate.cxx\(100000000,10000\)
    
    
    g++ -o toyCalibrate.exe toyCalibrate.cpp `root-config --cflags --glibs`
     
    ./toyCalibrate.exe
    ./toyCalibrate.exe 1000
    ./toyCalibrate.exe 10000
    
    
    
     
    
    
    
     