#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
    int i = 0;
    
    token = strtok(command, " \n");
    do{
        allTokens[i++] = token;        
    } while(token = strtok(NULL, " \n"));
    allTokens[i++] = token;
    
    return allTokens;
}

void execute(char **tokens){
    int p_id = fork();
    int status;

    if(p_id < 0){
        perror("Ocorreu um erro durante a chamada de fork!\n");
        return;
    }

    if(p_id == 0){
        execvp(tokens[0], tokens);
        perror("Ocorreu um erro durante a chamada de execvp!\n");
        exit(EXIT_FAILURE);
    }
    if(p_id > 0){
        waitpid(p_id, &status, 0);
    }
}

int main(){
    char *fgetsResult;
    do {
        type_prompt();

        char command[MAX_COMMAND_SIZE];
        fgetsResult = fgets(command, sizeof(command), stdin);

        char **tokens;
        if(fgetsResult != NULL){
            tokens = tokenize(command);
            execute(tokens);
            free(tokens);
        }

    } while (fgetsResult != NULL);

    printf("\n");
    return 0;
}