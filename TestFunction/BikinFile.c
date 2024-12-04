#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "cropdata.txt"
#define MAX_LINE_LENGTH 100
#define MAX_RECORDS 48

typedef struct {
    int index;
    char name[20];
    char rarity[10];
    char status[10];
} Crop;

// Function to read and display all records from the CSV file
void readAllRecords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Crop crop;
    char line[MAX_LINE_LENGTH];

    printf("\n%-5s%-20s%-10s%-10s\n", "ID", "Name", "Rarity", "Status");
    printf("--------------------------------------------------\n");

    // Skip header line
    fgets(line, sizeof(line), file);

    // Read records
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%19[^,],%9[^,],%9s", 
               &crop.index, crop.name, crop.rarity, crop.status);

        printf("%-5d%-20s%-10s%-10s\n", 
               crop.index, crop.name, crop.rarity, crop.status);
    }

    fclose(file);
}

// Function to add or update a record in the CSV file
void addOrUpdateRecord(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read all records into memory
    Crop crops[MAX_RECORDS];
    int count = 0;
    char line[MAX_LINE_LENGTH];

    // Skip header line
    fgets(line, sizeof(line), file);

    // Read records into the array
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%19[^,],%9[^,],%9s", 
               &crops[count].index, crops[count].name, 
               crops[count].rarity, crops[count].status);
        count++;
    }
    fclose(file);

    // Prompt user for record details
    int recordNumber;
    printf("Enter record number to add or update (1-%d): ", MAX_RECORDS);
    scanf("%d", &recordNumber);

    if (recordNumber < 1 || recordNumber > MAX_RECORDS) {
        printf("Invalid record number.\n");
        return;
    }

    Crop *crop = &crops[recordNumber - 1];

    printf("Enter crop name: ");
    scanf("%s", crop->name);
    printf("Enter rarity (Common/Uncommon/Rare/Epic/Legendary): ");
    scanf("%s", crop->rarity);
    printf("Enter status (Obtained/Not): ");
    scanf("%s", crop->status);

    // Write updated records back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Write header
    fprintf(file, "Index,Name,Rarity,Status\n");

    // Write all records
    for (int i = 0; i < MAX_RECORDS; i++) {
        fprintf(file, "%d,%s,%s,%s\n", 
                crops[i].index, crops[i].name, 
                crops[i].rarity, crops[i].status);
    }

    fclose(file);
    printf("Record updated successfully.\n");
}

// Main menu
int main() {
    int choice;

    do {
        printf("\nCrop Management System\n");
        printf("1. View All Records\n");
        printf("2. Add/Update a Record\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readAllRecords(FILENAME);
                break;
            case 2:
                addOrUpdateRecord(FILENAME);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

