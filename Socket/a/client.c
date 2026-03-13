#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

/*a)En utilisant un socket local en mode connecté avec 5 connexions simultanées
maximum. Le nom du socket est pris en paramètre à l’exécution des programmes.*/

int main(int argc,char* argv[]){
    int socketfd, server_addr_len;
    struct sockaddr_un server_addr;
    char message[50];

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, argv[1]);
    server_addr_len = strlen(server_addr.sun_path)+ sizeof(server_addr.sun_family);

    if((socketfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0 ){
        perror("creating");
        exit(1);
    }
    if((connect(socketfd, (struct sockaddr *) &server_addr, server_addr_len))<0){
        perror("connecting");
        exit(1);
    }
    printf("enter your message: ");
    bzero(message, sizeof(message));
    fgets(message, sizeof(message), stdin);
    write(socketfd, message, strlen(message));
    bzero(message, sizeof(message));
    int nbread = read(socketfd, message, sizeof(message));
    if(nbread < 0){
        perror("reading");
    }
    printf("\nThe received message from the server is: %s\n", message);

    return 0;
}