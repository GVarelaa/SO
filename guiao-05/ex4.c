#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    int pipe_fd[2];
    if(pipe(pipe_fd) < 0){
        perror("pipe");
        return -1;
    }

    //ls /etc | wc -l.

    if(fork() == 0){
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);

        execlp("ls", "ls", "/etc", NULL);

        _exit(0);
    }

    if(fork() == 0){
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);

        execlp("wc", "wc", "-l", NULL);

        _exit(0);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}