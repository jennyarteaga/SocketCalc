#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <vector>
#include <cstring>

using std::cout, std::cerr, std::endl;



#define MAXBUF 1024

struct sockaddr_in server_addr, client_addr; // server and client address structs
int server_sock, client_sock;                // server and client socket descriptors
int portnum = 13000;                         
std::vector<char> buffer(MAXBUF);                      // buffer for received messages
int n;                                       // stores number of bytes sent/received


int main() {
    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP, protocol 0 = default
    if (server_sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // Prepare the sockaddr_in struct so binding knows where to go
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Bind to localhost (loopback address)
    server_addr.sin_port = htons(portnum);    // Convert port to network byte order

    // cast the struct server_addr (which is a ipv4 info) to (struct sockaddr *) because bind takes a pointer 
    struct sockaddr *server = (struct sockaddr *)&server_addr;

    // get the size of the struct
    socklen_t server_len = sizeof(server_addr);

    // Bind the socket to the address and port number
    int bind_status = (::bind(server_sock, server, server_len));

    if (bind_status < 0) {
        cerr << "Bind failed" << endl;
        close(server_sock);                 
        return -1;
    }
    

    // Listen
    listen(server_sock, 2);                   
    cout << "Server listening on port " << portnum << endl;

    // cast the struct client_addr to (struct sockaddr *) because accept takes a pointer
    struct sockaddr *client = (struct sockaddr *)&client_addr;
    
    
    // length of the client address struct
    socklen_t client_len = sizeof(client_addr); 

        cout << "Waiting for a client to connect..." << endl;


        client_sock = accept(server_sock, client, &client_len); 

        if (client_sock < 0) {
            cerr << "Accept failed" << endl;
            close(server_sock);                 
            return -1;
        }
       
        cout << "Client connected" << endl;



        n = recv(client_sock, buffer.data(), buffer.size() - 1, 0); 

        if (n < 0) {
            cerr << "Receive failed" << endl;
            close(client_sock);                 
            close(server_sock);                 
            return -1;
        }
        buffer[n] = '\0';    



        cout << "Message received from client: " << buffer.data() << endl;
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
