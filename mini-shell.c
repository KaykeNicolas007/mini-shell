#include <stdio.h>

#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

int main(){
    char* fgetsResult;
    do {
        printf(AZUL"mini-shell: "RESET);

        char command[1024];
        fgetsResult = fgets(command, sizeof(command), stdin);

        printf("%s", command);
    } while (fgetsResult != NULL);
    printf("saindo...\n");
    return 0;
}