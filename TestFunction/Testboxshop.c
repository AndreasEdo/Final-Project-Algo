#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define FILENAME "cropdata.txt"
#define MAX_LINE_LENGTH 100
#define MAX_RECORDS 48

typedef struct {
    int index;
    char name[20];
    char rarity[10];
    char status[10];
} Crop;

int random(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}


int commonbox(){
	srand(time(NULL));
	int a = random(1,1000);
	if(a < 450){
		int common = random(1,17);
		return common;
	}else if(a<800){
		int uncommon = random(1,12);
		return uncommon + 17;
	}else if(a<925){
		int rare = random(1,11);
		return rare + 29;
	}else if(a<980){
		int epic = random(1,6);
		return epic + 40;
	}else if(a<1000){
		int legendary = random(1,2);
		return legendary + 46;
	}
}

int rarebox(){
	srand(time(NULL));
	int a = random(1,500);
	if(a < 150){
		int common = random(1,17);
		return common;
	}else if(a<300){
		int uncommon = random(1,12);
		return uncommon + 17;
	}else if(a<425){
		int rare = random(1,11);
		return rare + 29;
	}else if(a<475){
		int epic = random(1,6);
		return epic + 40;
	}else if(a<500){
		int legendary = random(1,2);
		return legendary + 46;
	}
}

int epicbox(){
	srand(time(NULL));
	int a = random(1,250);
	if(a < 25){
		int common = random(1,17);
		return common;
	}else if(a<50){
		int uncommon = random(1,12);
		return uncommon + 17;
	}else if(a<100){
		int rare = random(1,11);
		return rare + 29;
	}else if(a<150){
		int epic = random(1,6);
		return epic + 40;
	}else if(a<250){
		int legendary = random(1,2);
		return legendary + 46;
	}
}


void boxshop(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }


    Crop crops[MAX_RECORDS];
    int count = 0;
    char line[MAX_LINE_LENGTH];


    fgets(line, sizeof(line), file);


    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%19[^,],%9[^,],%9s", 
               &crops[count].index, crops[count].name, 
               crops[count].rarity, crops[count].status);
        count++;
    }
    fclose(file);
	int option;
	while(1){
		printf("---WELCOME TO THE SHOP---\n");
    	printf("1.Common Box(50 Coin)\n");
    	printf("2.Rare Box(100 Coin)\n");
    	printf("3.Epic Box(200 Coin)\n");
    	printf("Choose an Option:");
    	scanf("%d", &option);
    	if(option == 1 || option == 2 || option == 3){
    		break;
		}
		printf("Invalid Input\n");
	}
    
    
    int recordNumber;
    if(option == 1){
    	recordNumber = commonbox();
	}else if(option == 2){
		recordNumber = rarebox();
	}else if(option == 3){
		recordNumber = epicbox();
	}else{
		printf("Invalid number");
	}

    Crop *crop = &crops[recordNumber - 1];

    strcpy(crop->status, "Obtained");

    // Write updated records back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }


    fprintf(file, "Index,Name,Rarity,Status\n");


    for (int i = 0; i < MAX_RECORDS; i++) {
        fprintf(file, "%d,%s,%s,%s\n", 
                crops[i].index, crops[i].name, 
                crops[i].rarity, crops[i].status);
    }

    fclose(file);
    printf("Record updated successfully. YOU GOT %s\n", crop->name);
}


int main() {



    boxshop(FILENAME);


    return 0;
}
