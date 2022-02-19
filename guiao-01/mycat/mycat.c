#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>


int main(int argc, char *argv[]){
    int f1 = 0;
    int f2 = 1;

    char buffer[1024];
    int n_bytes = 0;

    while((n_bytes = read(f1, &buffer, 1024)) > 0){
        write(f2, &buffer, n_bytes);
    }

    return 1;
}

