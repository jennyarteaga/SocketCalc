# Connecting Server and Client to a Privelged Port 

# Overview
A simple TCP client and server program in C++ that connects to a well known port (0-1023). 

# How to run
1. Compile code using g++
2. Run file
Example: g++ server.cpp -o server g++ client.cpp -o client
IF RUNNING ON WINDOWS GIVE PERMISSION BY: setcap 'cap_net_bind_services =+ ep'
