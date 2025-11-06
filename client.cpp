// client 
#include <sys/types.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>


#define MAXBUF 1024


struct sockaddr_in server_addr;
int client_sock;
int portnum = 443;
char buffer[MAXBUF];
int n;

int main () {
    // create socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // configure server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnum);

    // server ip 
    std::string server_ip = "10.106.13.0";
    inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr);

    // connect to server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return -1;
    }

    // send data
    const char* message = "Hello from client!";
    n = send(client_sock, message, strlen(message), 0);
    if (n < 0) {
        std::cerr << "Error sending data" << std::endl;
        return -1;
    }

    std::cout << "Message sent to server" << std::endl;
    close(client_sock);
    return 0;
}
