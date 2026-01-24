#include<stdio.h>
#include<signal.h>
#include<unistd.h>
/*Write a program that counts the signals it receives and displays this counter
and the received signal number*/
    int counter[NSIG];
      
void handler(int sig){
        counter[sig] += 1;
        signal(sig, handler);
        printf("Signal received: %d, count: %d\n", sig, counter[sig]);
    }

int main(){
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    kill(getpid(), SIGUSR1);
    kill(getpid(), SIGUSR2);
    kill(getpid(), SIGUSR1);
    kill(getpid(), SIGUSR2);
    return 0;
}
