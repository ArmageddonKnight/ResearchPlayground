import copy
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('--stride', type=int, nargs=2, default=(2, 2))
args = parser.parse_args()
print(args.stride)


def factorize(f, depth, factors, stack=[], remainder=None):
    if depth == 1:
        import copy

        stack.append(remainder)
        factors.append(copy.deepcopy(stack))
        stack.pop(-1)
        return
    if remainder is None:
        remainder = f
    for i in range(1, remainder + 1):
        if remainder % i != 0:
            continue
        stack.append(i)
        factorize(f, depth - 1, factors, stack, remainder // i)
        stack.pop(-1)


factors = []

factorize(2, 5, factors, [])
print(factors)

factors = []

factorize(4, 5, factors, [])
print(factors)
