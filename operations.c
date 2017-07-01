#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "include.h"

//do each option 1 by one

void operations(Car * rentList, Car * availableList, Car * repairList)
{
    int option = 0;
    option = getOption();
    printf("User selected: %d\n", option);

    Car * toBeAdded = NULL;

    while(option != 8)
    {
        switch(option)
        {
            case 1:
                availableList = Option1(availableList);  //this doesn't leak memory and works fine.          
                break;

            case 2:
                toBeAdded  = getCar();
                Car * returnVal = searchList(rentList, toBeAdded);

                if(returnVal == NULL)
                {
                    printf("The node does not exist in this list -- rentList\n");
                    break;
                }

                Car * value = createCar(returnVal->numPlate, returnVal->returnDate, returnVal->mileCar);
                availableList = organizeList(availableList, value);
                rentList = removeNode(rentList, value);
                break;

            case 3:
                toBeAdded = getCar();
                Car * returnValue = searchList(rentList, toBeAdded);

                if(returnValue == NULL)
                {
                    printf("the node does not exist in this list -- rentList Option 3\n");
                    break;
                }

                Car * valueCar = createCar(returnValue->numPlate, returnValue->returnDate, returnValue->mileCar);
                repairList = organizeList(repairList, valueCar);
                rentList = removeNode(rentList, valueCar);
                break;

            case 4:
                toBeAdded = getCar();
                printf("WORKS\n");
                Car * returnValue2 = searchList(repairList, toBeAdded);
                printf("WORKSX2\n");

                if(returnValue2 == NULL)
                {
                    printf("the node does not exist in this list -- rentList Option 3\n");
                    break;
                }

                Car * valueCar2 = createCar(returnValue2->numPlate, returnValue2->returnDate, returnValue2->mileCar);
                availableList = organizeList(availableList, valueCar2);
                repairList = removeNode(repairList, valueCar2);
                break;

            case 5:
                toBeAdded = getFirstCar(availableList);
                if(toBeAdded == NULL)
                {
                    printf("There is no car in the availableList\n");
                    break;
                }
                Car * toBeRented = createCar(toBeAdded->numPlate, toBeAdded->returnDate, toBeAdded->mileCar);
                rentList = organizeList(rentList, toBeRented);
                availableList = removeNode(availableList, toBeRented);
                break;

            case 6:
                printf("CARS AVAILABLE\n");
                printList(availableList);

                printf("CARS RENTED\n");
                printList(rentList);

                printf("CARS UNDER REPAIR\n");
                printList(repairList);
                break;


            case 7:
                printf("Quit simulator\n");
                freeList(rentList);
                freeList(availableList);
                freeList(repairList);

                Option7(); //need to free all the lists
                break;
        }

        option = getOption();
        printf("User selected: %d\n", option);
    }
}


Car * getFirstCar(Car * list)
{
    Car * temp = list;

    if(temp == NULL)
    {
        return NULL;
    }

    return temp;
}


int getOption()
{
    char userInput[100] = {0};
    int option = 0;

    printf("\n\nTASKS\n");
    printf("  (1) add a new car to the available-for-rent list\n");
    printf("  (2) Add a returned car to the available-for-rent list\n");
    printf("  (3) add a returned car to the repair list\n");
    printf("  (4) Transfer a car from the repair list to the available-for-rent list\n");
    printf("  (5) rent the first available car\n");
    printf("  (6) Print all the lists\n");  
    printf("  (7) quit\n");

    do
    {
        printf("Option: ");
        fgets(userInput, 100, stdin);
        char * input = removeNewline(userInput);
        option = atoi(input);
        memset(userInput, 0, strlen(userInput));
    } while(option <= 0 || option >= 8);

    return option;
}



Car * Option1(Car * availableList)
{
    printf("Make new car available to rent\n");
    Car * car_node = getCar();
    availableList = organizeList(availableList, car_node);
    printf("Added new car\n");
    return availableList;
}


Car * removeNode(Car * list, Car * toBeRemoved)
{
    Car * temp = list;

    if(temp == NULL)
    {
        printf("List is empty");
        return NULL;
    }


    while(temp != NULL)
    {
        if(strcmp(toBeRemoved->numPlate, temp->numPlate) == 0 && (toBeRemoved -> mileCar == temp->mileCar))
        {
            printf("Found Car to be removed\n");
            break;
            
        }
        temp = temp->next;
    }

            if(temp->next == NULL && temp->prev == NULL) //when list only has one node
            {
                printf("Entered only one node\n");
                printList(temp);
                freeList(temp);
                list = NULL;
            }

            else if(temp->next != NULL && temp->prev != NULL) //middle of the list
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;

                freeNode(temp);
            }

            else if(temp->next != NULL && temp->prev == NULL) //front of the list
            {
                printf("Removing from the front of node:\n");
                list->next->prev = NULL;
                list = list->next;  
                freeNode(temp);              
            }

            else if(temp->next == NULL && temp->prev != NULL) //at the end of the list
            {
                temp->prev->next = NULL;
                freeNode(temp);
            }

    return list;
}

Car * searchList(Car * list, Car * node) //This searches the list and returns a pointer to the node
{
    Car * temp = list;
    Car * findNode = NULL;

    while(temp != NULL)
    {
        if(strcmp(node->numPlate, temp->numPlate) == 0 && (node -> mileCar == temp->mileCar))
        {
            printf("Found Car\n");
            findNode = temp;
            freeNode(node);
            return findNode;
        }

        temp = temp->next;
    }


    return NULL;
}


void freeNode(Car * node)
{
    free(node->numPlate);
    free(node);
}

Car * createCar(char * plate, int date, int mileage)
{
    Car * node = malloc(sizeof(Car));
    node->numPlate = malloc(sizeof(char) * (strlen(plate) + 1));
    strcpy(node->numPlate, plate);

    node->returnDate = date;
    node->mileCar = mileage;
    node->next = NULL;
    node->prev = NULL;

    return node;
}



Car * getCar() //this gets the user input and returns the value --based on the type of operation chosen by the user
{
    char * plateNumber;
    int mileage = 0;
    int date = -111111;
    plateNumber = getPlate();
    mileage = getMiles();
    Car * node = createNode(plateNumber, date, mileage);
    return node;
}


void Option7()
{
    printf("SELECTED :::: Quit this program\n");
    exit(1);
    return;
}





