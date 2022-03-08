#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    pid_t pai = getppid();
    pid_t atual = getpid();

    printf("Processo pai : %d\nProcesso atual : %d\n", pai, atual);

    return 0;
}