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

    int List1 = 0;
    int List2 = 1;
    int List3 = 2;

    storeFile(rentFile, List1);
    storeFile(availableFile, List2);
    storeFile(repairFile, List3); //need to store values inside structs and return a linked list of those
}

void storeFile(FILE * openFile, int ListType) //to store the files in a certain way just pass in values as parameters and then based on that just organise your linked list
{


    printf("LIST NUMBER: %d\n", ListType);
    char storeVal[100] = {0};
    char * plateNumber; //this will have a malloced value of the plate number
    int returnDate;
    int mileage;

    int count = 0; //this is to check up which value has been sent in -- if 1 then plateNumber, if 2 then mieage, if 3 then return date


    char value[100] = {0}; //this will store the strings one by one
    int t = 0; //this is for iteration



    Car * list = NULL; //this will store the linked list

    while(fgets(storeVal, 100, openFile) != NULL)
    {
        count = 0;
        t = 0;
        for(int i = 0; i < strlen(storeVal); i++)
        {
            if(storeVal[i] != ',' && storeVal[i] != '\n')
            {
                value[t] = storeVal[i];
                t++;
            }

            else
            {
                t = 0;
                switch(count)
                {
                    case 0:
                        plateNumber = checkPlate(value);
                        // printf("plate number: %s", plateNumber);
                         //remove this free statement and move it to another place in the code
                        //a function that will check and return the plate number
                        break;

                    case 1:
                        //a function that will check the date and return it in integer format
                        returnDate = checkDate(value);
                        // printf("return date: %d", returnDate);
                        break;

                    case 2:
                        //a function that will check the mileage and return it
                        mileage = checkMileage(value);
                        //printf("Mileage: %d\n", mileage);
                    break;

                }
                count++;
                memset(value, 0, strlen(value));
            }
        }

        Car * data_node = createNode(plateNumber, returnDate, mileage);
        printf("Plate: %s, Date: %d, Mileage: %d\n", data_node->numPlate, data_node->returnDate, data_node->mileCar);


        //based on the list type, simply organize the list


        //create a loading animation on terminal when the file is being loaded
    }

    //close the file here.


    //create a special loop that will test the file on the spot and write out which values cannot be stored.

    //this will create a list and return the link of that list
    //it won't be void anymore, after doing that I will use the three linked lists to run my main program
}


Car * createNode(char * plate, int date, int mileage)
{
    Car * node = malloc(sizeof(Car));
    node->numPlate = malloc(sizeof(char) * strlen(plate));
    strcpy(node->numPlate, plate);
    free(plate);

    node->returnDate = date;
    node->mileCar = mileage;

    return node;
}


char * checkPlate(char * value)
{
    //check for malloc, if it is returned properly

    //add the logic here to check if the value returned is correct

    char * string = malloc(sizeof(char) * strlen(value));
    strcpy(string, value);
    return string;
}


int checkDate(char * value)
{
    //add logic here to check if the date is not a non-alphabetcal character

    int date = atoi(value);
    return date;
}


int checkMileage(char * value)
{
    int miles = atoi(value);
    return miles;
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