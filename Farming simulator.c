#include "Utilityfunction.c"
#include "Animasinyiram.c"
#include "Animasinanam.c"

#include "Highscore.c"
#include "Displaymenu.c"
#include "Plantandharvest.c"








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

