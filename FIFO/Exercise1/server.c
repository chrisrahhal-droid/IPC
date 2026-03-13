#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#define BUFSIZE 256

int main(){
    unlink("serverfifo");
    if((mkfifo("serverfifo", 0644)) == -1){
        perror("fifo creation");
        exit(1);
    }
    int fdread = open("serverfifo", O_RDONLY);
    if(fdread == -1){
        perror("opening fifo");
        exit(1);
    }
    char buf[BUFSIZE];
    int nbread = read(fdread, buf, BUFSIZE);
        if(nbread == -1){
        perror("reading");
        exit(1);
    }
    int numbers[nbread];
    int sum = 0;

    for(int i=0;i<nbread;i++){
        numbers[i] = buf[i] - '0';
        sum += numbers[i];
    }

    close(fdread);
    int fdwrite = open("clientfifo", O_WRONLY);
    if(fdwrite == -1){
        perror("opening fifo");
        exit(1);
    }

    char result[BUFSIZE];
    sprintf(result, "%d", sum);
    int nbwrite = write(fdwrite, result, strlen(result)+1);
    if(nbwrite == -1){
        perror("writing in fifo");
        exit(1);
    }
    close(fdwrite);
    unlink("serverfifo");
    return 0;
}