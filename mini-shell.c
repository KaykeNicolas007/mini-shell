#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"
#define MAX_ARGS 64
#define MAX_COMMAND_SIZE 1024

void type_prompt(){
    printf(BLUE"mini-shell: "RESET);
    fflush(stdout);
}

char **tokenize(char *command){
    char *token;
    char **allTokens = malloc(MAX_ARGS * sizeof(char *));
    
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

        char command[MAX_COMMAND_SIZE];
        fgetsResult = fgets(command, sizeof(command), stdin);

        if(fgetsResult != NULL){
            tokenize(command);
        }
    } while (fgetsResult != NULL);

    printf("\n");
    return 0;
}