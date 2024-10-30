#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //para direccion de la primera parte
#define PROMPT '$'
#define CYAN "\x1b[36m"
#define RESET "\033[0m"
#define COMMAND_LINE_SIZE 1024

void imprimir_prompt();
char *read_line(char *line); 
int parse_args(char **args, char *line);
int execute_line(char *line);
int check_internal(char **args);
int internal_cd(char **args);
int internal_export(char **args);
int internal_source(char **args);
int internal_jobs(char **args);
int internal_fg(char **args);
int internal_bg(char **args);

int main(){
    char line[COMMAND_LINE_SIZE];
    while(1){
        imprimir_prompt();
        if(read_line(line)){
            execute_line(line);
        }
    }
}

char *read_line(char *line){

    if(fgets(line,COMMAND_LINE_SIZE, stdin) != NULL){
        printf("Has introducido: %s", line);
        for(int i = 0; i < COMMAND_LINE_SIZE; i++){
            if(line[i] == '\n' ){
                line[i] == '\0';
                break;
            }
        }
        return line;
    } else{
        if(feof(stdin)){
            printf("Adios\n");
            exit(0);
        }
    }
    return NULL;
}

int execute_line(char *line){
    char *args[COMMAND_LINE_SIZE];
    int tok = parse_args(args,line);
    if(tok > 0){
        check_internal(args);
    } else{
        printf("no hay tokens");
    }
}

int check_internal(char **args){
    if (strcmp(args[0], "cd") == 0) {
        return internal_cd(args);
    }
    //export
    else if (strcmp(args[0], "export") == 0) {
        return internal_export(args);
    }
    //source
    else if (strcmp(args[0], "source") == 0) {
        return internal_source(args);
    }
    //jobs
    else if (strcmp(args[0], "jobs") == 0) {
        return internal_jobs(args);
    }
    //fg
    else if (strcmp(args[0], "fg") == 0) {
        return internal_fg(args);
    }
    //bg
    else if (strcmp(args[0], "bg") == 0) {
        return internal_bg(args);
    }
    //exit
    else if (strcmp(args[0], "exit") == 0) {
        printf("Adios\n");
        exit(0);
    }

    return 0;
}

int parse_args(char **args, char *line){
    int num = 0;
    int booleano = 0;
    char *token = strtok(line," ");

    while(token != NULL){
        for (int i = 0; token[i] != '\0'; i++) {
            if (token[i] == '#') {
                if(token[i+1] != '\0'){
                    printf("Token[%d]: %s\n", num, token); 
                    args[num] = NULL;  
                    printf("Token[%d] corregido: NULL\n", num); 
                    booleano = 1;
                    break;
                } else{
                    token[i] = '\0';
                }
            }
        }
        if(booleano){
            //si encontramos un '#' dejamos de mirar la linea
            break;
        }

        if((token[num] == '\0')){
            args[num] = NULL;
            printf("Token[%d]: NULL\n", num);
        } else{
            args[num] = token;
            printf("TokenPORRA[%d]: %s\n", num, token);
        }
        num++;

        token = strtok(NULL, " ");
    }
    args[num] = NULL;

    return num;
}

int internal_cd(char **args){
    printf("Se implementará esta función posteriormente\n");
    return 1;
}
int internal_export(char **args){
    printf("Se implementará esta función posteriormente\n");
    return 1;
}
int internal_source(char **args){
    printf("Se implementará esta función posteriormente\n");
    return 1;
}
int internal_jobs(char **args){
    printf("Se implementará esta función posteriormente\n");
    return 1;
}
int internal_fg(char **args){
    printf("Se implementará esta función posteriormente\n");
    return 1;
}
int internal_bg(char **args){
    printf("Se implementará esta función posteriormente\n");
    return 1;
}

void imprimir_prompt(){
    char direct[COMMAND_LINE_SIZE];
    const char *user = getenv("USER");
    const char *home = getenv("HOME");

    // Obtener el directorio actual
    if (getcwd(direct, sizeof(direct)) != NULL) {
        printf(CYAN "%s:%s$ " RESET , user ? user : "usuario", direct );
        fflush(stdout);
        sleep(1);  
    } else {
        perror("getcwd() error");
    }
}