import tensorflow as tf
import numpy as np

import argparse

parser = argparse.ArgumentParser(description='Tensorflow Dense2 Microbenchmark')
parser.add_argument('--batch-size', '-b', type=int, help='batch size')
parser.add_argument('--input-size', '-i', type=int, help='input size')


if __name__ == '__main__':
    args = parser.parse_args()

    batch_size, input_size = args.batch_size, args.input_size
    state_size = 4 * input_size

    I = tf.placeholder(shape=[batch_size, input_size], dtype=tf.float32)
    H = tf.placeholder(shape=[batch_size, input_size], dtype=tf.float32)

    W_i2h = tf.Variable(tf.ones(shape=[state_size, input_size]))
    W_h2h = tf.Variable(tf.ones(shape=[state_size, input_size]))

    Y_I = tf.matmul(I, W_i2h, transpose_b=True)
    Y_H = tf.matmul(H, W_h2h, transpose_b=True)

    with tf.Session() as sess:
        sess.run(tf.global_variables_initializer())
        Y_I, Y_H = sess.run((Y_I, Y_H), 
                feed_dict={
                    I : np.ones(shape=[batch_size, input_size]),
                    H : np.ones(shape=[batch_size, input_size])})
        print(Y_I, Y_H)
