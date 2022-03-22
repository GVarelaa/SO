#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    for(int i = 0; i < argc-1; i++){
        if(fork() == 0){
            if(execlp(argv[i+1], argv[i+1], NULL) < 0) perror("exec");
            _exit(1);
        }
    }

    for(int i = 0; i < argc-1; i++){
        wait(NULL);
    }

    return 0;
}