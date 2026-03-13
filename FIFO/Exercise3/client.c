#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define BUFSIZE 256

struct Message{
    int pid;
    char filename[20];
};

void Copying(int, int, char*);
//Client
int main(int argc, char* argv[]){
    if(argc!=2){
        perror("not enough args");
        exit(1);
    }
    int pid = getpid();
    char fifoname[20];
    sprintf(fifoname, "fifo.%d", pid);


    mkfifo(fifoname, 0666);
    int fdwrite = open("fifo.serv", O_WRONLY);
    if(fdwrite == -1){
        perror("open fifo.serv");
        return -1;
    }
    char filename[20];
    struct Message message;
    message.pid = pid;
    strcpy(message.filename, argv[1]);
    write(fdwrite, &message, sizeof(message));
    int fdread = open(fifoname, O_RDONLY);
    if(fdread == -1){
        perror("open fifo for reading");
        exit(1);
    }
    char buf[BUFSIZE];
    Copying(fdread, STDOUT_FILENO, buf);
    close(fdwrite);
    close(fdread);
    unlink(fifoname);
    return 0;
}

void Copying(int in, int out, char* buf){
    int nbread;
    while((nbread = read(in, buf, BUFSIZE)) >0){
        write(out, buf, nbread);
    }
}
