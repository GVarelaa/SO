#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    int fd_pipe[3][2];
    for(int i = 0; i < 4; i++){
        if(i==0){
            pipe(fd_pipe[i]);

            if(fork()==0){
                close(fd_pipe[i][0]);
                //dup
                //close

                //exec
            }
        }
        else if(i==3){

        }
        else{

        }
    }

    return 0;
}