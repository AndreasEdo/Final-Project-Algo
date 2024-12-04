#include "Utilityfunction.h"

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void press_enter_to_continue() {
    while (getchar() != '\n') { }
}

void clear_screen() {
    printf("\nEnter 1 to continue...\n");
    int input;
    while (1) {
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &input) == 1) {
                if (input == 1) {
                    break;
                }
            }
        }
        printf("Invalid input! Please enter 1 to continue.\n");
    }
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int get_valid_input(const char *prompt, int min, int max) {
    int input;
    char buffer[100];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin)) {
            if (sscanf(buffer, "%d", &input) == 1) {
                if (input >= min && input <= max) {
                    return input;
                } else {
                    printf("Input out of range! Please enter a number between %d and %d.\n", min, max);
                }
            } else {
                printf("Invalid input! Please enter a valid number.\n");
            }
        }
    }
}

void printMenu(int selectedoption) {
    const char *menuItems[] = {"Play", "Crops Data"};
    int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);
	int y = 8;
    for (int i = 0; i < menuSize; i++) {
    	
        if (i == selectedoption) {
        	gotoxy(50,y);
        	y++;
            printf(" > %s\n", menuItems[i]);  
        } else {
        	gotoxy(50,y);
        	y++;
            printf("   %s\n", menuItems[i]);
        }
    }
}

int option() {
    int selectedoption = 0;
    char key;

    while (1) {
        system("cls");
        gotoxy(50,8);
        printMenu(selectedoption);

        key = getch();

        if (key == -32) {
            key = getch();
            if (key == 72) {
                selectedoption--;
                if (selectedoption < 0) {
                    selectedoption = 1;
                }
            } else if (key == 80) {
                selectedoption++;
                if (selectedoption > 1) {
                    selectedoption = 0;
                }
            }
        } else if (key == '\r') {
            return selectedoption + 1;
        }
    }
}

void get_username(char *username) {
    printf("Enter your username: ");
    fgets(username, username_length, stdin);
}

