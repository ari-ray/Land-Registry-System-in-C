#include <stdio.h>
#include <string.h>

#define MAX_RECORDS 200

//Struct to hold a single land record
typedef struct{
    int khatianNumber; //unique identifier for a plot of land
    char ownerName[100];
    char plotNumber[20];
    float area; //size of land (in shotok)
    char landType[20];
    int lastYr; //last year tax was paid
} LandRecord;

//Global variable to track number of records
int currentSize = 0;

//Safe input function for strings
void safeInput(char *buffer, int size){
    if(fgets(buffer, size, stdin)){
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline
    }
}

//Prompt user to enter a new land record
void promptRecordDetails(LandRecord *recordPtr){
    printf("\nEnter Khatian Number: ");
    scanf("%d", &recordPtr->khatianNumber);
    getchar(); 

    printf("Enter Owner Name: ");
    safeInput(recordPtr->ownerName, sizeof(recordPtr->ownerName)); //for reading the strings

    printf("Enter Plot Number: ");
    safeInput(recordPtr->plotNumber, sizeof(recordPtr->plotNumber));

    printf("Enter Land Area (shotok): ");
    scanf("%f", &recordPtr->area);
    getchar();

    printf("Enter Land Type: ");
    safeInput(recordPtr->landType, sizeof(recordPtr->landType));

    printf("Enter Last Payment Year: ");
    scanf("%d", &recordPtr->lastYr);
    getchar();
}

//Display a single record
void displayRecord(const LandRecord *recordPtr){
    printf("\nKhatian Number: %d\n", recordPtr->khatianNumber);
    printf("Owner Name: %s\n", recordPtr->ownerName);
    printf("Plot Number: %s\n", recordPtr->plotNumber);
    printf("Land Area: %.2f shotok\n", recordPtr->area);
    printf("Land Type: %s\n", recordPtr->landType);
    printf("Last Tax Payment Year: %d\n", recordPtr->lastYr);
}

//Find records by khatian number
int findrecordsbykhatian(LandRecord registry[], int searchKhatian, LandRecord *results, int maxResults){
    int count = 0;
    for (int i = 0; i < currentSize; i++) {
        if (registry[i].khatianNumber == searchKhatian && count < maxResults) {
            results[count++] = registry[i];
        }
    }
    return count;
}

//Generate a list of defaulters
int getdefaulterlist(LandRecord registry[], int currentYear, LandRecord *results){
    int count = 0;
    for (int i = 0; i < currentSize; i++) {
        if (registry[i].lastYr < currentYear) {
            results[count++] = registry[i];
        }
    }
    return count;
}

//Save registry to a text file
void saveregistrytofile(LandRecord registry[], const char *filename){
    FILE *fp = fopen(filename, "w");
    if(!fp){
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(fp, "%d\n", currentSize);

    for(int i = 0; i < currentSize; i++){
        fprintf(fp, "%d|%s|%s|%.2f|%s|%d\n",
                registry[i].khatianNumber,
                registry[i].ownerName,
                registry[i].plotNumber,
                registry[i].area,
                registry[i].landType,
                registry[i].lastYr);
    }

    fclose(fp);
    printf("Registry saved successfully to '%s'.\n", filename);
}

//Load registry from a text file
void loadregistrytofile(LandRecord registry[], const char *filename) {
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("Error opening file for reading.\n");
        return;
    }

    int count = 0;
    if(fscanf(fp, "%d\n", &count) != 1){
        printf("Error reading record count.\n");
        fclose(fp);
        return;
    }

    if(count > MAX_RECORDS){
        printf("File contains too many records.\n");
        fclose(fp);
        return;
    }

    for(int i = 0; i < count; i++){
        char line[300];
        if (!fgets(line, sizeof(line), fp)) {
            printf("Error reading record %d\n", i+1);
            fclose(fp);
            return;
        }
        sscanf(line, "%d|%99[^|]|%19[^|]|%f|%19[^|]|%d",  //storing a line safely
               &registry[i].khatianNumber,
               registry[i].ownerName,
               registry[i].plotNumber,
               &registry[i].area,
               registry[i].landType,
               &registry[i].lastYr);
    }

    currentSize = count;
    fclose(fp);
    printf("Registry loaded successfully from '%s'.\n", filename);
}

// Main program
int main(){
    LandRecord registry[MAX_RECORDS];
    LandRecord searchArray[MAX_RECORDS];
    LandRecord defaulterList[MAX_RECORDS];
    int choice, khatian, found, defaulternumber;

    do {
        printf("\n\nMenu:\n");
        printf("1. Add new land record\n");
        printf("2. Search record by khatian\n");
        printf("3. Display all records\n");
        printf("4. Generate Tax defaulters\n");
        printf("5. Save registry to file\n");
        printf("6. Load registry from file\n");
        printf("0. Exit\n");
        printf("Select option: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch(choice){
            case 1:
                if(currentSize < MAX_RECORDS){
                    promptRecordDetails(&registry[currentSize]);
                    currentSize++;
                }
                else{
                    printf("Registry full!\n");
                }
                break;

            case 2:
                printf("Enter Khatian Number: ");
                scanf("%d", &khatian);
                getchar();

                found = findrecordsbykhatian(registry, khatian, searchArray, MAX_RECORDS);
                if(found == 0){
                    printf("Not registered.\n");
                } 
                else{
                    for (int i = 0; i < found; i++) {
                        displayRecord(&searchArray[i]);
                    }
                }
                break;

            case 3:
                for(int i = 0; i < currentSize; i++){
                    displayRecord(&registry[i]);
                }
                break;

            case 4:
                defaulternumber = getdefaulterlist(registry, 2025, defaulterList);
                if(defaulternumber == 0){
                    printf("No defaulters.\n");
                } 
                else{
                    for(int i = 0; i < defaulternumber; i++){
                        displayRecord(&defaulterList[i]);
                    }
                }
                break;

            case 5:
                saveregistrytofile(registry, "Register.txt");
                break;

            case 6:
                loadregistrytofile(registry, "Register.txt");
                break;

            case 0:
                printf("Exiting...\n");
                break;

                
            default:
                printf("Invalid choice.\n");
                break;
        }
    }while(choice != 0);

    return 0;
}