#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    signal(SIGUSR1, handler);
}

int main(){
    
    pid_t pid;
    int i;
    signal(SIGUSR1, handler);
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }
    if (pid == 0){
        pid = getppid();
    for (i = 1; i <= 100; i += 2){
        printf("%d\n", i);
        kill(pid, SIGUSR1);
        pause();
        }
    }else{
    for (i = 2; i <= 100; i += 2){
        pause();
        printf("%d\n", i);
        kill(pid, SIGUSR1);
        }
    }
return 0;
}
