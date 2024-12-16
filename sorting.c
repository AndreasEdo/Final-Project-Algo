
#include "struct.c"

// Function to swap two `highscore` structs
void swaphighscore(highscore *a, highscore *b) {
    highscore temp = *a;
    *a = *b;
    *b = temp;
}

// Quicksort function
void quicksorthighscore(highscore arr[], int left, int right) {
    if (left < right) {
        int i = left, j = left - 1;
        int pivot = arr[right].hs;

        while (i < right) {
            if (arr[i].hs >= pivot) {
                j++;
                swaphighscore(&arr[j], &arr[i]);
            }
            i++;
        }

        j++;
        swaphighscore(&arr[j], &arr[right]);

        quicksorthighscore(arr, left, j - 1);
        quicksorthighscore(arr, j + 1, right);
    }
}

void sorths(const char *hsFile) {
    highscore Highscore[15];
    int count = 0;
    char line[MAX_LINE_LENGTH];
    FILE *file = fopen(hsFile, "r");

    if (file == NULL) {
        perror("Error opening highscore file");
        return;
    }

    // Skip the header line
    fgets(line, sizeof(line), file);

    // Read data from file
    while (fgets(line, sizeof(line), file)) {
        

        // Parse the line into `name` and `hs`
        sscanf(line, "%49[^,],%d", Highscore[count].name, &Highscore[count].hs);
        count++;
    }
    fclose(file);

    // Sort the array using quicksort
    quicksorthighscore(Highscore, 0, count - 1);

    
}

int main() {
    
    sorths(HIGHSCORE);
    return 0;
}
