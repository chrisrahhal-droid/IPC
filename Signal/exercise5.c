#include<stdio.h>
#include<signal.h>
#include<unistd.h>

struct sigaction action;
sigset_t ens;
//struct sigaction action; if we wrote it (globaly) no need to add sigemptyset(&action.sa_mask); action.sa_flags = 0;
void handler(int sig){
    printf("\nEntering the handler with the signal: %d\n", sig);
    sigprocmask(SIG_BLOCK, NULL, &ens);
    printf("\nblocked signals:\n");
    for(int i=1; i<NSIG;i++){
        if(sigismember(&ens, i)){
            printf("%d\n", i);
        }
    }
    if(sig == SIGINT){}
    printf("Exit handler\n");
}

int main(){
    printf("PID: %d\n", getpid());
    action.sa_handler = handler;
    sigaction(SIGQUIT, &action,NULL);
    sigaddset(&action.sa_mask, SIGQUIT);
    sigaction(SIGINT, &action, NULL);
    while(1){
        sleep(1);
    }
    return 0;
}