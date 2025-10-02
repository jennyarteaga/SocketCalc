#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>

using namespace std;

#define MAXBUF 1024
struct sockaddr_in server_addr; // struct to hold server IP and port
int sock;                       // Socket file descriptor
int portnum = 13000;            
char buffer[MAXBUF];            // buffer to store received data
int n;                          // stores number of bytes sent/received

int main() {
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock < 0) {
        cerr << "Error creating socket" << endl;
        return -1;
    }

    // Get server address
    struct hostent *server;           // struct for host info
    server = gethostbyname("localhost"); // resolve "localhost" to IP address
    if (server == NULL) {
        cerr << "No such host" << endl;
        close(sock);                 
        return -1;
    }

    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;    // IPv4
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length); // copy IP address
    server_addr.sin_port = htons(portnum); // convert port to network byte order

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { 
        cerr << "Connection failed" << endl;
        close(sock);                  
        return -1;
    }
    cout << "Connected to server" << endl;

    // Send a message to server
    const char *message = "Hello, Server!";
    n = send(sock, message, strlen(message), 0);
    if (n < 0) {
        cerr << "Send failed" << endl;
        close(sock);                  
        return -1;
    }
    cout << "Message sent to server" << endl;

    // Close the socket
    close(sock);                      
    return 0;
}





