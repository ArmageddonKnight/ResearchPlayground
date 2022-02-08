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
I = np.reshape(I, (1, 1, 5, 5))
J = np.reshape(J, (1, 1, 3, 3))
conv2d_layer = torch.nn.Conv2d(1, 1, kernel_size=3, padding=1,
                               bias=False)
conv2d_layer.weight = torch.nn.Parameter(torch.Tensor(J))
I = torch.Tensor(I)
print(conv2d_layer(I))