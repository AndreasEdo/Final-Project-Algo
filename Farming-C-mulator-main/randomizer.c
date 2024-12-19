#include "struct.h"
#include <time.h>
#include <stdlib.h>

// Function to generate a random number between lower and upper (inclusive)
int random(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}

// Common Box Function
int commonbox() {
    srand(time(NULL));
    int a = random(1, 1000);
    if (a < 490) {
        return random(1, 17);  // 49%
    } else if (a < 820) {
        return random(1, 12) + 17;  // 43%
    } else if (a < 953) {
        return random(1, 11) + 29;  //13.3%
    } else if (a < 998) {
        return random(1, 6) + 40;   //4.5%
    } else {
        return random(1, 2) + 46;   //0.2%
    }
}

// Rare Box Function
int rarebox() {
    srand(time(NULL));
    int a = random(1, 500);
    if (a < 150) {
        return random(1, 17);  // 30%
    } else if (a < 360) {
        return random(1, 12) + 17;  //42%
    } else if (a < 460) {
        return random(1, 11) + 29;  //20%
    } else if (a < 495) {
        return random(1, 6) + 40;   //7%
    } else {
        return random(1, 2) + 46;   //1%
    }
}

// Epic Box Function
int epicbox() {
    srand(time(NULL));
    int a = random(1, 1000);
    if (a < 170) {
        return random(1, 17);  // 17%
    } else if (a < 390) {
        return random(1, 12) + 17;  // 22%
    } else if (a < 740) {
        return random(1, 11) + 29;  // 35%
    } else if (a < 920) {
        return random(1, 6) + 40;   // 18%
    } else {
        return random(1, 2) + 46;   // 8%
    }
}

void tipsrandomizer(){
	srand(time(NULL));
	int tips = random(1,7);
	printf("\n\n");
	printf("Tip: ");

	if(tips == 1){
		printf("Always type 0 to exit.");
	}else if(tips == 2){
		printf("Prioritize the highest rarity.");
	}else if(tips == 3){
		printf("The Epic box had the highest chance to obtain a legendary crop.");
	}else if(tips == 4){
		printf("Save some money to buy Epic box.");
	}else if(tips == 5){
		printf("Remember, it's not gambling if it's the only thing you can spend money on.");
	}else if(tips == 6){
		printf("Binus @Malang? Mboiss!");
	}else if(tips == 7){
		printf("Bambang Cak Telo :)");
	}
	printf("\n\n");
}

void wateradderrandomizer(const char *plotFile){
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
    
    for(int i=0;i<5;i++){
    	if(strcmp(plotData[i].status,"NotPlanted") == 0){
    		continue;
		}
		
		if(strcmp(plotData[i].plotcrop.rarity, "Common") == 0){
			if(plotData[i].water_needed == Common.water){
				continue;
			}
		}else if(strcmp(plotData[i].plotcrop.rarity, "Uncommon") == 0){
			if(plotData[i].water_needed == Uncommon.water){
				continue;
			}
		}else if(strcmp(plotData[i].plotcrop.rarity, "Rare") == 0){
			if(plotData[i].water_needed == Rare.water){
				continue;
			}
		}else if(strcmp(plotData[i].plotcrop.rarity, "Epic") == 0){
			if(plotData[i].water_needed == Epic.water){
				continue;
			}
		}else if(strcmp(plotData[i].plotcrop.rarity, "Legendary") == 0){
			if(plotData[i].water_needed == Legendary.water){
				continue;
			}
		}
		
		
		
    	srand(time(NULL));
		int wateradd = random(1,100);
		if(wateradd > 10){
			plotData[i].water_needed += 1;
		}
	}
	
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
}

void sellrandomizer(int sellcost, int **COINS, int *p){
	*p=0;
	srand(time(NULL));
	int b = random(1,1000);
	if(b<40){
		printf("\nThis Crop is contaminated!\n");
		sellcost = sellcost/2;
		**COINS += sellcost;
	}else if(b>920){
		printf("\nGod Damn Best crop I have seen in years!\n");
		sellcost = sellcost*2;
		**COINS += sellcost;
	}else if(b>800){
		printf("\nBring me more of this goodie!\n");
		sellcost = sellcost/2*3;
		**COINS += sellcost;
	}else if(b>540){
		sellcost = sellcost/5*5;
		printf("\nNice crop you got there!\n"); 
		**COINS += sellcost;
	}else{
		**COINS += sellcost;
	}
	*p = sellcost;
}

