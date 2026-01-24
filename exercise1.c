#include<stdio.h>
#include<signal.h>
#include<unistd.h>

sigset_t set1, set2;
int sig;

void handler(int sig){
    signal(SIGINT, handler);
}

int main(){
    signal(SIGINT, handler);
    sigemptyset(&set1);
    sigaddset(&set1, SIGINT);
    sigaddset(&set1, SIGQUIT);
    sigaddset(&set1, SIGUSR1);

    sigprocmask(SIG_SETMASK, &set1, NULL);
    
    sleep(15);

    sigpending(&set2);
    printf("\npending signals: ");
    for(sig = 1; sig < NSIG; sig++){
        if(sigismember(&set2, sig)){
            printf("%d", sig);
        }
    }
    printf("\nEnd of process\n");
    printf("deblocking signals\n ");
    sleep(1);
    sigemptyset(&set1);
    sigprocmask(SIG_SETMASK, &set1, NULL);
    return 0;
}
