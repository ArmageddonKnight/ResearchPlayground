import unittest.mock
from functools import partial

import pytest


@pytest.mark.parametrize(
    "a", [1, 2, 3]
)
class TestA:
    @pytest.fixture()
    def fixture(self, a):
        return a
    
    def test_foo(self, fixture):
        print(fixture)


mock = unittest.mock.MagicMock()

mock_call = partial(mock.__call__, 3)

mock(1, 2, 3)
mock_call(4)
print(mock.mock_calls)
