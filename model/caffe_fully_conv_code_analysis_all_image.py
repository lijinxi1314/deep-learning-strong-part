import numpy as np
import matplotlib.pyplot as plt
caffe_root='/home/mima375029938/caffe/'
import sys
sys.path.insert(0,caffe_root+'python')
import caffe
net = caffe.Net('/home/mima375029938/caffe_lll/deploy.prototxt', 
                '/home/mima375029938/caffe_lll/p1_alexnet_finetune__iter_10000.caffemodel', 
                caffe.TEST)
params = ['fc6', 'fc7', 'fc8_pd']
# fc_params = {name: (weights, biases)}
fc_params = {pr: (net.params[pr][0].data, net.params[pr][1].data) for pr in params}

#for fc in params:
#    print ('{} weights are {} dimensional and biases are {} dimensional'.format(fc, fc_params[fc][0].shape, fc_params[fc][1].shape))

net_full_conv = caffe.Net('/home/mima375029938/caffe_lll/deploy2.prototxt', 
                '/home/mima375029938/caffe_lll/p1_alexnet_finetune__iter_10000.caffemodel', 
                caffe.TEST)
params_full_conv = ['conv6', 'conv7', 'conv8_pd']
# fc_params = {name: (weights, biases)}
conv_params = {pr: (net_full_conv.params[pr][0].data, net_full_conv.params[pr][1].data) for pr in params_full_conv}

#for conv in params_full_conv:
#    print ('{} weights are {} dimensional and biases are {} dimensional'.format(conv, conv_params[conv][0].shape, conv_params[conv][1].shape))

for pr, pr_conv in zip(params, params_full_conv):
    conv_params[pr_conv][0].flat = fc_params[pr][0].flat  
    conv_params[pr_conv][1][...] = fc_params[pr][1]
net_full_conv.save('/home/mima375029938/caffe_lll/p1_alexnet_finetune__iter_10000__full_conv.caffemodel')



import os
path='/home/mima375029938/caffe_lll/images'
labels_file="/home/mima375029938/caffe_lll/predict_result_2.txt"
x=[]
files=os.listdir(path)
for file in files:
    if not os.path.isdir(file):
        im = caffe.io.load_image(file)
        transformer = caffe.io.Transformer({'data': net_full_conv.blobs['data'].data.shape})
        transformer.set_mean('data', np.load('/home/mima375029938/caffe/python/caffe/imagenet/ilsvrc_2012_mean.npy').mean(1).mean(1))
        transformer.set_transpose('data', (2,0,1))
        transformer.set_channel_swap('data', (2,1,0))
        transformer.set_raw_scale('data', 255.0)
# make classification map by forward and print prediction indices at each location
        out = net_full_conv.forward_all(data=np.asarray([transformer.preprocess('data', im)]))
        #print (out['prob'][0,1])
        #print (file)
        line= out['prob'][0,1]
        x.append(line)
print (x)
np.savetxt(labels_file,x,fmt='%s',newline='\n')
        #np.savetxt(labels_file,out['prob'][0,1],fmt='%s',newline=' ')

#labels_file="/home/mima375029938/caffe_lll/predict_result_2.txt"   newline=''
#np.savetxt(labels_file,out['prob'][0,1],fmt='%s',newline=' ')



