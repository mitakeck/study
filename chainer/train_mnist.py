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

# 学習用データを N 個, 検証用データを残りの個数と設定
N = 60000
x_train, x_test = np.split(mnist.data, [N])
y_train, y_test = np.split(mnist.target, [N])
N_test = y_test.size

# 多層パーセプトロンモデルの設定
model = FunctionSet(
	l1 = F.Linear(784, n_units),
	l2 = F.Linear(n_units, n_units),
	l3 = F.Linear(n_units, 10))

# ニューラルネットの構造
def forward(x_data, y_data, train=True):
	# 配列から Chainer の Variable 型に変換
	x, t = Variable(x_data), Variable(y_data)
	# F.relu = max(0, x)
	h1 = F.dropout(F.relu(model.l1(x)), train=train)
	h2 = F.dropout(F.relu(model.l2(h1)), train=train)
	y = model.l3(h2)
	return F.softmax_cross_entropy(y, t), F.accuracy(y, t)

optimizer = optimizers.Adam()
optimizer.setup(model.collect_parameters())



#########


train_loss = []
train_acc = []
test_loss = []
test_acc = []

for epoch in xrange(1, n_epoch+1):
	print 'epoch: {}'.format(epoch)

	perm = np.random.permutation(N)
	sum_accuracy = 0
	sum_loss = 0
	for i in xrange(0, N, batchsize):
		x_batch = x_train[perm[i:i+batchsize]]
		y_batch = y_train[perm[i:i+batchsize]]

		optimizer.zero_grads()
		loss, acc = forward(x_batch, y_batch)
		loss.backward()
		optimizer.update()

		train_loss.append(loss.data)
		train_acc.append(acc.data)
		sum_loss += float(cuda.to_cpu(loss.data)) * batchsize
		sum_accuracy += float(cuda.to_cpu(acc.data)) * batchsize

	print 'train mean loss={}, accuracy={}'.format(sum_loss/N, sum_accuracy/N)

	sum_accuracy = 0
	sum_loss = 0
	for i in xrange(0, N_test, batchsize):
		x_batch = x_test[i:i+batchsize]
		y_batch = y_test[i:i+batchsize]
		loss, acc = forward(x_batch, y_batch, train=False)
		test_loss.append(loss.data)
		test_acc.append(acc.data)
		sum_loss += float(cuda.to_cpu(loss.data)) * batchsize
		sum_accuracy += float(cuda.to_cpu(acc.data)) * batchsize

	print 'test mean loss={}, accuracy={}'.format(sum_loss/N, sum_accuracy/N)

plt.figure(figsize=(8, 6))
plt.plot(range(len(train_acc)), train_acc)
plt.plot(range(len(test_acc)), test_acc)
plt.legend(["train_acc", "test_acc"], loc=4)
plt.title("Accuracy of digit recognition.")
plt.show()




