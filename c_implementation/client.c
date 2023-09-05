#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int arv, char **argc) {
    // Create socket structure
    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1234);
    socklen_t server_info_len = sizeof(server_info);
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
