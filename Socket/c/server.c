#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    int socketfd;
    struct sockaddr_in server_addr, from_addr;

    if(argc < 2){
        fprintf(stderr, "no port number is provided");
        exit(1);
    }
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socketfd < 0){
        perror("creating");
        exit(1);
    }   
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));
    socklen_t length = sizeof(struct sockaddr_in);
    if((bind(socketfd, (struct sockaddr *) &server_addr, length)) < 0){
        perror("binding");
        exit(1);
    }
    char buffer[50];
    while (1){
        length = sizeof(struct sockaddr_in);
        bzero(buffer, sizeof(buffer));
        int n = recvfrom(socketfd, buffer, sizeof(buffer), 0,(struct sockaddr *) &from_addr, &length);
        if(n < 0){
            fprintf(stderr, "reading");
            exit(1);
            }
        printf("the received message from the client is:  %s", buffer);
        bzero(buffer, sizeof(buffer));
        int s = sendto(socketfd, "I got your message", 18, 0, (struct sockaddr*) &from_addr, length);
        if(s < 0){
            perror("sending");
            exit(1);
            }
        }   
    return 0;
}