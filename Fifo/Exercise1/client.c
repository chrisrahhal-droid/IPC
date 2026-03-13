/*Exercise
 • Write 2 programs in C, one is a client and the other is
 a server. Both communicate using named pipes. The
 client sends many integers to the server, and the
 server calculates their sum and returns the result to
 the client.*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#define BUFSIZE 256

 int main(){
    unlink("clientfifo");
    if((mkfifo("clientfifo", 0644)) == -1){
        perror("fifo creation");
        exit(1);
    }
    int fd = open("serverfifo", O_WRONLY);
    if(fd == -1){
        perror("fifo opening");
        exit(1);
    }
    int nbwrite = write(fd, "567", 3);
    if(nbwrite == -1){
        perror("fifo writing");
        exit(1);
    }
    close(fd);
    int fd1 = open("clientfifo", O_RDONLY);
    if(fd1 == -1){
        perror("fifo opening");
        exit(1);
    }
    char buf[BUFSIZE];
    int nbread = read(fd1, &buf, BUFSIZE);
    if(nbread == -1){
        perror("reading");
        exit(1);
    }
    printf("the sum is: %s\n", buf);
    
    close(fd1);
    unlink("clientfifo");
    return 0;
 }