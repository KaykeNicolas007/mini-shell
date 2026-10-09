#include <stdio.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]){
    char buffer[BUFFER_SIZE];

    printf("Tamanho do buffer: %dB\nQuantidade de argumentos: %d\n", BUFFER_SIZE, argc);
    for(int i = 0; i < argc; i++){
        printf("Token[%d] = %s\n", i, argv[i]);
    }

    return 0;
}