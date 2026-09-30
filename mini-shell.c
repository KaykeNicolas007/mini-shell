#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

void type_prompt(){
    printf(AZUL"mini-shell: "RESET);
    fflush(stdout);
}

char **tokenize(char *command){
    char *token;
    char **allTokens = malloc(64 * sizeof(char *));
    
    token = strtok(command, " \n");
    do{
        int i = 0;
        allTokens[i++] = token;        
    } while(token = strtok(NULL, " \n"));
    
    return allTokens;
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