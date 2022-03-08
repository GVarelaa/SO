#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    pid_t pid = fork();

    if(pid == 0){
        printf("Processo pai : %d\n", getppid());
        printf("Processo atual : %d\n", getpid());
        _exit(5);
    }
    else{
        int status;
        int finished_pid;

        printf("Processo-filho : %d\n", pid);  

        printf("Processo pai : %d\n", getppid());
        printf("Processo atual : %d\n", getpid()); 

        finished_pid = wait(&status);
        printf("Finished pid : %d; Status code %d\n", finished_pid, WEXITSTATUS(status));
    }

    return 0;
}