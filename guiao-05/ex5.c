#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    int pipe_fd1[2];
    int pipe_fd2[2];
    int pipe_fd3[2];

    if(pipe(pipe_fd1) < 0){
        perror("pipe");
        return -1;
    }

    if(pipe(pipe_fd2) < 0){
        perror("pipe");
        return -1;
    }

    if(pipe(pipe_fd3) < 0){
        perror("pipe");
        return -1;
    }

    //grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l.

    if(fork() == 0){
        close(pipe_fd2[0]);
        close(pipe_fd2[1]);

        close(pipe_fd3[0]);
        close(pipe_fd3[1]);


        close(pipe_fd1[0]);
        dup2(pipe_fd1[1], 1);
        close(pipe_fd1[1]);

        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);

        _exit(0);
    }

    if(fork() == 0){
        close(pipe_fd3[0]);
        close(pipe_fd3[1]);
        
        close(pipe_fd1[1]);
        dup2(pipe_fd1[0], 0);
        close(pipe_fd1[0]);

        close(pipe_fd2[0]);
        dup2(pipe_fd2[1], 1);
        close(pipe_fd2[1]);

        execlp("cut", "cut", "-f7", "-d:", NULL);

        _exit(0);
    }

    if(fork() == 0 ){
        close(pipe_fd1[0]);
        close(pipe_fd1[1]);

        close(pipe_fd2[1]);
        dup2(pipe_fd2[0], 0);
        close(pipe_fd2[0]);

        close(pipe_fd3[0]);
        dup2(pipe_fd3[1], 1);
        close(pipe_fd3[1]);

        execlp("uniq", "uniq", NULL);

        _exit(0);
    }

    if(fork() == 0){
        close(pipe_fd1[0]);
        close(pipe_fd1[1]);

        close(pipe_fd2[0]);
        close(pipe_fd2[1]);

        close(pipe_fd3[1]);
        dup2(pipe_fd3[0], 0);
        close(pipe_fd3[0]);

        execlp("wc", "wc", "-l", NULL);

        _exit(0);
    }

    close(pipe_fd1[0]);
    close(pipe_fd1[1]);

    close(pipe_fd2[0]);
    close(pipe_fd2[1]);

    close(pipe_fd3[0]);
    close(pipe_fd3[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}