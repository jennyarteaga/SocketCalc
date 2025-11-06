#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>

using namespace std;

#define MAXBUF 1024
struct sockaddr_in server_addr; 
int sock;                      
int portnum = 443;            
char buffer[MAXBUF];            
int n;                        

int main() {
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock < 0) {
        cerr << "Error creating socket" << endl;
        return -1;
    }

    struct hostent *server;          
    server = gethostbyname("localhost"); 
    if (server == NULL) {
        cerr << "No such host" << endl;
        close(sock);                 
        return -1;
    }

    server_addr.sin_family = AF_INET;   
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length); // copy IP address
    server_addr.sin_port = htons(portnum); 

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { 
        cerr << "Connection failed" << endl;
        close(sock);                  
        return -1;
    }
    cout << "Connected to server" << endl;

    const char *message = "Hello, Server!";
    n = send(sock, message, strlen(message), 0);
    if (n < 0) {
        cerr << "Send failed" << endl;
        close(sock);                  
        return -1;
    }
    cout << "Message sent to server" << endl;

    close(sock);                      
    return 0;
}




