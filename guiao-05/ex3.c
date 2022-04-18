#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    int pipe_fd[2];

    if(pipe(pipe_fd) < 0){
        perror("pipe");
        return -1;
    }

    if(fork() == 0){
        close(pipe_fd[1]);
        
        int dup_f = dup2(pipe_fd[0], 0);
        close(pipe_fd[0]);

        execlp("wc", "wc", NULL);

        close(dup_f);

        _exit(0);
    }
    
    close(pipe_fd[0]);

    char buf[5];
    int read_bytes;
    while((read_bytes = read(0, buf, 5)) > 0){
        write(pipe_fd[1], buf, read_bytes);
    }

    close(pipe_fd[1]);

    wait(NULL);

    return 0;
}