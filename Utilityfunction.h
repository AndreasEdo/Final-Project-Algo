#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)
#endif

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


void gotoxy(int x, int y);
void clear_screen();
int get_valid_input(const char *prompt, int min, int max);


#endif 

