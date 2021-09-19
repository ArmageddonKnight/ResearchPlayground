import abc

class A(abc.ABC):
    @abc.abstractmethod
    def f(self):
        pass

class B(A):
    def f(self, b):
        print(b)

B().f(3)
