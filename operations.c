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

    while(option != 8)
    {
        switch(option)
        {
            case 1:
                printf("Make new car available to rent\n");
                availableList = Option1(availableList);  //this doesn't leak memory and works fine.          
                break;

            case 2:
                printf("add a returned car to the available-for-rent list\n"); //no memory leaks here
                node = Option2_3(rentList);

                if(node == NULL)
                {
                    printf("Option 2 -- No vehicle match your request\n");
                }

                else
                {
                    availableList = organizeList(availableList, node);
                }
                break;

            case 3:
                printf("Move returned car to Garage for repair\n");
                node = Option2_3(rentList);

                if(node == NULL)
                {
                    printf("Option 3 -- No vehicle match your request\n");
                }

                else
                {
                    repairList = organizeList(repairList, node);
                    printList(repairList);
                }
                break;

            case 4:
                printf("Transfer repaired car to the available for rent section\n");
                node = Option4(repairList);

                if(node == NULL)
                {
                    printf("Option 4 -- No vehicle match your request\n");
                }

                else
                {
                    availableList = organizeList(availableList, node);
                    printList(availableList);
                }
                break;

            case 5: //THIS SECTION SEGFAULTS -- NEED TO FIX THIS

                printf("Fix this section\n");
                // printf("Rent the first available car\n");
                // Car * temp = rentList->next; //This will store the one node after value in the list
                // Car * node = Option5(rentList);

                // availableList = organizeList(availableList, node);
                // printList(availableList);
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



Car * Option1(Car * availableList) //This is option 1
{
    Operation_type  createCar  = op_1;
    Car * car_node = getCar(createCar, availableList); // need to take care of the NULL values
    availableList = organizeList(availableList, car_node);
    printf("Added new car\n");
    return availableList;
}



Car * Option2_3(Car * rentList) //make the date equal to -1 because now the car is ready to be sent out for renting again
{
    Operation_type  returnCar  = op_2;
    Car * node = getCar(returnCar, rentList); //this is the option to run second loop

    if(node == NULL)
    {
        printf("No Cars rented out\n");
    }

    return node;
}

Car * Option4(Car * repairList)
{
    Operation_type availableCar = op_2;
    Car * node = getCar(availableCar, repairList);

    if(node == NULL)
    {
        printf("No cars under repair\n");
    }

    return node;
}


Car * getCar(Operation_type x, Car * list_type) //this gets the user input and returns the value --based on the type of operation chosen by the user
{
    char * plateNumber;

    int mileage = 0;
    int date = -1;

    Car * node = NULL;
    Car * createdEntry = NULL;
    Car * temp = list_type;

    plateNumber = getPlate();
    mileage = getMiles();


    if(x == op_1)
    {
        node = createNode(plateNumber, date, mileage);
    }

    if(x == op_2)
    {

        printf("THIS IS FOR OPTION 2\n");
        createdEntry = createNode(plateNumber, date, mileage);
        node = searchList(temp, createdEntry);
        //node could be null
    }

    return node;
}


//This will search the list and return the pointer to the car -- remove the node from teh list later
Car * searchList(Car * list, Car * node) //dont remove the node itself, simply return a poiter to that value
{
    Car * head = list;
    Car * temp = list;
    Car * foundCar = NULL;
    if(temp == NULL)
    {
        printf("List is empty\n");
        return NULL;
    }

    while(temp != NULL)
    {
        if((strcmp(temp->numPlate, node->numPlate) == 0) && (temp->mileCar == node->mileCar))
        {
            printf("Found a car in the list\n");
            foundCar = temp;
            break;
        }

        temp = temp->next;
    }

    if(foundCar != NULL)
    {
        printf("foundCar: %s %d %d\n", foundCar->numPlate, foundCar->mileCar, foundCar->returnDate);
        //logic used to be here to remove the node from the list
    }


    //FREE THE NODES HERE FOR 
    free(node->numPlate);
    free(node);


    return foundCar;
}



Car * Option5(Car * rentList)
{
    printf("SELECTED :::: Rent the first available car\n");
    Car * node = extractFirstCar(rentList);
    return node;
}



//SEG FAULTS HERE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! -- need to fix this
Car * extractFirstCar(Car * rentList) //only return the pointer to the first list
{
    Car * temp = rentList;

    if(temp == NULL)
    {
        printf("the list is empty\n");
        return NULL;
    }

    

    rentList = rentList->next;
    temp->next->prev = NULL; //this will unlink the first node
    temp->next = NULL;

    if(temp->next == NULL)
    {
        printf("The node next pointer is NULL\n");
    }

    if(temp->prev == NULL)
    {
        printf("The node prev pointer is NULL\n");
    }

    printf("The first node:%s %d %d\n", temp->numPlate, temp->mileCar, temp->returnDate);
    printf("SEG FAULT\n");

    return temp;
}

void Option7()
{
    printf("SELECTED :::: Quit this program\n");
    exit(1);
    return;
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



