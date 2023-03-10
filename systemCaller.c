#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <sys/stat.h> 

int parseInput(char *input, char *parseInput[]);
void changeDirectories(char *inputPath);
int executeCommand(char *command[]);

int main()
{
    while (1)
    {
	    char *input = NULL;          //for storing the user input
        printf("exampleShelltsoon$ ");
        scanf(" %m[^\n]", &input); //reads the string into input; space first to account for \n from input
        char *parsedInput[20];
        int last = parseInput(input, parsedInput);         //pass input to parseInput
        parsedInput[last] = NULL;         //Add NULL as "last" string in array
        /* code */
        if (strcmp ("exit", parsedInput[0]) == 0) //command is exit
        {
            return 0; //return from main
        }
        else if (strcmp ("cd", parsedInput[0]) == 0) //command is change directories
        {
            changeDirectories(parsedInput[1]); //use chdir
        }
        else //use execvp
        {
            int success = executeCommand(parsedInput);
            if (success == 1)
            {
                printf("execvp failure");
            }
        }
    }
	return 0;
}

int executeCommand(char *command[])
{
	/*code */
    int status;
    int exeOutcome;
    
    if (fork() != 0)
    {
        wait(&status);  
    }
    else {
        /* fork succeeded */
        exeOutcome = execvp(command[0], command);
        if (exeOutcome == -1){
            return 1;
        }
    }
    
}

void changeDirectories(char *inputPath)
{
	/*Use chdir with the input path */
    int success = chdir(inputPath);
	if(success == -1 ){
        printf("Path Not Found! \n");
    }
}

int parseInput(char *inputStr, char *splitWords[])
{
      int wordInd = 0;
      splitWords[0] = strtok(inputStr, " \n"); //gets first token
      while(splitWords[wordInd] != NULL){     
            splitWords[++wordInd] = strtok(NULL, " \n"); //walks through rest of tokens (splits on " " and "\n")
      }
      return wordInd;
}

