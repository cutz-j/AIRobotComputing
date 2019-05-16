### Python user-event (1, 2) server ###
import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("127.0.0.1", 5000))
server_socket.listen(5)

print("TCP server Start")

while 1:
    client_socket, address = server_socket.accept() # client response event
    print("Connected")
    
    while 1:
        data = input("(1: openCV or 2: openGL >> ") # user-event
        client_socket.send(data.encode('euc_kr'))
        
#        data = client_socket.recv(512)
#        print("<<", data)

server_socket.close()
print("Server END")