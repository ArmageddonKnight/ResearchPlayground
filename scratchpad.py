class A:
    def f(self):
        print("A")

class B(A):
    def f(self):
        super().f()
        print("B")

B().f()
