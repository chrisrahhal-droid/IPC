#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

struct sigaction action, action1, action2;

void handler(int sig) {
    
    printf("signal %d => ", sig);
    
            if(sig == SIGTSTP){
                printf("I have received a SIGTSTP.\n");
            
            // Temporarily set SIGTSTP to default behavior
            action1.sa_handler = SIG_DFL;
            sigaction(SIGTSTP, &action1, &action2);  // Save old handler
            
            printf("Then I sleep....\n");
            kill(getpid(), SIGSTOP);  // Stop myself

            printf("They woke me?\n");
            
            // Restore old handler
            sigaction(SIGTSTP, &action2, NULL);
            printf("Here we go again!\n");
            }
            
            if(sig == SIGINT){}
            if(sig == SIGTERM){
                printf("I was asked to stop the program.\n");
                exit(EXIT_SUCCESS);
            }
    }

int main() {
    printf("PID: %i\n", getpid());
    action.sa_handler = handler;
    
    sigaction(SIGTSTP, &action, NULL);   // Ctrl+Z
    sigaction(SIGINT, &action, NULL);    // Ctrl+C
    sigaction(SIGTERM, &action, NULL);   // kill command
    
    for (int i = 1; i < 60; i++) {
        sleep(1);
        printf("%d\n", i);
    }
    
    return 0;
}