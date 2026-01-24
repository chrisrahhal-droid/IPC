#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void sigproc(int sig){
    signal(SIGINT, sigproc);
    printf("\nyou have pressed CTRL+C\n");
}

void quitproc(int sig){
    signal(SIGQUIT, quitproc);
    printf("\nCTRL+BackSlash is pressed to quit\n");
    exit(0);
}

int main(){
    signal(SIGINT, sigproc);
    signal(SIGQUIT, quitproc);
    printf("CTRL+C is disabled use CTRL+BackSlash \n");
    while(1){
        printf("running\n");
        sleep(2);
    }
    return 0;
}
