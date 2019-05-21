### Python user-event (1, 2) server ###
import socket
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt


img_list = []

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("127.0.0.1", 5000))
server_socket.listen(5)

#print("TCP server Start")

while 1:
    client_socket, address = server_socket.accept() # client response event
    print("Connected")
    
    while 1:
        data = input("(1: openCV or 2: openGL >> ") # user-event
        client_socket.send(data.encode('euc_kr'))
        
        if int(data) == 1:
            while 1:
                data = client_socket.recv(255).decode("euc_kr")
                print("<<", data)
                if data == '':
                    break # 통신Delay로 imgae 복원의 어려움
                if data != ' ':
                    img_list.append(data)
            while 1:
                ## image draw ##
                img_str = "".join(img_list)
                img_str = img_str.strip()
                img_list = img_str.split(".")
                img_arr = np.array(img_list[:-1], dtype=np.int)
                img = np.zeros(shape=[188, 112, 3], dtype=np.int)
                for i in range(img.shape[0]):
                    for j in range(img.shape[1]):
                        for k in range(img.shape[2]):
                            img[i, j, k] = img_arr[(i * img.shape[1] * 3) + (j * 3) + k]
                img[:, :, 0], img[:, :, 2] = img[:, :, 2], img[:, :, 0]
                outImg = Image.fromarray(img.astype('uint8'))
                outImg.transpose(4).show()
                break

server_socket.close()
print("Server END")

#img = np.array(img_list, dtype=np.int)