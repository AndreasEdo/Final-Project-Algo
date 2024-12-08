#include "struct.h"
#include <time.h>
#include <stdlib.h>

// Function to generate a random number between lower and upper (inclusive)
int random(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}

// Common Box Function
int commonbox() {
    srand(time(NULL));
    int a = random(1, 1000);
    if (a < 490) {
        return random(1, 17);  // 49%
    } else if (a < 820) {
        return random(1, 12) + 17;  // 43%
    } else if (a < 953) {
        return random(1, 11) + 29;  //13.3%
    } else if (a < 998) {
        return random(1, 6) + 40;   //4.5%
    } else {
        return random(1, 2) + 46;   //0.2%
    }
}

// Rare Box Function
int rarebox() {
    srand(time(NULL));
    int a = random(1, 500);
    if (a < 150) {
        return random(1, 17);  // 30%
    } else if (a < 360) {
        return random(1, 12) + 17;  //42%
    } else if (a < 460) {
        return random(1, 11) + 29;  //20%
    } else if (a < 495) {
        return random(1, 6) + 40;   //7%
    } else {
        return random(1, 2) + 46;   //1%
    }
}

// Epic Box Function
int epicbox() {
    srand(time(NULL));
    int a = random(1, 1000);
    if (a < 170) {
        return random(1, 17);  // 17%
    } else if (a < 390) {
        return random(1, 12) + 17;  // 22%
    } else if (a < 740) {
        return random(1, 11) + 29;  // 35%
    } else if (a < 920) {
        return random(1, 6) + 40;   // 18%
    } else {
        return random(1, 2) + 46;   // 8%
    }
}

