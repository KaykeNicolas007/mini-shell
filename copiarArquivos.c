#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]){
    char buffer[BUFFER_SIZE];

    if(argc != 3){
        fprintf(stderr, 
            "A quantidade de argumentos precisa ser obrigatoriamente 3\n\t1 - Nome do programa\n\t2 - Arquivo de origem\n\t3 - Arquivo de destino\n");
        exit(EXIT_FAILURE);
    }

    printf("Tamanho do buffer: %dB\nQuantidade de argumentos: %d\n", BUFFER_SIZE, argc);
    for(int i = 0; i < argc; i++){
        printf("Token[%d] = %s\n", i, argv[i]);
    }

    return 0;
}