#ifndef LOGIC_H
#define LOGIC_H

#include "appcontext.h"

enum Base {
    DEC = 10,
    BIN = 2,
    OCT = 8
};

void initialization(AppContext* context);
void updateNumberSystem(const char* systemType, int selectedSystem, AppContext* context);
void setSourceNumberSystem(int selectedSystem, AppContext* context);
void setTargetNumberSystem(int selectedSystem, AppContext* context);
void validateUserInput(const char* userInput, AppContext* context);
void performConversion(AppContext* context);
char* convertDiffSystems(char* userInput, int sourceSystem, int targetSystem);
int calculateMaxDigitsCount(int systemBase);
void fillWithZeros(char* buffer, int* index, int maxBufferSize);
void reverseString(char* str);

#endif // LOGIC_H
