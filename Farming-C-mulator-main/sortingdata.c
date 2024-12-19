#include "struct.c"

void swapdata(Crop *a, Crop *b) {
    Crop temp = *a;
    *a = *b;
    *b = temp;
}

void quicksortalphabet(Crop arr[], int left, int right) {
    if (left < right) {
        int i = left, j = left - 1;
        char pivot[20];
        strcpy(pivot, arr[right].name);

        while (i < right) {
            if (strcmp(arr[i].name, pivot) <= 0) {
                j++;
                swapdata(&arr[j], &arr[i]);
            }
            i++;
        }

        j++;
        swapdata(&arr[j], &arr[right]);

        quicksortalphabet(arr, left, j - 1);
        quicksortalphabet(arr, j + 1, right);
    }
}

void sortalphabetdata(const char *fileName) {
    Crop crop[MAX_RECORDS];
    int count = 0;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening file!");
        Sleep(3000);
        return;
    }
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%19[^,],%9[^,],%9s", &crop[count].index, crop[count].name, crop[count].rarity, crop[count].status);
        count++;
    }
    fclose(file);

    quicksortalphabet(crop, 0, count - 1);
    printf("%-5s|%-20s|%-10s|%-10s|\n", "Index", "Name", "Rarity", "Status");
    printf("-----|--------------------|----------|----------|\n");
    for (int i = 0; i < count; i++) {
        printf("%-5d|%-20s|%-10s|%-10s|\n", crop[i].index, crop[i].name, crop[i].rarity, crop[i].status);
    }
    printf("\n");
}

void quicksortstatus(Crop arr[], int left, int right) {
    if (left < right) {
        int i = left, j = left - 1;
        char pivot[20];
        strcpy(pivot, arr[right].status);
        

        while (i < right) {
            if (strcmp(arr[i].status ,pivot)<=0) {
                j++;
                swapdata(&arr[j], &arr[i]);
            }
            i++;
        }

        j++;
        swapdata(&arr[j], &arr[right]);

        quicksortstatus(arr, left, j - 1);
        quicksortstatus(arr, j + 1, right);
    }
}

void sortstatusdata(const char *fileName) {
    Crop crop[MAX_RECORDS];
    int count = 0;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening highscore file!");
        Sleep(3000);
        return;
    }
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        

        
        sscanf(line, "%d,%19[^,],%9[^,],%9s", &crop[count].index, crop[count].name, crop[count].rarity, crop[count].status);
        count++;
    }
    fclose(file);
    quicksortstatus(crop, 0, count - 1);
    printf("%-5s|%-20s|%-10s|%-10s|\n", "Index", "Name", "Rarity", "Status"); 
    printf("-----|--------------------|----------|----------|\n");
	for(int i=0;i<MAX_RECORDS;i++)
    {
    	printf("%-5d|%-20s|%-10s|%-10s|\n", crop[i].index, crop[i].name, crop[i].rarity, crop[i].status);
	}
	printf("\n");
}

void quicksortstatusobtained(Crop arr[], int left, int right) {
    if (left < right) {
        int i = left, j = left - 1;
        char pivot[20];
        strcpy(pivot, arr[right].status);
        

        while (i < right) {
            if (strcmp(arr[i].status ,pivot)>=0) {
                j++;
                swapdata(&arr[j], &arr[i]);
            }
            i++;
        }

        j++;
        swapdata(&arr[j], &arr[right]);

        quicksortstatusobtained(arr, left, j - 1);
        quicksortstatusobtained(arr, j + 1, right);
    }
}

void sortstatusdataobtained(const char *fileName) {
    Crop crop[MAX_RECORDS];
    int count = 0;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        perror("Error opening highscore file!");
        Sleep(3000);
        return;
    }
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        

        
        sscanf(line, "%d,%19[^,],%9[^,],%9s", &crop[count].index, crop[count].name, crop[count].rarity, crop[count].status);
        count++;
    }
    fclose(file);
    quicksortstatusobtained(crop, 0, count - 1);
    printf("%-5s|%-20s|%-10s|%-10s|\n", "Index", "Name", "Rarity", "Status"); 
    printf("-----|--------------------|----------|----------|\n");
	for(int i=0;i<MAX_RECORDS;i++)
    {
    	printf("%-5d|%-20s|%-10s|%-10s|\n", crop[i].index, crop[i].name, crop[i].rarity, crop[i].status);
	}
	printf("\n");
}

int cropsData() {
	while(1){
		while(1){
			int a;
			printf("=== CROPS MENU ===\n");
			printf("1. Sort by Alphabet\n");
			printf("2. Sort by Obtained\n");
			printf("3. Sort by Not Obtained\n");
			printf("0. Back to Database Menu\n");
			printf("------------------\n\n");
			printf("Enter input: ");
			scanf(" %d", &a);
			system("cls");
			if(a == 1){
				sortalphabetdata(FILENAME);
				break;
			}else if(a == 2){
				sortstatusdataobtained(FILENAME);
				break;
			}else if(a == 3){
				sortstatusdata(FILENAME);
				break;
			}else if(a == 0){
				printf("Returning to Database Menu...\n");
				return 0;
			}else{
				printf("Invalid input! Please try again.\n");
			}
			
		}
		
	}
	
    return 0;
}

