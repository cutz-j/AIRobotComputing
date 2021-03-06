import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.decomposition import TruncatedSVD
import os

lenna = Image.open("d:/data/lenna/Lenna.png").convert("RGB")
arr = np.array(lenna)
lenna_svd = np.zeros_like(lenna)
lenna.show()



def minMaxScale(matrix):
    '''
    function: svd성능을 위해 MinMaxScaling
    
    inputs:
        - matrix: R,G,B 각각의 matrix
        
    outputs:
        - mat_scale: scaling matrix
        - mm: minmax 정보를 담은 object
    '''
    mm = MinMaxScaler()
    mat_scale = mm.fit_transform(matrix)
    return mat_scale, mm

def monoSVD(image_matrix, k):
    '''
    function: R,G,B 각각을 독립적으로 svd한 후, k고유 feature까지 추출하여 리턴
    
    inputs:
        - image_matrix: image_matrix (n, n, 1)
        - k: k_value
    
    outputs:
        - svd_mat: 압축된 matrix
    '''
    U, D, V = np.linalg.svd(image_matrix)
    
    svd_mat = np.matrix(U[:, :k]) * np.diag(D[:k]) * np.matrix(V[:k, :])
    
    return svd_mat

def rgb(R, G, B, k):
    '''
    function: 각각의 RGB채널을 합성
    
    inputs:
        - R
        - G
        - B
        - k: compression k
    
    outputs:
        - rgb: 최종 합성된 matrix
    '''
    ## revert ##
    R_svd = mm1.inverse_transform(monoSVD(R, k))
    G_svd = mm2.inverse_transform(monoSVD(G, k))
    B_svd = mm3.inverse_transform(monoSVD(B, k))

    rgb = np.zeros(image_size)
    
    rgb[:,:,0] = R_svd
    rgb[:,:,1] = G_svd
    rgb[:,:,2] = B_svd
    
    rgb[rgb < 0] = 0
    rgb[rgb > 255] = 0
    
    return rgb

def visualizeExplainedRatio(R, G, B):
    '''
    fuction: 설명된 분산 그래프
    
    inputs:
        - R:
        - G:
        - B:
    '''
    def svdSklearn(matrix):
        svd = TruncatedSVD(n_components=300, random_state=77)
        svd.fit_transform(matrix)
        cumsum = np.cumsum(svd.explained_variance_ratio_)
        return cumsum
    r_cumsum = svdSklearn(R)
    g_cumsum = svdSklearn(G)
    b_cumsum = svdSklearn(B)
    
    plt.figure(figsize=(10, 10))
    plt.title("RGB explained Ratio")
    plt.xlabel("k")
    plt.ylabel("cumsum of explained Ratio")
    plt.plot(r_cumsum, 'r', label='R_explained')
    plt.plot(g_cumsum, 'g', label='G_explained')
    plt.plot(b_cumsum, 'b', label='B_explained')
    plt.legend(loc='lower right')
    plt.show()

def k_compression():
    '''
    function: k=[300 ~ 100] 까지 50 단위로 이미지 생성 후 시각화
    '''
    k = range(250, 9, -30) # k range [250, 220, 190, 160, 130, 100, 70, 40, 10]
    platte = [] # image list
    
    for i in k:
        res = rgb(R_scale, G_scale, B_scale, i)
        res_image = Image.fromarray(res.astype("uint8"))
        res_image.save("d:/data/lenna/lenna%d.png" %(i))
        filesize = "K=%d " %(i) + "(" + str(os.path.getsize("d:/data/lenna/lenna%d.png" %(i)))[:3] + "k)"
        platte.append((res_image, filesize))
        
    fig = plt.figure(figsize=(8, 8))
    columns = 3
    rows = 3
    for i in range(1, columns*rows + 1):
        img = platte[i-1][0]
        fig.add_subplot(rows, columns, i, label=platte[i-1][1])
        fig.get_axes()[i-1].set_title(platte[i-1][1])
        plt.imshow(img)
        ax = plt.gca()
        ax.set_axis_off()
    
    plt.grid(False)
    plt.show()
    return platte

    

## rgb 분리 ##
image_size = arr.shape
R, G, B = arr[:,:,0], arr[:,:,1], arr[:,:,2]

## rgb scaling: svd performance ##
R_scale, mm1 = minMaxScale(R)
G_scale, mm2 = minMaxScale(G)
B_scale, mm3 = minMaxScale(B)

visualizeExplainedRatio(R_scale, G_scale, B_scale) # 약 k=100 까지는 90% 설명되는 것으로 판단 가능

platte = k_compression()