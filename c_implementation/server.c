#ifdef _WIN32
#include <winsock2.h> // Windows-specific headers
#include <ws2tcpip.h>
#else
#include <netinet/in.h> // Unix-like system headers
#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {

    // Windows specific stuff for sockets.

#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup");
        return -1;
    }
#endif

    // Create the socket struct
    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1234);

#ifdef _WIN32
    int server_info_len = sizeof(server_info);
#else
    socklen_t server_info_len = sizeof(server_info);
#endif
    struct sockaddr client_info;

#ifdef _WIN32
    int client_info_len = sizeof(client_info);
#else
    socklen_t client_info_len = sizeof(client_info);
#endif
    // Create the socket itself
    int sockfd = socket(server_info.sin_family, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket");
        return -1;
    }
    //Define socker options
    int reuse = 1;
#ifdef _WIN32
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse))) {
        perror("Socket addr already used.");
        return -1;
    }
#else
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuse, sizeof(reuse))) {
        perror("Socket addr already used.");
        return -1;
    }
#endif
    // Create the bind
    if ( 0 > bind(sockfd, (struct sockaddr*)&server_info, server_info_len)) {
        perror("Binding");
        return -1;
    }
    // Create the listener
    if (0 > listen(sockfd, 0)) {
        perror("Listener");
        return -1;
    }
    // Accepter
    setvbuf(stdout, NULL, _IOLBF, 0);
    int new_socket = accept(sockfd, &client_info, &client_info_len);
    if (0 > new_socket ) {
        perror("Accepter");
        return -1;
    }
    char *ovo = "uabo\n";
    char *failed = "You failed bozo L\n";
    char buffer[69];
    ssize_t receaved = recv(new_socket, buffer, sizeof(buffer), 0);
    if (receaved <= 0) {
        perror("Receive");
    } else {
        buffer[receaved] = '\0'; // Null-terminate the received data as a string
    }
    if (strcmp(buffer, "ovo") == 0){
        send(new_socket, ovo, strlen(ovo), 0);
    } else {
        send(new_socket, failed, strlen(failed), 0);
        return -1;
    }
#ifdef _WIN32
    // Cleanup Winsock
    WSACleanup();
#else
    close(new_socket);
#endif
    return 0;
}
