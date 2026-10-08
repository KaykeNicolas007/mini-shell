#include <stdio.h>

int main(int argc, char **args){
    while(--argc > 0){
        printf("Token: %s\n", args[argc]);
    }
    return 0;
}