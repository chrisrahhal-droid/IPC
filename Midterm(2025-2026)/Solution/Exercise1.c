#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(){
    int fd[2];
    pid_t pid;
    if(pipe(fd) == -1){
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }
    if(pid==0){
        close(fd[1]);
        int out_fd = open("result.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
        if(out_fd < 0){
            perror("open");
            exit(1);
        }
        dup2(fd[0], STDIN_FILENO);
        dup2(out_fd, STDOUT_FILENO);

        close(fd[0]);
        close(out_fd);

        execlp("grep", "grep", "error", NULL);
        perror("execlp grep");
        exit(1);
    }else{
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("cat", "cat", "input.txt", NULL);
        perror("execlp cat");
        exit(1);
    }
    return 0;
}
