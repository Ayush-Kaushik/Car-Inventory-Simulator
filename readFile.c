#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "include.h"


//THIS C FILE CONTAINS FUNCTION FOR INITIALISATION AND OPENING OF FILES

int main(int argc, char const *argv[]) //just the starting point
{
    mainProgram(argc, argv);
    return 0;
}

void mainProgram(int argc, char const *argv[]) //starts the program itself
{
    File * names = getInput(); 
    openFiles(names);
}
 
File * getInput() //gets the user input for file names
{
    char carRent[100] = {0};
    char carRepair[100] = {0};
    char carAvailable[100] = {0};

    printf("Welcome to car rental simulator\n");
    printf("Input the following lists\n");
    printf("Rented Cars: ");
    fgets(carRent, 100, stdin);
    char * rented = removeNewline(carRent);

    printf("Cars under repair: ");
    fgets(carRepair, 100, stdin);
    char * repair = removeNewline(carRepair);

    printf("Cars available for rent: ");
    fgets(carAvailable, 100, stdin);
    char * available = removeNewline(carAvailable);

    File * fileNames = createFileNames(rented, repair, available);
    return fileNames;
}

File * createFileNames(char * rented, char * repair, char * available) //creates the file names
{
    File * name = malloc(sizeof(File)); //a malloced struct with file names
    name->carRented = malloc(sizeof(char) * (strlen(rented) + 1));
    strcpy(name->carRented, rented);

    name->availableRent = malloc(sizeof(char) * (strlen(available) + 1));
    strcpy(name->availableRent, available);

    name->inRepair = malloc(sizeof(char) * (strlen(repair) + 1));
    strcpy(name->inRepair, repair);
    return name;
}


void openFiles(File * names) //opens the files
{
    FILE * rentFile = fopen(names->carRented, "r");
    FILE * availableFile = fopen(names->availableRent, "r");
    FILE * repairFile = fopen(names->inRepair, "r");

    if(rentFile == NULL || availableFile == NULL || repairFile == NULL) 
    {
        printf("Please re-run the program with correct input files\n");

        if(rentFile != NULL)
        {
            fclose(rentFile);
        }

        if(availableFile != NULL)
        {
            fclose(availableFile);
        }
        
        if(repairFile != NULL)
        {
            fclose(repairFile);
        }
          
        freeFiles(names);
        exit(1);
    }

    freeFiles(names);
    getData(rentFile, availableFile, repairFile);
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