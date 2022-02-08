import numpy as np
import torch

I = np.array([[0, 0, 0, 0, 0],
              [0, 0, 1, 1, 1],
              [1, 1, 1, 1, 0],
              [0, 1, 1, 1, 0],
              [0, 0, 1, 0, 0]
              ])
J = np.array([[-1, -1, -1],
              [0, 0, 0],
              [1, 1, 1]])
I_conv_J = np.zeros(I.shape)

I_padded = np.pad(I, (1, 1))

for i in range(5):
    for j in range(5):
        for wi in range(3):
            for wj in range(3):
                I_conv_J[i, j] += I_padded[i + wi, j + wj] * J[wi, wj]

print(I_conv_J)
