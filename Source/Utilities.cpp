// File: Utilities.cpp
#include "Utilities.h"

// Function definition
void Textcolor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
