#include <stdio.h>
#include <string.h>

#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

void type_prompt(){
    printf(AZUL"mini-shell: "RESET);
    fflush(stdout);
}

void tokenize(char *command){
    char *token;

    token = strtok(command, " ");
    printf("%s\n", token);

    while(token = strtok(NULL, " ")){
        printf("%s\n", token);
    }
}

int main(){
    char* fgetsResult;
    do {
        type_prompt();

        char command[1024];
        fgetsResult = fgets(command, sizeof(command), stdin);

        if(fgetsResult != NULL){
            tokenize(command);
        }

    } while (fgetsResult != NULL);
    printf("\n");
    return 0;
}