#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Create the socket struct
    struct sockaddr_in server_info;
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(1234);

    socklen_t server_info_len = sizeof(server_info);

    struct sockaddr client_info;
    socklen_t client_info_len = sizeof(client_info);

    // Create the socket itself
    int sockfd = socket(server_info.sin_family, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket");
        return -1;
    }
    //Define socker options
    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &reuse, sizeof(reuse))) {
        perror("Socket addr already used.");
        return -1;
    }
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
    int i = 0;
    char *failed = "You failed bozo L\n";
    char buffer[69];
    ssize_t sent;
    ssize_t receaved = recv(new_socket, buffer, sizeof(buffer), 0);
    if (receaved <= 0) {
        perror("Receive");
    } else {
        buffer[receaved] = '\0'; // Null-terminate the received data as a string
    }
    if (strcmp(buffer, "ovo") == 0){
        sent = send(new_socket, ovo, strlen(ovo), 0);
    } else {
        sent = send(new_socket, failed, strlen(failed), 0);
        return -1;
    }
    close(new_socket);
    return 0;
}
