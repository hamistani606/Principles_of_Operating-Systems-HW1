/* ------------------------------------------------------------------------------------------------------
    File Name:                  simpleshell.c
    Description:                A general system process call API in C that uses fork, wait, and execvp
    Coder:                      Heather Amistani
    Class:                      CS 446, 1001
    Assignment:                 Homework 1: Process API
    Date:                       2024/02/11
 --------------------------------------------------------------------------------------------------------*/

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <unistd.h> 

#define LENGTHMAX 1024
#define TOKENSMAX 64

int parseInput(char *input, char *splitCommand[]);
void changeDirectories(char*);
int executeCommand(char* []);

int main(){
    char input[LENGTHMAX];
    char *splitCommand[TOKENSMAX];
    int running = 1;

    while(running){
        printf("$ ");
        fgets(input, sizeof(input), stdin);
        parseInput(input, splitCommand);
        if(strcmp(splitCommand[0], "exit") == 0){
            break;
        }
        executeCommand(splitCommand);
    }

    return 0;
}

int parseInput(char *userInput, char *splitCommand[]){
    int commandIndex = 0;
    splitCommand[0] = strtok(userInput, " \n");
    while(splitCommand[commandIndex] != NULL){
        splitCommand[++commandIndex] = strtok(NULL, " \n");
    }
    return commandIndex;
}

void changeDirectories(char *path){
    if(chdir(path) != 0){
        perror("chdir failed");
    }
}

int executeCommand(char* splitCommand[]){
    if(splitCommand[0] == NULL) {
        return 1;
    }
    if(strcmp(splitCommand[0], "cd") == 0){
        changeDirectories(splitCommand[1]);
        return 0;
    }
    pid_t pid = fork();
    if(pid == 0){
        if(execvp(splitCommand[0], splitCommand) == -1){
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else if(pid < 0){
        perror("fork");
        return 1;
    } else{
        int status;
        waitpid(pid, &status, 0);
    }
    return 0;
}