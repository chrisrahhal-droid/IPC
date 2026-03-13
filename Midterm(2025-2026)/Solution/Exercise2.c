#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(){

    int p1[2];//Parent -> Child
    int p2[2];//Child -> Parent
    pid_t pid;

    if(pipe(p1)== -1 || pipe(p2) == -1){
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if(pid<0){
        perror("fork");
        exit(1);
    }
    if(pid>0){
        //Parent process
        close(p1[0]);
        close(p2[1]);
        for(int i=1;i<=10;i++){
            write(p1[1], &i, sizeof(int));
            int result;
            read(p2[0], &result, sizeof(int));
            printf("Parent sent: %d | Child returned: %d\n", i, result);
        }

        close(p1[1]);
        close(p2[0]);
        wait(NULL);
    }else{
        close(p1[1]);
        close(p2[0]);

        int num;
        while(read(p1[0], &num, sizeof(int))> 0){
            int square = num * num;
            write(p2[1], &square, sizeof(int));
        }
        close(p1[0]);
        close(p2[1]);
        exit(0);

    }
    return 0;
}
