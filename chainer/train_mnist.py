# -*- coding:utf-8 -*-
# %matplotlib inline
import matplotlib.pyplot as plt
import numpy as np
from sklearn.datasets import fetch_mldata
from chainer import cuda, Variable, FunctionSet, optimizers
import chainer.functions  as F
import sys

# plt.style.use('ggplot')

batchsize = 100
n_epoch = 20
n_units = 1000

print 'fetch MNIST dataset'
mnist = fetch_mldata('MNIST original')
mnist.data = mnist.data.astype(np.float32)
mnist.data /= 255
mnist.target = mnist.target.astype(np.int32)


def draw_digit(data):
	size = 28
	plt.figure(figsize=(2.5, 3))

	X, Y = np.meshgrid(range(size), range(size))
	Z = data.reshape(size, size)
	Z = Z[::-1,:]
	plt.xlim(0, 27)
	plt.ylim(0, 27)
	plt.pcolor(X, Y, Z)
	plt.gray()
	plt.tick_params(labelbottom="off")
	plt.tick_params(labelleft="off")
	plt.show()

draw_digit(mnist.data[5])
draw_digit(mnist.data[12345])
draw_digit(mnist.data[33455])
