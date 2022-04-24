from argparse import ArgumentParser
from enum import Enum


class ExecMode(Enum):
    kRun = 'run'
    kProfile = 'profile'
    kExport = 'export'

    def __str__(self):
        return self.value

parser = ArgumentParser()
parser.add_argument('--mode', type=ExecMode, choices=list(ExecMode),
                    default=ExecMode.kRun)

args = parser.parse_args()
print(f"Execution Mode: {args.mode}")


if __name__ == '__main__':
    class A:
        pass
