# Client and Server Authentication

This folder contains a TCP client-server application written in C++ with basic authentication. 
The client sends username:password credentials to the server, and the server responds with "Accepted" or "Rejected".

#Files
1. Server.cpp: listens for a  connection from a client
2. Client.cpp: connects to server
3. Resolve.cpp: prints getbyhostname and takes 2 arguments
Example: ./resolve www.example.com

# How to run 
1. Compile code using g++
2. Run file

Example:
g++ server.cpp -o server
./server
g++ client.cpp -o client
./client
g++ resolve.cpp -o resolve
./resolve
