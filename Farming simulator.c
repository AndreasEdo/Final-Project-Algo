#include "struct.c"
#include "randomizer.c"

void shop_menu(int *coins, const char *filename, const char *inventory) {
    while (1) {
        // Transfer all the file to struct
        FILE *file = fopen(filename, "r+");
        if (file == NULL) {
            perror("Error opening file");
            return;
        }

        Crop crops[MAX_RECORDS];
        int count = 0;
        char line[MAX_LINE_LENGTH];

        fgets(line, sizeof(line), file); // Skip the header line

        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%d,%19[^,],%9[^,],%9s", 
                   &crops[count].index, crops[count].name, 
                   crops[count].rarity, crops[count].status);
            count++;
        }
        fclose(file);

        // Shop menu
        int option;
        int recordNumber;
        while (1) {
            printf("---WELCOME TO THE SHOP---\n");
            printf("1. Common Box (50 Coin)\n");
            printf("2. Rare Box (100 Coin)\n");
            printf("3. Epic Box (200 Coin)\n");
            printf("0. Exit Shop\n");
            printf("Choose an Option: ");
            scanf("%d", &option);
            if (option == 1) {
                if (*coins >= 50) {
                    recordNumber = commonbox();
                    *coins -= 50; // Deduct coins correctly
                    break;
                }
                printf("You don't have enough money!!\n");
            } else if (option == 2) {
                if (*coins >= 100) {
                    recordNumber = rarebox();
                    *coins -= 100; // Deduct coins correctly
                    break;
                }
                printf("You don't have enough money!!\n");
            } else if (option == 3) {
                if (*coins >= 200) {
                    recordNumber = epicbox();
                    *coins -= 200; // Deduct coins correctly
                    break;
                }
                printf("You don't have enough money!!\n");
            } else if (option == 0) {
                printf("Exiting shop\n");
                Sleep(5000);
                system("cls");
                return; // Exit the shop menu
            }
            printf("Invalid Input\n");
        }

        // Rewrite the crop's status
        Crop *crop = &crops[recordNumber - 1];
        strcpy(crop->status, "Obtained");

        printf("\nRecord updated successfully. YOU GOT %s (%s)\n", crop->name, crop->rarity);

       
        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return;
        }

        fprintf(file, "Index,Name,Rarity,Status\n");
        for (int i = 0; i < MAX_RECORDS; i++) {
            fprintf(file, "%d,%s,%s,%s\n", 
                    crops[i].index, crops[i].name, 
                    crops[i].rarity, crops[i].status);
        }
        fclose(file);

       
        file = fopen(inventory, "r+");
        if (file == NULL) {
            perror("Error opening file");
            return;
        }

        Inventory invencrop[MAX_RECORDS] = {0};
        count = 0;

        fgets(line, sizeof(line), file); 

        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%19[^,],%9[^,],%d", 
                   invencrop[count].crop.name, 
                   invencrop[count].crop.rarity, 
                   &invencrop[count].quantity);
            count++;
        }
        fclose(file);

        for (int i = 0; i < count; i++) {
            if (strcmp(invencrop[i].crop.name, crop->name) == 0) {
                invencrop[i].quantity += 1; 
                break;
            } else if (i == count - 1) {
     
                strcpy(invencrop[count].crop.name, crop->name);
                strcpy(invencrop[count].crop.rarity, crop->rarity);
                invencrop[count].quantity = 1;
                count++;
                break;
            }
        }

        file = fopen(inventory, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return;
        }

        fprintf(file, "Name,Rarity,Quantity\n");
        for (int i = 0; i < count; i++) {
            if (invencrop[i].quantity > 0) {
                fprintf(file, "%s,%s,%d\n", 
                        invencrop[i].crop.name, invencrop[i].crop.rarity, invencrop[i].quantity);
            }
        }
        fclose(file);

        printf("\n--- Updated Inventory ---\n");
        for (int i = 0; i < count; i++) {
            printf("%s (%s) - Quantity: %d\n", 
                   invencrop[i].crop.name, 
                   invencrop[i].crop.rarity, 
                   invencrop[i].quantity);
        }
        printf("-------------------------\n");

        Sleep(5000); 
    }
}

void displayplotcrop(const char *plotFile) {
    printf("\n----PLOTS STATUS----\n");
    FILE *file = fopen(plotFile, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    typedef struct {
        int number;
        char status[15];
        Crop plotcrop;
        int water_needed;
        int time_to_harvest;
    } Plot;

    Plot plotData;
    char line[MAX_LINE_LENGTH];

    // Print table header
    printf("\n%-5s%-15s%-20s%-10s%-15s%-15s\n", "Num", "Status", "Crop Name", "Rarity", "Water Needed", "Time to Harvest");
    printf("--------------------------------------------------------------------------------------------\n");

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
        perror("Error opening file");
        return;
    }
	printf("-------INVENTORY-------");
    Inventory inventory;
    char line[MAX_LINE_LENGTH];

    // Print table header
    printf("\n%-20s%-10s%-10s\n", "Name", "Rarity", "Quantity");
    printf("------------------------------------------\n");

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



void plantCrop(const char *plotFile, const char *inventoryFile) {
    system("cls");
    displayinventory(inventoryFile);
    displayplotcrop(plotFile);

    // Load inventory data
    FILE *file = fopen(inventoryFile, "r+");
    if (file == NULL) {
        perror("Error opening inventory file");
        return;
    }

    Inventory inventory[MAX_RECORDS];
    int countinv = 0;
    char line[MAX_LINE_LENGTH];

    fgets(line, sizeof(line), file); // Skip the header line
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%19[^,],%9[^,],%d", 
               inventory[countinv].crop.name, inventory[countinv].crop.rarity, &inventory[countinv].quantity);
        countinv++;
    }
    fclose(file);

    // Load plot data
    file = fopen(plotFile, "r+");
    if (file == NULL) {
        perror("Error opening plot file");
        return;
    }

    typedef struct {
        int number;
        char status[15];
        Crop plotcrop;
        int water_needed;
        int time_to_harvest;
    } Plot;

    Plot plotData[5];
    int count = 0;

    fgets(line, sizeof(line), file); // Skip the header line
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%14[^,],%19[^,],%9[^,],%d,%d", 
               &plotData[count].number, plotData[count].status, 
               plotData[count].plotcrop.name, plotData[count].plotcrop.rarity, 
               &plotData[count].water_needed, &plotData[count].time_to_harvest);
        count++;
    }
    fclose(file);

    // Ask user for crop choice
    char cropchoice[100];
    int cropFound = 0, i;
    while (1) {
        printf("\nChoose a crop to plant: ");
        scanf("%s", cropchoice);

        for (i = 0; i < countinv; i++) {
            if (strcmp(inventory[i].crop.name, cropchoice) == 0) {
                cropFound = 1;
                break;
            }
        }

        if (cropFound) break;
        printf("Invalid crop name! Try again.(Make sure the capital Letter is correct)\n");
    }

    // Ask user for plot choice
    int plotchoice;
    while (1) {
        printf("Choose a plot to plant (1-5): ");
        scanf("%d", &plotchoice);

        if (plotchoice >= 1 && plotchoice <= 5) {
            plotchoice--; // Convert to 0-based index
            if (strcmp(plotData[plotchoice].status, "NotPlanted") == 0) {
                break;
            }
            printf("Plot is already planted! Choose another plot.\n");
        } else {
            printf("Invalid plot choice! Try again.\n");
        }
    }

    // Update inventory and plot data
    inventory[i].quantity -= 1;
    strcpy(plotData[plotchoice].plotcrop.name, inventory[i].crop.name);
    strcpy(plotData[plotchoice].plotcrop.rarity, inventory[i].crop.rarity);
    strcpy(plotData[plotchoice].status, "Planted");

    if (strcmp(plotData[plotchoice].plotcrop.rarity, "Common") == 0) {
        plotData[plotchoice].time_to_harvest = Common.time;
        plotData[plotchoice].water_needed = Common.water;
    } else if (strcmp(plotData[plotchoice].plotcrop.rarity, "Uncommon") == 0) {
        plotData[plotchoice].time_to_harvest = Uncommon.time;
        plotData[plotchoice].water_needed = Uncommon.water;
    } else if (strcmp(plotData[plotchoice].plotcrop.rarity, "Rare") == 0) {
        plotData[plotchoice].time_to_harvest = Rare.time;
        plotData[plotchoice].water_needed = Rare.water;
    } else if (strcmp(plotData[plotchoice].plotcrop.rarity, "Epic") == 0) {
        plotData[plotchoice].time_to_harvest = Epic.time;
        plotData[plotchoice].water_needed = Epic.water;
    } else if (strcmp(plotData[plotchoice].plotcrop.rarity, "Legendary") == 0) {
        plotData[plotchoice].time_to_harvest = Legendary.time;
        plotData[plotchoice].water_needed = Legendary.water;
    }

    // Remove crop from inventory if quantity is 0
    if (inventory[i].quantity <= 0) {
        for (int j = i; j < countinv - 1; j++) {
            inventory[j] = inventory[j + 1];
        }
        countinv--;
    }

    // Save updated inventory
    file = fopen(inventoryFile, "w");
    if (file == NULL) {
        perror("Error saving inventory file");
        return;
    }

    fprintf(file, "Name,Rarity,Quantity\n");
    for (int j = 0; j < countinv; j++) {
        fprintf(file, "%s,%s,%d\n", inventory[j].crop.name, inventory[j].crop.rarity, inventory[j].quantity);
    }
    fclose(file);

    // Save updated plot data
    file = fopen(plotFile, "w");
    if (file == NULL) {
        perror("Error saving plot file");
        return;
    }

    fprintf(file, "Num,Status,CropName,CropRarity,WaterNeeded,TimeToHarvest\n");
    for (int j = 0; j < count; j++) {
        fprintf(file, "%d,%s,%s,%s,%d,%d\n", plotData[j].number, plotData[j].status, 
                plotData[j].plotcrop.name, plotData[j].plotcrop.rarity, 
                plotData[j].water_needed, plotData[j].time_to_harvest);
    }
    fclose(file);

    system("cls");
    printf("Crop planted successfully!\n");
    displayplotcrop(plotFile);
}




int main() {

  
    int coins = 1000;
	

    printf("Welcome to the Advanced Farming Game!\n");
	
  	int season_days = SEASON_DAYS;
    while (season_days > 0) { 
		int daily_actions = 10;
        while (daily_actions > 0 && season_days > 0) {
        	
			system("cls");
            printf("=== Season Progress ===\n");
            printf("Days remaining: %d\n", season_days);
            printf("Coins: %d\n", coins);
            printf("Actions remaining today: %d\n", daily_actions);
            printf("=======================\n");
			
			displayplotcrop(PLOT);
			
            printf("\n--- Actions ---\n");
            printf("1. Plant Crops\n");
            printf("2. Water Crops\n");
            printf("3. Harvest Crops\n");
            printf("4. Visit Shop\n");
            printf("5. Wait a Day (Ends Actions)\n");
            printf("----------------\n");
			
			
            int action;
            while(1){
            	printf("\nEnter Input(1-5):");
            	scanf("%d", &action);
            	if(action >= 1 && action <= 5){
            		break;
				}
				
				printf("\nInvalid Input!!!");
			}
			
            switch (action) {
                case 1: { 
                	plantCrop(PLOT, INVENTORY);
					break;
                }
                case 2: { // Water Crops
					break;
                }
                case 3: { // Harvest Crops
                    break;
                }
                case 4: { // Visit Shop
    				printf("\n--- Visiting Box Shop ---\n");
    				shop_menu(&coins, FILENAME, INVENTORY);
    				daily_actions--;
    				break;
                }
                case 5: { // Wait a Day
                    printf("\n--- Waiting a Day ---\n");

                    daily_actions = 0; // End all remaining actions for the day

                
                    printf("A day has passed.\n");
                    break;
                }
                default:
                    printf("Invalid action! Please choose a number between 1 and 5.\n");
                    break;
            }

            
        }

        if (daily_actions == 0 && season_days > 0) {
            printf("\nYou have used all actions for today. Moving to the next day...\n");

            season_days--;

        }
    }

    // Season ended
    printf("=== Season Over ===\n");
    printf("Total coins earned: %d\n", coins);
    printf("===================\n");


    return 0;
}

