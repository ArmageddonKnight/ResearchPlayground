#!/usr/bin/python3
"""
MXNet Benchmark on Batch Normalization
"""
import mxnet as mx
import argparse
import ctypes

parser = argparse.ArgumentParser(description="MXNet BatchNorm Microbenchmark")
parser.add_argument('--batch-size', '-b', type=int, help='batch size')
parser.add_argument('--input-size', '-i', type=int, help='input size')
_cudart = ctypes.CDLL('libcudart.so')


if __name__ == '__main__':
    args = parser.parse_args()

    batch_size, input_size = args.batch_size, args.input_size
    state_size = 4 * input_size

    I = mx.sym.Variable('I')
    W_i2h = mx.sym.Variable('W_i2h')

    Y_I = mx.sym.FullyConnected(I, 
            weight=W_i2h,
            no_bias=True,
            num_hidden=state_size)
    # Y_I = mx.sym.BatchNorm(Y_I)

    exec = Y_I.simple_bind(ctx=mx.gpu(), 
                I=(batch_size, input_size), 
            W_i2h=(state_size, input_size))
    
    exec.forward(is_train=False, 
                I=mx.nd.ones(shape=(batch_size, input_size)),
            W_i2h=mx.nd.ones(shape=(state_size, input_size)))

    mx.nd.waitall()
