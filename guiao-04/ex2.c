#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]){
    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_RDWR, 0640);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);

    int stdout_fd = dup(1);
    
    dup2(ifd, 0); // dup2(3,0);
    close(ifd); // close(3);

    dup2(ofd, 1); // dup2(4,1);
    close(ofd); // close(4);
    
    dup2(efd, 2); // dup2(5,2);
    close(efd); // close(5);


    if(fork() == 0){
        write(1, "contents", 8);
        
        char *buffer = malloc(8);
        lseek(1, 0, SEEK_SET);
        read(1, buffer, 8);
        
        write(stdout_fd, buffer, 8);

        _exit(0);
    }

    wait(NULL);

    return 0;
}