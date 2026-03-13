/*Write a program that creates a ring of 3 processes connected by pipes.
– The first process should ask the user for a string and then send it to the second
•••process.
– The second process should reverse the string and send it to the third process.
– The third process should convert the string to uppercase and send it back to the
first process.
When the first process gets the processed string, it should display it to the terminal.
When this is done, all 3 processes should terminate.
Here's an illustration of the process ring:*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<string.h>
#include<ctype.h>

#define BUFSIZE 256

void reverseLine(char *, int);
int main(){
    int fd1[2], fd2[2], fd3[2];
    int pid1, pid2;
    char buf1[BUFSIZE], buf2[BUFSIZE], buf3[BUFSIZE];
    int nbRead1, nbRead2, nbRead3;

    if(pipe(fd1) <0 || pipe(fd2) <0 || pipe(fd3) <0){
        perror("pipe");
        exit(1);
    }
    pid1 = fork();
    if(pid1 !=0){
        pid2 = fork();
            if(pid2!=0){
                close(fd1[0]);
                close(fd2[0]);
                close(fd2[1]);
                close(fd3[1]);
            while(nbRead1 = read(STDIN_FILENO, buf1, BUFSIZE)){
                write(fd1[1], buf1, nbRead1);
                nbRead3 = read(fd3[0], buf3, BUFSIZE);
                write(STDOUT_FILENO, buf3, nbRead3);
            }
                close(fd1[1]);
                close(fd3[0]);
                wait(NULL); }
                
                else{
                    close(fd1[0]);
                    close(fd1[1]);
                    close(fd2[1]);
                    close(fd3[0]);
                    while(nbRead3 = read(fd2[0], buf3, BUFSIZE)){
                        for(int i=0;i<nbRead3;i++){
                            buf3[i] = toupper(buf3[i]);
                        }
                        write(fd3[1], buf3, nbRead3);
                    }
                    close(fd2[0]);
                    close(fd3[1]);
                    exit(0);
                }
        wait(NULL);
    }
    else{
        close(fd1[1]);
        close(fd2[0]);
        close(fd3[0]);
        close(fd3[1]);
        while(nbRead2 = read(fd1[0], buf2, BUFSIZE)){
            reverseLine(buf2, nbRead2-1);
            write(fd2[1], buf2, nbRead2);
        }
        close(fd1[0]);
        close(fd2[1]);
    }
    return 0;
}
void reverseLine(char*buffer, int n){
    int i;
    char tmp;
    for(i=0;i<n/2;i++){
        tmp = buffer[i];
        buffer[i] = buffer[n-i-1];
        buffer[n-i-1] = tmp;
    }
}