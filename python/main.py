from typing import Tuple

import torch
from torch.autograd import Function
from torch.autograd.function import FunctionCtx


class MulConstant(Function):
    @staticmethod
    def forward(  # type: ignore[override]
        x: torch.Tensor, constant: int
    ) -> torch.Tensor:
        return x * constant

    @staticmethod
    def setup_context(
        ctx: FunctionCtx, inputs: Tuple[torch.Tensor, int], output: torch.Tensor
    ) -> None:
        _, constant = inputs
        ctx.constant = constant  # type: ignore[attr-defined]

    @staticmethod
    def backward(  # type: ignore[override]
        ctx: FunctionCtx, grad_y: torch.Tensor
    ) -> Tuple[torch.Tensor, None]:
        return grad_y * ctx.constant, None  # type: ignore[attr-defined]


print(MulConstant.apply(torch.tensor(3, dtype=torch.float32), 4))

x = torch.tensor(3, dtype=torch.float32)
x.requires_grad_(True)
y = x * 4
y.backward()
print(x._grad)
