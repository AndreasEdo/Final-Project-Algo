

#include "Utilityfunction.c"


void wateringcan() {
    gotoxy(50, 3);
    printf("  ___");
    gotoxy(50, 4);
    printf(" |   |");
    gotoxy(49, 5);
    printf(" _|___|_");
    gotoxy(45, 6);
    printf("|   |       |");
    gotoxy(45, 7);
    printf("|---|       |");
    gotoxy(45, 8);
    printf("|---|       |");
    gotoxy(45, 9);
    printf("|   |_______|");
}

void wateringcanLiftedframe1() {
    gotoxy(54, 1);
    printf("__");
    gotoxy(51, 2);
    printf("__/  \\");
    gotoxy(50, 3);
    printf("/ /    \\");
    gotoxy(49, 4);
    printf("/ /      \\");
    gotoxy(48, 5);
    printf("/ /        \\");
    gotoxy(47, 6);
    printf("/_/          |");
    gotoxy(49, 7);
    printf("\\         /");
    gotoxy(49, 8);
    printf("/\\       /");
    gotoxy(47, 9);
    printf("\\/ /\\     /");
    gotoxy(46, 10);
    printf("| \\/  \\   /");
    gotoxy(47, 11);
    printf("| \\   \\ /");
    gotoxy(46, 12);
    printf("| |     -");
}

void wateringcanLiftedframe2() {
    gotoxy(54, 1);
    printf("__");
    gotoxy(51, 2);
    printf("__/  \\");
    gotoxy(50,3);
    printf("/ /    \\");
    gotoxy(49, 4);
    printf("/ /      \\");
    gotoxy(48, 5);
    printf("/ /        \\");
    gotoxy(47, 6);
    printf("/_/          |");
    gotoxy(49, 7);
    printf("\\         /");
    gotoxy(49, 8);
    printf("/\\       /");
    gotoxy(47, 9);
    printf("\\/ /\\     /");
    gotoxy(46, 10);
    printf("| \\/  \\   /");
    gotoxy(47, 11);
    printf(" |\\   \\ /");
    gotoxy(47, 12);
    printf("|      -");
}



void waterFrame1() {
    gotoxy(45, 13); printf("|   |");
    gotoxy(46, 14); printf("|   |");
}

void waterFrame2() {
    gotoxy(45, 13); printf("|   |");
    gotoxy(46, 14); printf("|   |");
    gotoxy(45, 15); printf("|   |");
    gotoxy(46, 16); printf("|   |");
}

void waterFrame3() {
    gotoxy(45, 13); printf("|   |");
    gotoxy(47, 14); printf("|   |");
    gotoxy(46, 15); printf("|   |");
    gotoxy(47, 16); printf("|   |");
    gotoxy(46, 17); printf("|   |");
}

void waterFrame4() {
    gotoxy(44, 13); printf("|   |");
    gotoxy(45, 14); printf("|   |");
    gotoxy(44, 15); printf("|   |");
    gotoxy(45, 16); printf("|   |");
    gotoxy(44, 17); printf("|   |");
}

void waterFrame5() {
    gotoxy(45, 13); printf("|   |");
    gotoxy(46, 14); printf("|   |");
    gotoxy(45, 15); printf("|   |");
    gotoxy(46, 16); printf("|   |");
    gotoxy(45, 17); printf("|   |");
}



void animationwatering() {
    system("cls");
    wateringcan();
    gotoxy(50,18);
    printf("Watering");
    Sleep(1000);

    system("cls");
    wateringcanLiftedframe1();
    waterFrame1();
    gotoxy(50,18);
    printf("Watering.");
    Sleep(500);

    system("cls");
    wateringcanLiftedframe2();
    waterFrame2();
    gotoxy(50,18);
    printf("Watering.");
    Sleep(500);

    system("cls");
    wateringcanLiftedframe1();
    waterFrame3();
    gotoxy(50,18);
    printf("Watering..");
    Sleep(500);
	
	system("cls");
    wateringcanLiftedframe2();
    waterFrame1();
    gotoxy(50,18);
    printf("Watering...");
    Sleep(500);
    
    system("cls");
    wateringcanLiftedframe2();
    waterFrame2();
    gotoxy(50,18);
    printf("Watering.");
    Sleep(500);
    
    
    system("cls");
    wateringcanLiftedframe2();
    waterFrame4();
    gotoxy(50,18);
    printf("Watering..");
    Sleep(500);

    system("cls");
    wateringcanLiftedframe1();
    waterFrame5();
    gotoxy(50,18);
    printf("Watering...");
    Sleep(500);

    
}

int main(){
	animationwatering();
}






