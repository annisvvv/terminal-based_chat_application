#include <stdio.h>
#include <sys/socket.h> //socket library socket(), bind(), listen(), accept(), connect(), send(), recv(), shutdown(), AF_INET, SOCK_STREAM, SOCK_DGRAM
#include <netinet/in.h> //Internet family definitions (IPv4 & IPv6) htons(), htonl(), ntohs(), ntohl()
#include <arpa/inet.h> //Address conversion helpers inet_addr(), inet_ntoa(), inet_pton(), inet_ntop()
#include <stdlib.h> //Memory management → malloc(), free() 
// Program control → exit(), atoi(), rand() 
#include <string.h> //String handling functions
#include <unistd.h> //UNIX system calls

#define BACKLOG_QUEUE_SIZE 5
#define BUFFER_SIZE 1024
#define PORT 8080

int main() {
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //(fro ipv4, socket type TCP, default protocol) 
    // sockfd return 0 if the socket is create 
    // -1 if not
    if (sockfd == -1){ //check for error
        perror("failed socket.\n");
        return 1;
    }
    printf("Socket created succesfully\n");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET; //AF_NET for IPv4
    server_addr.sin_port = htons(8080); //specify the port
    server_addr.sin_addr.s_addr = INADDR_ANY; //specify the ip range

    printf("do you want to listen oor connect (1/2) :\n");
    int choice;
    scanf("%d", &choice);
    getchar(); // consume the newline character 

    if (choice == 1){
        
            //bind the socket to the local ip and port number
        if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){ 
            perror("bind failed\n");
            return 1;
        }
        printf("Socket created succesfully!\n");

    
        if (listen(sockfd, BACKLOG_QUEUE_SIZE) == -1){
            perror("Error listening\n");
            return 1;
        }

        //accepting connexions
        struct sockaddr_in client_addr;
        socklen_t client_size = sizeof(client_addr);

        int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_size);
        if (client_fd == -1){
            perror("error accepting connexion\n");
            exit(1);
        }
        printf("client connected\n\n");

        char buffer[BUFFER_SIZE];
        while(1){
            memset(buffer, 0, sizeof(buffer));
            int recv_len = recv(client_fd, buffer, sizeof(buffer), 0);
            if (recv_len <= 0) {
                printf("Client disconnected\n");
                break;
            }
            printf("Client: %s\n", buffer);

            if (strncmp(buffer, "exit", 4) == 0) {
                printf("Exit command received. Closing connection.\n");
                break;
            }

            printf("You: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strcspn(buffer, "\n")] = 0; // Remove newline
            send(client_fd, buffer, strlen(buffer), 0);
        }

            close(client_fd);
            close(sockfd);
    }
    else if (choice == 2){
            char server_ip[16];
            printf("\nEnter the server IP address: ");
            scanf("%15s", server_ip);
            getchar(); // consume the newline character

            //convert text ip to binary
        if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) { 
            perror("\nInvalid address or address not supported\n");
            exit(1);
        }

        if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("connexion failed\n");
        exit(1);
        }
        printf("connexion established\n\n"); 
        
        char buffer[BUFFER_SIZE];
        while (1) {
                printf("You: ");
                fgets(buffer, BUFFER_SIZE, stdin);
                buffer[strcspn(buffer, "\n")] = 0; // Remove newline
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
    }

    
    return 0;
}