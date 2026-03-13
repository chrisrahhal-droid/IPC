#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>

#define BUFSIZE 256

struct Message{
    int pid;
    char filename[20];
};

void Copying(int, int, char*);
//Server
int main(){
    int fdread, fdwrite;
    char filename[20], fifoname[20];

    mkfifo("fifo.serv",0666);
    
    fdread = open("fifo.serv", O_RDONLY);
    struct Message message;
    read(fdread, &message, sizeof(message));
    int  pid = message.pid;
    strcpy(filename, message.filename);
    int fd = open(filename, O_RDONLY);
    if(fd == -1){
        printf("failed to open the file of the fifo");
        return -1;
    }
    char buf[BUFSIZE];
    sprintf(fifoname, "fifo.%d", pid);
    fdwrite = open(fifoname, O_WRONLY);
    if(fdwrite == -1){
        printf("failed to open fifo.%d",pid);
        return -1;
    }
    Copying(fd, fdwrite, buf);
    close(fd);
    close(fdread);
    close(fdwrite);
    unlink("fifo.serv");
    return 0;
}
void Copying(int in, int out, char* buf){
    int nbread;
    while((nbread = read(in, buf, BUFSIZE)) >0){
        write(out, buf, nbread);
    }
}