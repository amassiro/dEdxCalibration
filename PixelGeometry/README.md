
Copy files:
====

    scp amassiro@lxplus.cern.ch:/afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/Test/Wino_M_300_cTau_3_Chunk12/treeProducerXtracks/tree.root data/
    scp amassiro@lxplus.cern.ch:/afs/cern.ch/work/a/amassiro/CMG/DisappearingTracks/CMSSW_9_4_6_patch1/src/CMGTools/TTHAnalysis/cfg/tree_DY.root data/
    
Draw:
====

    g++ -o drawPixel.exe drawPixel.cpp `root-config --cflags --glibs`
     
    ./drawPixel.exe data/tree.root   data/tree.root  
    
    ./drawPixel.exe data/tree_filtered_DY.root   data/tree_filtered_DY.root
    
    
    
Filter:
====

    g++ -o filterTree.exe filterTree.cpp `root-config --cflags --glibs`
     
    ./filterTree.exe data/tree.root   data/tree_out.root  
    ./filterTree.exe ../../XTracks/CR_MC/DYJetsToLL_M50/treeProducerXtracks/tree.root   data/tree_mc.root  
    ./filterTree.exe data/tree_DY.root   data/tree_filtered_DY.root  
 
 
 
 
Draw geometry:
====

    r99t data/tree_filtered_DY.root  
    
    tree = (TTree*)  _file0 -> Get ("tree");
    
    tree->Draw("IsoTrack_XbyLayer0[best_track]:IsoTrack_YbyLayer0[best_track]")    
    
    # BPIX
    
    tree->Draw("IsoTrack_layerPixelByLayer0[best_track]:IsoTrack_ladderPixelByLayer0[best_track]", "", "colz")    
    tree->Draw("IsoTrack_layerPixelByLayer0[best_track]:IsoTrack_ladderPixelByLayer0[best_track]", "IsoTrack_ladderPixelByLayer0[best_track]>-10", "colz")    
    
    tree->Draw("IsoTrack_layerPixelByLayer1[best_track]:IsoTrack_ladderPixelByLayer1[best_track]", "IsoTrack_ladderPixelByLayer1[best_track]>-10", "colz")    
    
    
    tree->Draw("IsoTrack_layerPixelByLayer0[best_track]:IsoTrack_modulePixelByLayer0[best_track]", "IsoTrack_layerPixelByLayer0[best_track]>-10", "colz")    
    
    
    
    
    # FPIX
    
    modulePixel
    sidePixel  
    diskPixel  
    bladePixel 
    panelPixel    
    
    tree->Draw("IsoTrack_diskPixelByLayer0[best_track]:IsoTrack_modulePixelByLayer0[best_track]", "IsoTrack_diskPixelByLayer0[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer1[best_track]:IsoTrack_modulePixelByLayer1[best_track]", "IsoTrack_diskPixelByLayer1[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer2[best_track]:IsoTrack_modulePixelByLayer2[best_track]", "IsoTrack_diskPixelByLayer2[best_track]>-10", "colz")    
    
    tree->Draw("IsoTrack_diskPixelByLayer0[best_track]:IsoTrack_bladePixelByLayer0[best_track]", "IsoTrack_diskPixelByLayer0[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer0[best_track]:IsoTrack_panelPixelByLayer0[best_track]", "IsoTrack_diskPixelByLayer0[best_track]>-10", "colz")    
     
    tree->Draw("IsoTrack_diskPixelByLayer1[best_track]:IsoTrack_panelPixelByLayer1[best_track]", "IsoTrack_diskPixelByLayer1[best_track]>-10", "colz")    
    tree->Draw("IsoTrack_diskPixelByLayer2[best_track]:IsoTrack_panelPixelByLayer2[best_track]", "IsoTrack_diskPixelByLayer2[best_track]>-10", "colz")    
    
    
    
    
    
    
    
    
    
    
    