import mxnet as mx

import argparse

parser = argparse.ArgumentParser(description='MXNet Dense2 Microbenchmark')
parser.add_argument('--batch-size', '-b', 
        type=int, help='batch size')
parser.add_argument('--input-size', '-i',
        type=int, help='input size')


if __name__ == '__main__':
    args = parser.parse_args()

    batch_size, input_size = \
            args.batch_size, \
            args.input_size
    state_size = 4 * input_size

    I = mx.symbol.Variable('I')
    H = mx.symbol.Variable('H')

    
