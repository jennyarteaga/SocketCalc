// server
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <vector>
#include <cstring>


#define MAXBUF 1024

struct sockaddr_in server_addr, client_addr; 
int server_sock, client_sock;                
int portnum = 443;                         
char buffer[MAXBUF];                          
int n;     

int main () {
    // create socket 
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // configure server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portnum);

    // bind socket to address
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return -1;
    }

    // listen
    listen(server_sock, 5);
    std::cout << "Server listening on port " << portnum << std::endl;

    // accept client 
    socklen_t client_len = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
    if (client_sock < 0) {
        std::cerr << "Error accepting client" << std::endl;
        return -1;
    } 
    std::cout << "Client connected" << std::endl;

    // receive data
    n = recv(client_sock, buffer, MAXBUF-1, 0);
    if (n < 0) {
        std::cerr << "Error receiving data" << std::endl;
        return -1;
    }

    buffer[n] = '\0';
    std::cout << "Received message: " << buffer << std::endl;

    // close sockets
    close(client_sock);
    close(server_sock);
}
