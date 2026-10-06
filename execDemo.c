#include <stdio.h>

int main(int argc, char **args){
    while(--argc > 0){
        printf("Token: %s\n", args[argc]);
    }
    printf("Fim da execução.\n");
    return 0;
}