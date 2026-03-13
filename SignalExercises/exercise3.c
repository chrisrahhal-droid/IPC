#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>

void handler (int sig){
    printf("\nreceived signal number:%d\n", sig);
    if(sig == SIGTSTP){
        printf("I sleep...\n");
        kill(getpid(), SIGSTOP);
        signal(SIGTSTP, handler);
    }
    else if (sig == SIGINT){}
    else{
        printf("End of the program\n");
        exit(EXIT_SUCCESS);
    }
}

int main(){
    printf("%d\n", getpid());
    signal(SIGTSTP, handler);
    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    while(1){
        sleep(1);
        printf("running\n");
    }
    
}