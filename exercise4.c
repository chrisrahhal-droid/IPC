#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/signal.h>
#include<unistd.h>

struct sigaction action;
int nb_quit = 0, nb_int = 0;

void handler(int sig){
    if(sig == SIGINT){
        printf("\nnb_int = %d\n", ++nb_int);
        if(nb_int == 3){
            exit(SIGINT);
        }
    }else if(sig == SIGQUIT){
        printf("\nnb_quit = %d\n", ++nb_quit);
        if(nb_quit == 3){
            exit(SIGQUIT);
        }
    }else{
        printf("ERROR");
        exit(1);
    }
}

int main(){
    printf("pid: %d\n", getpid());
    action.sa_handler = handler;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    while(1){
        sleep(1);
    }
    return 0;
}