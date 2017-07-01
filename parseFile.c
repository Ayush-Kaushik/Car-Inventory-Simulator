#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "include.h"


//THIS C FILE DEALS WITH PARSING THE FILE OPENED AND CREATING LINKED LISTS OUT OF IT

void getData(FILE * rentFile, FILE * availableFile, FILE * repairFile)
{
    Car * rentList = storeFile(rentFile);
    Car * availableList = storeFile(availableFile);
    Car * repairList = storeFile(repairFile);
    operations(rentList, availableList, repairList);
}

Car * storeFile(FILE * openFile)
{
    char storeVal[100] = {0};
    char value[100] = {0};
    char * plateNumber;
    int returnDate = 0;
    int mileage = 0;
    int count = 0;
    int t = 0; 
    Car * list = NULL; //head of linked list

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
                        break;

                    case 1:
                        returnDate = checkDate(value);
                        break;

                    case 2:
                        mileage = checkMileage(value);
                        break;
                }
                count++;
                memset(value, 0, strlen(value));
            }
        }


        if(plateNumber == NULL || returnDate == -111111 || mileage == -1) 
        {
            mileage = 0;
            returnDate = 0;
        }

        else
        {
            Car * data_node = createNode(plateNumber, returnDate, mileage);
            list = organizeList(list, data_node);
        }
    }

    fclose(openFile);
    printList(list);
    return list;
}

char * checkPlate(char * value)
{
    int number = 0;
    int length = strlen(value);
<<<<<<< HEAD
=======
//-------------------------------------------
>>>>>>> af78209b30bed2e453398a5823fc03c0bcd475a6

    for(int i = 0; i < strlen(value); i++)
        {
            number = mathOperator(value[i]);

            if(number == -1)
            {
                break;
            }
            else
            {
                if(length == i)
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if(number == -1)
        {
            return NULL;
        }

<<<<<<< HEAD
=======

//--------------------------------------------

>>>>>>> af78209b30bed2e453398a5823fc03c0bcd475a6
        char * string = malloc(sizeof(char) * (strlen(value) + 1));
        strcpy(string, value);
        return string;
}

int checkDate(char * value) //check for user input non-alphabetical characters
{
    int number = 0;
    int date = 0;

    if(strlen(value) != 8)
    {
        printf("%s\n", value);
        return -111111;
    }

    for(int i = 0; i < strlen(value); i++)
        {
            number = checkDigit(value[i]);

            if(number == -1)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        if(number == -1)
        {
            return -111111;
        }

    date = atoi(value);
    return date;
}

int checkMileage(char * value)
{
    int number = 0;
    int miles = 0;
        for(int i = 0; i < strlen(value); i++)
        {
            number = checkDigit(value[i]);

            if(number == -1)
            {
                break;
            }
            else
            {
                continue;
            }
        }

        if(number == -1)
        {
            return -1;
        }


    miles = atoi(value);
    return miles;
}

Car * createNode(char * plate, int date, int mileage)
{
    Car * node = malloc(sizeof(Car));
    node->numPlate = malloc(sizeof(char) * (strlen(plate) + 1));
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

    Car * temp = list;
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

