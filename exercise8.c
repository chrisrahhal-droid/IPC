#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void sighup(int sig){
    signal(SIGHUP, sighup);
    printf("Child: I have received a SIGHUP\n");
}
void sigint(int sig){
    signal(SIGINT, sigint);
    printf("Child: I have received a SIGINT\n");
}
void sigquit(int sig){
    printf("My Daddy has killed me!!!\n");
    exit(0);
}

int main(){
    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        
        while(1){
            pause();
        }
    }else{
        sleep(1);
        printf("\nParent: sending SIGHUP\n");
        kill(pid, SIGHUP);
        sleep(3);
        printf("\nParent: sending SIGINT\n");
        kill(pid, SIGINT);
        sleep(3);
        printf("\nParent: sending SIGQUIT\n");
        kill(pid, SIGQUIT);
        sleep(3);
    }
}

