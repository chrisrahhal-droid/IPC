#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    int timeleft;

    printf("Set the alarm and sleep\n");
    alarm(10);
    sleep(5);

    timeleft = alarm(0);
    printf("Time left before cancel, and rearm: %d\n", timeleft);

    alarm(timeleft);

    printf( "Hanging around, waiting to die\n" );
    pause();
    return EXIT_SUCCESS;
}