from socket import *

HOST = 'localhost' # can also be ip address 
PORT = 13000

# Creating socket and intializing connection
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((HOST, PORT))

message = input("Send a message to server: ")
clientSocket.send(message.encode())
response = clientSocket.recv(1024)
print("From Server:", response.decode())

clientSocket.close()
