#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main(){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1){
        perror("failed socket");
        return 1;
    }
    printf("socket creeated succesfully\n");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    //inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr); //####

    //convert text ip to binary
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) { 
        perror("Invalid address or address not supported");
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("connexion failed");
        exit(1);
    }
    printf("connexion established");

    char buffer[BUFFER_SIZE];
     while (1) { //####
            printf("You: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            send(sockfd, buffer, strlen(buffer), 0);
    
            if (strncmp(buffer, "exit", 4) == 0)
                break;
    
            memset(buffer, 0, sizeof(buffer));
            int recv_len = recv(sockfd, buffer, sizeof(buffer), 0);
            if (recv_len <= 0) {
                printf("Server disconnected\n");
                break;
            }
            printf("Server: %s\n", buffer);
        }
    
        close(sockfd);
        return 0;
}