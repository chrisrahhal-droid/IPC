#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
int fd;

void handler(int sig){
    printf("file closed and exiting..\n");
    close(fd);
    exit(0);
    signal(SIGINT, handler);
}

int main(){
    printf("%i\n", getpid());
    signal(SIGINT, handler);
    char* filename = "test.txt";
    fd = open(filename, O_WRONLY | O_CREAT, 0600);
    if(fd < 0){
        perror("failed to open the file on mode write");
        exit(1);
    }
    printf("printing into the file\n");
    for(int i=0;i<5;i++){
        write(fd, "abcdefghijkl\n", 13);
        sleep(5);
    }
    kill(getpid(), SIGINT);
    return 0;
}
