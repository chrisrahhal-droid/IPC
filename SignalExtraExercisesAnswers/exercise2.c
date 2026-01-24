#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    signal(SIGHUP, SIG_IGN);
    printf("Sending SIGHUP Signal\n");
    kill(getpid(), SIGHUP);
    execvp(argv[1], &argv[1]);
    return 0;
}