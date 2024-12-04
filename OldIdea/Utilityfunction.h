#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)
#endif

#define MAX_PLOTS 5
#define MAX_INVENTORY 3
#define MAX_SEEDS_PER_CROP 100
#define SEASON_DAYS 90
#define MAX_HIGH_SCORES 10
#define username_length 50


#define HIGH_SCORE_FILE "highscore.txt"

typedef struct {
    char username[username_length];
    int score;
} HighScore;


typedef struct {
    char name[20];
    int buy_cost;
    int growth_time;
    int water_needed;
    int sell_price;
} Crop;

typedef struct {
    Crop crop;
    int quantity;
} Inventory;

typedef struct {
    int is_planted;
    Crop crop;
    int quantity;
    int time_remaining;
    int fertility;
} Plot;

void gotoxy(int x, int y);
void press_enter_to_continue();
void clear_screen();
int get_valid_input(const char *prompt, int min, int max);
void printMenu(int selectedoption);
int option();
void get_usernname(char *username);

#endif

