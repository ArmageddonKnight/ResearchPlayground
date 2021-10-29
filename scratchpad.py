class A:
    def __del__(self):
        print("Object is deleted")
    def f(self):
        print("f")


def g():
    a = A()
    return a.f()

g()
print("Invoked g")
