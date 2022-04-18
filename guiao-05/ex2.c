#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

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
        
        char buffer[4];
        int read_bytes;
        printf("reading some data...\n");
        while((read_bytes = read(pipe_fd[0], buffer, 4)) > 0){
            write(1, buffer, read_bytes);
        }
        close(pipe_fd[0]); // fechar o de leitura do filho (?)
        _exit(0);
    }

    close(pipe_fd[0]); // fechar o descritor de leitura

    printf("sending...\n");
    write(pipe_fd[1], "ola sou o pipe\n", 15);

    close(pipe_fd[1]); // fechar o descritor de escrita para desbloquear o filho

    wait(NULL);

    return 0;
}