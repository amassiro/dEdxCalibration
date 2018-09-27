AutoEncoder
====

    python training.py
    

    
 
    
Prepare flat tree
====

    g++ -o prepareTree.exe prepareTree.cpp `root-config --cflags --glibs`
     

    ./prepareTree.exe     Data/SR_MC/DYJetsM50_HT100to200/treeProducerXtracks/tree.root      Data/flat_tree_Z.root
    ./prepareTree.exe     Data/Signal/Wino_M_300_cTau_10/treeProducerXtracks/tree.root       Data/flat_tree_Sig_Wino_M_300_cTau_10.root
 
    