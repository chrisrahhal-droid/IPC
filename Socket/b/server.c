#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[]){
    int socket_listener_fd, socket_connection_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;

    if(argc < 2){
        fprintf(stderr, "no port_number is provided");
        exit(1);
    }
    int port_number = atoi(argv[1]);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if((socket_listener_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("creating socket");
        exit(1);
    }
    if((bind(socket_listener_fd,(struct sockaddr *) &server_addr, sizeof(server_addr))) < 0){
        perror("binding");
        exit(1);
    }
    listen(socket_listener_fd, 5);
    client_addr_len = sizeof(client_addr);

    socket_connection_fd = (accept(socket_listener_fd, (struct sockaddr *) &client_addr, &client_addr_len));
    if(socket_connection_fd < 0){
        perror("connecting");
        exit(1);
    }
    char buffer[50];
    bzero(buffer, 50);
    int nbread = read(socket_connection_fd, buffer, sizeof(buffer));
    if(nbread < 0){
        fprintf(stderr, "failed to read from the socket");
        exit(1);
    }
    printf("the received message from the client is: %s", buffer);
    write(socket_connection_fd, "I got your message", 18);
    return 0;
}
