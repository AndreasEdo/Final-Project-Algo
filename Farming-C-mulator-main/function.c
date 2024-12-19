#include "struct.h"

void plotstatuschanger(const char *plotFile){
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
    	if(plotData[i].time_to_harvest == 0 && plotData[i].water_needed == 0){
    		strcpy(plotData[i].status, "Ready");
		}else if(plotData[i].time_to_harvest > 0 || plotData[i].water_needed > 0){
			strcpy(plotData[i].status, "Planted");
		}else if(plotData[i].time_to_harvest == -1 && plotData[i].water_needed == -1){
			strcpy(plotData[i].status, "NotPlanted");
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

void plottimeremover(const char *plotFile){
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
    	if(plotData[i].time_to_harvest != -1 && plotData[i].time_to_harvest != 0){
    		plotData[i].time_to_harvest -= 1;
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




void inventoryclear(const char *invFile){
	FILE *file;
	file = fopen(invFile, "w");
	fprintf(file, "");
	fclose(file);
}

void plotclear(const char *plotFile){
	FILE *file;
	plot plotData[5];
	file = fopen(plotFile, "r+");
	if (file == NULL) {
        perror("Error opening plot file!");
        Sleep(3000);
        return;
    }


	char line[MAX_LINE_LENGTH];
    int count;
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
    	strcpy(plotData[i].plotcrop.name, "None");
    	strcpy(plotData[i].plotcrop.rarity, "None");
    	strcpy(plotData[i].status, "NotPlanted");
    	plotData[i].time_to_harvest = -1;
    	plotData[i].water_needed = -1;
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
