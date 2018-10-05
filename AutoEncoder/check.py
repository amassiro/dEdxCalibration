from keras.utils import np_utils
from keras.models import Sequential
from keras.layers import Dense, Dropout

import ROOT as root
import numpy as np

np.random.seed(1234)


def getDataFromFile(fileinfo, branchlist) :

        tfil = root.TFile(fileinfo)
        tree = tfil.Get('flatTree')
        datasize = tree.GetEntriesFast()
        
        print "Reading NN inputs from " + fileinfo
        data = np.empty([datasize, len(branchlist)])
        counter = 0
        for entry in tree :
                bridx = 0
                for branch in branchlist :
                        data[counter][bridx] = getattr(entry, branch)
                        bridx = bridx + 1

                counter = counter + 1
        
        tfil.Close()

        return data



#######################################
#
# Start here
#
import collections

zllfile = 'Data/flat_tree_Z.root'
sigfiles = collections.OrderedDict()
# {}

sigfiles['Wino_M_1000_cTau_10'] = 'Data/MoreData/Wino_M_1000_cTau_10/treeProducerXtracks/flat_tree.root'
sigfiles['Wino_M_1000_cTau_20'] = 'Data/MoreData/Wino_M_1000_cTau_20/treeProducerXtracks/flat_tree.root'
sigfiles['Wino_M_300_cTau_10' ] = 'Data/MoreData/Wino_M_300_cTau_10/treeProducerXtracks/flat_tree.root'
#sigfiles['Wino_M_300_cTau_3'  ] = 'Data/MoreData/Wino_M_300_cTau_3/treeProducerXtracks/flat_tree.root'
sigfiles['Wino_M_300_cTau_30' ] = 'Data/MoreData/Wino_M_300_cTau_30/treeProducerXtracks/flat_tree.root'
#sigfiles['Wino_M_500_cTau_10' ] = 'Data/MoreData/Wino_M_500_cTau_10/treeProducerXtracks/flat_tree.root'
#sigfiles['Wino_M_500_cTau_20' ] = 'Data/MoreData/Wino_M_500_cTau_20/treeProducerXtracks/flat_tree.root'
sigfiles['Wino_M_650_cTau_10' ] = 'Data/MoreData/Wino_M_650_cTau_10/treeProducerXtracks/flat_tree.root'
sigfiles['Wino_M_650_cTau_20' ] = 'Data/MoreData/Wino_M_650_cTau_20/treeProducerXtracks/flat_tree.root'
#sigfiles['Wino_M_800_cTau_10' ] = 'Data/MoreData/Wino_M_800_cTau_10/treeProducerXtracks/flat_tree.root'
#sigfiles['Wino_M_800_cTau_20' ] = 'Data/MoreData/Wino_M_800_cTau_20/treeProducerXtracks/flat_tree.root'


 
#brlist  = ['tk_dedxl0', 'tk_dedxl1', 'tk_dedxl2', 'tk_dedxl3']
brlist  = ['tk_dedxl0', 'tk_dedxl1', 'tk_dedxl2', 'tk_dedxl3', 'tk_dedxl4', 'tk_dedxl5', 'tk_dedxl6', 'tk_category']

numvars = len(brlist)

#print " files = ", files
print " brlist = ", brlist
data_sigs = {}


for name, name_file in sigfiles.items():
  data_sigs[name] = getDataFromFile(name_file, brlist)

data_bkg = getDataFromFile(zllfile, brlist)


labels = {}
data_all = {}
for name, data_sig in data_sigs.items():
  labels[name] = np.vstack( [np.ones((len(data_sigs[name]), 1)), np.zeros((len(data_bkg), 1))] )
  data_all[name] = np.vstack( [data_sigs[name],  data_bkg ] )

num_sigs = len(data_sigs)
print " num_sigs = ", num_sigs


# load model
from keras.models import load_model

model = load_model("xtracks_NN.h5")
model.summary()




#########################################################
## plot

import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D as plt3d

import matplotlib as mpl
mpl.rcParams['figure.facecolor'] = 'white' 


##########################################################
#### ROC curve

from sklearn.metrics import roc_curve

labels_predict = {}
false_positive = {}
true_positive  = {}
thresholds     = {}
for name, data_sig in data_sigs.items():
  labels_predict[name] = model.predict(data_all[name]).ravel()
  false_positive[name], true_positive[name], thresholds[name] = roc_curve(labels[name], labels_predict[name])
    

plt.figure(1)
plt.plot([0, 1], [1, 0], 'k--')


# HEP glossary
colors = iter(cm.rainbow(np.linspace(0,1,num_sigs)))
for name, data_sig in data_sigs.items():
  false_positive_one_minus_rates_keras = [ (1-value) for value in false_positive[name] ]
  color = next(colors)
  plt.plot(true_positive[name], false_positive_one_minus_rates_keras, c=color, label=name)

plt.xlabel('Signal efficiency')
plt.ylabel('Background rejection')
plt.title('ROC curve')
plt.legend(loc='best')
  



##########################################################
#### histograms inputs


ivar = 0
for name_var in brlist:
  print name_var
  fig = plt.figure(ivar+2)
  
  if ivar < numvars :
    #                bkg                    all signals                                                                                                                              range           normalized
    plt.hist(  [(data_bkg)[:,ivar]] + [(data_sigs[name])[:,ivar] for name, name_file in sigfiles.items() ], label= ["bkg"] + [name  for name, name_file in sigfiles.items() ]  , range = (-1, 10) , normed = 1,   bins = 20 )
  else :
    #                bkg                    all signals                                                                                                                              range           normalized
    plt.hist(  [(data_bkg)[:,ivar]] + [(data_sigs[name])[:,ivar] for name, name_file in sigfiles.items() ], label= ["bkg"] + [name  for name, name_file in sigfiles.items() ]  , range = (-1, 10) , normed = 1 )
    
    
  plt.title(name_var)
  plt.xlabel(name_var)
  plt.ylabel("Frequency")
  plt.legend(loc='upper right')
  
  ivar += 1
 
   

#########################################################
## plots only at the end

plt.show()


