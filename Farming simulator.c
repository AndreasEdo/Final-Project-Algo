#include "struct.c"
#include "randomizer.c"

#include "Animasi/gotoxy.c"
#include "Animasi/Animasinanam.c"
#include "Animasi/Animasishop.c"

void shop_menu(int *coins, const char *filename, const char *inventory) {
    while (1) {
        // Transfer all the file to struct
        system("cls");
        textonly();
        FILE *file = fopen(filename, "r+");
        if (file == NULL) {
            perror("Error opening file");
            return;
        }

        Crop crops[MAX_RECORDS];
        int count = 0;
        char line[MAX_LINE_LENGTH];

        fgets(line, sizeof(line), file); 

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
        int cost;
        while (1) {
        	
        	
        	gotoxy(0,0);
            printf("---WELCOME TO THE SHOP---\n");
            printf("Coins:%d", *coins);
    
			if(*coins < -450){
            	printf("(Dont't go over -500 I repeat do not)\n");
			}else if(*coins < -400){
            	printf("(Please tell me you have a plan)\n");
			}else if(*coins < -250){
            	printf("(You are deeply in debt)\n");
			}else if(*coins < 0){
				printf("(It's fine you can fix that)\n");
			}else{
				printf("\n");
			}
			
            printf("1. Common Box (50 Coin)\n");
            printf("2. Rare Box (100 Coin)\n");
            printf("3. Epic Box (200 Coin)\n");
            printf("0. Exit Shop\n");
            printf("Choose an Option: ");
            scanf("%d", &option);
            if (option == 1) {
                
                recordNumber = commonbox();
                cost = 50;
                *coins -= 50; // Deduct coins correctly
                break;
                
            } else if (option == 2) {
                
                recordNumber = rarebox();
                cost = 100;
                *coins -= 100; // Deduct coins correctly
                break;
                
            } else if (option == 3) {
                
                recordNumber = epicbox();
                cost = 200;
                *coins -= 200; 
                break;
                
            } else if (option == 0) {
            	goodbye();
            	Sleep(2000);
                goinghomeanimation();
                system("cls");
                return; // Exit the shop menu
            }
            wronginput();
            Sleep(1000);
            system("cls");
        }

        // Rewrite the crop's status
        Crop *crop = &crops[recordNumber - 1];
        if(strcmp(crops[recordNumber-1].status,"Not") == 0){
        	printf("You got a new seed\n");
		}
        strcpy(crop->status, "Obtained");
		
		system("cls");
        printf("\nInventory updated successfully. YOU GOT %s (%s)\n", crop->name, crop->rarity);
        printf("Coins -%d (Coins:%d)\n", cost, *coins);

       
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
            Sleep(5000);
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
        if(count == 0){
        	count = 1;
		}
        fclose(file);
		
        for (int i = 0; i < count; i++) {
            if (strcmp(invencrop[i].crop.name, crop->name) == 0) {
                invencrop[i].quantity += 1; 
                break;
            } else if (i == count-1) {
     
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
        shopkeeperbuy();
        Sleep(2000);
    }
}

void plotstatuschanger(const char *plotFile){
	plot plotData[5];
	int count =0;
	char line[MAX_LINE_LENGTH];
	FILE *file;
	file = fopen(plotFile, "r+");
    if (file == NULL) {
        perror("Error opening plot file");
        return;
    }



    
    fgets(line, sizeof(line), file); 
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%14[^,],%19[^,],%9[^,],%d,%d", 
               	&plotData[count].number, plotData[count].status, 
               	plotData[count].plotcrop.name, plotData[count].plotcrop.rarity, 
               	&plotData[count].water_needed, &plotData[count].time_to_harvest);
        count++;
    }
    fclose(file);
    
    for(int i=0;i<5;i++){
    	if(plotData[i].time_to_harvest == 0 && plotData[i].water_needed == 0){
    		strcpy(plotData[i].status, "Ready");
		}else if(plotData[i].time_to_harvest > 0 || plotData[i].water_needed > 0){
			strcpy(plotData[i].status, "Planted");
		}else if(plotData[i].time_to_harvest == -1 && plotData[i].water_needed == -1){
			strcpy(plotData[i].status, "NotPlanted");
		}
	}
	
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
	
}

void displayplotcrop(const char *plotFile) {
    printf("\n----PLOTS STATUS----\n");
    FILE *file = fopen(plotFile, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }


    plot plotData;
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



void plantCrop(const char *plotFile, const char *inventoryFile,int *moves) {
    
	while(1){
		system("cls");
		printf("\nActions left today:%d\n\n", *moves);
			
		if(*moves == 0){
			printf("\nYou have used all your Actions for today Exiting");
			Sleep(5000);
		    return;
		}
		
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
	
	    fgets(line, sizeof(line), file); 
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
	
	
	
	    plot plotData[5];
	    int count = 0;
	
	    fgets(line, sizeof(line), file); 
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
			if(strcmp(cropchoice, "0") == 0){
				printf("Returning to home");
				Sleep(5000);
				return;
			}
			
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
	            plotchoice--; 
	            if (strcmp(plotData[plotchoice].status, "NotPlanted") == 0) {
	            	
	                break;
	            }
	            printf("Plot is already planted! Choose another plot.\n");
	        } else if (plotchoice == 0){
	        	printf("Cancelling planting");
	            Sleep(5000);
	            return;
	        }else{
	        	printf("Invalid plot choice\n");
			}
	    }
		displaynanam();
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
		*moves -= 1;
	    system("cls");
	    printf("Crop planted successfully!\n");
	    Sleep(5000);
	    
	}
}

void watercrop(const char *plotFile, int *moves){
	system("cls");
	while(1){
		plotstatuschanger(plotFile);
		system("cls");
		printf("\nActions left today:%d\n\n", *moves);
			
		if(*moves == 0){
			printf("\nYou have used all your Actions for today Exiting");
			Sleep(5000);
		    return;
		}
		
		
		FILE *file;
		file = fopen(plotFile, "r+");
	    if (file == NULL) {
	        perror("Error opening plot file");
	        return;
	    }
	
	
	
	    plot plotData[5];
	    int count = 0;
		char line[MAX_LINE_LENGTH];
	    fgets(line, sizeof(line), file); 
	    while (fgets(line, sizeof(line), file)) {
	        sscanf(line, "%d,%14[^,],%19[^,],%9[^,],%d,%d", 
	               &plotData[count].number, plotData[count].status, 
	               plotData[count].plotcrop.name, plotData[count].plotcrop.rarity, 
	               &plotData[count].water_needed, &plotData[count].time_to_harvest);
	        count++;
	    }
	    fclose(file);
	    displayplotcrop(plotFile);
	    int plotchoice;
	
	    while(1){
	        printf("\nChoose a plot to water:");
	    	scanf("%d", &plotchoice);
			if(plotchoice >= 1 && plotchoice <= 5){
				if(plotData[plotchoice-1].water_needed <= 0){
					printf("This plot need no more water\n");
				}else{
					plotData[plotchoice-1].water_needed -= 1;
					break;
				}
			}else if(plotchoice == 0){
				printf("\nGoing back inside\n");
				Sleep(5000);
				return;
			}else{
				printf("Invalid input\n");
			}	
		}
		
		printf("Plot %d (-1) water needed\n", plotchoice);
		Sleep(5000);
		
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
	    *moves -= 1;
	    
	}
	
}



void harvestcrop(const char *plotFile, int *coins, int *moves){
	while(1){
		system("cls");
		printf("\nActions left today:%d\n\n", *moves);
			
		if(*moves == 0){
			printf("\nYou have used all your Actions for today Exiting");
			Sleep(5000);
		    return;
		}
		
		
		plot plotData[5];
		int count =0;
		char line[MAX_LINE_LENGTH];
		FILE *file;
		file = fopen(plotFile, "r+");
    	if (file == NULL) {
        	perror("Error opening plot file");
        	return;
    	}



    
    	fgets(line, sizeof(line), file); 
    	while (fgets(line, sizeof(line), file)) {
        	sscanf(line, "%d,%14[^,],%19[^,],%9[^,],%d,%d", 
               		&plotData[count].number, plotData[count].status, 
               		plotData[count].plotcrop.name, plotData[count].plotcrop.rarity, 
               		&plotData[count].water_needed, &plotData[count].time_to_harvest);
        	count++;
    	}
    	fclose(file);
    	
		displayplotcrop(plotFile);
		int choice;
		while(1){
			printf("\nChoose a Plot to harvest(1-5):");
	
			scanf("%d", &choice);
			if(choice >= 1 && choice <= 5){
				if(strcmp(plotData[choice-1].status,"Ready") == 0){
					break;
				}else if((strcmp(plotData[choice-1].status,"Ready")) != 0){
					printf("The plot's seed is not Ready\n");
				}	
			}else if(choice == 0){
				printf("Going back home\n");
				Sleep(5000);
				return;
			}
			
			printf("\nInvalid Input choose another plot\n");
		}
		

		int s;
		if(strcmp(plotData[choice-1].plotcrop.rarity ,"Common") == 0){
			sellrandomizer(Common.sell_value, &coins, &s);
			printf("\nYou earn a total of %d Coins (Your coins: %d)\n", s, *coins);
		}else if(strcmp(plotData[choice-1].plotcrop.rarity ,"Uncommon") == 0){
			sellrandomizer(Uncommon.sell_value, &coins, &s);
			printf("\nYou earn a total of %d Coins (Your coins: %d)\n", s, *coins);
		}else if(strcmp(plotData[choice-1].plotcrop.rarity ,"Rare") == 0){
			sellrandomizer(Rare.sell_value, &coins, &s);
			printf("\nYou earn a total of %d Coins (Your coins: %d)\n", s, *coins);
		}else if(strcmp(plotData[choice-1].plotcrop.rarity ,"Epic") == 0){
			sellrandomizer(Epic.sell_value, &coins, &s);
			printf("\nYou earn a total of %d Coins (Your coins: %d)\n", s, *coins);
		}else if(strcmp(plotData[choice-1].plotcrop.rarity ,"Legendary") == 0){
			sellrandomizer(Legendary.sell_value, &coins, &s);
			printf("\nYou earn a total of %d Coins (Your coins: %d)\n", s, *coins);
		}
		strcpy(plotData[choice-1].plotcrop.name, "None");
		strcpy(plotData[choice-1].status, "NotPlanted");
		strcpy(plotData[choice-1].plotcrop.rarity, "None");
		plotData[choice-1].time_to_harvest = -1;
		plotData[choice-1].water_needed = -1;
	
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
    	*moves -= 1;
    	printf("Moves -1\n");
    	Sleep(5000);
    	
 
    	
    	
	}
	
}

void plottimeremover(const char *plotFile){
	plot plotData[5];
	int count =0;
	char line[MAX_LINE_LENGTH];
	FILE *file;
	file = fopen(plotFile, "r+");
    if (file == NULL) {
        perror("Error opening plot file");
        return;
    }



    
    fgets(line, sizeof(line), file); 
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%14[^,],%19[^,],%9[^,],%d,%d", 
               	&plotData[count].number, plotData[count].status, 
               	plotData[count].plotcrop.name, plotData[count].plotcrop.rarity, 
               	&plotData[count].water_needed, &plotData[count].time_to_harvest);
        count++;
    }
    fclose(file);
    for(int i=0;i<5;i++){
    	if(plotData[i].time_to_harvest != -1 && plotData[i].time_to_harvest != 0){
    		plotData[i].time_to_harvest -= 1;
		}
	}
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
	
}




void inventoryclear(const char *invFile){
	FILE *file;
	file = fopen(invFile, "w");
	fprintf(file, "");
	fclose(file);
}

void plotclear(const char *plotFile){
	FILE *file;
	plot plotData[5];
	file = fopen(plotFile, "r+");
	if (file == NULL) {
        perror("Error opening plot file");
        return;
    }


	char line[MAX_LINE_LENGTH];
    int count;
    fgets(line, sizeof(line), file); 
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%14[^,],%19[^,],%9[^,],%d,%d", 
               	&plotData[count].number, plotData[count].status, 
               	plotData[count].plotcrop.name, plotData[count].plotcrop.rarity, 
               	&plotData[count].water_needed, &plotData[count].time_to_harvest);
        count++;
    }
    fclose(file);
    
    for(int i=0;i<5;i++){
    	strcpy(plotData[i].plotcrop.name, "None");
    	strcpy(plotData[i].plotcrop.rarity, "None");
    	strcpy(plotData[i].status, "NotPlanted");
    	plotData[i].time_to_harvest = -1;
    	plotData[i].water_needed = -1;
	}
	
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
	
}

int main() {

  
    int coins = 50;
	inventoryclear(INVENTORY);
	plotclear(PLOT);
	
    printf("Welcome to the Advanced Farming Game!\n");
    char username[1000];
	char yn;

	do {
    	printf("Input username (up to 20 characters): ");
    	scanf("%s", username);

    	if (strlen(username) > 20) {
        	printf("\nUsername cannot be more than 20 characters\n");
    	} else {
        	printf("\nAre you sure you want your name to be %s?\n", username);
        	printf("Input Y/N: ");

        
        	int c;
        	while ((c = getchar()) != '\n' && c != EOF);

        	scanf("%c", &yn);
    	}
	} while (strlen(username) > 20 || yn == 'n' || yn == 'N');
	
  	int season_days = SEASON_DAYS;
    while (season_days > 0) { 
    	plotstatuschanger(PLOT);
		int daily_actions = 10;
        while (daily_actions > 0 && season_days > 0) {
        	
			system("cls");
            printf("=== Season Progress ===\n");
            printf("Days remaining: %d\n", season_days);
            printf("Coins: %d", coins);
            
            if(coins < -450){
            	printf("(Dont't go over -500 I repeat do not)\n");
			}else if(coins < -400){
            	printf("(Please tell me you have a plan)\n");
			}else if(coins < -250){
            	printf("(You are deeply in debt)\n");
			}else if(coins < -100){
				printf("(You are really-really broke)\n");
			}else if(coins < 0){
				printf("(It's fine you can fix that)\n");
			}else{
				printf("\n");
			}
            printf("Actions remaining today: %d\n", daily_actions);
            printf("=======================\n");
			
			displayplotcrop(PLOT);
			tipsrandomizer();
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
				
				printf("\nInvalid Input!!!\n");
			}
			
            switch (action) {
                case 1: { 
                	plantCrop(PLOT, INVENTORY, &daily_actions);
                
					break;
                }
                case 2: { // Water Crops
                	watercrop(PLOT, &daily_actions);
					break;
                }
                case 3: { // Harvest Crops
                	harvestcrop(PLOT,  &coins, &daily_actions);
                    break;
                }
                case 4: { // Visit Shop
    				shopanimation();
    				shopkeeperanimation();
    				Sleep(1000);
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
                
            }

            
        }
		
//		if(coins <= -500){
//			system("cls");
//			printf("YOU ARE IN BIG TROUBLE");
//			return 0;
//		}
		
        if (daily_actions == 0 && season_days > 0) {
            printf("\nYou have used all actions for today. Moving to the next day...\n");
			plottimeremover(PLOT); 
			wateradderrandomizer(PLOT);
            season_days--;

        }
    }

    // Season ended
    printf("=== Season Over ===\n");
    printf("Total coins earned: %d\n", coins);
    printf("===================\n");


    return 0;
}

