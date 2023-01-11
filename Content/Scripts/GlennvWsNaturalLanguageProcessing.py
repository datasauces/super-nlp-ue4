
#converted for ue4 use from
#https://github.com/tensorflow/docs/blob/master/site/en/tutorials/_index.ipynb

from __future__ import print_function
from subprocess import call

def installPip(log=print):
    """
    Pip is the standard package manager for Python. Starting with Python 3.4
    it's included in the default installation, but older versions may need to
    download and install it. This code should pretty cleanly do just that.
    """
    log("Installing pip, the standard Python Package Manager, first")
    from os     import remove
    from urllib import urlretrieve
    urlretrieve("https://bootstrap.pypa.io/get-pip.py", "get-pip.py")
    call(["python", "get-pip.py"])

    # Clean up now...
    remove("get-pip.py")

def getPip(log=print):
    """
    Pip is the standard package manager for Python.
    This returns the path to the pip executable, installing it if necessary.
    """
    from os.path import isfile, join
    from sys     import prefix
    # Generate the path to where pip is or will be installed... this has been
    # tested and works on Windows, but will likely need tweaking for other OS's.
    # On OS X, I seem to have pip at /usr/local/bin/pip?
    pipPath = join(prefix, 'Scripts', 'pip.exe')

    # Check if pip is installed, and install it if it isn't.
    if not isfile(pipPath):
        installPip(log)
        if not isfile(pipPath):
            raise("Failed to find or install pip!")
    return pipPath

def installIfNeeded(moduleName, nameOnPip=None, notes="", log=print):
    """ Installs a Python library using pip, if it isn't already installed. """
    from pkgutil import iter_modules

    # Check if the module is installed
    if moduleName not in [tuple_[1] for tuple_ in iter_modules()]:
        log("Installing " + moduleName + notes + " Library for Python")
        call([getPip(log), "install", nameOnPip if nameOnPip else moduleName])


installIfNeeded("nltk")
installIfNeeded("gensim")
installIfNeeded("pandas")

from gensim.models import Word2Vec, KeyedVectors
#import pandas as pd
import nltk

import tensorflow as tf
import unreal_engine as ue
from TFPluginAPI import TFPluginAPI

#additional includes
from tensorflow.python.keras import backend as K	#to ensure things work well with multi-threading
from tensorflow import keras
import numpy as np   	#for reshaping input
import operator      	#used for getting max prediction from 1x10 output array
import random
import os

scripts_path = ue.get_content_dir() + "Scripts"
word2vec_dir = scripts_path + '/GoogleNews-vectors-negative300.bin'
word2vecmodel = KeyedVectors.load_word2vec_format(word2vec_dir, binary=True, limit=100000)




class KerasBackProp(TFPluginAPI):

	#keras stop callback
	class StopCallback(tf.keras.callbacks.Callback):
		def __init__(self, outer):
			self.outer = outer
			self.monitor = 'acc'
			self.value = 1
			self.verbose = 0
			
		def on_train_begin(self, logs={}):
			self.losses = []

		#def on_batch_end(self, batch, logs={}):
		def on_epoch_end(self, epoch, logs={}):
			if(self.outer.shouldStop):
				#notify on first call
				if not (self.model.stop_training):
					ue.log('Early stop called!')
				self.model.stop_training = True

			else:
				#json convertible types are float64 not float32
				logs['acc'] = np.float64(logs['acc'])
				accuracy = np.float64(logs['acc'])
				logs['loss'] = np.float64(logs['loss'])
				self.outer.callEvent("AccuracyUpdate", logs['acc'], True)
				self.outer.callEvent('TrainingUpdateEvent', logs, True)
					
			current = logs.get(self.monitor)
			if current is None:
				warnings.warn("Early stopping requires %s available!" % self.monitor, RuntimeWarning)

			if current >= self.value:
				if self.verbose > 0:
					print("Epoch %05d: early stopping THR" % epoch)
				self.model.stop_training = True

	#Called when TensorflowComponent sends Json input
	def onJsonInput(self, jsonInput):
		#build the result object
		result = {'word0':-1,}

		#If we try to predict before training is complete
		if not hasattr(self, 'model'):
			ue.log_warning("Warning! No 'model' found, prediction invalid. Did training complete?")
			return result

		#prepare the input
		
		#these are float values passed through the json from unreal to python
		actionindex = jsonInput['actionindex']
		word0 = jsonInput['word0']
		word1 = jsonInput['word1']
		word2 = jsonInput['word2']
		word3 = jsonInput['word3']
		word4 = jsonInput['word4']
		word5 = jsonInput['word5']
		word6 = jsonInput['word6']
		word7 = jsonInput['word7']
		word8 = jsonInput['word8']
		word9 = jsonInput['word9']
		inputarray = [word0,word1,word2,word3,word4,word5,word6,word7,word8,word9]
		ue.log(repr(inputarray))
		self.callEvent(str(repr(inputarray)), {}, True)
		inputarray_word2vec = np.zeros((1,10,300))
		
		ue.log("Print Word2Vec Input:")
		self.callEvent(str(repr(inputarray)), {}, True)
		
		for	index in range(10):
			try:
				inputarray_word2vec[0][index] = word2vecmodel[inputarray[index]]
				ue.log(repr(inputarray_word2vec[0][index]))
				ue.log("valid word")
			except:
				#inputarray_word2vec[0][index] = np.random.uniform(low=-1, high=1, size=300)
				ue.log("invalid word")
				#self.callEvent("word2vec failed, entered non-words", {}, True)
		index+=1
		
		inputarray_word2vec = np.asarray(inputarray_word2vec)
		
		ue.log("Print CNN Input:")
		ue.log(repr(inputarray_word2vec))
		
		#run the input through our network using stored model and graph
		with self.graph.as_default():
			ue.log("Start Predict")
			output = self.model.predict(inputarray_word2vec)
			ue.log(repr(output))
			self.callEvent("SetTempID", actionindex, True)
			self.callEvent("JsonOutput", output.tolist(), True)
			ue.log("Finished Predict")

	#Called when TensorflowComponent signals begin training (default: begin play)
	def onBeginTraining(self):
		ue.log("starting KerasBackProp training")
	
		#Load model from 		scripts_path + '/my_model.h5'
		try:
			ue.log("Try loading model")
			tf.keras.backend.clear_session()
			model = tf.keras.models.load_model(scripts_path + '/my_model.h5')