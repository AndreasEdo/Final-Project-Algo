#include "Utilityfunction.h"


// Function to display the status of all plots
void display_farm(Plot plots[], int max_plots) {
    printf("\n--- Farm Plots Status ---\n");
    for (int i = 0; i < max_plots; i++) {
        printf("Plot %d: ", i + 1);
        if (plots[i].is_planted) {
            printf("Planted (%s) | Quantity: %d | Days Remaining: %d | Fertility Modifier: +%d days\n", 
                plots[i].crop.name, plots[i].quantity, plots[i].time_remaining, plots[i].fertility);
        } else {
            printf("Empty\n");
        }
    }
    printf("-------------------------\n");
}

// Function to display the inventory
void display_inventory(Inventory inventory[], int size) {
    printf("\n--- Seed Inventory ---\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s | Quantity: %d\n", i + 1, inventory[i].crop.name, inventory[i].quantity);
    }
    printf("-----------------------\n");
}


void shop_menu(Crop crops[], Inventory inventory[], int *coins) {
    while (1) { 
        printf("\n--- Shop ---\n");
        for (int i = 0; i < MAX_INVENTORY; i++) {
            printf("%d. %s | Cost: %d coins | Growth Time: %d days | Sell Price: %d coins\n", 
                i + 1, crops[i].name, crops[i].buy_cost, crops[i].growth_time, crops[i].sell_price);
            printf("   * Bulk Discount: Buy in multiples of 5 for %d coins each\n", crops[i].buy_cost - 5);
        }
        
        printf("----------------\n");
        
        int choice = get_valid_input("Choose a crop to buy (1-3) or 0 to exit: ", 0, MAX_INVENTORY);
        if (choice == 0) {
            printf("Exiting shop.\n");
            break; 
        }
        choice--; // Adjust for 0-based indexing

        printf("Enter quantity to buy (max %d per crop or 0 to cancel): ", MAX_SEEDS_PER_CROP - inventory[choice].quantity);
        int quantity = get_valid_input("", 0, MAX_SEEDS_PER_CROP - inventory[choice].quantity);

        if (quantity == 0) {
            printf("Purchase canceled. Returning to shop menu.\n");
            system("cls");
            continue; // Return to the shop menu
        }

        // Calculate bulk discount
        int cost_per_seed = crops[choice].buy_cost;
        if (quantity % 5 == 0) {
            cost_per_seed -= 5;
            system("cls");
            printf("Bulk discount applied! New cost per seed: %d coins\n", cost_per_seed);
            Sleep(1000);
        }

        int total_cost = cost_per_seed * quantity;
        if (*coins >= total_cost) {
            *coins -= total_cost;
            inventory[choice].quantity += quantity;
            system("cls");
            printf("Successfully bought %d %s seeds for %d coins!\n", quantity, crops[choice].name, total_cost);
            Sleep(1000);
        } else {
        	system("cls");
            printf("Insufficient coins! You need %d more coins.\n", total_cost - *coins);
            Sleep(1000);
        }
    }
}


void displayintro() {
    int console_width = 100; 
    

    char line[] = "--------------------------------------";
    gotoxy(40, 2);
    printf("%s", line);
    gotoxy(40, 5);
    printf("%s", line);


    gotoxy(45, 3);
    char Welcome[] = "Welcome to Farming Simulator!";
    for (int i = 0; i < strlen(Welcome); i++) {
        printf("%c", Welcome[i]);
        Sleep(100);
    }

    gotoxy(46, 4);
    char press1[] = "Press Enter to continue...";
    for (int i = 0; i < strlen(press1); i++) {
        printf("%c", press1[i]);
        Sleep(100);
    }


}



