#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char* argv[]){
    int ifd = open("/etc/passwd", O_RDONLY);
    int ofd = open("saida.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);
    int efd = open("erros.txt", O_CREAT | O_TRUNC | O_WRONLY, 0640);

    int stdin_fd = dup(0);
    
    dup2(ifd, 0); // dup2(3,0);
    close(ifd); // close(3);

    dup2(ofd, 1); // dup2(4,1);
    close(ofd); // close(4);
    
    dup2(efd, 2); // dup2(5,2);
    close(efd); // close(5);


    write(stdin_fd, "terminei", 8);

    return 0;
}