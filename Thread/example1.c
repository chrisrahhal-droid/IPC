#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>

int val[3];
pthread_t id[3];
void * thread(void * num){
    while(1){
        val[(int)num]++;
        sleep(1);

    }
}

int main(){
    for(int i=0; i<3; i++){
        pthread_create(&id[i], NULL, thread, (void*) i);
    }
    for(int i=0;i<30;i++){
        sleep(1);
        printf("%d %d %d\n", val[0], val[1], val[2]);
    }
    exit(0);
}
