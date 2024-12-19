#include "struct.c"
#include "randomizer.c"
#include "function.c"
#include "display.c"
#include "sortingdata.c"
#include "highscore.c"

#include "Animasi/gotoxy.c"
#include "Animasi/Animasinanam.c"
#include "Animasi/Animasishop.c"
#include "Animasi/gantihari.c"
#include "Animasi/gameover.c"
#include "Animasi/animasinyiram.c"
#include "Animasi/animasiawal.c"

void shop_menu(int *coins, const char *filename, const char *inventory);
void plantCrop(const char *plotFile, const char *inventoryFile,int *moves);
void watercrop(const char *plotFile, int *moves);
void harvestcrop(const char *plotFile, int *coins, int *moves);



int main() {
    int coins = STARTING_COINS;
    int cointtoday = coins;
	inventoryclear(INVENTORY);
	plotclear(PLOT);
    char username[1000];
	char yn;
	
	char startingInput[100];
	int startMenu = -1;
	
	char databaseInput[100];
	int databaseMenu = -1;
	
    while (1) {
        do {
        	printf("| Farming C-mulator |\n\n");
            printf("=== STARTING MENU ===\n");
            printf("1. Play\n");
            printf("2. Database\n");
            printf("0. Exit\n");
            printf("---------------------\n\n");
            printf("Enter input: ");
            
            scanf("%s", startingInput);
            startMenu = atoi(startingInput);
            
            system("cls");
            if (startMenu < 0 || startMenu > 2) {
                printf("Invalid input! Please enter a valid input!\n\n");
            }
        } while (startMenu < 0 || startMenu > 2);

        switch (startMenu) {
            case 1:
                printf("Loading game...\n");
                Sleep(3000);
                system("cls");
                goto game;

            case 2:
                printf("Loading data...\n");
                Sleep(3000);
                system("cls");

                while (1) {
                    do {
                        printf("=== DATABASE MENU ===\n");
                        printf("1. High Score\n");
                        printf("2. Crops\n");
                        printf("0. Back to Starting Menu\n");
                        printf("---------------------\n\n");
                        printf("Enter input: ");
                        
                        scanf("%s", databaseInput);
                        databaseMenu = atoi(databaseInput);
                        
                        system("cls");
                        if (databaseMenu < 0 || databaseMenu > 2) {
                            printf("Invalid input! Please enter a valid input!\n\n");
                        }
                    } while (databaseMenu < 0 || databaseMenu > 2);
                    
                    switch (databaseMenu) {
                        case 1:
                            printf("Loading highscores...\n");
                            Sleep(3000);
                            system("cls");
                            highscoreOptionsMenu();
                            Sleep(2000);
                            system("cls");
                            break;
                        case 2:
                            printf("Loading crops...\n");
                            Sleep(3000);
                            system("cls");
                            cropsData();
                            Sleep(2000);
                            system("cls");
                            break;
                        case 0:
                            printf("Returning to Starting Menu...\n");
                            Sleep(3000);
                            system("cls");
                            break;
                    }
                    
                    if (databaseMenu == 0) {
                        break;
                    }
                }
                break;
                
            case 0:
                printf("Exiting...\n");
                Sleep(2000);
                return 0;
        }
    }
	
	game:
	do {
		system("cls");
		printf("=== INPUT USERNAME ===\n\n");
   		printf("Enter (up to 20 characters): ");
   		scanf("%s", username);

	   	if (strlen(username) > 20) {
	       	printf("\nUsername cannot be more than 20 characters!\n");
	       	Sleep(2000);
	   	} else {
	       	printf("\nAre you sure you want your name to be \"%s\"? (Y/N): ", username);

       
       	int c;
       	while ((c = getchar()) != '\n' && c != EOF);

       	scanf("%c", &yn);
   		}
	} while (strlen(username) > 20 || yn == 'n' || yn == 'N');
	
	system("cls");
	intro();
	
	system("cls");
	gotoxy(50,7);
	printf("Good luck \033[0;36m%s\033[0m", username);
	Sleep(3000);
	system("cls");
	suntomoonStart();
  	int season_days = SEASON_DAYS;
    while (season_days > 0) {
		
    	plotstatuschanger(PLOT);
		int daily_actions = 10;
        while (daily_actions > 0 && season_days > 0) {
        	
			system("cls");
            printf("=== SEASON PROGRESS ===\n");
            printf("Days remaining: \033[0;31m%d\033[0m\n", season_days);
            printf("Coin(s): \033[0;33m%d\033[0m ", coins);
            
            if(coins < -450){
            	printf("(Dont't go over -500! I repeat do not!)\n");
			}else if(coins < -400){
            	printf("(Please tell me you have a plan.)\n");
			}else if(coins < -250){
            	printf("(You are deeply in debt.)\n");
			}else if(coins < -100){
				printf("(You are really-really broke.)\n");
			}else if(coins < 0){
				printf("(It's fine you can fix that.)\n");
			}else{
				printf("\n");
			}
            printf("Today's remaining actions: \033[0;34m%d\033[0m\n", daily_actions);
            printf("-----------------------\n");
			
			displayplotcrop(PLOT);
			tipsrandomizer();
            printf("\n=== ACTIONS ===\n");
            printf("1. Plant Crops\n");
            printf("2. Water Crops\n");
            printf("3. Harvest Crops\n");
            printf("4. Visit Shop\n");
            printf("5. Skip a Day (Ends all today's actions)\n");
            printf("6. Retire\n");
            printf("---------------\n");
			
			
            int action;
            while(1){
            	printf("\nEnter input (1-5): ");
            	scanf("%d", &action);
            	if(action >= 1 && action <= 6){
            		break;
				}
				
				printf("\nInvalid input! Please enter a valid input!\n");
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
                	system("cls");
                    printf("Sleeping in the bunk is good, isn't it?\n");
                    Sleep(3000);
					daily_actions = 0; 
                    break;
                }
                case 6: { // Retire
                	system("cls");
					season_days = 0;
                	printf("Looks like farming isn't really suitable for you. Better luck next time!\n");
                    Sleep(4000);
                    system("cls");
                    goodbye();
                    Sleep(2000);
					break;
				}
            }

            
        }
		
		if(coins <= -500){
			system("cls");
			gameover();
			return 0;
		}
		
        if (daily_actions == 0 && season_days > 0) {
        	system("cls");
            printf("You have used all actions for today. Moving to the next day...\n");
            Sleep(2000);
			plottimeremover(PLOT); 
			wateradderrandomizer(PLOT);
            season_days--;
            
            printf("\nYou earn %d coins today!", coins-cointtoday);
            Sleep(2000);
            system("cls");
            suntomoon();
            
            cointtoday = coins;

        }
    }

    // Season ended
    system("cls");
	printf("=== Season Over ===\n");
    printf("Total coins earned: \033[0;33m%d\033[0m\n", coins);
    InputHighScore(username, coins, HIGHSCORE);
    printf("\n\n==========NEW HIGHSCORE===============\n");
    displaySortedByScoreDescending(HIGHSCORE);
    printf("-------------------\n");
    Sleep(7000);
	

    return 0;
}



void shop_menu(int *coins, const char *filename, const char *inventory) {
    while (1) {
        
        //transfer all the cropdata.txt to struct
        system("cls");
        textonly();
        FILE *file = fopen(filename, "r+");
        if (file == NULL) {
            perror("Error opening file!");
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
            printf("=== WELCOME TO THE SHOP ===\n\n");
            printf("Your coin(s): \033[0;33m%d\033[0m ", *coins);
    
			if(*coins < -450){
            	printf("(Dont't go over -500! I repeat do not!)\n");
			}else if(*coins < -400){
            	printf("(Please tell me you have a plan.)\n");
			}else if(*coins < -250){
            	printf("(You are deeply in debt.)\n");
			}else if(*coins < 0){
				printf("(It's fine you can fix that.)\n");
			}else{
				printf("\n");
			}
			
			printf("\n");
            printf("1. Common Box (50 Coin)\n");
            printf("2. Rare Box (100 Coin)\n");
            printf("3. Epic Box (200 Coin)\n");
            printf("0. Exit Shop\n");
            printf("\nChoose an Option: ");
            scanf("%d", &option);
            if (option == 1) {
                
                recordNumber = commonbox();
                cost = 50;
                *coins -= 50; 
                break;
                
            } else if (option == 2) {
                
                recordNumber = rarebox();
                cost = 100;
                *coins -= 100; 
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
                return; 
            }
            wronginput();
            Sleep(1000);
            system("cls");
        }

        // Rewrite the crop's status
        Crop *crop = &crops[recordNumber - 1];
        if(strcmp(crops[recordNumber-1].status,"Not") == 0){
        	printf("You got a new seed!\n");
		}
        strcpy(crop->status, "Obtained");
		
		
		system("cls");
        printf("\nInventory updated successfully! You got %s (%s)\n", crop->name, crop->rarity);
        printf("\nReduce -%d coins. Remaining coin(s): \033[0;33m%d\033[0m\n", cost, *coins);


       //rewrite and update the cropdata.txt
        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing!");
            return;
        }

        fprintf(file, "Index,Name,Rarity,Status\n");
        for (int i = 0; i < MAX_RECORDS; i++) {
            fprintf(file, "%d,%s,%s,%s\n", 
                    crops[i].index, crops[i].name, 
                    crops[i].rarity, crops[i].status);
        }
        fclose(file);

       //input inventory.txt to a struct
        file = fopen(inventory, "r+");
        if (file == NULL) {
            perror("Error opening file!");
            Sleep(3000);
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
		}//to store it in inventory since it start with 0
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
            perror("Error opening file for writing!");
            Sleep(3000);
            return;
        }
		//update inventory.txt
        fprintf(file, "Name,Rarity,Quantity\n");
        for (int i = 0; i < count; i++) {
            if (invencrop[i].quantity > 0) {
                fprintf(file, "%s,%s,%d\n", 
                        invencrop[i].crop.name, invencrop[i].crop.rarity, invencrop[i].quantity);
            }
        }
        fclose(file);
        
		//show inventory
        printf("\n=== Updated Inventory ===\n");
        for (int i = 0; i < count; i++) {
            printf("%s (%s) - Quantity: %d\n", 
                   invencrop[i].crop.name, 
                   invencrop[i].crop.rarity, 
                   invencrop[i].quantity);
        }
        printf("---------------------------\n");
        Sleep(7000); 
        shopkeeperbuy();
        Sleep(3000);
    }
}

void plantCrop(const char *plotFile, const char *inventoryFile,int *moves) {
    
	while(1){
		system("cls");
		printf("\nActions left today: \033[0;34m%d\033[0m\n\n", *moves);
			
		if(*moves == 0){
			printf("\nYou have used all your actions for today. Exiting...");
			Sleep(3000);
		    return;
		}
		
		displayinventory(inventoryFile);
	    displayplotcrop(plotFile);
	    
	    
	
	    // Load inventory data
	    FILE *file = fopen(inventoryFile, "r+");
	    if (file == NULL) {
	        perror("Error opening inventory file!");
	        Sleep(3000);
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
	        perror("Error opening plot file!");
	        Sleep(3000);
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
				printf("\nReturning to home...\n");
				Sleep(3000);
				return;
			}
			
	        for (i = 0; i < countinv; i++) {
	            if (strcmp(inventory[i].crop.name, cropchoice) == 0) {
	                cropFound = 1;
	                break;
	            }
	        }
	
	        if (cropFound) break;
	        printf("Invalid crop name! Make sure the capital letter is correct!\n");
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
	            printf("Plot is already planted. Choose another plot!\n");
	        } else if (plotchoice == 0){
	        	printf("Cancelling planting...");
	            Sleep(3000);
	            return;
	        }else{
	        	printf("Invalid plot choice!\n");
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
	        perror("Error saving inventory file!");
	        Sleep(3000);
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
	        perror("Error saving plot file!");
	        Sleep(3000);
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
	    Sleep(3000);
	    
	}
}

void watercrop(const char *plotFile, int *moves){
	system("cls");
	while(1){
		plotstatuschanger(plotFile);
		system("cls");
		printf("\nActions left today: \033[0;34m%d\033[0m\n\n", *moves);
			
		if(*moves == 0){
			printf("\nYou have used all your actions for today. Exiting...");
			Sleep(3000);
		    return;
		}
		
		
		FILE *file;
		file = fopen(plotFile, "r+");
	    if (file == NULL) {
	        perror("Error opening plot file!");
	        Sleep(3000);
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
	        printf("\nChoose a plot to water: ");
	    	scanf("%d", &plotchoice);
			if(plotchoice >= 1 && plotchoice <= 5){
				if(plotData[plotchoice-1].water_needed <= 0){
					printf("This plot needs no more water!\n");
				}else{
					plotData[plotchoice-1].water_needed -= 1;
					break;
				}
			}else if(plotchoice == 0){
				printf("\nGoing back inside...\n");
				Sleep(3000);
				return;
			}else{
				printf("Invalid input!\n");
			}	
		}
		animationwatering();
		system("cls");
		printf("Plot %d (-1) water needed\n", plotchoice);
		Sleep(5000);
		
		file = fopen(plotFile, "w");
	    if (file == NULL) {
	        perror("Error saving plot file!");
	        Sleep(3000);
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
		printf("\nActions left today: \033[0;34m%d\033[0m\n\n", *moves);
			
		if(*moves == 0){
			printf("\nYou have used all your actions for today. Exiting...");
			Sleep(3000);
		    return;
		}
		
		
		plot plotData[5];
		int count =0;
		char line[MAX_LINE_LENGTH];
		FILE *file;
		file = fopen(plotFile, "r+");
    	if (file == NULL) {
        	perror("Error opening plot file!");
        	Sleep(3000);
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
			printf("\nChoose a Plot to harvest (1-5): ");
	
			scanf("%d", &choice);
			if(choice >= 1 && choice <= 5){
				if(strcmp(plotData[choice-1].status,"Ready") == 0){
					break;
				}else if((strcmp(plotData[choice-1].status,"Ready")) != 0){
					printf("This plot isn't yet ready to be harvested. Choose another plot!\n");
			        continue;
				}	
			}else if(choice == 0){
				printf("\nGoing back home...\n");
				Sleep(3000);
				return;
			}else{
				printf("Invalid input!\n");
			}
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
       		perror("Error saving plot file!");
       		Sleep(3000);
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
    	Sleep(5000);
    	
 
    	
    	
	}
	
}





