#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
pid_t pid;
void handler(int sig){
        printf("Timeout! Killing child\n");
        kill(pid, SIGKILL);
        exit(0);
    }
int main(){
    pid = fork();
    if(pid == 0){
        while(1){
            printf("Child running...\n");
            sleep(5);
        }
    }else{
            signal(SIGALRM, handler);
            alarm(10);            
            wait(NULL);
    }

    return 0;
}
