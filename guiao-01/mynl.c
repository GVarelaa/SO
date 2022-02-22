#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


char readln_buf[2048];

int readln_bud_end;

int readln_buf_pos;


int readc(int fd, char *c){
    //verifica se tenho mais bytes para ler


    // se tiver, retorna escreve no endereço (c) e atualiza estado global (pos atual)


    //se nao tiver, vai ler a disco, e retorna 1 carater (atualizando o estado)

    return read(fd, c, 1);
}



ssize_t readln(int fd, char *line, size_t size){
    int i;

    for(i = 0; i < size && read(fd, &line[i], 1) > 0; i++){ 
        if(line[i] == '\n') {i++; break;}
    }

    return i;
}



ssize_t readln2(int fd, char *line, size_t size){
    int n_bytes = read(fd, line, size);
    char *backup = line;
    char *pos = strchr(line, '\n');

    if(pos){
        lseek(fd, -(line-pos+1), SEEK_CUR);
    }

    return pos-backup+1;
}



int main(int argc, char *argv[]){
    int f1 = open(argv[1], O_RDONLY);

    if(f1 < 0){
        perror("Open file1\n");
        return 1;
    }

    char buffer[1024];
    char number[10];
    int n_bytes = 0;
    int line_count = 1;

    while((n_bytes = readln(f1, buffer, 1024)) > 0){
        if(n_bytes != 1024){
            sprintf(number, "%d  ", line_count);
            write(1, &number, 3);
            line_count++;
        }
        write(1, &buffer, n_bytes);
    }

    close(f1);

    return 1;
}