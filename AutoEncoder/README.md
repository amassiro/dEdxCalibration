AutoEncoder
====

    
 
    
Prepare flat tree
====

    g++ -o prepareTree.exe prepareTree.cpp `root-config --cflags --glibs`
     

    ./prepareTree.exe     Data/SR_MC/DYJetsM50_HT100to200/treeProducerXtracks/tree.root      Data/flat_tree_Z.root
    ./prepareTree.exe     Data/Signal/Wino_M_300_cTau_10/treeProducerXtracks/tree.root       Data/flat_tree_Sig_Wino_M_300_cTau_10.root
 
    ./prepareTree.exe     Data/Signal/Wino_M_300_cTau_10/treeProducerXtracks/tree.root       Data/flat_tree_Sig_Wino_M_300_cTau_10.root
    
    ./prepareTree.exe     Data/Signal/Wino_M_1000_cTau_10/treeProducerXtracks/tree.root       Data/flat_tree_Sig_Wino_M_1000_cTau_10.root
    ./prepareTree.exe     Data/Signal/Wino_M_300_cTau_10/treeProducerXtracks/tree.root        Data/flat_tree_Sig_Wino_M_300_cTau_10.root
    ./prepareTree.exe     Data/Signal/Wino_M_300_cTau_3/treeProducerXtracks/tree.root         Data/flat_tree_Sig_Wino_M_300_cTau_3.root
    ./prepareTree.exe     Data/Signal/Wino_M_300_cTau_30/treeProducerXtracks/tree.root        Data/flat_tree_Sig_Wino_M_300_cTau_30.root
    ./prepareTree.exe     Data/Signal/Wino_M_500_cTau_10/treeProducerXtracks/tree.root        Data/flat_tree_Sig_Wino_M_500_cTau_10.root
    ./prepareTree.exe     Data/Signal/Wino_M_650_cTau_10/treeProducerXtracks/tree.root        Data/flat_tree_Sig_Wino_M_650_cTau_10.root
    ./prepareTree.exe     Data/Signal/Wino_M_800_cTau_10/treeProducerXtracks/tree.root        Data/flat_tree_Sig_Wino_M_800_cTau_10.root
 
 
    hadd    Data/flat_tree_Sig.root   \
         Data/flat_tree_Sig_Wino_M_1000_cTau_10.root       \
         Data/flat_tree_Sig_Wino_M_300_cTau_10.root        \
         Data/flat_tree_Sig_Wino_M_300_cTau_3.root         \
         Data/flat_tree_Sig_Wino_M_300_cTau_30.root        \
         Data/flat_tree_Sig_Wino_M_500_cTau_10.root        \
         Data/flat_tree_Sig_Wino_M_650_cTau_10.root        \
         Data/flat_tree_Sig_Wino_M_800_cTau_10.root        
         
         
         
    ls -alrth  Data/MoreData/*/treeProducerXtracks/ | grep "Data" | tr ":" " " | awk '{print " ./prepareTree.exe     "$1"tree.root "$1"flat_tree.root"}' 
    ls -alrth  Data/MoreData/*/treeProducerXtracks/ | grep "Data" | tr ":" " " | awk '{print " ./prepareTree.exe     "$1"tree.root "$1"flat_tree.root"}'   | /bin/sh
    
    hadd    Data/flat_tree_Sig_all.root  \
         Data/MoreData/Wino_M_1000_cTau_10/treeProducerXtracks/flat_tree.root   \
         Data/MoreData/Wino_M_1000_cTau_20/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_300_cTau_10/treeProducerXtracks/flat_tree.root   \
           Data/MoreData/Wino_M_300_cTau_3/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_300_cTau_30/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_500_cTau_10/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_500_cTau_20/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_650_cTau_10/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_650_cTau_20/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_800_cTau_10/treeProducerXtracks/flat_tree.root   \
          Data/MoreData/Wino_M_800_cTau_20/treeProducerXtracks/flat_tree.root   
          



Simple NN train
====

    python training.py
    

    
Simple NN check train
====

    python check.py
    
    
    
    
    