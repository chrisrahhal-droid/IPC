#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>   // for exit, atoi
#include <unistd.h>   // for read, write
#include <string.h>   // for bzero, bcopy


int main(int argc, char* argv[]){
    int socketfd;
    struct sockaddr_in server_addr, from_addr;
    struct hostent* server;
    socklen_t addr_len;

    if(argc != 3){
        fprintf(stderr, "three arguments are required(filename, hostname, portnumber)");
        exit(1);
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server = gethostbyname(argv[1]);
    if(server == NULL){
        perror("failed to locate host");
        exit(1);
    }
    bcopy(server->h_addr_list[0], &server_addr.sin_addr, server->h_length);
    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(socketfd < 0){
        perror("creating");
        exit(1);
    }
    printf("enter your message: ");
    char buffer[50];
    bzero(buffer, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);
    addr_len = sizeof(struct sockaddr_in);
    int n = sendto(socketfd, buffer, strlen(buffer), 0,(struct sockaddr *) &server_addr, addr_len);
    if(n < 0){
        perror("sending");
        exit(1);
    }
    bzero(buffer, sizeof(buffer));
    int nbread = recvfrom(socketfd, buffer, sizeof(buffer), 0,(struct sockaddr  *) &from_addr, &addr_len);
    if(nbread < 0){
        perror("reading");
        exit(1);
    }
    printf("the received message from the server is: %s\n", buffer);
    
    return 0;
}