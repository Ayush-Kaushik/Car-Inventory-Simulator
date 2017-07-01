#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "include.h"

//THIS C FILE DEALS WITH MISCELLANEOUS FUNCTIONS THAT ARE USED THROUGHOUT THE PROGRAM

void printList(Car * list)
{
    Car * temp = list;

    if(temp == NULL)
    {
        return;
    }


    while(temp != NULL)
    {
        printf("Plate: %s, Date: %d, Mileage: %d\n", temp->numPlate, temp->returnDate, temp->mileCar);
        temp = temp->next;
    }
}

void freeList(Car * list)
{
    printf("This works\n");
    Car * temp = list;

    while(temp != NULL)
    {
        Car * temp2 = temp;
        temp = temp->next;
        free(temp2->numPlate);
        free(temp2);
     }

     free(temp);
}


int getMiles()
{
    char input[100] = {0};
    int number = 0;


    printf("Enter the mileage: ");
    fgets(input, 100, stdin);
    char * value = removeNewline(input);


    do{
        for(int i = 0; i < strlen(value); i++)
        {

            number = checkDigit(value[i]);

            if(number == -1)
            {
                printf("error\n");
                break;
            }
            else
            {
                printf("no-error\n");
                continue;
            }
        }

        if(number == -1)
        {
            memset(input, 0, strlen(input));
            printf("** Please enter numeric values only **\n\n");
            printf("Enter the mileage: ");
            fgets(input, 100, stdin);
            value = removeNewline(input);
        }

    }while(number == -1);

    number = atoi(value);
    return number;
}


int checkDigit(char symbol)
{
    if(isdigit(symbol))
    {
        return 1;
    }
    
    return -1;
}


char * getPlate() //add logic to check for user input --this will return the plate itself after getting the user input
{
    char input[100] = {0}; //this will get the fgets input
    int number = 0;

    printf("Enter the plate number: ");
    fgets(input, 100, stdin);
    char * value = removeNewline(input);
    printf("%s\n", value);
    int length = strlen(value);

    do
    {
        for(int i = 0; i < strlen(value); i++)
        {
            number = mathOperator(value[i]);

            if(number == -1)
            {
                // printf("error\n");
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
                    // printf("no-error\n");
                    continue;
                }
            }
        }

        if(number == -1)
        {
            memset(input, 0, strlen(input));
            printf("** Please enter alphabetic/ numeric values only **\n\n");
            printf("Enter the plate number: ");
            fgets(input, 100, stdin);
            value = removeNewline(input);
        }
    }while(number == -1);
        

    char * string = malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(string, value);

    return string;
}


int mathOperator(char symbol)
{
    bool isAlphabet = false;
    bool isNumeric = false;

    if(isdigit(symbol) != 0)
    {
        isNumeric = true;
    }

    else if(isalpha(symbol) != 0)
    {
        isAlphabet = true;
    }
    else if(isspace(symbol) != 0)
    {
        return -1;
    }
    else //for symbol
    {
        return -1;
    }

    return 1;
}


char * removeNewline(char * string)
{
    int ln = strlen(string);
    if(string[ln-1] == '\n') {
        string[ln-1] = '\0';
    }
    return string;
}