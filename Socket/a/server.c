#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    int socket_listener_fd, socket_connection_fd;
    struct sockaddr_un client_addr, server_addr;
    char message[50];  
    socklen_t client_addr_len, server_addr_len;

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, argv[1]);
    server_addr_len = strlen(server_addr.sun_path)+ sizeof(server_addr.sun_family);

    if((socket_listener_fd = socket(AF_UNIX,SOCK_STREAM, 0))< 0){
        perror("creating");
        exit(1);
    }
    unlink(argv[1]);
    if((bind(socket_listener_fd, (struct sockaddr *) &server_addr, server_addr_len)) <0){
        perror("binding");
        exit(1);
    }
    listen(socket_listener_fd, 5);
    client_addr_len = sizeof(client_addr);
    if((socket_connection_fd = accept(socket_listener_fd, (struct sockaddr *) &client_addr, &client_addr_len))< 0){
        perror("accepting");
        exit(1);
    }
    bzero(message, sizeof(message));
    int nbread = read(socket_connection_fd, message, sizeof(message));
    if(nbread < 0){
        perror("reading");
        exit(1);
    }
    printf("The received message from the client is: %s\n", message);
    write(socket_connection_fd, "I got your message", 18);

    return 0;
}