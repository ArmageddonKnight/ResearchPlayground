import torch


A = {"123": None}

torch.save(torch.tensor(456), "tmp.pt")

item = A["123"]
item.copy_(torch.load("tmp.pt"))
print(A)
