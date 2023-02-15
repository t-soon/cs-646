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
    int test = 0;
    while (1)
    {
	    char *input = NULL;          //for storing the user input
        printf("exampleShelltsoon$ ");
        scanf("%m[^\n]", &input); //reads the string into input
        //printf("%s", input);
        char *parsedInput[20];
        //pass input to parseInput
        int last = parseInput(input, parsedInput);
        //Add NULL as last string in array <-- hmmm
        parsedInput[last] = NULL;
        /* code */
        if (strcmp ("exit", parsedInput[0]) == 0) //command is exit
        {
            //this one works!
            return 0; //return from main
        }
        else if (strcmp ("cd", parsedInput[0]) == 0) //command is change directories
        {
            changeDirectories(parsedInput[1]); //use chdir
        }
        else //use execvp
        {
            int success;
            success = executeCommand(parsedInput);
            if (success == 1)
            {
                printf("execvp failure");
            }
            else{
                printf("not failure");
            }
            
        }
        test++;
    }
	return 0;
}

int executeCommand(char *command[])
{
	/*code */
    int status;
    int idx = 1;
    while (command[idx] != NULL) {
        if (fork() == -1)
        {
            /* fork failed */
            printf("fork failed!");
        } else {
            /*do child*/
            int exeOutput = execvp(command[0], command);
            if (exeOutput == -1)
            {
                //the process failed; only returns if error
                return 1;
            }
            wait(&status);
        }
    }
}

void changeDirectories(char *inputPath)
{
	/*Use chdir with the input path */
    int success = chdir(inputPath);
	if(success == -1 ){
        printf("Path Not Found! \n");
    } else {
        printf("complete \n");
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

