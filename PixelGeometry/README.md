
Copy files:
====

    scp amassiro@lxplus.cern.ch:/afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/Test/Wino_M_300_cTau_3_Chunk12/treeProducerXtracks/tree.root data/
    
Draw:
====

    g++ -o drawPixel.exe drawPixel.cpp `root-config --cflags --glibs`
     
    ./drawPixel.exe data/tree.root   data/tree.root  
    
Filter:
====

    g++ -o filterTree.exe filterTree.cpp `root-config --cflags --glibs`
     
    ./filterTree.exe data/tree.root   data/tree_out.root  
    ./filterTree.exe ../../XTracks/CR_MC/DYJetsToLL_M50/treeProducerXtracks/tree.root   data/tree_mc.root  
    ./filterTree.exe data/tree_DY.root   data/tree_filtered_DY.root  
 
 
 
 
 
    
    
    