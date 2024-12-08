#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CROPS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int index;
    char name[MAX_NAME_LENGTH];
    char rarity[MAX_NAME_LENGTH];
    char status[MAX_NAME_LENGTH];
} Crop;


int compareByIndex(const void *a, const void *b) {
    return ((Crop *)a)->index - ((Crop *)b)->index;
}

int compareByName(const void *a, const void *b) {
    return strcmp(((Crop *)a)->name, ((Crop *)b)->name);
}

int compareByRarity(const void *a, const void *b) {
    return strcmp(((Crop *)a)->rarity, ((Crop *)b)->rarity);
}

void sortCrops(Crop crops[], int count, int (*compare)(const void *, const void *)) {
    qsort(crops, count, sizeof(Crop), compare);
}

void printCrops(Crop crops[], int count) {
    printf("Index\tName\tRarity\tStatus\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t%s\t%s\n", crops[i].index, crops[i].name, crops[i].rarity, crops[i].status);
    }
}

int main() {
    FILE *file = fopen("cropdata.txt", "r");
    if (!file) {
        perror("Unable to open file");
        return 1;
    }

    Crop crops[MAX_CROPS];
    int count = 0;

    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    
    while (fgets(buffer, sizeof(buffer), file) && count < MAX_CROPS) {
        sscanf(buffer, "%d,%49[^,],%49[^,],%49[^,\n]", &crops[count].index, crops[count].name, crops[count].rarity, crops[count].status);
        count++;
    }
    fclose(file);

    sortCrops(crops, count, compareByIndex);
    printf("Sorted by Index:\n");
    printCrops(crops, count);

    sortCrops(crops, count, compareByName);
    printf("\nSorted by Name:\n");
    printCrops(crops, count);

    sortCrops(crops, count, compareByRarity);
    printf("\nSorted by Rarity:\n");
    printCrops(crops, count);

    return 0;
}
