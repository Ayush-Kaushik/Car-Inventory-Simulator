#ifndef CAR_STORAGE_SIMULATOR_
#define CAR_STORAGE_SIMULATOR_

typedef struct Car
{
    int returnDate;
    int mileCar;
    char * numPlate;
    struct Car * next;
    struct Car * prev;

} Car;

typedef struct file
{
    char * carRented;
    char * availableRent;
    char * inRepair;
} File;


void mainProgram(int argc, char const *argv[]);//this will run the main program

File * getInput(); //get user input

char * removeNewline(char * string);

File * createFileNames(char * rented, char * repair, char * available);

void openFiles(File * names);

void freeFiles(File * files);

void getData(FILE * rentFile, FILE * availableFile, FILE * repairFile);

Car * storeFile(FILE * openFile);

char * checkPlate(char * value);
char * getPlate();
int getMiles();
int checkDigit(char symbol);

int checkDate(char * value);

int checkMileage(char * value);

Car * createNode(char * plate, int date, int mileage);

Car * organizeList(Car * list, Car * data_node);

void printList(Car * list);


void operations(Car * rentList, Car * availableList, Car * repairList);

int getOption();



//----- IN PROGRAM OPTIONS ------

Car * Option1(Car * availableList);
Car * getCar();
Car * searchList(Car * list, Car * node);
Car * createCar(char * plate, int date, int mileage);
void freeNode(Car * node);
Car * removeNode(Car * list, Car * toBeRemoved);
Car * getFirstCar(Car * list);

void Option7();
void freeList(Car * list);



int mathOperator(char symbol);



#endif