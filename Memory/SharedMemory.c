#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>

int main(){

    int segment_id;
    const int shared_segment_size = 0x6400;
    char* shared_memory;
    struct shmid_ds shmbuffer;

    segment_id = shmget(IPC_PRIVATE, shared_segment_size, IPC_CREAT | IPC_EXCL|S_IRUSR |S_IWUSR);

    shared_memory  = shmat(segment_id, 0, 0);

    shmctl(segment_id, IPC_STAT, &shmbuffer);

    int segment_size = shmbuffer.shm_segsz;

    printf("Segment size = %d", segment_size);

    sprintf(shared_memory, "\nhello chris");

    printf("%s", shared_memory);

    shmdt(shared_memory);

    shmctl(segment_id, IPC_RMID, 0);
    
    return 0;

}