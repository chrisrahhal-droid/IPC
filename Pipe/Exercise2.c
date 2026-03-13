/*Write a C program that creates 2 processes A and B that can communicate via
a pipe. The process "A" open a file given by argument to the program and transfers the
content of the file to process B via the pipe. The process "B" write the content of the pipe
to a second file given also by argument. Verify if the first file have the default permissions
0644.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include <sys/wait.h>

#define BUFSIZE 256

void Copying(int, int , char*);
int main(int argc, char* argv[]){
    int fd[2];
    char buf1[BUFSIZE], buf2[BUFSIZE];
    pid_t pid;
    char* fsrc;
    char* fdest;
    int fd1, fd2;


    if(argc != 3){
        fprintf(stderr, "wrong usage");
        exit(1);
    }

    fsrc = argv[1];
    fdest = argv[2];

    fd1 = open(fsrc, O_RDONLY);
    if(fd1 < 0){
        perror("failed open");
        exit(1);
    };
    if(pipe(fd) < 0){
        perror("failed to create a pipe");
        exit(1);
    };
    pid = fork();
    if(pid <0){
        perror("fork");
        exit(1);
    };
    if(pid == 0){
        close(fd[1]);
        fd2 = open(fdest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(fd2 < 0){
            perror("failed to open the file for wriing");
            exit(1);
        }
        Copying(fd[0], fd2, buf2);
        close(fd2);
        close(fd[0]);
        exit(0);
    }
    close(fd[0]);
    Copying(fd1, fd[1], buf1);

    close(fd1);
    close(fd[1]);
    wait(NULL);
    

    return 0;
}
void Copying(int in, int out, char* buf){
    int nbRead ;
    while(1){
        nbRead = read(in, buf, BUFSIZE);
        if(nbRead == -1){
            perror("read");
            exit(1);
        }
        if(nbRead == 0){
            break;
        }
        write(out, buf, nbRead);
    
    }
}