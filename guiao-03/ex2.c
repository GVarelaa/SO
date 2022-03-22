#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    pid_t pid = fork();

    if(pid == 0){
        if(execl("/bin/ls2", "/bin/ls", "-l", NULL) < 0 ) perror("exec");
        _exit(1); // SEM O EXIT E SE DER ERRO, ELE CONTINUA A EXECUÇÃO E PRINTA DOIS DONES
    }
    else{
        wait(NULL);
    }

    printf("done\n");

    return 0;
}