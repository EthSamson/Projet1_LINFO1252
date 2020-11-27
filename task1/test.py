import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("stats/stats1.csv")
# Getting shape of the df 
shape = data.shape 
  
# Printing Number of columns 
print('Number of columns :', shape[1])

