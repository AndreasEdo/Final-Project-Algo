#include "gotoxy.h"

void intro() {
    char line1[] = "You just got this old farm";
    char line2[] = "From a heritance";
    char line3[] = "Do you think you can";
    char line4[] = "Make this farm better?";
    
    gotoxy(47,4);
    for(int i=0;i<strlen(line1);i++){
    	printf("%c", line1[i]);
    	Sleep(100);
	}
	gotoxy(53,5);
	for(int i=0;i<strlen(line2);i++){
    	printf("%c", line2[i]);
		Sleep(100);
	}
	gotoxy(51,6);
	for(int i=0;i<strlen(line3);i++){
    	printf("%c", line3[i]);
    	Sleep(100);
	}
	gotoxy(50,7);
	for(int i=0;i<strlen(line4);i++){
    	printf("%c", line4[i]);
    	Sleep(100);
	}
}

