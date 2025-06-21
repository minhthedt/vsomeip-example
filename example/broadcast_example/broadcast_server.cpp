#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in recvAddr;
    char buffer[1024];
    int port = 12345;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Set up receive address
    memset(&recvAddr, 0, sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_port = htons(port);
    recvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&recvAddr, sizeof(recvAddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    std::cout << "Waiting for broadcast messages..." << std::endl;

    // Receive broadcast message
	while (true) {
		socklen_t addrLen = sizeof(recvAddr);
		int len = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&recvAddr, &addrLen);
		if (len < 0) {
			perror("Receive failed");
			close(sockfd);
			return 1;
		}
		buffer[len] = '\0';
		std::cout << "Received message: " << buffer << std::endl;
	}

    close(sockfd);
    return 0;
}