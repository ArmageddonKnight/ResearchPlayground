def A(a, b, c):
    print(a, b, c)


def B():
    return 2, 3


A(*B(), 3)

A = [1, 2, 3]

for a in A:
    if a == 3:
        A.append(4)
    print(a)
