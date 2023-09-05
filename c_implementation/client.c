#ifdef _WIN32
#include <winsock2.h> // Windows-specific headers
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int arv, char **argc) {
// Windows specific stuff for sockets.
#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup");
        return -1;
    }
#endif

    // Create socket structure
    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1234);

    #ifdef _WIN32
    int server_info_len = sizeof(server_info);
#else
    socklen_t server_info_len = sizeof(server_info);
#endif
    if(inet_pton(AF_INET, "127.0.0.1", &server_info.sin_addr.s_addr ) <= 0) {
        perror("Conversion");
        return -1;
    }

    // Create the socket itself
    int sockfd = socket(server_info.sin_family, SOCK_STREAM ,0);
    if (sockfd < 0) {
        perror("Socket");
        return -1;
    }

    // Connect to the server.
    if(connect(sockfd, (struct sockaddr*)&server_info ,server_info_len) < 0) {
        perror("Connect");
        return -1;
    }

    // Send and receives the message from the server.
    char buffer[69];

    ssize_t input_length = scanf("%s", buffer);
    if (input_length != 1) {
        perror("Input");
        return -1;
    }

    send(sockfd, buffer, strlen(buffer), 0);
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("%s", buffer);

    // Close the socket and returns success.
    close(sockfd);
    return 0;
}
