#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Allocates memory dynamically for a character array
 * of length+1. The extra +1 is for the null character.
 *
 */
char* stringAlloc(int length)
{
    return ((char*)malloc(sizeof(char)*length+1));
}

/*
 * Returns the number of arguments in a given string 'line',
 * delimited by a single space
 *
 */
int getNumberOfArgs(char *line)
{
    int i, argCount=1;
    for(i=0; line[i]!='\0'; i++)
        if(line[i] == ' ')
            argCount++;
    return argCount;
}

/*
 * Returns the string starting from index 'lowerIndex'
 * to 'higherIndex' in the given string 'string'.
 */
char* getStringFromIndex(char *string, int lowerIndex, int higherIndex)
{
    int i,k=0;
    char *newString = stringAlloc(higherIndex-lowerIndex+1);
    for(i=lowerIndex; i <= higherIndex; i++)
        newString[k++] = string[i];
    newString[i] = '\0';
    return newString;
}

/*
 * Returns an array of arguments as strings.
 * A single line of string with arguments delimited by a space
 * and the number of arguments must be provided as inputs.
 *
 */
char** splitToArgArray(char* line, int argc)
{
    int i,argIndex=0, lowerIndex;
    char** argv = malloc(sizeof(char*)*argc);
    char* stringFromIndex;

    /*
     * The for loop below, iterates through all the characters in the input 'line',
     * and copies the characters from lowerIndex to 'i' ( i is the higher index ) to
     * the arguments array.
     */
    for(i=0, lowerIndex=0; line[i]!='\0'; i++)
    {
        if(line[i] == ' ')
        {
            argv[argIndex] = stringAlloc(i-lowerIndex+1);
            stringFromIndex = getStringFromIndex(line, lowerIndex, i);

            strcpy(argv[argIndex], stringFromIndex);
            argIndex++;
            lowerIndex=i+1;

            /* Free up memory used to find string from index */
            free(stringFromIndex);
        }

    }

    /* For the last argument */
    argv[argIndex] = stringAlloc(i-lowerIndex+1);
    stringFromIndex = getStringFromIndex(line, lowerIndex, i);
    strcpy(argv[argIndex], stringFromIndex);

    /* Free up memory used to find string from index */
    free(stringFromIndex);

    return argv;
}

int ourMain(int argc, char* argv[])
{
    /* Print the arguments stored in the array argv */
    int i;
    for(i=0; i<argc; i++)
        printf("\nArgument %d is %s", i+1, argv[i]);
    return 0;
}

int main()
{
    char **argv; // Arguments array.
    char *argLine=malloc(sizeof(char)); // Stores Input line read from the user.
                                        // Initialized to '\0' if args are not provided.
    int argc; // Stores the argument count.
    int lineLength=0;
    char ch;

    // Read in a line of contents until user hits ‘Enter’
    while((ch=getchar()) != '\n')
    {
        argLine = (char*) realloc(argLine, sizeof(char)*(lineLength+1));
        argLine[lineLength++] = ch;
    }
    argLine[lineLength]='\0';

    if( argLine[0] != '\0')
    {
        // Find the no. of arguments in the line entered by user
        argc=getNumberOfArgs(argLine);

        // Split the line entered by user into an array of arguments
        argv=splitToArgArray(argLine, argc);

        // Call our hypothetical main function
        ourMain(argc, argv);

        // Free up memory used by arguments array
        free(argv);
    }
    else
        printf("No arguments! ");

    free(argLine); // Free up memory used by input line.

    return 0;
}

