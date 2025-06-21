#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define MULTICAST_ADDR "239.255.0.1"  // Multicast group address
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in local_addr;
    struct ip_mreq mreq;
    char buffer[BUFFER_SIZE];

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Allow multiple sockets to use the same port number
    int reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse)) < 0) {
        perror("Setting SO_REUSEADDR failed");
        close(sock);
        return 1;
    }

    // Bind to the multicast port
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(PORT);

    if (bind(sock, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
        perror("Binding failed");
        close(sock);
        return 1;
    }

    // Join the multicast group
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq)) < 0) {
        perror("Joining multicast group failed");
        close(sock);
        return 1;
    }

    std::cout << "Listening for multicast messages..." << std::endl;

    // Receive messages
    while (true) {
        ssize_t nbytes = recvfrom(sock, buffer, BUFFER_SIZE - 1, 0, nullptr, nullptr);
        if (nbytes < 0) {
            perror("Receiving failed");
            break;
        }
        buffer[nbytes] = '\0';  // Null-terminate the received data
        std::cout << "Received message: " << buffer << std::endl;
    }

    // Leave the multicast group
    setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));

    // Close the socket
    close(sock);
    return 0;
}