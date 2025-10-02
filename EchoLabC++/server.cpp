#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

using namespace std;

#define MAXBUF 1024

struct sockaddr_in server_addr, client_addr; // server and client address structs
int server_sock, client_sock;                // server and client socket descriptors
int portnum = 13000;                         
char buffer[MAXBUF];                          // buffer for received messages
int n;                                       // stores number of bytes sent/received

int main() {
    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, protocol 0 = default
    if (server_sock < 0) {
        cerr << "Error creating socket" << endl;
        return -1;
    }

    // Prepare the sockaddr_in struct so binding knows where to go
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP
    server_addr.sin_port = htons(portnum);    // Convert port to network byte order

    // Bind
    if (::bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { // Bind socket to IP & port
        cerr << "Bind failed" << endl;
        close(server_sock);                   // Close socket on error
        return -1;
    }

    // Listen
    listen(server_sock, 5);                   
    cout << "Server listening on port " << portnum << endl;

    // Accept an incoming connection
    socklen_t client_len = sizeof(client_addr);                  // length of client address struct
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len); 
    if (client_sock < 0) {
        cerr << "Accept failed" << endl;
        close(server_sock);                 
        return -1;
    }
    cout << "Connection accepted" << endl;

    // Receive a message from client
    n = recv(client_sock, buffer, MAXBUF - 1, 0); 
    if (n < 0) {
        cerr << "Receive failed" << endl;
        close(client_sock);                 
        close(server_sock);                 
        return -1;
    }
    buffer[n] = '\0';                        // adds soecial character at the end to indicate where string ends
    cout << "Received message: " << buffer << endl;

    // Send a reply to client
    const char *reply = "Message received";
    n = send(client_sock, reply, strlen(reply), 0); 
    if (n < 0) {
        cerr << "Send failed" << endl;
        close(client_sock);                
        close(server_sock);                 
        return -1;
    }
    cout << "Reply sent" << endl;

    // Close sockets
    close(client_sock);                     
    close(server_sock);                     
    return 0;
}
