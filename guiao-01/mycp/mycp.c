#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main(int argc, char* argv[]){
    int f1 = open(argv[1], O_RDONLY);

    if(f1 < 0){
        perror("open file1");
        return 1;
    }

    int f2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0640);

    if(f2 < 0){
        perror("open file2");
        return 1;
    }

    char buffer[1024];
    int n_bytes = 0;

    while((n_bytes = read(f1, &buffer, 1024)) > 0){
        write(f2, &buffer, n_bytes);
    }

    close(f1); close(f2);
}