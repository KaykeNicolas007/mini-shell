#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]){
    int origin_success;
    char buffer[BUFFER_SIZE];

    if(argc != 3){
        fprintf(stderr, 
            "A quantidade de argumentos precisa ser obrigatoriamente 3\n\t1 - Nome do programa\n\t2 - Arquivo de origem\n\t3 - Arquivo de destino\n");
        exit(EXIT_FAILURE);
    }

    origin_success = open(argv[1], O_RDONLY);
    if(origin_success < 0){
        fprintf(stderr, 
            "O arquivo '%s' não pôde ser aberto ou não existe!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("Retorno do open: %d\nTamanho do buffer: %dB\nQuantidade de argumentos: %d\n", origin_success, BUFFER_SIZE, argc);
    for(int i = 0; i < argc; i++){
        printf("Token[%d] = %s\n", i, argv[i]);
    }

    return 0;
}