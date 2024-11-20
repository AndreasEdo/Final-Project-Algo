#include "Utilityfunction.h"


// Function to plant crops on a plot
void plant_crop(Plot *plot, Inventory inventory[], int size) {
    printf("\n--- Plant Crops ---\n");
    display_inventory(inventory, size);

    // List only crops that have seeds available
    int available_crops = 0;
    for (int i = 0; i < size; i++) {
        if (inventory[i].quantity >= 10) { // Need at least 10 seeds to plant
            printf("%d. %s (Available: %d)\n", i + 1, inventory[i].crop.name, inventory[i].quantity);
            available_crops++;
        }
    }
    if (available_crops == 0) {
        printf("No seeds available to plant. Visit the shop to buy seeds.\n");
        return;
    }

    int choice = get_valid_input("Choose a crop to plant (1-3) or 0 to cancel: ", 0, size);
    if (choice == 0) {
        printf("Cancelling planting action.\n");
        return;
    }
    choice--; // Adjust for 0-based indexing

    // Check if enough seeds are available
    if (inventory[choice].quantity < 10) {
        printf("Not enough seeds to plant 10 crops. You have %d seeds.\n", inventory[choice].quantity);
        return;
    }

    // Plant 10 seeds
    plot->is_planted = 1;
    plot->crop = inventory[choice].crop;
    plot->quantity = 10;
    plot->time_remaining = plot->crop.growth_time;
    
    displaynanam();
    
    // Check for fertility modifier
    if (plot->fertility > 0 && strcmp(plot->crop.name, plot->crop.name) == 0 && plot->fertility < 100) {
        plot->time_remaining += 5;
        printf("Fertility decreased! Growth time increased by 5 days.\n");
    }

    // Deduct seeds from inventory
    inventory[choice].quantity -= 10;
	gotoxy(32,15);
    printf("Successfully planted 10 %s seeds on this plot.\n", plot->crop.name);
   
}

// Function to harvest a specific plot
void harvest_plot(Plot *plot, int *coins) {
    if (!plot->is_planted) {
        printf("This plot is empty. Nothing to harvest.\n");
        return;
    }
    if (plot->time_remaining > 0) {
        printf("Crop is not ready to harvest. Days remaining: %d\n", plot->time_remaining);
        return;
    }

    // Calculate earnings
    int earnings = plot->quantity * plot->crop.sell_price;
    *coins += earnings;
    printf("Successfully harvested %d %s and earned %d coins!\n", 
        plot->quantity, plot->crop.name, earnings);

    // Reset the plot
    plot->is_planted = 0;
    plot->quantity = 0;
    plot->time_remaining = 0;

    // Decrease fertility for future planting
    plot->fertility -= 10;
    if (plot->fertility < 50) {
        plot->fertility = 50; // Minimum fertility
    }
}

