import pandas as pd
import numpy as np
import os
os.chdir("d:/lecture/AIrobotComputing")

all_data = pd.read_csv("BEST MOVIES of 2017.txt", sep="\t", index_col=0, header=None)

Comedy_bool = all_data[7].str.contains("Comedy")

comedy = all_data[Comedy_bool]

#arr_idx = []
#for i in range(len(all_data.iloc[:, 6])):
#    if 'Comedy' in all_data.iloc[i, 6]:
#        arr_idx.append(i)

comedy_sort = comedy.sort_values(by=4, ascending=False)

comedy_sort.to_csv("comedy_sort.csv", header=None)
