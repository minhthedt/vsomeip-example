#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in broadcastAddr;
    const char *message = "Hello, Broadcast!";
    int broadcastEnable = 1;
    int port = 12345;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Enable broadcast option
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) < 0) {
        perror("Broadcast enable failed");
        close(sockfd);
        return 1;
    }

    // Set up broadcast address
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_port = htons(port);
    broadcastAddr.sin_addr.s_addr = inet_addr("255.255.255.255");

    // Send broadcast message
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) < 0) {
        perror("Broadcast send failed");
        close(sockfd);
        return 1;
    }

    std::cout << "Broadcast message sent: " << message << std::endl;

    close(sockfd);
    return 0;
}