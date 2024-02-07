import pytest


@pytest.fixture()
def some_fixture() -> int:
    print("Creating some fixture")
    return 1
