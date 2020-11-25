import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("stats/stats1.csv")
oneThread = np.array(data["one_thread"])
twoThreads = np.array(data["two_threads"])
threeThreads = np.array(data["three_threads"])
fourThreads = np.array(data["four_threads"])
fiveThreads = np.array(data["five_threads"])
sixThreads = np.array(data["six_threads"])

means = [np.mean(oneThread),
         np.mean(twoThreads),
         np.mean(threeThreads),
         np.mean(fourThreads),
         np.mean(fiveThreads),
         np.mean(sixThreads)]

stds = [np.std(oneThread),
        np.std(twoThreads),
        np.std(threeThreads),
        np.std(fourThreads),
        np.std(fiveThreads),
        np.std(sixThreads)]

fig1 = plt.figure(figsize=(10,10))

X = [i for i in range(2,14,2)]

plt.errorbar(X, means, stds, fmt='.-', capsize=5, ecolor='red')

plt.xlabel('Nombre de philosphe')
plt.ylabel('Temps [sec]')
            
plt.xlim(0,len(X)+1)
plt.ylim(0, round(max(means)+max(stds)+1))

plt.xticks(np.linspace(0, 2*len(X)+2,  len(X)+2))
plt.yticks(np.linspace(0,round(max(means)+max(stds)+1),11))

plt.grid(True)
plt.title("Problemes des philosophes")
plt.savefig("img/philo.png")
plt.savefig("img/philo.pdf")

plt.show()
plt.close()
