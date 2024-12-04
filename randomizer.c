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
    if (a < 450) {
        return random(1, 17);  // Common crop index
    } else if (a < 800) {
        return random(1, 12) + 17;  // Uncommon crop index
    } else if (a < 925) {
        return random(1, 11) + 29;  // Rare crop index
    } else if (a < 980) {
        return random(1, 6) + 40;   // Epic crop index
    } else {
        return random(1, 2) + 46;   // Legendary crop index
    }
}

// Rare Box Function
int rarebox() {
    srand(time(NULL));
    int a = random(1, 500);
    if (a < 150) {
        return random(1, 17);  // Common crop index
    } else if (a < 300) {
        return random(1, 12) + 17;  // Uncommon crop index
    } else if (a < 425) {
        return random(1, 11) + 29;  // Rare crop index
    } else if (a < 475) {
        return random(1, 6) + 40;   // Epic crop index
    } else {
        return random(1, 2) + 46;   // Legendary crop index
    }
}

// Epic Box Function
int epicbox() {
    srand(time(NULL));
    int a = random(1, 250);
    if (a < 25) {
        return random(1, 17);  // Common crop index
    } else if (a < 50) {
        return random(1, 12) + 17;  // Uncommon crop index
    } else if (a < 100) {
        return random(1, 11) + 29;  // Rare crop index
    } else if (a < 150) {
        return random(1, 6) + 40;   // Epic crop index
    } else {
        return random(1, 2) + 46;   // Legendary crop index
    }
}

