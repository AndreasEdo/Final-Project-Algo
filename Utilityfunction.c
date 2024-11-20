#include "Utilityfunction.h"


void gotoxy(int x, int y) {
   
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
}


// Function to clear the console with "Press 1 to continue..."
void clear_screen() {
    printf("\nEnter 1 to continue...\n");
    int input;
    while (1) {
        // Read input as a string to handle non-integer inputs
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Try to parse input as integer
            if (sscanf(buffer, "%d", &input) == 1) {
                if (input == 1) {
                    break;
                }
            }
        }
        printf("Invalid input! Please enter 1 to continue.\n");
    }

    // Clear the console
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to get valid integer input within a range
int get_valid_input(const char *prompt, int min, int max) {
    int input;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Attempt to parse integer
            if (sscanf(buffer, "%d", &input) == 1) {
                if (input >= min && input <= max) {
                    return input;
                } else {
                    printf("Input out of range! Please enter a number between %d and %d.\n", min, max);
                }
            } else {
                printf("Invalid input! Please enter a valid number.\n");
            }
        } else {
            printf("Error reading input! Please try again.\n");
        }
    }
}


