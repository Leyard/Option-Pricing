import numpy as np
from scipy.stats import norm
import matplotlib.pyplot as plt

sample = []
n = 10000
init = 0.1
for _ in range(n):
    prop = np.random.normal(loc=init)
    if (np.random.uniform() < norm.pdf(prop)/norm.pdf(init)):
        sample.append(prop)
        print(prop)
        init = prop
    else:
        sample.append(init)
        print(init)

plt.figure(figsize=(4, 4))
plt.hist(sample, bins=100, edgecolor='white')
plt.show()

