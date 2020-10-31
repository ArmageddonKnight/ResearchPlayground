import pytest


@pytest.mark.parametrize("A,B", [(8, 8), (9, 9), (10, 10)])
def test_eval(A, B):
    assert A == B
