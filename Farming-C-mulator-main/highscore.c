#include "struct.c"

void swapHighscoreData(highscore *a, highscore *b) {
    highscore temp = *a;
    *a = *b;
    *b = temp;
}

void quickSortByName(highscore arr[], int left, int right) {
    if (left < right) {
        int i = left, j = left - 1;
        char pivot[50];
        strcpy(pivot, arr[right].name);

        while (i < right) {
            if (strcmp(arr[i].name, pivot) <= 0) {
                j++;
                swapHighscoreData(&arr[j], &arr[i]);
            }
            i++;
        }

        j++;
        swapHighscoreData(&arr[j], &arr[right]);

        quickSortByName(arr, left, j - 1);
        quickSortByName(arr, j + 1, right);
    }
}

void displaySortedByName(const char *fileName) {
    highscore highscoreData[MAX_RECORDS];
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
        sscanf(line, "%49[^,],%d", highscoreData[count].name, &highscoreData[count].hs);
        count++;
    }
    fclose(file);

    quickSortByName(highscoreData, 0, count - 1);
    printf("%-20s|%-10s|\n", "Username", "Highscore");
    printf("--------------------|----------|\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s|%-10d|\n", highscoreData[i].name, highscoreData[i].hs);
    }
    printf("\n");
}

void quickSortByScoreAscending(highscore arr[], int left, int right) {
    if (left < right) {
        int i = left, j = left - 1;
        int pivot = arr[right].hs;

        while (i < right) {
            if (arr[i].hs <= pivot) {  // Ascending
                j++;
                swapHighscoreData(&arr[j], &arr[i]);
            }
            i++;
        }

        j++;
        swapHighscoreData(&arr[j], &arr[right]);

        quickSortByScoreAscending(arr, left, j - 1);
        quickSortByScoreAscending(arr, j + 1, right);
    }
}

void quickSortByScoreDescending(highscore arr[], int left, int right) {
    if (left < right) {
        int i = left, j = left - 1;
        int pivot = arr[right].hs;

        while (i < right) {
            if (arr[i].hs > pivot) {  // Descending
                j++;
                swapHighscoreData(&arr[j], &arr[i]);
            }
            i++;
        }

        j++;
        swapHighscoreData(&arr[j], &arr[right]);

        quickSortByScoreDescending(arr, left, j - 1);
        quickSortByScoreDescending(arr, j + 1, right);
    }
}

void displaySortedByScoreAscending(const char *fileName) {
    highscore highscoreData[MAX_RECORDS];
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
        sscanf(line, "%49[^,],%d", highscoreData[count].name, &highscoreData[count].hs);
        count++;
    }
    fclose(file);

    quickSortByScoreAscending(highscoreData, 0, count - 1);
    printf("%-20s|%-10s|\n", "Username", "Highscore");
    printf("--------------------|----------|\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s|%-10d|\n", highscoreData[i].name, highscoreData[i].hs);
    }
    printf("\n");
}

void displaySortedByScoreDescending(const char *fileName) {
    highscore highscoreData[MAX_RECORDS];
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
        sscanf(line, "%49[^,],%d", highscoreData[count].name, &highscoreData[count].hs);
        count++;
    }
    fclose(file);

    quickSortByScoreDescending(highscoreData, 0, count - 1);
    printf("%-20s|%-10s|\n", "Username", "Highscore");
    printf("--------------------|----------|\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s|%-10d|\n", highscoreData[i].name, highscoreData[i].hs);
    }
    printf("\n");
}

int highscoreOptionsMenu() {
    while (1) {
        int choice;
        printf("=== HIGHSCORE MENU ===\n");
        printf("1. Sort by Username (Alphabetical)\n");
        printf("2. Sort by Highscore (Ascending)\n");
        printf("3. Sort by Highscore (Descending)\n");
        printf("0. Back to Database Menu\n");
        printf("----------------------\n\n");
        printf("Enter input: ");
        scanf(" %d", &choice);
        system("cls");

        if (choice == 1) {
            displaySortedByName("highscore.txt");
        } else if (choice == 2) {
            displaySortedByScoreAscending("highscore.txt");
        } else if (choice == 3) {
            displaySortedByScoreDescending("highscore.txt");
        } else if (choice == 0) {
            printf("Returning to Database Menu...\n");
            return 0;
        } else {
            printf("Invalid input! Please try again.\n");
        }
    }

    return 0;
}

void InputHighScore(char name[20], int highscorE, const char* highscoreFile){
	highscore highscoreData[MAX_RECORDS];
    int count = 0;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(highscoreFile, "r");

    if (file == NULL) {
        perror("Error opening file!");
        Sleep(3000);
        return;
    }
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%49[^,],%d", highscoreData[count].name, &highscoreData[count].hs);
        count++;
    }
    fclose(file);
    
    strcpy(highscoreData[count].name,name);
	highscoreData[count].hs = highscorE; 
    
    file = fopen(highscoreFile, "w");
        if (file == NULL) {
            perror("Error opening file for writing!");
            Sleep(3000);
            return;
        }
	
    fprintf(file, "Name,Score\n");
    for (int i = 0; i < count+1; i++) {
    
        fprintf(file, "%s,%d\n", 
                highscoreData[i].name, highscoreData[i].hs);
        
    }
    fclose(file);
}

