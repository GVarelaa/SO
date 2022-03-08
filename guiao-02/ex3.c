#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

    for(int i = 1; i<=10; i++){
        pid_t pid = fork();

        if(pid == 0){
            printf("Processo pai : %d\nProcesso filho : %d\n", getppid(), getpid());
        
            _exit(i);
        }
        else{
            int status;
            wait(&status);

            printf("Codigo saida : %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}