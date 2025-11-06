#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <cstring>
#include <vector>

using std::cout, std::cerr, std::endl, std::string;

#define MAXBUF 1024
struct sockaddr_in server_addr; 
int sock;                       
int portnum = 13000;        
std::vector<char> buffer(MAXBUF);
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
        memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);    // copy resolved IP address    
        server_addr.sin_port = htons(portnum); 

     
        if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { 
            cerr << "Connection failed" << endl;
            close(sock);                  
            return -1;
        }
        cout << "Connected to server" << endl;

    

  
        // User credientials 
        string userCreditials = "user1:passw0rd";

        // recieve authentication if server accepted or rejected the credentials
        int n = send(sock, userCreditials.data(), userCreditials.size(), 0);
        if (n < 0) {
            cerr << "Error sending data" << endl;
            close(sock);                 
            return -1;
        }
        cout << "Sent credentials to server" << endl;



        n = recv(sock, buffer.data(), MAXBUF, 0);
        if (n < 0) {
            cerr << "Error receiving data" << endl;
            close(sock);                 
            return -1;
        }
        buffer[n] = '\0';
        cout << "Server response: " << buffer.data() << endl;



        close(sock);    

       
       
       
    return 0;
}
