#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person{
    char name[30]; // 30 bytes
    int age; // 4 bytes
} Person;


int main(int argc, char* argv[]){
    if(argc == 4){
            if(!strcmp(argv[1], "-i")){
            int file = open("file.bin", O_CREAT | O_APPEND | O_RDWR, 0640);

            Person p;
            strcpy(p.name, argv[2]);
            p.age = atoi(argv[3]);

            int n_bytes = write(file, &p, sizeof(struct Person));

            if(n_bytes < 0){
                perror("Write");
                return 1;
            }

            printf("Registo efetuado com sucesso. Posição : %ld", lseek(file, 0, SEEK_END) / sizeof(struct Person));


        }
        else if(!strcmp(argv[1], "-u")){
            int file = open("file.bin", O_CREAT | O_RDWR, 0640);

            Person p;

            while(read(file, &p, sizeof(struct Person)) > 0){
                if(!strcmp(p.name, argv[2])){
                    p.age = atoi(argv[3]);

                    lseek(file, -sizeof(struct Person), SEEK_CUR);

                    write(file, &p, sizeof(struct Person));
                }
            }
        }
        else if(!strcmp(argv[1], "-o")){
            int file = open("file.bin", O_CREAT | O_RDWR, 0640);

            Person p;

            lseek(file, (atoi(argv[2])-1)*sizeof(struct Person), SEEK_SET);

            read(file, &p, sizeof(struct Person));
            p.age = atoi(argv[3]);

            lseek(file, -sizeof(struct Person), SEEK_CUR);

            write(file, &p, sizeof(struct Person));            
        }
    }

    int file = open("file.bin", O_RDONLY);

    Person p;

    while(read(file, &p, sizeof(struct Person)) > 0){
        printf("Nome : %s | Idade : %d\n", p.name, p.age);
    }

    return 1;
}


