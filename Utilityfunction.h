#ifndef UTILITYFUNCTION_H
#define UTILITYFUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)
#endif



void gotoxy(int x, int y);

#endif 

