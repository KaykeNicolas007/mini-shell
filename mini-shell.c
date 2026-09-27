#include <stdio.h>

int main(){
    printf("mini-shellzinho: ");

    char command[20];
    fgets(command, sizeof(command), stdin);

    printf("\nResultado: %s\n", command);
    return 0;
}