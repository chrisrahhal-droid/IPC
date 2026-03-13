#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
int life = 5;

void handler(int sig){
    if(sig == SIGINT){
        life--;
        printf("\nyou lost on life, Remaining:%d\n", life);

    }else if(sig == SIGUSR1){
        life+=10;
        printf("\nyou gained 10 lives, Remaining:%d\n ", life);
    }
}


int main(){
    printf("PID: %d\n", getpid());
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGUSR1, &action, NULL);

    while(life>0){
        sleep(1);
    }
    printf("Game Over!\n");
    return 0;
}