#include "struct.h"

void displayplotcrop(const char *plotFile) {
    printf("\n=== PLOTS STATUS ===\n");
    FILE *file = fopen(plotFile, "r");
    if (file == NULL) {
        perror("Error opening file!");
        Sleep(3000);
        return;
    }


    plot plotData;
    char line[MAX_LINE_LENGTH];
	
    // Print table header
    printf("\n%-5s%-15s%-20s%-10s%-15s%-15s\n", "Num", "Status", "Crop Name", "Rarity", "Water Needed", "Time to Harvest");
    printf("--------------------------------------------------------------------------------\n");
	
    // Skip header line
    fgets(line, sizeof(line), file);

    // Read records and print data
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%14[^,],%19[^,],%9[^,],%d,%d", 
               &plotData.number, plotData.status, plotData.plotcrop.name, plotData.plotcrop.rarity, 
               &plotData.water_needed, &plotData.time_to_harvest);
        
       

        printf("%-5d%-15s%-20s%-10s%-15d%-15d\n", 
               plotData.number, plotData.status, plotData.plotcrop.name, plotData.plotcrop.rarity, 
               plotData.water_needed, plotData.time_to_harvest);
    }

    fclose(file);
}

void displayinventory(const char *inventoryFile) {
    FILE *file = fopen(inventoryFile, "r");
    if (file == NULL) {
        perror("Error opening file!");
        Sleep(3000);
        return;
    }
	printf("=== INVENTORY ===\n");
    Inventory inventory;
    char line[MAX_LINE_LENGTH];

    // Print table header
    printf("\n%-20s%-10s%-10s\n", "Name", "Rarity", "Quantity");
    printf("--------------------------------------\n");

    // Skip header line
    fgets(line, sizeof(line), file);

    // Read records and print data
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%19[^,],%9[^,],%d", 
               inventory.crop.name, inventory.crop.rarity, &inventory.quantity);

        printf("%-20s%-10s%-10d\n", 
               inventory.crop.name, inventory.crop.rarity, inventory.quantity);
    }

    fclose(file);
}
