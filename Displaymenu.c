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

// Function to handle the shop
void shop_menu(Crop crops[], Inventory inventory[], int *coins) {
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
        return;
    }
    choice--; // Adjust for 0-based indexing

    printf("Enter quantity to buy (max %d per crop): ", MAX_SEEDS_PER_CROP - inventory[choice].quantity);
    int quantity = get_valid_input("", 1, MAX_SEEDS_PER_CROP - inventory[choice].quantity);

    // Calculate bulk discount
    int cost_per_seed = crops[choice].buy_cost;
    if (quantity % 5 == 0) {
        cost_per_seed -= 5;
        printf("Bulk discount applied! New cost per seed: %d coins\n", cost_per_seed);
    }

    int total_cost = cost_per_seed * quantity;
    if (*coins >= total_cost) {
        *coins -= total_cost;
        inventory[choice].quantity += quantity;
        printf("Successfully bought %d %s seeds for %d coins!\n", quantity, crops[choice].name, total_cost);
    } else {
        printf("Insufficient coins! You need %d more coins.\n", total_cost - *coins);
    }
    
}

