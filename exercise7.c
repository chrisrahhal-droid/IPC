#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig){
    printf("The response is not arrived in time \n");
    exit(0);
}

int main(){
    int response;
    signal(SIGALRM, handler);
    printf("Question?\n");
    alarm(15); // will send SIGALARM to the running process after 15s
    scanf("%d", &response);
    alarm(0); //cancels any pending alarm
    printf("response is read\n");
    return 0;
}