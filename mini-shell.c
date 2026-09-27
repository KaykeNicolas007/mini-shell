#include <stdio.h>

#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

int main(){
    while (1){
        printf(AZUL"mini-shell: "RESET);

        char command[1024];
        fgets(command, sizeof(command), stdin);

        printf("%s\n", command);
    }
    return 0;
}