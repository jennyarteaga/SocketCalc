from socket import *

HOST = 'localhost'
PORT = 13000

serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind((HOST, PORT)) 

serverSocket.listen(1)
print(f'The Server is ready to recieve and listening on port {PORT}')

while True: 
    connectionSocket, addr = serverSocket.accept()
    message = connectionSocket.recv(1024).decode()
    print("Recieved Message")
    connectionSocket.send(message.encode())


connectionSocket.close()
serverSocket.close()


