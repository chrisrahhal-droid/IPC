#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>    // for exit()
#include<sys/wait.h>  // for wait()

void handler(int sig){
    printf("\n signal received is: %d\n", sig);
    if(sig == SIGUSR1){
        signal(SIGUSR1, handler);
    }else{
        signal(sig, SIG_IGN);
    }
}

int main(){
    
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    int pid, s;
    pid = fork();

    if(pid < 0){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        while(1){
            printf("Number of signal <0 to finish: ");
            scanf("%d", &s);
            if(s < 0){
                break;
            }
            kill(getppid(), s);
            sleep(1);
        }
    }else{
        wait(NULL);
    }

    return 0;

}