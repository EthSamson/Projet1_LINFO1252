import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data1 = pd.read_csv("task1/stats/philo.csv")
data2 = pd.read_csv("task2/stats/philo.csv")

#Traitement du fichier csv des philosophes(posix)
oneThread1 = np.array(data1["one_thread"])
twoThreads1 = np.array(data1["two_threads"])
threeThreads1 = np.array(data1["three_threads"])
fourThreads1 = np.array(data1["four_threads"])
fiveThreads1 = np.array(data1["five_threads"])
sixThreads1 = np.array(data1["six_threads"])

means1 = [np.mean(oneThread1),
          np.mean(twoThreads1),
          np.mean(threeThreads1),
          np.mean(fourThreads1),
          np.mean(fiveThreads1),
          np.mean(sixThreads1)]

stds1 = [np.std(oneThread1),
        np.std(twoThreads1),
        np.std(threeThreads1),
        np.std(fourThreads1),
        np.std(fiveThreads1),
        np.std(sixThreads1)]

#Traitement du fichier csv des philosophes(my_mutex)
oneThread2 = np.array(data2["one_thread"])
twoThreads2 = np.array(data2["two_threads"])
threeThreads2 = np.array(data2["three_threads"])
fourThreads2 = np.array(data2["four_threads"])
fiveThreads2 = np.array(data2["five_threads"])
sixThreads2 = np.array(data2["six_threads"])

means2 = [np.mean(oneThread2),
          np.mean(twoThreads2),
          np.mean(threeThreads2),
          np.mean(fourThreads2),
          np.mean(fiveThreads2),
          np.mean(sixThreads2)]

stds2 = [np.std(oneThread2),
        np.std(twoThreads2),
        np.std(threeThreads2),
        np.std(fourThreads2),
        np.std(fiveThreads2),
        np.std(sixThreads2)]

philo = plt.figure()

shape = data1.shape
X = range(2,2*(shape[1]), 2)

plt.errorbar(X, means1, stds1, fmt='.-', capsize=5, ecolor='black', label="Philosophes tâche 1")
plt.errorbar(X, means2, stds2, fmt='.-', capsize=5, ecolor='grey', label="Philosophes tâche 2")

plt.xlabel("Nombre de philosphes")
plt.xlim(0, 2*len(X)+1)

plt.ylabel("Temps [sec]")
plt.ylim(0, max(round(max(means1)+max(stds1)+1),round(max(means2)+max(stds2)+1)))

plt.grid(True)
plt.title("Evaluation du problème des philosophes")
plt.legend()
plt.savefig("img/philo.png")
plt.savefig("img/philo.pdf")

plt.show()
plt.close()
