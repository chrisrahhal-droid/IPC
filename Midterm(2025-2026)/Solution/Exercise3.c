#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>

#define FIFO_NAME "myfifo"

int factorial(int n){
    int result = 1;
    for(int i=2;i<=n;i++){
        result *=i;
    }
    return result;
}

int main(){

    pid_t pid;
    int fd;
    if(mkfifo(FIFO_NAME, 0666) == -1){
        if(errno != EEXIST){
        perror("mkfifo");
        exit(1);
        }
    }

    pid=fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }
    if(pid>0){
        //Parent process
        fd = open(FIFO_NAME, O_WRONLY);
        if(fd == -1){
            perror("open fifo for writing");
            exit(1);
        }

        for(int i=1;i<=5;i++){
            write(fd, &i, sizeof(int));
        }
        close(fd);
        wait(NULL);
        unlink(FIFO_NAME);
    }else{
        //Child process
        fd = open(FIFO_NAME, O_RDONLY);
        if(fd == -1){
            perror("open fifo for reading");
            exit(1);
        }
        int num;
        for(int i=0;i<5;i++){
            read(fd, &num, sizeof(int));
            printf("Child received: %d | Factorial: %d\n", num, factorial(num));
        }
        close(fd);
        exit(0);
    }
    return 0;
}
