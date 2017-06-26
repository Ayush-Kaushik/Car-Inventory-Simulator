#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "include.h"

int main(int argc, char const *argv[])
{
    mainProgram(argc, argv);
    return 0;
}

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

    Car * rentList = storeFile(rentFile, List1);
    Car * availableList = storeFile(availableFile, List2);
    Car * repairList = storeFile(repairFile, List3); //need to store values inside structs and return a linked list of those
    operations(rentList, availableList, repairList);
}

Car * storeFile(FILE * openFile, int ListType) //to store the files in a certain way just pass in values as parameters and then based on that just organise your linked list
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
        // printf("Plate: %s, Date: %d, Mileage: %d\n", data_node->numPlate, data_node->returnDate, data_node->mileCar);

        list = organizeList(list, data_node);
        //create a loading animation on terminal when the file is being loaded
    }

    printList(list);
    return list;

    
}


Car * createNode(char * plate, int date, int mileage)
{
    Car * node = malloc(sizeof(Car));
    node->numPlate = malloc(sizeof(char) * strlen(plate));
    strcpy(node->numPlate, plate);
    free(plate);

    node->returnDate = date;
    node->mileCar = mileage;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


Car * organizeList(Car * list, Car * data_node)
{

    Car * temp = list; //this is another pointer to add values to the list
    if(temp == NULL)
    {
        temp = data_node;
        return temp;
    }

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = data_node;
    data_node->prev = temp;
    return list;
}


//do you want to write the output to a file?

void printList(Car * list)
{
    Car * temp = list;
    while(temp != NULL)
    {
        printf("Plate: %s, Date: %d, Mileage: %d\n", temp->numPlate, temp->returnDate, temp->mileCar);
        temp = temp->next;
    }
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