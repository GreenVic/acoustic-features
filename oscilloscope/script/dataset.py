'''
Dataset utilties for Keras.

Keras script on Jupyter Notebook or the oscilloscope GUI uses 
these utilities to manipulate dataset.

Author: https://github.com/araobp

'''

import numpy as np
import sklearn.preprocessing as pp
import matplotlib.pyplot as plt
from keras.utils import to_categorical
from keras import models

import os
import time
import glob
import random
import pickle
import yaml

def plot_accuracy(history):
    '''
    Plot training & validation accuracy values for Keras output
    '''
    plt.plot(history.history['acc'])
    plt.plot(history.history['val_acc'])

    plt.title('Model accuracy')
    plt.ylabel('Accuracy')
    plt.xlabel('Epoch')
    plt.legend(['Train', 'Test'], loc='upper left')
    plt.show()

def plot_loss(history):
    '''
    Plot training & validation loss values for Keras output
    '''
    plt.plot(history.history['loss'])
    plt.plot(history.history['val_loss'])
    plt.title('Model loss')
    plt.ylabel('Loss')
    plt.xlabel('Epoch')
    plt.legend(['Train', 'Test'], loc='upper left')
    plt.show()

def plot_layer(activations, sample, layer, num_columns):
    '''
    Visualize convolution layers and pool layers
    '''
    a = activations[layer].shape
    rows = int(a[3]/num_columns)
    fig, axarr = plt.subplots(rows, num_columns, figsize=[4*num_columns,5])
    for i in range(a[3]):
        row = int(i/num_columns)
        x, y = row, i-num_columns*row
        axarr[x, y].imshow(np.rot90(activations[layer][sample, :, :, i]), cmap='gray')
        axarr[x, y].set_xticks([])
        axarr[x, y].set_yticks([])
    fig.subplots_adjust(left=0, right=1, bottom=0, top=1, hspace=0, wspace=0)
    fig.tight_layout()

def to_keras_input(data, labels, shape, cutout=None, flatten=False):
    '''
    Convert data into Keras input format
    '''
    keras_labels = []
    keras_data = []
    random.shuffle(data)
    for l, d in data:
        keras_labels.append(labels.index(l))
        keras_data.append(d)
    keras_data = np.array(keras_data, dtype='float')
    keras_data = keras_data.reshape(shape)
    if cutout:
        keras_data = keras_data[:,:,cutout[0]:cutout[1],:]
    if flatten:
        s = keras_data.shape
        keras_data = keras_data.reshape((s[0], s[1]*s[2]))
    keras_labels = to_categorical(keras_labels)
    return (keras_data, keras_labels)

class DataSet:
    '''
     - /dataset_folder --+-- /data/*.csv
                         |
                         +-- /dataset.yaml
                         |
                         +-- /class_labels.yaml
                         |
                         +-- /*.h5
    '''

    def __init__(self, dataset_folder):

        self.dataset_folder = dataset_folder    
        with open(dataset_folder + '/dataset.yaml') as f:
            attr = yaml.load(f)
        self.filters = attr['filters']
        self.files = attr['files']
        self.samples = attr['samples']
        self.length = attr['length']
        self.num_train_files = attr['training_files']
        self.num_test_files = self.files - self.num_train_files
        self.feature = attr['feature']
        self.stride = attr['stride']
        self.cutoff = attr['cutoff']
        if attr['model']:
            self.model = models.load_model(dataset_folder + '/' + attr['model'])
        else:
            self.model = None
        
        if not self.cutoff:
            self.cutoff = self.filters

        if self.feature == 'mfcc':
            self.shape = (self.length, self.cutoff-1)  # DC removed
        else:
            self.shape = (self.length, self.cutoff)

        # Generate windows
        windows = []
        a, b, i = 0, 0, 0
        while True:
            a, b = self.stride*i, self.stride*i+self.length
            if b > 200:
                break
            windows.append([a, b, self.cutoff])
            i += 1
        self.windows = windows

        # Note: "class_labels.yaml" is generated by serialize() method
        self.class_labels = None
        class_labels_file = dataset_folder + '/class_labels.yaml'
        if os.path.isfile(class_labels_file):
            with open(class_labels_file, 'r') as f:
                self.class_labels = yaml.load(f)
    
    def serialize(self):
        '''
        Merge all the csv files (raw data) into "merged.P" file
        with Python pickle module.
        '''
        merged = {}
        labels = []

        data_files = glob.glob(self.dataset_folder+'/data/*-features-*.csv')
        for file in data_files:
            params = file.split('-') 
            label = params[2]
            pos = params[3]
            try:
                pos = int(pos)
            except:
                pos = 0
            w = self.windows[pos]
            start = w[0] * self.filters
            end = w[1] * self.filters

            with open(file) as f:
                data = np.array(f.read().split(',')).astype(float)
                mfsc = data[:self.samples*self.filters][start:end]
                mfcc = data[self.samples*self.filters:][start:end]
            if label not in labels:
                labels.append(label)
                merged[label] = []
            merged[label].append([mfsc, mfcc])

        for label in labels:
            merged[label] = merged[label][:self.files]
        with open(self.dataset_folder+'/merged.P', 'wb') as f:
            pickle.dump(merged, f)
        with open(self.dataset_folder+'/class_labels.yaml', 'w') as f:
            yaml.dump(labels, f)
        
    def _load(self):
        with open(self.dataset_folder+'/merged.P', 'rb') as f:
            data_set = pickle.load(f)
        return data_set
   
    def generate(self, update=True, flatten=False):
        '''
        Note:
        This method assumes that pickled object "merged.P" exists in the dataset directory.
        Execute serialize() before this method for the first time to merge all the csv files
        into "merged.P".
        '''
        train_data_mfsc = []
        train_data_mfcc = []
        test_data_mfsc = []
        test_data_mfcc = []
        
        # Merge all the csv files into "merge.P"
        if update:
            self.serialize()

        # Load "merge.P"
        data_set = self._load()
        labels = list(data_set.keys())

        # Shuffle for train data set and test data set
        for label in labels:
            random.shuffle(data_set[label])
            train = data_set[label][:self.num_train_files]
            test = data_set[label][self.num_train_files:]
            for d in train:
                train_data_mfsc.append([label, d[0]])
                train_data_mfcc.append([label, d[1]])
            for d in test:
                test_data_mfsc.append([label, d[0]])
                test_data_mfcc.append([label, d[1]])
        features = {}
        shape_train = (self.num_train_files*len(labels), self.length, self.filters, 1)
        shape_test = (self.num_test_files*len(labels), self.length, self.filters, 1)
        features['mfsc'] = [*(to_keras_input(train_data_mfsc, labels, shape_train)),
                            *(to_keras_input(test_data_mfsc, labels, shape_test))]
        shape_train = (self.num_train_files*len(labels), self.length, self.filters, 1)
        shape_test = (self.num_test_files*len(labels), self.length, self.filters, 1)
        features['mfcc'] = [*(to_keras_input(train_data_mfcc, labels, shape_train, cutout=(1, self.cutoff), flatten=flatten)),
                            *(to_keras_input(test_data_mfcc, labels, shape_test, cutout=(1, self.cutoff), flatten=flatten))]

        return features

    def count_class_labels(self):
        '''
        Count the number of csv files for each class
        '''

        data_files = glob.glob(self.dataset_folder + '/data/*features*.csv')
        class_labels = {}

        for file in data_files:
            label = file.replace('\\', '/').split('/')[-1].split('-')[2]
            if label not in class_labels:
                class_labels[label] = 1
            else:
                class_labels[label] = class_labels[label] + 1

        return class_labels
