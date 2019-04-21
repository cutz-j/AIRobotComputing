### programming 1&2 ###
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

file_open = open("d:/data/python_pros_and_cons.txt", "r")
text = file_open.readline()
file_open.close()


res = text[text.count("language"):text.count("Python")]

## programming 2 ##
all_data = pd.read_csv("d:/data/Best MOVIES of 2017.txt", sep="\t",
                       header=None, index_col=0)
genre = all_data.iloc[:,6]
all_data_comedy = all_data[genre.str.contains("Comedy")]
res = all_data_comedy.sort_values(by=4, ascending=False)

  
### PIL&matplotlib ###
from PIL import Image

file_open = Image.open("d:/data/colorwheel.png").convert("RGB")
arr = np.array(file_open)
file_open.show()

target = np.array([254, 39, 18])
copy = np.zeros_like(arr)

for i in range(arr.shape[0]):
    for j in range(arr.shape[1]):
        if (arr[i,j,0]==target[0]) & (arr[i,j,1]==target[1]) & (arr[i,j,2]==target[2]):
            copy[i,j,:] = arr[i,j,:]
        
image_res = Image.fromarray(copy)
image_res.show()

## programming 2 ##
quarter1 = arr[:240, :240, :].copy()
quarter3 = arr[240:, 240:, :].copy()
copy = np.copy(arr)

quarter1 = np.flip(quarter1, axis=0)
quarter1 = np.flip(quarter1, axis=1)
quarter3 = np.flip(quarter3, axis=0)
quarter3 = np.flip(quarter3, axis=1)

arr[:240, :240, :] = quarter3
arr[240:, 240:, :] = quarter1

image_res = Image.fromarray(arr)
image_res.show()

### SVD ###
lenna = Image.open("d:/data/lenna/Lenna.png").convert("RGB")
arr = np.array(lenna).astype(np.float32)
res_arr = np.zeros_like(arr)

k = 20
for i in range(3):
    U, D, V = np.linalg.svd(arr[:,:,i])
    res_arr[:,:,i] = np.matrix(U[:,:k]) * np.diag(D[:k]) * np.matrix(V[:k,:])


res_arr[res_arr > 255] = 255
res_arr[res_arr < 0] = 0    
res = Image.fromarray(res_arr.astype('uint8'))
res.show()