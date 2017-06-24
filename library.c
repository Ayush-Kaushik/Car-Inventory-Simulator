#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "include.h"

//OKAY FIRST TRY TO MAKE STRUCTS OUT OF CAR INFORMATION
//ASK CO-OP COUNCELLER IF I COULD UPLOAD THIS FILE AS A GITHUB PROJECT
//FINISH THIS AND THEN MAKE THE CODE MORE COMPACT IN SECOND VERSION -- CREATE A NEW BRANCH OF THIS INFORMATION


int main(int argc, char const *argv[])
{
    mainProgram(argc, argv);
    return 0;
}

//Close the files -> I dont need list types since I already have three lists and they will be stored in eahc list seperately.

void mainProgram(int argc, char const *argv[])
{
    File * names = getInput(); 
    openFiles(names);
}

void openFiles(File * names)
{
    FILE * rentFile = fopen(names->carRented, "r");
    FILE * availableFile = fopen(names->availableRent, "r");
    FILE * repairFile = fopen(names->inRepair, "r");

    if(rentFile == NULL || availableFile == NULL || repairFile == NULL) 
    {
        printf("Please re-run the program with correct input files\n");
        freeFiles(names);
        exit(1);
    }

    getData(rentFile, availableFile, repairFile);
}

void getData(FILE * rentFile, FILE * availableFile, FILE * repairFile)
{
    storeFile(rentFile);
    storeFile(availableFile);
    storeFile(repairFile); //need to store values inside structs and return a linked list of those
}

void storeFile(FILE * openFile)
{
    char storeVal[100] = {0};
    while(fgets(storeVal, 100, openFile) != NULL)
    {
        printf("%s", storeVal);
    }

    //close the file here.


    //create a special loop that will test the file on the spot and write out which values cannot be stored.

    //this will create a list and return the link of that list
    //it won't be void anymore, after doing that I will use the three linked lists to run my main program
}

void freeFiles(File * files)
{
    if(files != NULL)
    {
        free(files->carRented);
        free(files->availableRent);
        free(files->inRepair);
        free(files);
    }
    
    return;
}

File * getInput()
{
    char carRent[100] = {0};
    char carRepair[100] = {0};
    char carAvailable[100] = {0};

    printf("Welcome to car rental simulator\n");
    printf("Enter the file containing car that are rented: ");
    fgets(carRent, 100, stdin);

    char * rented = removeNewline(carRent);

    printf("Enter the file containing car in repair: ");
    fgets(carRepair, 100, stdin);
    char * repair = removeNewline(carRepair);

    printf("Enter the file containing car availabe for rent ");
    fgets(carAvailable, 100, stdin);
    char * available = removeNewline(carAvailable);

    File * fileNames = createFileNames(rented, repair, available);
    return fileNames;
}

File * createFileNames(char * rented, char * repair, char * available)
{
    File * name = malloc(sizeof(File));
    name->carRented = malloc(sizeof(char) * strlen(rented));
    strcpy(name->carRented, rented);

    name->availableRent = malloc(sizeof(char) * strlen(available));
    strcpy(name->availableRent, available);

    name->inRepair = malloc(sizeof(char) * strlen(repair));
    strcpy(name->inRepair, repair);

    return name;
}

//this function removed newline
char * removeNewline(char * string)
{
    int ln = strlen(string);
    if(string[ln-1] == '\n') {
        string[ln-1] = '\0';
    }
    return string;
}