#include "console_color.h"

/// Normal
void clr_red () {
    printf("\033[0;31m");
}

void clr_green () {
    printf("\033[0;32m");
}

void clr_yellow () {
    printf("\033[0;33m");
}

void clr_blue () {
    printf("\033[0;34m");
}

void clr_magenta () {
    printf("\033[0;35m");
}

void clr_cyan () {
    printf("\033[0;35m");
}


/// Bold
void clr_Red () {
    printf("\033[1;31m");
}

void clr_Green () {
    printf("\033[1;32m");
}

void clr_Yellow () {
    printf("\033[1;33m");
}

void clr_Blue () {
    printf("\033[1;34m");
}

void clr_Magenta () {
    printf("\033[1;35m");
}

void clr_Cyan () {
    printf("\033[1;35m");
}


/// reset the color
void clr_reset () {
    printf("\033[0m");
}