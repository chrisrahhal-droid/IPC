/*Write a C program that contains a producer process (reads from the stdin and
write to a pipe) and a consumer process that makes capital letter the small letter (reads
from the pipe and writes to the stdout).*/

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<ctype.h>


#define BUFSIZE 256

int main(){

    int fd[2];
    pid_t pid;
    int nbRead;
    char c;
    char buf1[BUFSIZE], buf2[BUFSIZE];
    
    if(pipe(fd)<0){
        perror("pipe");
        exit(1);
    }
    
    pid = fork();
    
    if(pid != 0){
        close(fd[0]);
        while((nbRead = read(STDIN_FILENO, buf1, BUFSIZE)) > 0){
            write(fd[1], buf1, nbRead);
        }
    close(fd[1]);
    wait(NULL);
    }
    else{
        close(fd[1]);
        while((nbRead = read(fd[0], &c, 1)) > 0){
            c = toupper(c);
            write(STDOUT_FILENO, &c, nbRead);
        }
        close(fd[0]);
        exit(0);
    }
    return 0;
}
