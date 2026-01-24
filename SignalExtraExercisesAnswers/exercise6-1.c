#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
int life = 5;

void handler(int sig){
    if(sig == SIGINT){
        life--;
        printf("\nyou lost on life, Remaining:%d\n", life);
        signal(SIGINT, handler);
    }else if(sig == SIGUSR1){
        life+= 10;
        printf("\nyou gained 10 lives, Remaining:%d\n ", life);
        signal(SIGUSR1, handler);
    }
}

int main(){
    printf("PID: %d\n", getpid());
    signal(SIGINT, handler);
    signal(SIGUSR1, handler);
    while(life>0){
        sleep(1);
    }
    printf("Game over!\n");
    return 0;
}