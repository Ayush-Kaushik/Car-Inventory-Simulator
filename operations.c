#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "include.h"

void operations(Car * rentList, Car * availableList, Car * repairList)
{
    int option = 0;
    option = getOption();
    printf("User selected: %d\n", option);
    Car * node = NULL;

    while(option != 7)
    {
        switch(option)
        {
            case 1:
                printf("Add a new car to the available-for-rent list\n");
                availableList = Option1(availableList);                
                break;

            case 2:
                printf("Add a returned car to the available-for-rent list\n");
                node = Option2_3(rentList);

                if(node == NULL)
                {
                    printf("There is no car in that list that matches your request\n");
                }

                else
                {
                    availableList = organizeList(availableList, node);
                }
                break;

            case 3:
                printf("Add a returned car to the repair list\n");
                node = Option2_3(rentList);

                if(node == NULL)
                {
                    printf("Cannot find the car in the rent list\n");
                }

                else
                {
                    repairList = organizeList(repairList, node);
                    printf("New repairList:\n");
                    printList(repairList);

                }
                break;

            case 4:
                printf("Transfer a car from the repair list to the available-for-rent list\n");
                node = Option4(repairList);

                if(node == NULL)
                {
                    printf("canno find your car in the repair list -- to transfer to available for rent list\n");
                }

                else
                {
                    availableList = organizeList(availableList, node);
                    printf("New available for rent list: \n");
                    printList(availableList);
                }
                break;

            case 5:
                printf("Rent the first available car\n");
                Option5();
                break;

            case 6:
                printf("THE AVAILABLE LIST\n");
                printList(availableList);

                printf("THE RENT LIST\n");
                printList(rentList);

                printf("THE REPAIR LIST\n");
                printList(repairList);
                break;


            case 7:
                printf("Quit this program\n");
                Option7();
                break;
        }

        option = getOption();
        printf("User selected: %d\n", option);
    }
}

int getOption()
{
    char userInput[100] = {0};
    int option = 0;

    do{
        printf("Select user input: ");
        fgets(userInput, 100, stdin);
        char * input = removeNewline(userInput);
        option = atoi(input);
        memset(userInput, 0, strlen(userInput));
    } while(option <= 0 || option >= 8);
    return option;
}

Car * Option1(Car * availableList)
{
    Operation_type  createCar  = op_1;
    Car * car_node = getCar(createCar, availableList); // need to take care of the NULL values

    availableList = organizeList(availableList, car_node);
    printList(availableList);
    return availableList;
}

Car * Option2_3(Car * rentList)
{
    Operation_type  returnCar  = op_2;
    Car * node = getCar(returnCar, rentList); //this is the option to run second loop

    //here I am supposed to get the car value and search the linked list.
    //then return this node. -- make the date equal to -1 because now the car is ready to be sent out for renting again

    if(node == NULL)
    {
        printf("The node returned is NULL, hence the car is not present");
    }

    return node;
}

Car * Option4(Car * repairList)
{
    printf("SELECTED :::: Transfer a car from the repair list to the available-for-rent list\n");

    Operation_type availableCar = op_2;
    Car * node = getCar(availableCar, repairList);

    if(node == NULL)
    {
        printf("The car requested for transfer does not exist in the list\n");
    }

    return node;
}


Car * getCar(Operation_type x, Car * list_type) //this gets the user input and returns the value --based on the type of operation chosen by the user
{
    char input[100] = {0};
    char * value;
    char * plateNumber;
    char * mileageValue;
    int mileage = 0;
    int date = -1;
    Car * node = NULL;
    Car * createdEntry = NULL;
    Car * temp = list_type;

    printf("Enter the plate number: ");
    fgets(input, 100, stdin);
    value = removeNewline(input);
    plateNumber = checkPlate(value);

    printf("Enter the mileage: ");
    fgets(input, 100, stdin);
    mileageValue = removeNewline(input);
    mileage = checkMileage(mileageValue);
    memset(input, 0, strlen(input));


    if(x == op_1)
    {
        node = createNode(plateNumber, date, mileage);
    }

    if(x == op_2)
    {
        //SEARCH AND RETURN THE NODE HERE
        createdEntry = createNode(plateNumber, date, mileage);
        node = searchList(temp, createdEntry);
        printf("Option2: %s %d %d\n", node->numPlate, node->mileCar, node->returnDate);
    }


    return node;
}


//This will search the list and return the pointer to the car that has to be moved to the list
Car * searchList(Car * list, Car * node)
{
    Car * temp = list;
    Car * foundCar = NULL;
    if(temp == NULL)
    {
        printf("The list is empty\n");
        // return NULL;
    }

    while(temp->next != NULL)
    {
        if((strcmp(temp->numPlate, node->numPlate) == 0) && (temp->mileCar == node->mileCar))
        {

            printf("Found a car in the list\n");
            foundCar = temp;
            break;

            //return NULL; //change this into an actual value
        }

        temp = temp->next;
    }

    if(foundCar != NULL)
    {
        printf("foundCar: %s %d %d\n", foundCar->numPlate, foundCar->mileCar, foundCar->returnDate);
        printf("the car before foundCar: %s %d %d\n",foundCar->prev->numPlate, foundCar->prev->mileCar, foundCar->prev->returnDate);

        //now simply remove that car and join the linked list

        foundCar->prev->next = foundCar->next;
        foundCar->next->prev = foundCar->prev;

        foundCar->next = NULL;
        foundCar->prev = NULL;
    }    
    return foundCar;
}



void Option5()
{
    printf("SELECTED :::: Rent the first available car\n");
    return;
}


void Option7()
{
    printf("SELECTED :::: Quit this program\n");
    return;
}




