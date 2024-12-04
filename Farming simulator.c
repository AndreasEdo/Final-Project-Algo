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

