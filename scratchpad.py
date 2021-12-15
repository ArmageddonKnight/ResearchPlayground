import numpy as np

Vendor   = np.array([0.67, 0.95, 0.82, 0.64, 0.75])
Ansor    = np.array([1.00, 1.00, 1.00, 1.00, 1.00])
DietCode = np.array([0.99, 1.10, 1.01, 1.01, 1.18])
W = np.array([16, 23, 25, 28, 32])

print("{}, {}".format(np.sum(DietCode) / np.sum(Vendor), np.sum(DietCode) / np.sum(Ansor)))
print("{}, {}".format(np.sum(DietCode * W) / np.sum(Vendor * W), np.sum(DietCode * W) / np.sum(Ansor * W)))
print("{}, {}".format(np.sum(W / Vendor) / np.sum(W / DietCode), np.sum(W / Ansor) / np.sum(W / DietCode)))
