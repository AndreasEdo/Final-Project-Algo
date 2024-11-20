#include "Utilityfunction.c"
#include "Animasinyiram.c"
#include "Animasinanam.c"


#define MAX_PLOTS 5
#define MAX_INVENTORY 3
#define MAX_SEEDS_PER_CROP 100
#define SEASON_DAYS 90

#define HIGH_SCORE_FILE "highscore.txt"


// Structure to represent a crop
typedef struct {
    char name[20];
    int buy_cost;
    int growth_time;
    int water_needed;
    int sell_price;
} Crop;

// Structure to represent inventory for each crop
typedef struct {
    Crop crop;
    int quantity; // Number of seeds
} Inventory;

// Structure to represent a plot
typedef struct {
    int is_planted;
    Crop crop;
    int quantity; // Number of crops planted (max 10)
    int time_remaining; // Days until harvest
    int fertility; // Extra days added to growth_time if replanting same crop
} Plot;



// Function to clear the console with "Press 1 to continue..."
void clear_screen() {
    printf("\nEnter 1 to continue...\n");
    int input;
    while (1) {
        // Read input as a string to handle non-integer inputs
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Try to parse input as integer
            if (sscanf(buffer, "%d", &input) == 1) {
                if (input == 1) {
                    break;
                }
            }
        }
        printf("Invalid input! Please enter 1 to continue.\n");
    }

    // Clear the console
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to get valid integer input within a range
int get_valid_input(const char *prompt, int min, int max) {
    int input;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Attempt to parse integer
            if (sscanf(buffer, "%d", &input) == 1) {
                if (input >= min && input <= max) {
                    return input;
                } else {
                    printf("Input out of range! Please enter a number between %d and %d.\n", min, max);
                }
            } else {
                printf("Invalid input! Please enter a valid number.\n");
            }
        } else {
            printf("Error reading input! Please try again.\n");
        }
    }
}

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

// Function to read the high score from a file
int read_high_score() {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file == NULL) {
        // If file doesn't exist, assume high score is 0
        return 0;
    }
    int high_score = 0;
    fscanf(file, "%d", &high_score);
    fclose(file);
    return high_score;
}

// Function to write the high score to a file
void write_high_score(int score) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file == NULL) {
        printf("Error saving high score!\n");
        return;
    }
    fprintf(file, "%d", score);
    fclose(file);
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

// Function to load the high score from a file
int load_high_score() {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    if (file == NULL) {
        return 0;
    }
    int high_score = 0;
    fscanf(file, "%d", &high_score);
    fclose(file);
    return high_score;
}

// Function to save the high score to a file
void save_high_score(int high_score) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (file == NULL) {
        printf("Error saving high score!\n");
        return;
    }
    fprintf(file, "%d", high_score);
    fclose(file);
}

int main() {
	
	
    // Initialize crops
    Crop crops[MAX_INVENTORY] = {
        {"Wheat", 10, 15, 5, 20},
        {"Corn", 15, 20, 7, 25},
        {"Rice", 20, 25, 10, 30}
    };
	
    // Initialize inventory
    Inventory inventory[MAX_INVENTORY];
    for (int i = 0; i < MAX_INVENTORY; i++) {
        inventory[i].crop = crops[i];
        inventory[i].quantity = 0; // Start with 0 seeds
    }

    // Initialize plots
    Plot plots[MAX_PLOTS];
    for (int i = 0; i < MAX_PLOTS; i++) {
        plots[i].is_planted = 0;
        plots[i].quantity = 0;
        plots[i].time_remaining = 0;
        plots[i].fertility = 100; // Start with full fertility
    }

    // Starting coins
    int coins = 1000;
	
	int MAX_ACTIONS_PER_DAY=10;
    // Season days
    int season_days = SEASON_DAYS;

    // Load high score
    int high_score = load_high_score();

    printf("Welcome to the Advanced Farming Game!\n");
    clear_screen();
    
    system("cls");
	gotoxy(30,5);
    printf("%d Days in the season remaining!!\n", season_days);
    Sleep(1000);
    gotoxy(38,6);
    printf("Loading the day");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".");
    Sleep(1000);
    printf(".");
    // Main game loop
    while (season_days > 0) {
        int daily_actions = MAX_ACTIONS_PER_DAY; // Reset daily actions

        while (daily_actions > 0 && season_days > 0) {
        	
            
            
            if(season_days<90 && daily_actions==10){//iki gawe animasi ganti hari 
            	gotoxy(30,5);
            	printf("%d Days in the season remaining!!\n", season_days+1);
            	Sleep(2000);
            	system("cls");
            	gotoxy(30,5);
            	printf("%d Days in the season remaining!!\n\n", season_days);
            	Sleep(1000);
            	gotoxy(38,6);
            	printf("The next day");
            	Sleep(1000);
            	printf(".");
            	Sleep(1000);
            	printf(".");
            	Sleep(1000);
            	printf(".");
            	Sleep(1000);
            	printf(".");
            	Sleep(1000);
			}
			
			system("cls");
            printf("=== Season Progress ===\n");
            printf("Days remaining: %d\n", season_days);
            printf("Coins: %d\n", coins);
            printf("High Score: %d coins\n", high_score);
            printf("Actions remaining today: %d\n", daily_actions);
            printf("=======================\n");

            // Display farm and inventory
            display_farm(plots, MAX_PLOTS);
            display_inventory(inventory, MAX_INVENTORY);

            // Display actions
            printf("\n--- Actions ---\n");
            printf("1. Plant Crops\n");
            printf("2. Water Crops\n");
            printf("3. Harvest Crops\n");
            printf("4. Visit Shop\n");
            printf("5. Wait a Day (Ends Actions)\n");
            printf("----------------\n");

            // Get user action
            int action = get_valid_input("Enter your choice (1-5): ", 1, 5);

            // Perform action
            switch (action) {
                case 1: { // Plant Crops
                    printf("\n--- Planting Crops ---\n");
                    display_farm(plots, MAX_PLOTS);
                    int plot_choice = get_valid_input("Choose a plot to plant (1-5) or 0 to cancel: ", 0, MAX_PLOTS);
                    if (plot_choice != 0) {
                        plant_crop(&plots[plot_choice - 1], inventory, MAX_INVENTORY);
                        daily_actions--;
                    }
                    Sleep(5000);
                    break;
                }
                case 2: { // Water Crops
                	system("cls");
                    animationwatering();
                    int watered = 0;
                    for (int i = 0; i < MAX_PLOTS; i++) {
                        if (plots[i].is_planted && plots[i].crop.water_needed > 0) {
                            plots[i].crop.water_needed--;
                            gotoxy(32,20);
                            printf("Watered plot %d (%s). Remaining water needed: %d\n", 
                                i + 1, plots[i].crop.name, plots[i].crop.water_needed);
                            Sleep(5000);
                            watered = 1;
                        }
                    }
                    if (!watered) {
                        printf("No crops need watering.\n");
                    } else {
                        daily_actions--;
                    }
                    break;
                }
                case 3: { // Harvest Crops
                    printf("\n--- Harvesting Crops ---\n");
                    display_farm(plots, MAX_PLOTS);
                    int harvest_choice = get_valid_input("Choose a plot to harvest (1-5) or 0 to cancel: ", 0, MAX_PLOTS);
                    if (harvest_choice != 0) {
                        harvest_plot(&plots[harvest_choice - 1], &coins);
                        daily_actions--;
                    }
                    Sleep(5000);
                    break;
                }
                case 4: { // Visit Shop
                    printf("\n--- Visiting Shop ---\n");
                    shop_menu(crops, inventory, &coins);
                    daily_actions--;
                    Sleep(5000);
                    break;
                }
                case 5: { // Wait a Day
                    printf("\n--- Waiting a Day ---\n");
                    
                    daily_actions = 0; // End all remaining actions for the day

                    // Update plots
                    for (int i = 0; i < MAX_PLOTS; i++) {
                        if (plots[i].is_planted && plots[i].time_remaining > 0) {
                            plots[i].time_remaining--;
                            if (plots[i].time_remaining <= 0) {
                                printf("Crop on plot %d (%s) is ready to harvest!\n", 
                                    i + 1, plots[i].crop.name);
                                Sleep(5000);
                            }
                        }
                    }
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
            clear_screen();
            season_days--;

            // Update plots
            for (int i = 0; i < MAX_PLOTS; i++) {
                if (plots[i].is_planted && plots[i].time_remaining > 0) {
                    plots[i].time_remaining--;
                    if (plots[i].time_remaining <= 0) {
                        printf("Crop on plot %d (%s) is ready to harvest!\n", 
                            i + 1, plots[i].crop.name);
                    }
                }
            }
        }
    }

    // Season ended
    printf("=== Season Over ===\n");
    printf("Total coins earned: %d\n", coins);
    if (coins > high_score) {
        printf("New High Score: %d coins!\n", coins);
        save_high_score(coins);
    } else {
        printf("High Score remains at: %d coins.\n", high_score);
    }
    printf("===================\n");

    return 0;
}

