import mxnet as mx
import argparse

parser = argparse.ArgumentParser(description='MXNet Dense2 Microbenchmark')
parser.add_argument('--batch-size', '-b', type=int, help='batch size')
parser.add_argument('--input-size', '-i', type=int, help='input size')


if __name__ == '__main__':
    args = parser.parse_args()

    batch_size, input_size = args.batch_size, args.input_size
    state_size = 4 * input_size

    I = mx.sym.Variable('I')
    H = mx.sym.Variable('H')
    W_i2h = mx.sym.Variable('W_i2h')
    W_h2h = mx.sym.Variable('W_h2h')

    Y_I = mx.sym.FullyConnected(I, weight=W_i2h, num_hidden=state_size, no_bias=True)
    Y_H = mx.sym.FullyConnected(H, weight=W_h2h, num_hidden=state_size, no_bias=True)

    output = mx.sym.Group((Y_I, Y_H))

    exec = output.simple_bind(ctx=mx.gpu(), 
            I=(batch_size, input_size), 
            H=(batch_size, input_size),
            W_i2h=(state_size, input_size),
            W_h2h=(state_size, input_size))
    
    outputs = exec.forward(is_train=False, 
            I=mx.nd.ones(shape=(batch_size, input_size)),
            H=mx.nd.ones(shape=(batch_size, input_size)),
            W_i2h=mx.nd.ones(shape=(state_size, input_size)),
            W_h2h=mx.nd.ones(shape=(state_size, input_size)))

    print(outputs[0].asnumpy(), outputs[1].asnumpy())
