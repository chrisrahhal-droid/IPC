/* Write a C program that is equivalent to the shell command
ps aux | grep root | wc -l*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>

int main(){
    int fd1[2], fd2[2];
    pid_t pid1, pid2;
    
    if(pipe(fd1) <0){
        perror("pipe");
        exit(1);
    }
    pid1 = fork();
    if(pid1 != 0){
        close(fd1[0]);
        
        dup2(fd1[1], 1);
        execlp("ps", "ps", "aux", NULL);
        
        perror("ps");
        exit(1);
        close(fd1[1]);
        wait(NULL);
    }
    else{
        close(fd1[1]);
        if(pipe(fd2) <0){
            perror("pipe");
            exit(1);
        }
        pid2 = fork();
        if(pid2 !=0){
            close(fd2[0]);

            dup2(fd1[0], 0);
            dup2(fd2[1], 1);
            execlp("grep", "grep", "root", NULL);
            
            perror("grep");
            exit(1);
            close(fd2[1]);
            wait(NULL);
        }
        else{
            close(fd2[1]);

            dup2(fd2[0], 0);
            execlp("wc", "wc" ,"-l", NULL);
            
            perror("wc");
            exit(1);
        }
        close(fd1[0]);
    }
    return 0;
}