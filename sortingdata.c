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
        perror("Error opening file");
        return;
    }
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%19[^,],%9[^,],%9s", &crop[count].index, crop[count].name, crop[count].rarity, crop[count].status);
        count++;
    }
    fclose(file);

    quicksortalphabet(crop, 0, count - 1);
    for (int i = 0; i < count; i++) {
        printf("%d %s %s %s\n", crop[i].index, crop[i].name, crop[i].rarity, crop[i].status);
    }
}

int main() {
    sortalphabetdata(FILENAME);
    return 0;
}

