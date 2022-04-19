#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

    //grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l.

int main(int argc, char* argv[]){
    int pipe_fd[3][2];

    if(pipe(pipe_fd[0]) < 0){
        perror("pipe");
        return -1;
    }

    if(fork() == 0){
        close(pipe_fd[0][0]);
        dup2(pipe_fd[0][1], 1);
        close(pipe_fd[0][1]);

        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);

        _exit(0);
    }

    wait(NULL);

    if(pipe(pipe_fd[1]) < 0){
        perror("pipe");
        return -1;
    }

    if(fork() == 0){
        close(pipe_fd[0][1]);
        dup2(pipe_fd[0][0], 0);
        close(pipe_fd[0][0]);

        close(pipe_fd[1][0]);
        dup2(pipe_fd[1][1], 1);
        close(pipe_fd[1][1]);

        execlp("cut", "cut", "-f7", "-d:", NULL);

        _exit(0);
    }

    close(pipe_fd[0][0]); close(pipe_fd[0][1]);
    wait(NULL);

    if(pipe(pipe_fd[2]) < 0){
        perror("pipe");
        return -1;
    }

    if(fork() == 0){
        close(pipe_fd[1][1]);
        dup2(pipe_fd[1][0], 0);
        close(pipe_fd[1][0]);

        close(pipe_fd[2][0]);
        dup2(pipe_fd[2][1], 1);
        close(pipe_fd[2][1]);

        execlp("uniq", "uniq", NULL);

        _exit(0);
    }

    close(pipe_fd[1][0]); close(pipe_fd[1][1]);
    wait(NULL);

    if(fork() == 0){
        close(pipe_fd[2][1]);
        dup2(pipe_fd[2][0], 0);
        close(pipe_fd[2][0]);

        execlp("wc", "wc", "-l", NULL);

        _exit(0);
    }

    close(pipe_fd[2][0]); close(pipe_fd[2][1]);
    wait(NULL);


    return 0;
}