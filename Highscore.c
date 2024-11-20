
#include "Utilityfunction.h"



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

