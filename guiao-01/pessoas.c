#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

struct Person{
    char name[20]; // 20 bytes
    int age; // 4 bytes
}Person;


int main(int argc, char* argv[]){



    int f = open("file.bin", O_CREAT | O_TRUNC | O_RDWR, 0640);

    struct Person p;

    char *name = "tone esteves";

    strcpy(p.name, name);
    p.age = 44;

    int bytes = write(f, &p, sizeof(struct Person));

    struct Person p1_read;

    lseek(f, -sizeof(struct Person), SEEK_END);

    bytes = read(f, &p1_read, sizeof(struct Person));

    if(bytes < 0){
        perror("read");
        return 1;
    }


    printf("%d\n", bytes);
    printf("nome : %s\n", p1_read.name);
    printf("idade : %d\n", p1_read.age);


    return 1;
}


