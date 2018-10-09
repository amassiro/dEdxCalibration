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




def getDataFromFileWithCut(fileinfo, branchlist, cut_variable, cut_value) :

  tfil = root.TFile(fileinfo)
  tree = tfil.Get('flatTree')
  
  datasize = tree.GetEntries(cut_variable + " == " +  str(cut_value))
  
  print "Reading NN inputs from " + fileinfo
  data = np.empty([datasize, len(branchlist)])
  counter = 0
  for entry in tree :
    bridx = 0
    
    # check cut
    if getattr(entry, cut_variable) == cut_value :
    
      for branch in branchlist :
        data[counter][bridx] = getattr(entry, branch)
          
        bridx = bridx + 1
     
      counter = counter + 1
  
  tfil.Close()

  print " counter = ", counter 
  
  return data






def getDataFromFileWithCutGreater(fileinfo, branchlist, cut_variable, cut_value) :

  tfil = root.TFile(fileinfo)
  tree = tfil.Get('flatTree')

  datasize = tree.GetEntries(cut_variable + " >= " +  str(cut_value))
 
  print "Reading NN inputs from " + fileinfo
  data = np.empty([datasize, len(branchlist)])
  counter = 0
  for entry in tree :
    bridx = 0
    
    # check cut
    if getattr(entry, cut_variable) >= cut_value :
    
      for branch in branchlist :
        data[counter][bridx] = getattr(entry, branch)
        bridx = bridx + 1
     
      counter = counter + 1
  
  tfil.Close()

  print " counter = ", counter 
  
  return data




#######################################
#
# Start here
#

zllfile = 'Data/flat_tree_Z.root'
#sigfile = 'Data/flat_tree_Sig.root'
sigfile = 'Data/flat_tree_Sig_all.root'
#sigfile = 'Data/MoreData/Wino_M_650_cTau_20/treeProducerXtracks/flat_tree.root'
#sigfile = 'Data/flat_tree_Sig_Wino_M_300_cTau_10.root'

 
#brlist  = ['tk_dedxl0', 'tk_dedxl1', 'tk_dedxl2', 'tk_dedxl3', 'tk_dedxl4', 'tk_dedxl5', 'tk_dedxl6', 'tk_category']
#brlist  = ['tk_dedxl0', 'tk_dedxl1', 'tk_dedxl2', 'tk_dedxl3', 'tk_dedxl4', 'tk_dedxl5', 'tk_dedxl6']
brlist  = ['tk_dedxl0', 'tk_dedxl1', 'tk_dedxl2']
numvars = len(brlist)
ntrain  =  0.50   # 80% for train
ntest   =  1 - ntrain

#print " files = ", files
print " brlist = ", brlist
data_sig = getDataFromFileWithCut        (sigfile, brlist, 'tk_category', 1)
data_bkg = getDataFromFileWithCutGreater (zllfile, brlist, 'tk_category', 1 )


print " sig data.size = " , data_sig.size , " ---> ", data_sig.size/numvars
print " bkg data.size = " , data_bkg.size , " ---> ", data_bkg.size/numvars

datasize_sig = data_sig.size/numvars
datasize_bkg = data_bkg.size/numvars

#print "Shuffling data ..."
#np.random.shuffle(data_sig)
#np.random.shuffle(data_bkg)


print "data_sig =", data_sig

print "Splitting data between " + str(int(len(data_sig)*ntrain)) + " training and " + str(int(len(data_sig)*ntest)) + " testing samples sig ..."
print "Splitting data between " + str(int(len(data_bkg)*ntrain)) + " training and " + str(int(len(data_bkg)*ntest)) + " testing samples bkg ..."

data_sig_train = data_sig[ : int(len(data_sig)*ntrain)]
data_sig_test  = data_sig[ : int(len(data_sig)*ntrain)]

data_bkg_train = data_bkg[ int(len(data_bkg)*ntrain) : ]
data_bkg_test  = data_bkg[ int(len(data_bkg)*ntrain) : ]

data_train = np.vstack( [data_sig_train, data_bkg_train] )
data_test  = np.vstack( [data_sig_test,  data_bkg_test ] )

labels_train = np.vstack( [np.ones((len(data_sig_train), 1)), np.zeros((len(data_bkg_train), 1))] )
labels_test  = np.vstack( [np.ones((len(data_sig_test), 1)) , np.zeros((len(data_bkg_test), 1))]  )

print " data_train   = ", data_train
print " labels_train = ", labels_train


# define model

model = Sequential()

#model.add(Dense(200, input_dim = numvars, kernel_initializer='normal', activation='relu'))
#model.add(Dropout(0.3))
#model.add(Dense(100, input_dim = numvars, kernel_initializer='normal', activation='relu'))
#model.add(Dropout(0.3))
#model.add(Dense(50, kernel_initializer='normal', activation='relu'))
#model.add(Dropout(0.2))
model.add(Dense(50, input_dim = numvars, kernel_initializer='normal', activation='relu'))
#model.add(Dropout(0.2))
model.add(Dense(30, kernel_initializer='normal', activation='relu'))
#model.add(Dropout(0.2))
model.add(Dense(1, kernel_initializer='normal', activation='sigmoid'))



#model.add(Dense(100, input_dim = numvars, kernel_initializer='normal', activation='relu'))
##model.add(Dropout(0.3))
#model.add(Dense(50, kernel_initializer='normal', activation='relu'))
##model.add(Dropout(0.2))
#model.add(Dense(50, kernel_initializer='normal', activation='relu'))
##model.add(Dropout(0.2))
#model.add(Dense(30, kernel_initializer='normal', activation='relu'))
##model.add(Dropout(0.2))
#model.add(Dense(1, kernel_initializer='normal', activation='sigmoid'))

model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

model.summary()

# train model
history= model.fit(    data_train, labels_train, 
                       batch_size=len(data_train)/8,
                       epochs=100,
                       #epochs=200,
                       shuffle=True, 
                       validation_data = (data_test, labels_test) 
                   )

# save model
model.save("xtracks_NN_category.h5")




#########################################################
## plot

import matplotlib.pyplot as plt
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D as plt3d

import matplotlib as mpl
mpl.rcParams['figure.facecolor'] = 'white' 

#########################################################
## plot samples


range_ = ( (0, 10), (0, 10) )
fig = plt.figure(0, figsize=(12,12))

plt.subplot(2,2,1)
plt.title("Signal")
plt.xlabel("layer 0")
plt.ylabel("layer 1")
plt.hist2d(np.array(data_sig_train)[:,0], np.array(data_sig_train)[:,1], range=range_, bins=20, cmap=cm.coolwarm)

plt.subplot(2,2,2)
plt.title("Background")
plt.hist2d(np.array(data_bkg_train)[:,0], np.array(data_bkg_train)[:,1], range=range_, bins=20, cmap=cm.coolwarm)
plt.xlabel("layer 0")
plt.ylabel("layer 1")

#plt.subplot(2,2,3)
#plt.title("Signal")
#plt.xlabel("layer 2")
#plt.ylabel("layer 3")
#plt.hist2d(np.array(data_sig_train)[:,2], np.array(data_sig_train)[:,3], range=range_, bins=20, cmap=cm.coolwarm)

#plt.subplot(2,2,4)
#plt.title("Background")
#plt.hist2d(np.array(data_bkg_train)[:,2], np.array(data_bkg_train)[:,3], range=range_, bins=20, cmap=cm.coolwarm)
#plt.xlabel("layer 2")
#plt.ylabel("layer 3")



#########################################################
## validation plot

fig_validation = plt.figure(1, figsize=(12,12))

epochs = range(1, len(history.history["loss"])+1)
plt.plot(epochs, history.history["loss"], lw=3, label="Training loss")
plt.plot(epochs, history.history["val_loss"], lw=3, label="Validation loss")
plt.xlabel("Epoch"), plt.ylabel("Cross-entropy loss");



#########################################################
## plot structure of NN

#from keras.utils import plot_model, print_summary
#print_summary(model)

#plot_model(model, to_file='model_plot.png', show_shapes=True, show_layer_names=True)



##########################################################
#### ROC curve

from sklearn.metrics import roc_curve

labels_predicted_keras = model.predict(data_test).ravel()
false_positive_rates_keras, true_positive_rates_keras, thresholds_keras = roc_curve(labels_test, labels_predicted_keras)

#labels_predicted_keras = model.predict(data_train).ravel()
#false_positive_rates_keras, true_positive_rates_keras, thresholds_keras = roc_curve(labels_train, labels_predicted_keras)

from sklearn.metrics import auc
auc_keras = auc(false_positive_rates_keras, true_positive_rates_keras)

plt.figure(3)
plt.plot([0, 1], [0, 1], 'k--')
plt.plot(false_positive_rates_keras, true_positive_rates_keras, label='Keras (area = {:.3f})'.format(auc_keras))
plt.xlabel('False positive rate')
plt.ylabel('True positive rate')
plt.title('ROC curve')
plt.legend(loc='best')

# Zoom in view of the upper left corner.
plt.figure(4)
plt.xlim(0, 0.2)
plt.ylim(0.8, 1)
plt.plot([0, 1], [0, 1], 'k--')
plt.plot(false_positive_rates_keras, true_positive_rates_keras, label='Keras (area = {:.3f})'.format(auc_keras))
plt.xlabel('False positive rate')
plt.ylabel('True positive rate')
plt.title('ROC curve (zoomed in at top left)')
plt.legend(loc='best')



# HEP glossary
plt.figure(5)
plt.plot([0, 1], [1, 0], 'k--')
false_positive_one_minus_rates_keras = [ (1-value) for value in false_positive_rates_keras ]
plt.plot(true_positive_rates_keras, false_positive_one_minus_rates_keras)
plt.xlabel('Signal efficiency')
plt.ylabel('Background rejection')
plt.title('ROC curve')
plt.legend(loc='best')



#########################################################
## plots only at the end

plt.show()


