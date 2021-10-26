class A:

    @property
    def a(self):
        return 1

o = A()
print([attr if isinstance(attr, property) else None for attr in dir(o)])

d = {k: getattr(o, k, '') for k in o.__dir__() if k[:2] != '__' and type(getattr(o, k, '')).__name__ != 'method'}
print(d)
