#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define MULTICAST_ADDR "239.255.0.1"  // Multicast group address
#define PORT 12345

int main() {
    int sock;
    struct sockaddr_in multicast_addr;
    const char* message = "Hello, Multicast!";

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set up the multicast address
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);
    multicast_addr.sin_port = htons(PORT);

    // Send the message to the multicast group
    if (sendto(sock, message, strlen(message), 0, 
               (struct sockaddr*)&multicast_addr, sizeof(multicast_addr)) < 0) {
        perror("Message send failed");
        close(sock);
        return 1;
    }

    std::cout << "Message sent: " << message << std::endl;

    // Close the socket
    close(sock);
    return 0;
}