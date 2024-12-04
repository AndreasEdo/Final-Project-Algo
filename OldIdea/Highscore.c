
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
    FILE *file = fopen("highscore.csv", "w");
    if (file == NULL) {
        printf("Error saving high score!\n");
        return;
    }
    fprintf(file, "%d", score);
    fclose(file);
}


int load_high_scores(HighScore high_scores[]) {
    FILE *file = fopen("highscore.csv", "r");
    if (!file) {

        for (int i = 0; i < MAX_HIGH_SCORES; i++) {
            strcpy(high_scores[i].username, "None");
            high_scores[i].score = 0;
        }
        return 0;
    }
    
    int count = 0;
    while (fscanf(file, "%s %d", high_scores[count].username, &high_scores[count].score) == 2) {
        count++;
        if (count >= MAX_HIGH_SCORES) break;
    }
    fclose(file);
    return count;
}


void save_high_scores(HighScore high_scores[], int count) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    if (!file) {
        printf("Error saving high scores!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %d\n", high_scores[i].username, high_scores[i].score);
    }
    fclose(file);
}

void sort_high_scores(HighScore high_scores[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (high_scores[j].score > high_scores[i].score) {
                HighScore temp = high_scores[i];
                high_scores[i] = high_scores[j];
                high_scores[j] = temp;
            }
        }
    }
}

void update_high_scores(HighScore high_scores[], int *count, const char *username, int score) {
    // Add the new score
    if (*count < MAX_HIGH_SCORES) {
        strcpy(high_scores[*count].username, username);
        high_scores[*count].score = score;
        (*count)++;
    } else if (score > high_scores[MAX_HIGH_SCORES - 1].score) {
        // Replace the lowest score if the new score is higher
        strcpy(high_scores[MAX_HIGH_SCORES - 1].username, username);
        high_scores[MAX_HIGH_SCORES - 1].score = score;
    }

    // Sort the scores and keep only the top 10
    sort_high_scores(high_scores, *count);
    if (*count > MAX_HIGH_SCORES) {
        *count = MAX_HIGH_SCORES;
    }
}

void display_high_scores(HighScore high_scores[], int count) {
    printf("\n=== Top 10 High Scores ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d\n", i + 1, high_scores[i].username, high_scores[i].score);
    }
    printf("==========================\n");
}








