#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 32

int main(int argc, char *argv[]){
    int source_access, destination_access, read_bytes, written_bytes;
    char buffer[BUFFER_SIZE];

    if(argc != 3){
        fprintf(stderr, 
            "A quantidade de argumentos precisa ser obrigatoriamente 3\n\t1 - Nome do programa\n\t2 - Arquivo de origem\n\t3 - Arquivo de destino\n");
        exit(EXIT_FAILURE);
    }

    source_access = open(argv[1], O_RDONLY);
    if(source_access < 0){
        fprintf(stderr, 
            "O arquivo '%s' não pôde ser aberto ou encontrado!\n", argv[1]);
        exit(EXIT_FAILURE);
    }


    destination_access = open(argv[2], O_WRONLY);
    if(destination_access < 0){
        fprintf(stderr, 
            "O arquivo '%s' não pôde ser aberto ou encontrado!\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    do{
        read_bytes = read(source_access, buffer, BUFFER_SIZE);
        write(destination_access, buffer, read_bytes);
    }while(read_bytes > 0);

    close(source_access);
    close(destination_access);

    if(read_bytes == 0)
        exit(EXIT_SUCCESS);
    else
        exit(EXIT_FAILURE);

    return 0;
}