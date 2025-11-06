#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <vector>
#include <cstring>

using std::cout, std::cerr, std::endl, std::string;



#define MAXBUF 1024

struct sockaddr_in server_addr, client_addr;
int server_sock, client_sock;                
int portnum = 13000;                         
std::vector<char> buffer(MAXBUF);                     
int n;                                     


int main() {
    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    server_addr.sin_family = AF_INET;         
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    server_addr.sin_port = htons(portnum);    

    struct sockaddr *server = (struct sockaddr *)&server_addr;

    socklen_t server_len = sizeof(server_addr);

    int bind_status = (::bind(server_sock, server, server_len));

    if (bind_status < 0) {
        cerr << "Bind failed" << endl;
        close(server_sock);                 
        return -1;
    }
    

    listen(server_sock, 2);                   
    cout << "Server listening on port " << portnum << endl;

    struct sockaddr *client = (struct sockaddr *)&client_addr;
    
    
    socklen_t client_len = sizeof(client_addr); 

        cout << "Waiting for a client to connect..." << endl;


        client_sock = accept(server_sock, client, &client_len); 

        if (client_sock < 0) {
            cerr << "Accept failed" << endl;
            close(server_sock);                 
            return -1;
        }
       
        cout << "Client connected" << endl;



        // recieve authentication if server accepted or rejected the credentials
        n = recv(client_sock, buffer.data(), MAXBUF, 0);
        if (n < 0) {
            cerr << "Error receiving data" << endl;
            close(client_sock);                 
            close(server_sock);                 
            return -1;
        }
        buffer[n] = '\0';
        cout << "Received user credentials from client: " << buffer.data() << endl;
       
        string validCreds = "user1:passw0rd";
        string reply;

        if (buffer.data() == validCreds) {
            reply = "Accepted";
        } else {
        reply = "Rejected";
     }

     // send reply to client
        n = send(client_sock, reply.data(), reply.size(), 0);
        if (n < 0) {
            cerr << "Error sending data" << endl;
            close(client_sock);                 
            close(server_sock);                 
            return -1;
        }
        cout << "Sent authentication reply to client: " << reply << endl;
        
        
          

    close(client_sock);                     
    close(server_sock);                     
    return 0; 

}
