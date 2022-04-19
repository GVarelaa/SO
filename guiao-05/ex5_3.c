#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

//grep -v ˆ# /etc/passwd | cut -f7 -d: | uniq | wc -l.

int main(int argc, char* argv[]){
    int fd_pipe[3][2];

    for(int i = 0; i < 4; i++){
        if(i==0){
            pipe(fd_pipe[i]);

            if(fork() == 0){
                close(fd_pipe[i][0]);
                dup2(fd_pipe[i][1], 1);
                close(fd_pipe[i][1]);

                execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);

                _exit(0);
            }

            wait(NULL); 
        }
        else if(i==3){
            if(fork() == 0){
                close(fd_pipe[i-1][1]);
                dup2(fd_pipe[i-1][0], 0);
                close(fd_pipe[i-1][0]);

                execlp("wc", "wc", "-l", NULL);

                _exit(0);
            }

            close(fd_pipe[i-1][0]); close(fd_pipe[i-1][1]);
            wait(NULL);
        }
        else{
            pipe(fd_pipe[i]);

            if(fork() == 0){
                close(fd_pipe[i-1][1]);
                dup2(fd_pipe[i-1][0], 0);
                close(fd_pipe[i-1][0]);

                close(fd_pipe[i][0]);
                dup2(fd_pipe[i][1], 1);
                close(fd_pipe[i][1]);     

                if(i==1) execlp("cut", "cut", "-f7", "-d:", NULL);
                else if(i==2) execlp("uniq", "uniq", NULL);

                _exit(0);
            }

            close(fd_pipe[i-1][0]); close(fd_pipe[i-1][1]);
            wait(NULL);
        }
    }

    // wait(NULL);
    // wait(NULL);
    // wait(NULL);
    // wait(NULL);

    return 0;
}