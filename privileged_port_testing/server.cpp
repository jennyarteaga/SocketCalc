#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>

using namespace std;

#define MAXBUF 1024

struct sockaddr_in server_addr, client_addr; 
int server_sock, client_sock;                
int portnum = 443;                         
char buffer[MAXBUF];                          
int n;                                       

int main() {
    server_sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_sock < 0) {
        cerr << "Error creating socket" << endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;         
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(portnum);   

    // Bind
    if (::bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { 
        cerr << "Bind failed" << endl;
        close(server_sock);                  
        return -1;
    }

    listen(server_sock, 5);                   
    cout << "Server listening on port " << portnum << endl;

    socklen_t client_len = sizeof(client_addr);                  
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len); 
    if (client_sock < 0) {
        cerr << "Accept failed" << endl;
        close(server_sock);                 
        return -1;
    }
    cout << "Connection accepted" << endl;

    n = recv(client_sock, buffer, MAXBUF - 1, 0); 
    if (n < 0) {
        cerr << "Receive failed" << endl;
        close(client_sock);                 
        close(server_sock);                 
        return -1;
    }
    buffer[n] = '\0';                       

    const char *reply = "Message received";
    n = send(client_sock, reply, strlen(reply), 0); 
    if (n < 0) {
        cerr << "Send failed" << endl;
        close(client_sock);                
        close(server_sock);                 
        return -1;
    }
    cout << "Reply sent" << endl;

    close(client_sock);                     
    close(server_sock);                     
    return 0;
}