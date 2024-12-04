#include "Utilityfunction.h"

void shopandhomeframe(){
	gotoxy(50, 3);
	printf("/\\		__________");
	gotoxy(49, 4);
	printf("/  \\          |          |");
	gotoxy(48, 5);
	printf("/    \\         |   ____   |");
	gotoxy(47, 6);
	printf("--------        |   SEED   |");
	gotoxy(46, 7);
	printf("|        |       |   SHOP   |");
	gotoxy(46, 8);
	printf("|        |       |   ----   |");
	gotoxy(46, 9);
	printf("|  ____  |       |   ____   |");
	gotoxy(46, 10);
	printf("|  |  |  |       |  |    |  | ");
	gotoxy(46, 11);
	printf("|  | o|  |       |  | oo |  | ");
	gotoxy(43, 12);
	printf("___|__|__|__|_______|__|____|__|_________");
	
}

void personframe1(){
	gotoxy(51,10);
	printf("o");
	gotoxy(50,11);
	printf("-|-");
	gotoxy(50,12);
	printf("/ \\");
}

void personframe2(){
	gotoxy(52,10);
	printf("o");
	gotoxy(51,11);
	printf("-|-");
	gotoxy(51,12);
	printf("/ \\");
}

void personframe3(){
	gotoxy(53,10);
	printf("o");
	gotoxy(52,11);
	printf("-|-");
	gotoxy(52,12);
	printf("/ \\");
}

void personframe4(){
	gotoxy(54,10);
	printf("o");
	gotoxy(53,11);
	printf("-|-");
	gotoxy(53,12);
	printf("/ \\");
}

void personframe5(){
	gotoxy(55,10);
	printf("o");
	gotoxy(54,11);
	printf("-|-");
	gotoxy(54,12);
	printf("/ \\");
}

void personframe6(){
	gotoxy(56,10);
	printf("o");
	gotoxy(55,11);
	printf("-|-");
	gotoxy(55,12);
	printf("/ \\");
}

void personframe7(){
	gotoxy(57,10);
	printf("o");
	gotoxy(56,11);
	printf("-|-");
	gotoxy(56,12);
	printf("/ \\");
}

void personframe8() {
    gotoxy(58,10);
    printf("o");
    gotoxy(57,11);
    printf("-|-");
    gotoxy(57,12);
    printf("/ \\");
}

void personframe9() {
    gotoxy(59,10);
    printf("o");
    gotoxy(58,11);
    printf("-|-");
    gotoxy(58,12);
    printf("/ \\");
}

void personframe10() {
    gotoxy(60,10);
    printf("o");
    gotoxy(59,11);
    printf("-|-");
    gotoxy(59,12);
    printf("/ \\");
}

void personframe11() {
    gotoxy(61,10);
    printf("o");
    gotoxy(60,11);
    printf("-|-");
    gotoxy(60,12);
    printf("/ \\");
}

void personframe12() {
    gotoxy(62,10);
    printf("o");
    gotoxy(61,11);
    printf("-|-");
    gotoxy(61,12);
    printf("/ \\");
}

void personframe13() {
    gotoxy(63,10);
    printf("o");
    gotoxy(62,11);
    printf("-|-");
    gotoxy(62,12);
    printf("/ \\");
}

void personframe14() {
    gotoxy(64,10);
    printf("o");
    gotoxy(63,11);
    printf("-|-");
    gotoxy(63,12);
    printf("/ \\");
}

void personframe15() {
    gotoxy(65,10);
    printf("o");
    gotoxy(64,11);
    printf("-|-");
    gotoxy(64,12);
    printf("/ \\");
}

void personframe16() {
    gotoxy(66,10);
    printf("o");
    gotoxy(65,11);
    printf("-|-");
    gotoxy(65,12);
    printf("/ \\");
}

void personframe17() {
    gotoxy(67,10);
    printf("o");
    gotoxy(66,11);
    printf("-|-");
    gotoxy(66,12);
    printf("/ \\");
}

void shopanimation(){
	shopandhomeframe();
	personframe1();
	gotoxy(50,13);
	printf("Going to the shop.");
	Sleep(200);
	system("cls");

	
	
	shopandhomeframe();
	personframe2();
	gotoxy(50,13);
	printf("Going to the shop.");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe3();
	gotoxy(50,13);
	printf("Going to the shop..");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe4();
	gotoxy(50,13);
	printf("Going to the shop..");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe5();
	gotoxy(50,13);
	printf("Going to the shop...");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe6();
	gotoxy(50,13);
	printf("Going to the shop...");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe7();
	gotoxy(50,13);
	printf("Going to the shop....");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe8();
	gotoxy(50,13);
	printf("Going to the shop....");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe9();
	gotoxy(50,13);
	printf("Going to the shop...");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe10();
	gotoxy(50,13);
	printf("Going to the shop...");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe11();
	gotoxy(50,13);
	printf("Going to the shop..");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe12();
	gotoxy(50,13);
	printf("Going to the shop..");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe13();
	gotoxy(50,13);
	printf("Going to the shop.");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe14();
	gotoxy(50,13);
	printf("Going to the shop.");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe15();
	gotoxy(50,13);
	printf("Going to the shop..");
	Sleep(200);
	system("cls");
	
	shopandhomeframe();
	personframe16();
	gotoxy(50,13);
	printf("Going to the shop..");
	Sleep(200);
	system("cls");
}

void goinghomeanimation() {
    shopandhomeframe();
    personframe16();
    gotoxy(50,13);
    printf("Going back..");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe15();
    gotoxy(50,13);
    printf("Going back..");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe14();
    gotoxy(50,13);
    printf("Going back.");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe13();
    gotoxy(50,13);
    printf("Going back.");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe12();
    gotoxy(50,13);
    printf("Going back..");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe11();
    gotoxy(50,13);
    printf("Going back..");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe10();
    gotoxy(50,13);
    printf("Going back...");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe9();
    gotoxy(50,13);
    printf("Going back...");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe8();
    gotoxy(50,13);
    printf("Going back....");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe7();
    gotoxy(50,13);
    printf("Going back....");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe6();
    gotoxy(50,13);
    printf("Going back...");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe5();
    gotoxy(50,13);
    printf("Going back...");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe4();
    gotoxy(50,13);
    printf("Going back..");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe3();
    gotoxy(50,13);
    printf("Going back..");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe2();
    gotoxy(50,13);
    printf("Going back.");
    Sleep(200);
    system("cls");

    shopandhomeframe();
    personframe1();
    gotoxy(50,13);
    printf("Going back.");
    Sleep(200);
    system("cls");
}



