#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[]){
    int socketfd, port_number;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char message[50];

    if(argc < 3){
        fprintf(stderr, "more arguments are needed");
        exit(1);
    }
    port_number = atoi(argv[2]);

    
    if(((socketfd) = socket(AF_INET, SOCK_STREAM, 0))<0){
        perror("creating");
        exit(1);
    }
    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr, "Error locating host\n");
        exit(0);
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    bcopy(server->h_addr_list[0], &server_addr.sin_addr.s_addr, server->h_length);
    if(connect(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
        perror("connecting");
        exit(0);
    }
    printf("enter your message: ");
    bzero(message, sizeof(message));
    fgets(message, sizeof(message), stdin);
    write(socketfd,message, strlen(message));
    bzero(message, sizeof(message));
    int nbread = read(socketfd, message, sizeof(message));
    if(nbread < 0){
        perror("reading");
        exit(0);
    }
    printf("received message from the server is:%s\n", message);
    

    return 0;
}
