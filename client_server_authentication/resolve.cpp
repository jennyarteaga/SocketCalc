#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>

using std::cout, std::cerr, std::endl;


int main (int count, char *arg[]) {


    const char *hostname = arg[1];

    
    struct hostent *host = gethostbyname(hostname);
    if (host == NULL) {
        cerr << "Error: Unable to resolve hostname " << hostname << endl;
        return 1;
    }

    cout << "Name: " << host->h_name << endl;

    // aliases
    cout << "Aliases: ";
    if (host->h_aliases[0] == NULL) {
        cout << "No aliases" << endl;
    } else {
        for (int i = 0; host->h_aliases[i] != NULL; i++) {
            cout << host->h_aliases[i] << " ";
        }
    }


    // address type
    cout << "Address type: " << (host->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6") << endl;

    // length
    cout << "Address length: " << host->h_length << endl;

    // IP addresses
    cout << "IP Addresses: ";
    for (int i = 0; host->h_addr_list[i] != NULL; i++) {
        struct in_addr addr;
        memcpy(&addr, host->h_addr_list[i], sizeof(struct in_addr));
        cout << inet_ntoa(addr) << " ";
    }

}

