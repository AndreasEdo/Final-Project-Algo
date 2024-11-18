#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)
#endif

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void wateringcan() {
    gotoxy(30, 3);
    printf("  ___");
    gotoxy(30, 4);
    printf(" |   |");
    gotoxy(29, 5);
    printf(" _|___|_");
    gotoxy(25, 6);
    printf("|   |       |");
    gotoxy(25, 7);
    printf("|---|       |");
    gotoxy(25, 8);
    printf("|---|       |");
    gotoxy(25, 9);
    printf("|   |_______|");
}

void wateringcanLiftedframe1() {
    gotoxy(34, 1);
    printf("__");
    gotoxy(31, 2);
    printf("__/  \\");
    gotoxy(30, 3);
    printf("/ /    \\");
    gotoxy(29, 4);
    printf("/ /      \\");
    gotoxy(28, 5);
    printf("/ /        \\");
    gotoxy(27, 6);
    printf("/_/          |");
    gotoxy(29, 7);
    printf("\\         /");
    gotoxy(29, 8);
    printf("/\\       /");
    gotoxy(27, 9);
    printf("\\/ /\\     /");
    gotoxy(26, 10);
    printf("| \\/  \\   /");
    gotoxy(27, 11);
    printf("| \\   \\ /");
    gotoxy(26, 12);
    printf("| |     -");
}

void wateringcanLiftedframe2() {
    gotoxy(34, 1);
    printf("__");
    gotoxy(31, 2);
    printf("__/  \\");
    gotoxy(30, 3);
    printf("/ /    \\");
    gotoxy(29, 4);
    printf("/ /      \\");
    gotoxy(28, 5);
    printf("/ /        \\");
    gotoxy(27, 6);
    printf("/_/          |");
    gotoxy(29, 7);
    printf("\\         /");
    gotoxy(29, 8);
    printf("/\\       /");
    gotoxy(27, 9);
    printf("\\/ /\\     /");
    gotoxy(26, 10);
    printf("| \\/  \\   /");
    gotoxy(27, 11);
    printf(" |\\   \\ /");
    gotoxy(27, 12);
    printf("|      -");
}



void waterFrame1() {
    gotoxy(25, 13); printf("|   |");
    gotoxy(26, 14); printf("|   |");
}

void waterFrame2() {
    gotoxy(25, 13); printf("|   |");
    gotoxy(26, 14); printf("|   |");
    gotoxy(25, 15); printf("|   |");
    gotoxy(26, 16); printf("|   |");
}

void waterFrame3() {
    gotoxy(25, 13); printf("|   |");
    gotoxy(27, 14); printf("|   |");
    gotoxy(26, 15); printf("|   |");
    gotoxy(27, 16); printf("|   |");
    gotoxy(26, 17); printf("|   |");
}

void waterFrame4() {
    gotoxy(24, 13); printf("|   |");
    gotoxy(25, 14); printf("|   |");
    gotoxy(24, 15); printf("|   |");
    gotoxy(25, 16); printf("|   |");
    gotoxy(24, 17); printf("|   |");
}

void waterFrame5() {
    gotoxy(25, 13); printf("|   |");
    gotoxy(26, 14); printf("|   |");
    gotoxy(25, 15); printf("|   |");
    gotoxy(26, 16); printf("|   |");
    gotoxy(25, 17); printf("|   |");
}

void watering(){
	gotoxy(28,18);
	
}

void animationwatering() {
    system("cls");
    wateringcan();
    gotoxy(30,18);
    printf("Watering");
    Sleep(1000);

    system("cls");
    wateringcanLiftedframe1();
    waterFrame1();
    gotoxy(30,18);
    printf("Watering.");
    Sleep(500);

    system("cls");
    wateringcanLiftedframe2();
    waterFrame2();
    gotoxy(30,18);
    printf("Watering.");
    Sleep(500);

    system("cls");
    wateringcanLiftedframe1();
    waterFrame3();
    gotoxy(30,18);
    printf("Watering..");
    Sleep(500);
	
	system("cls");
    wateringcanLiftedframe2();
    waterFrame1();
    gotoxy(30,18);
    printf("Watering...");
    Sleep(500);
    
    system("cls");
    wateringcanLiftedframe2();
    waterFrame2();
    gotoxy(30,18);
    printf("Watering.");
    Sleep(500);
    
    
    system("cls");
    wateringcanLiftedframe2();
    waterFrame4();
    gotoxy(30,18);
    printf("Watering..");
    Sleep(500);

    system("cls");
    wateringcanLiftedframe1();
    waterFrame5();
    gotoxy(30,18);
    printf("Watering...");
    Sleep(500);

    
}



