#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

/*
pipe -> unidirecional
0    -> leitura
1    -> escrita
*/


int main(int argc, char* argv[]){

    int pipe_fd[2];

    if (pipe(pipe_fd) < 0){
        perror("pipe");
        return -1;
    }

    if(fork() == 0){
        close(pipe_fd[1]); // fechar o descritor de escrita
        
        //close(pipe_fd[0]);

        char buffer[4];
        int read_bytes = read(pipe_fd[0], buffer, 4);
        
        printf("reading some data...\n");
        write(1, buffer, read_bytes);

        _exit(0);
    }

    close(pipe_fd[0]); // fechar o descritor de leitura

    //close(pipe_fd[1]);

    printf("sending...\n");
    sleep(10); // o filho fica à espera que o pai escreva
    write(pipe_fd[1], "data", 4);

    close(pipe_fd[1]); // fechar o descritor de escrita para desbloquear o filho

    wait(NULL);

    return 0;
}