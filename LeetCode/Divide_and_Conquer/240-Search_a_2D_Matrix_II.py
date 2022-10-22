import numpy as np


def searchMatrix(matrix, target):
    # The idea is to move from the TOP LEFT corner and start moving leftward and
    # downward.
    m, n = 1, matrix.shape[1]

    while True:
        print(m, n)
        if matrix[m - 1, n - 1] == target:
            return True
        elif matrix[m - 1, n - 1] > target:
            n = n - 1
        elif matrix[m - 1, n - 1] < target:
            m = m + 1
        if n == 0 or m == (matrix.shape[0] + 1):
            return False


A = np.array(
    [
        [1, 4, 7, 11, 15],
        [2, 5, 8, 12, 19],
        [3, 6, 9, 16, 22],
        [10, 13, 14, 17, 24],
        [18, 21, 23, 26, 30],
    ],
    dtype=np.int32,
)

print(searchMatrix(A, 5))
