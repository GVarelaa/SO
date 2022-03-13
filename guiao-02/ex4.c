#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    for(int i = 0; i < 10; i++){
        pid_t pid = fork();
        
        if(pid == 0){
            exit(i+1);
        }
    }

    for(int j = 0; j < 10; j++){
        int status;
        pid_t pid = wait(&status);
        printf("Processo : %d\nCódigo : %d\n", pid, WEXITSTATUS(status));
    }

    return 0;
}