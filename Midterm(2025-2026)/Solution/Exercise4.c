#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SIZE 5

int factorial(int n){
    int result = 1;
    for(int i=2;i<=n;i++){
        result *=i;
    }
    return result;
}

int main(){
    int shm_id;
    int *shm_ptr;
    //Create shared memory segment
    shm_id = shmget(IPC_PRIVATE, SIZE* sizeof(int), IPC_CREAT | 0666);
    if(shm_id<0){
        perror("shmget");
        exit(1);
    }
    //Attach to shared memory
    shm_ptr = (int *) shmat(shm_id, NULL, 0);
    if(shm_ptr == (int *)-1){
        perror("shmat");
        exit(1);
    }
    pid_t pid = fork();

    if(pid<0){
        perror("fork");
        exit(1);
    }

    if(pid>0){
        //Parent process
        for(int i=0;i<SIZE;i++){
            shm_ptr[i] = i+1; //Write numbers 1 to 5
        }
        wait(NULL);
        for(int i=0;i<SIZE;i++){
            printf("Number: %d | Factorial:%d\n", i+1, shm_ptr[i]);
        }
        //Detach and remove shared memory
        shmdt(shm_ptr);
        shmctl(shm_id, IPC_RMID, NULL);
    }else{
        //Child process
        for(int i=0;i<SIZE;i++){
            shm_ptr[i] = factorial(shm_ptr[i]); //Compute factorial
        }
        shmdt(shm_ptr); //Detach
        exit(0);
    }
    return 0;
}
