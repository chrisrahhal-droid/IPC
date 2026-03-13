#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
    unlink("clientfifo");
    if((mkfifo("clientfifo", 0600)) == -1){
        perror("fifo");
        exit(1);
    }
    int fdwrite = open("serverfifo", O_WRONLY);
    if(fdwrite == -1){
        perror("fifo opening");
        exit(1);
    }
    int nbwrite = write(fdwrite, "hello", 5);
    if(nbwrite == -1){
        perror("writing");
        exit(1);
    }
    close(fdwrite);
    int fdread = open("clientfifo", O_RDONLY);
    if(fdread == -1){
        perror("fifo opening");
        exit(1);
    }
    char buf[256];
    int nbread = read(fdread, buf, 256);
    if(nbread == -1){
        perror("reading");
        exit(1);
    } 
    close(fdread);
    printf("the length of hello is : %s\n", buf);
    unlink("clientfifo");
    return 0;
}