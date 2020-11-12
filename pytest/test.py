import pytest


@pytest.mark.parametrize("A,B", [(8, 8), (9, 9), (10, 10)])
def test_eval(A, B):
    assert A == B


@pytest.fixture(scope="class", params=[('A', 'B'), ('B', 'C'), ('C', 'D')])
def n(request):
    print('setup once per each param', request.param)
    a, b = request.param
    print(a, b)
    return request.param[0]


class TestFoo:
    def test_something(self, n):
        print(n)
        assert n != 'D'


class MXFixture:
    __slots__ = 'in_arg_shapes', 'in_args_np', 'out_np_expected', 'out_shape', \
                'head_grad_np', 'arg_grads_np_expected'


@pytest.fixture(scope='class', params=[(1, 2, 3, 4)])
def mx_fixture(request):
    B, C, H, W = request.param
    ret = MXFixture()
    ret.in_arg_shapes = [(B, C, H, W), (C,), (C,)]
    return ret


def test_tvm(mx_fixture):
    print(mx_fixture.in_arg_shapes)


@pytest.yield_fixture
def passwd():
    return 0

def test_passwd(passwd):
    for i in range(5):
        print(passwd)


class B:
    __slots__ = 'b'
    def __init__(self):
        self.b = 10


class A:
    __slots__ = 'a'
    def __init__(self):
        self.a = [B()] * 5
    def __setitem__(self, i, v):
        print("setitem")
        self.a[i] = v
    def __getitem__(self, i):
        print("getitem")
        return self.a[i]

def test_A():
    a = A()
    a[2].b = 5
    print(a[2].b)
