import numpy as np


def searchMatrix(matrix, target):
    # The idea is to move from the TOP LEFT corner and start moving leftward and
    # downward.
    pass


A = np.array(
    [
        [1, 4, 7, 11, 15],
        [2, 5, 8, 12, 19],
        [3, 6, 9, 16, 22],
        [10, 13, 14, 17, 24],
        [18, 21, 23, 26, 30],
    ],
    dtype=np.float32,
)

print(searchMatrix(A, 5))
