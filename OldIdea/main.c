#include "Farmingsimulator.c"

int main(){
//    displayintro();
    press_enter_to_continue();
    switch(option()){
        case 1:
            farmingsim();
            break;
        case 2:
            printf("Crops Data\n");
            break;
        default:
            printf("Invalid Option\n");
    }
}

