#include "gotoxy.h"

void sunframe1(){
	gotoxy(50,8);
	printf("\\ /");
	gotoxy(49,9);
	printf("--O--");
	gotoxy(50,10);
	printf("/ \\");
}

void sunframe2(){
	gotoxy(49,7);
	printf("_____");
	gotoxy(48,8);
	printf("/  o  \\");
	gotoxy(48,9);
	printf("|o    |");
	gotoxy(48,10);
	printf("\\    o/");
	gotoxy(49,11);
	printf("-----");
}


void suntomoon(){
	int a = 59;int A = 45;
	int b = 12;int B = 8;
	int c = 58;int C = 44;
	int d = 13;int D = 9;
	int e = 59;int E = 44;
	int f = 14;int F = 10;
	int G = 44;int H = 11;
	int I = 45;int J = 12;
	for(int i=0;i<5;i++){
		gotoxy(a,b);
		printf("\033[0;33m");
		printf("\\ /");
		gotoxy(c,d);
		printf("--O--");
		gotoxy(e,f);
		printf("/ \\");
		printf("\033[0m");
		gotoxy(A, B);
		printf("_____");
		gotoxy(C,D);
		printf("/  o  \\");
		gotoxy(E,F);
		printf("|o    |");
		
		if(i<4){
			gotoxy(G,H);
			printf("\\    o/");
			gotoxy(I,J);
			printf("-----");
		}
		
		
		gotoxy(46,13);
		printf("| |o| |");
		gotoxy(45,12);
		printf("/_______\\");
		gotoxy(46,11);
		printf("/     \\");
		gotoxy(47,10);
		printf("/   \\");
		gotoxy(48,9);
		printf("/ \\");
		gotoxy(33,14);
		printf("-------------|-| |-|-------------------------------");
		gotoxy(40,15);
		printf("Changing to next day");
		if(i == 1){
			gotoxy(60,15);
			printf(".");
		}else if(i == 2){
			printf("..");
		}else if(i==3){
			printf("...");
		}else if(i==4){
			printf("..");
		}else{
			printf("...");
		}
		a--;
		b--;
		c--;
		d--;
		e--;
		f--;
		A--;
		B++;
		C--;
		D++;
		E--;
		F++;
		G--;
		H++;
		I--;
		J++;
		Sleep(500);
		system("cls");
		
		
		
	}
}

