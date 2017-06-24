#ifndef CAR_STORAGE_SIMULATOR_
#define CAR_STORAGE_SIMULATOR_

typedef struct Car
{
    int returnDate;
    int mileCar;
    char * numPlate;
    struct Car * next;

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

void storeFile(FILE * openFile, int ListType);

char * checkPlate(char * value);

int checkDate(char * value);

int checkMileage(char * value);

Car * createNode(char * plate, int date, int mileage);
#endif