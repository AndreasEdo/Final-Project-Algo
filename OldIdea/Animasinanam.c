

#include "Utilityfunction.h"

void padiframe1(){
	gotoxy(53,2);
	printf("__");
	gotoxy(50,3);
	printf("  / /");
	gotoxy(47,4);
	printf("/\\  / /__");
	gotoxy(46,5);
	printf("/  \\/ /   \\");
	gotoxy(50,6);
	printf("| |    \\");
	gotoxy(50,7);
	printf("| |");
	gotoxy(46,8);
	printf("   /| |\\   ");
	gotoxy(45,9);
	printf("  _/    /\\_");

}

void padiframe2(){
	gotoxy(53,3);
	printf("__");
	gotoxy(47,4);
	printf("\\    / /");
	gotoxy(47,5);
	printf(" \\  / /__");
	gotoxy(46,6);
	printf("   \\/ /   \\");
	gotoxy(50,7);
	printf("| |    \\");
	gotoxy(50,8);
	printf("| |");
	gotoxy(46,9);
	printf("   /| |\\   ");
	gotoxy(45,10);
	printf("  _/    /\\_");
}

void padiframe3(){
	gotoxy(53,4);
	printf("__");
	gotoxy(47,5);
	printf("\\    / /");
	gotoxy(47,6);
	printf(" \\  / /__");
	gotoxy(46,7);
	printf("   \\/ /   \\");
	gotoxy(50,8);
	printf("| |    \\");
	gotoxy(50,9);
	printf("| |");
	gotoxy(46,10);
	printf("   /| |\\   ");
	gotoxy(45,11);
	printf("  _/    /\\_");
}

void padiframe4(){
	gotoxy(53,6);
	printf("__");
	gotoxy(47,7);
	printf("     / /");
	gotoxy(47,8);
	printf("/\\  / /__");
	gotoxy(46,9);
	printf("   \\/ /   \\");
	gotoxy(50,10);
	printf("| |    \\");
	gotoxy(50,11);
	printf("| |");
	
}

void tanah1(){
	gotoxy(42,12);
	printf("--------| |---------");
}

void tanah2(){
	gotoxy(42,12);
	printf("--------------------");
}

void displaynanam(){
	system("cls");
	padiframe1();
	tanah2();
	gotoxy(46,13);
	printf("Planting.");
	Sleep(500);
	
	system("cls");
	padiframe2();
	tanah2();
	gotoxy(46,13);
	printf("Planting..");
	Sleep(500);
	
	system("cls");
	padiframe3();
	tanah2();
	gotoxy(46,13);
	printf("Planting...");
	Sleep(500);
	
	system("cls");
	padiframe4();
	tanah1();
	gotoxy(46,13);
	printf("Planting.");
	Sleep(500);
	
	system("cls");
	padiframe1();
	tanah2();
	gotoxy(46,13);
	printf("Planting..");
	Sleep(500);
	
	system("cls");
	padiframe2();
	tanah2();
	gotoxy(46,13);
	printf("Planting...");
	Sleep(500);
	
	system("cls");
	padiframe3();
	tanah2();
	gotoxy(46,13);
	printf("Planting.");
	Sleep(500);
	
	system("cls");
	padiframe4();
	tanah1();
	gotoxy(46,13);
	printf("Planting..");
	Sleep(500);
}


