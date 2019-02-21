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
         
         
         
    ls -alrth  Data/MoreData/*/treeProducerXtracks/ | grep "Data" | tr ":" " " | awk '{print " ./prepareTree.exe     "$1"tree.root "$1"flat_tree.root     1     "}' 
    ls -alrth  Data/MoreData/*/treeProducerXtracks/ | grep "Data" | tr ":" " " | awk '{print " ./prepareTree.exe     "$1"tree.root "$1"flat_tree.root     1     "}'   | /bin/sh
    
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
          

          
    ./prepareTree.exe   Data/../calibration/11Feb2019-SR/tree_Wino_M_1000_cTau_10.root  Data/../calibration/11Feb2019-SR/flat_tree_Wino_M_1000_cTau_10.root       1
    ./prepareTree.exe   Data/../calibration/11Feb2019-SR/tree_Wino_M_800_cTau_10.root  Data/../calibration/11Feb2019-SR/flat_tree_Wino_M_800_cTau_10.root         1
    ./prepareTree.exe   Data/../calibration/11Feb2019-SR/tree_Wino_M_300_cTau_10.root  Data/../calibration/11Feb2019-SR/flat_tree_Wino_M_300_cTau_10.root         1

    ./prepareTree.exe   Data/../calibration/11Feb2019-SR/tree_filtered_tree_DYJetsM50_HT200to400.root  Data/../calibration/11Feb2019-SR/flat_tree_filtered_tree_DYJetsM50_HT200to400.root         

    
    
    flatTree->Draw("tk_dedxl0:tk_pt", "tk_pt<200 && tk_dedxl0>0 && tk_dedxl0<20", "colz");
    flatTree->Draw("tk_dedxl0:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<1000 && tk_dedxl0>0 && tk_dedxl0<20", "colz");
    flatTree->Draw("tk_dedxl0:(tk_pt*cosh(tk_eta))", "(tk_pt)<200 && tk_dedxl0>0 && tk_dedxl0<20", "colz");
    
    hadd Data/../calibration/11Feb2019-SR/flat_tree_Wino_All_cTau_10.root Data/../calibration/11Feb2019-SR/flat_tree_Wino_M_*_cTau_10.root
    Data/../calibration/11Feb2019-SR/flat_tree_filtered_tree_DYJetsM50_HT200to400.root 
    
    
    r99t Data/../calibration/11Feb2019-SR/flat_tree_Wino_All_cTau_10.root    Data/../calibration/11Feb2019-SR/flat_tree_filtered_tree_DYJetsM50_HT200to400.root 

    r99t Data/../calibration/11Feb2019-SR/flat_tree_Wino_M_1000_cTau_10.root    Data/../calibration/11Feb2019-SR/flat_tree_filtered_tree_DYJetsM50_HT200to400.root 

    TTree* sig = (TTree*) _file0->Get("flatTree");
    TTree* bkg = (TTree*) _file1->Get("flatTree");
    
    bkg->Draw("tk_dedxl0:(tk_pt*cosh(tk_eta))", "(tk_pt)<200 && tk_dedxl0>0 && tk_dedxl0<20", "colz");
    sig->Draw("tk_dedxl0:(tk_pt*cosh(tk_eta))", "(tk_pt)<200 && tk_dedxl0>0 && tk_dedxl0<20", "same");

    
    bkg->Draw("tk_dedxl0:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && tk_dedxl0>0 && tk_dedxl0<20", "colz");
    sig->SetMarkerColor(kRed);
    sig->SetMarkerSize(0.5);
    sig->SetMarkerStyle(20);
    sig->Draw("tk_dedxl0:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && tk_dedxl0>0 && tk_dedxl0<20", "same");

    
    
    bkg->Draw("tk_dedxl1:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && tk_dedxl1>0 && tk_dedxl1<20", "colz");
    sig->SetMarkerColor(kRed);
    sig->SetMarkerSize(0.5);
    sig->SetMarkerStyle(20);
    sig->Draw("tk_dedxl1:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && tk_dedxl1>0 && tk_dedxl1<20", "same");


    bkg->Draw("tk_dedxl2:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && tk_dedxl2>0 && tk_dedxl2<20", "colz");
    sig->SetMarkerColor(kRed);
    sig->SetMarkerSize(0.5);
    sig->SetMarkerStyle(20);
    sig->Draw("tk_dedxl2:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && tk_dedxl2>0 && tk_dedxl2<20", "same");


    bkg->Draw("(tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.>0 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.<20", "colz");
    sig->SetMarkerColor(kRed);
    sig->SetMarkerSize(0.5);
    sig->SetMarkerStyle(20);
    sig->Draw("(tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<300 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.>0 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.<20", "same");

    
    
    bkg->Draw("(tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<1000 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.>0 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.<20", "colz");
    sig->SetMarkerColor(kRed);
    sig->SetMarkerSize(0.5);
    sig->SetMarkerStyle(20);
    sig->Draw("(tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.:(tk_pt*cosh(tk_eta))", "(tk_pt*cosh(tk_eta))<1000 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.>0 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.<20", "same");

    
    
    
    
    bkg->Draw("(tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.", "(tk_pt*cosh(tk_eta))<300 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.>0 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.<20", "");
    sig->Draw("(tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.", "1000.*((tk_pt*cosh(tk_eta))<300 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.>0 && (tk_dedxl0+tk_dedxl1+tk_dedxl2)/3.<20)", "same");

    
    
    bkg->Draw("tk_dedxl2:(tk_pt)", "(tk_pt)<300 && tk_dedxl2>0 && tk_dedxl2<20", "colz");
    sig->SetMarkerColor(kRed);
    sig->SetMarkerSize(0.5);
    sig->SetMarkerStyle(20);
    sig->Draw("tk_dedxl2:(tk_pt)", "(tk_pt)<300 && tk_dedxl2>0 && tk_dedxl2<20", "same");

    
    
    
    


Simple NN train
====

    python training.py
    
    python trainingCategory.py
    

    
Simple NN check train
====

    python check.py
    
    python checkCategory.py
    
    
Draw
====

    r99t Draw.cxx\(\"tk_dedxl0\",100,0,10,\"\"\)
    r99t Draw.cxx\(\"tk_dedxl1\",100,0,10,\"\"\)
    r99t Draw.cxx\(\"tk_dedxl2\",100,0,10,\"\"\)
    
    r99t Draw.cxx\(\"tk_dedxl0\",100,0,10,\"tk_category\=\=1\"\)
    r99t Draw.cxx\(\"tk_dedxl1\",100,0,10,\"tk_category\=\=1\"\)
    r99t Draw.cxx\(\"tk_dedxl2\",100,0,10,\"tk_category\=\=1\"\)

    
    r99t Draw.cxx\(\"tk_dedxl0\",100,0,10,\"tk_category\=\=2\"\)
    r99t Draw.cxx\(\"tk_dedxl1\",100,0,10,\"tk_category\=\=2\"\)
    r99t Draw.cxx\(\"tk_dedxl2\",100,0,10,\"tk_category\=\=2\"\)

    
Draw data vs MC for tracker
====

    r99t DrawTracker.cxx\(\"IsoTrack_dedxUnSmearedByLayer5\",100,0,10,\"IsoTrack_pixByLayer5\=\=0\"\)

    r99t DrawTracker.cxx\(\"IsoTrack_dedxUnSmearedByLayer0\",100,0,10,\"IsoTrack_pixByLayer0\=\=1\"\)

    
    
    
    
    
    
    