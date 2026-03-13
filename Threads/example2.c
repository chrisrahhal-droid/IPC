#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

int div_result;
pthread_t id;
void* thread(void* num){
    int * nums = (int *) num;
    div_result = nums[0] / nums[1];
    return NULL;
}

int main(int argc, char* argv[]){
    if(argc < 5){
        exit(1);
    }
    int values[2];
    values[0] = atoi(argv[3]);
    values[1] = atoi(argv[4]); 
    pthread_create(&id, NULL, thread, values);
    
    int mult_result = atoi(argv[1]) * atoi(argv[2]);
    pthread_join(id, NULL);
    printf("%d\n", mult_result + div_result);
    exit(0);
}
