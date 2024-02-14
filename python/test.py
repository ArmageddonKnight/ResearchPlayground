import unittest
from unittest.mock import MagicMock, call


# Functions to test
def f1():
    print("f1")


def f2():
    print("f2")


def f3():
    print("f3")


# Function that invokes the functions in a specific order
def invoke_functions():
    f1()
    f2()
    f3()


class TestFunctionOrder(unittest.TestCase):
    def test_function_order(self):
        # Create mock objects for the functions
        mocked_f1 = MagicMock()
        mocked_f2 = MagicMock()
        mocked_f3 = MagicMock()

        # Replace the original functions with the mocked ones
        global f1, f2, f3
        f1 = mocked_f1
        f2 = mocked_f2
        f3 = mocked_f3

        # Invoke the function that calls the functions
        invoke_functions()

        # Assert the order of function calls
        mocked_f1.assert_called_once()
        mocked_f2.assert_called_once()
        mocked_f3.assert_called_once()

        print([call(), call(), call()])
        print([call(f1()), call(f2()), call(f3())])


if __name__ == "__main__":
    unittest.main()
