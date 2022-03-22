#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    
    // sleep(10);

    // if(execlp("sleep", "sleep", "10", NULL) < 0){ // VERIFICAR
    //     perror("exec");
    // }

    if(execl("/bin/ls", "/bin/ls", "-l", NULL) < 0 ) perror("exec");

    //if(execlp("ls", "ls", "-l", NULL) < 0) perror("exec");

    // char *exec_args[] = {"/bin/ls", "-l", NULL};
    // execv("/bin/ls", exec_args);

    return 0;
}