import torch

device = torch.device('cuda')

import argparse

parser = argparse.ArgumentParser(description='PyTorch Dense2 Microbenchmark')
parser.add_argument('--batch-size', '-b', type=int, help='batch size')
parser.add_argument('--input-size', '-i', type=int, help='input size')


if __name__ == '__main__':
    args = parser.parse_args()

    batch_size, input_size = args.batch_size, args.input_size
    state_size = 4 * input_size

    I = torch.ones(batch_size, input_size, device=device)
    H = torch.ones(batch_size, input_size, device=device)

    W_i2h = torch.ones(state_size, input_size, device=device)
    W_h2h = torch.ones(state_size, input_size, device=device)

    Y_I = torch.matmul(I, W_i2h.t())
    Y_H = torch.matmul(H, W_h2h.t())
