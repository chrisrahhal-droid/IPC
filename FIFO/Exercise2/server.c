#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
    unlink("serverfifo");
    if((mkfifo("serverfifo", 0600)) == -1){
        perror("fifo creation");
        exit(1);
    }

    int fdread = open("serverfifo", O_RDONLY);
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
    int fdwrite = open("clientfifo", O_WRONLY);
    if(fdwrite == -1){
        perror("fifo opening");
        exit(1);
    }
    char size[256];
    sprintf(size, "%d", nbread);
    int nbwrite = write(fdwrite, size, strlen(size) + 1);
    close(fdwrite);
    unlink("serverfifo");
    return 0;
}