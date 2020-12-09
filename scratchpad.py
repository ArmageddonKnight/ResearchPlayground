def A(a, b, c):
    print(a, b, c)


def B():
    return 2, 3


A(*B(), 3)
