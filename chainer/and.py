# -*- coding: utf-8 -*-

# 参考 URL
# http://hi-king.hatenablog.com/entry/2015/06/27/194630

import random
import argparse
import numpy
import chainer
import chainer.optimizers

class SmallClassificationModel(chainer.FunctionSet):
	def __init__(self):
		"""
		利用する layer を記述
		"""
		super(SmallClassificationModel, self).__init__(
			# fc1 は 1 層目の layer
			fc1 = chainer.functions.Linear(2, 2),
			fc2 = chainer.functions.Linear(2, 2)
			)
	def _forward(self, x):
		"""
		layer 同士の結合を記述
		"""
		# h = self.fc1(x)
		h = self.fc2(chainer.functions.sigmoid(self.fc1(x)))
		return h

	def train(self, x_data, y_data):
		x = chainer.Variable(x_data.reshape(1, 2).astype(numpy.float32), volatile=False)
		y = chainer.Variable(y_data.astype(numpy.int32), volatile=False)
		h = self._forward(x)

		optimizer.zero_grads()
		# ロス関数
		error = chainer.functions.softmax_cross_entropy(h, y)
		error.backward()
		optimizer.update()

		print("x: {}".format(x.data))
		print("y: {}".format(h.data))
		print("h_class: {}".format(h.data.argmax()))

model = SmallClassificationModel()
optimizer = chainer.optimizers.MomentumSGD(lr=0.01, momentum=0.9)
optimizer.setup(model.collect_parameters())

data_and = [
	[numpy.array([0,0]), numpy.array([0])],
	[numpy.array([0,1]), numpy.array([0])],
	[numpy.array([1,0]), numpy.array([0])],
	[numpy.array([1,1]), numpy.array([1])]
]*1000

data_xor = [
	[numpy.array([0,0]), numpy.array([0])],
	[numpy.array([0,1]), numpy.array([1])],
	[numpy.array([1,0]), numpy.array([1])],
	[numpy.array([1,1]), numpy.array([0])]
]*1000

for invec, outvec in data_xor:
	model.train(invec, outvec)


