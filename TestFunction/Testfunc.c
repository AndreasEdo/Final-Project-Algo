#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


#define MAX_PLOTS 5
#define MAX_INVENTORY 3
#define MAX_SEEDS_PER_CROP 100
#define SEASON_DAYS 90
#define HIGH_SCORE_FILE "highscore.txt"

#define PLOT "plot.txt"
#define INVENTORY "inventory.txt"
#define FILENAME "cropdata.txt"
#define MAX_LINE_LENGTH 100
#define MAX_RECORDS 48



typedef struct {
    int index;
    char name[20];
    char rarity[10];
    char status[10];
} Crop;

typedef struct{
	int time;
	int water;
	int sell_value;
} rarity;

rarity Common = {3,3,25};
rarity Uncommon = {4,4,50};
rarity Rare = {5,5,75};
rarity Epic = {7,7,150};
rarity Legendary = {9,1,500};

typedef struct{
	int number;
	char status[15];
	Crop plotcrop;
	int water_needed;
	int time_to_harvest;
}plot;

typedef struct {
    Crop crop;
    int quantity; 
} Inventory;

void insertplot(const char *plotFile, plot plotData[]){
	FILE *file;
	file = fopen(plotFile, "r+");
    if (file == NULL) {
        perror("Error opening plot file");
        return;
    }

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
}

int main(){
	plot plotta[5];
	insertplot(PLOT, plotta);
	printf("%s", plotta[0].plotcrop.name);
}
