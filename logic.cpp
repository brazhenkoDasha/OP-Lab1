#include "logic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

void initialization(AppContext* context) {
    context->sourceSystem = BIN;
    context->targetSystem = DEC;
}

void setSourceNumberSystem(int selectedSystem, AppContext* context) {
    context->sourceSystem = selectedSystem;
}

void setTargetNumberSystem(int selectedSystem, AppContext* context) {
    context->targetSystem = selectedSystem;
}

void validateUserInput(const char* userInput, AppContext* context) {
    if (strlen(userInput) < 1) {
        context->errorType = NOT_ENTERED_TEXT;
        return;
    }

    if (context->sourceSystem == 0 || context->targetSystem == 0) {
        context->errorType = SYSTEM_NOT_SET;
        return;
    }

    const char* validChars = "0123456789ABCDEF";
    for (size_t i = 0; i < strlen(userInput); i++) {
        if (userInput[i] == '-' && i == 0 && context->sourceSystem == DEC) {
            continue;
        }
        bool isValidChar = false;
        for (int j = 0; j < context->sourceSystem; j++) {
            if (toupper(userInput[i]) == validChars[j]) {
                isValidChar = true;
                break;
            }
        }
        if (!isValidChar) {
            context->errorType = INVALID_INPUT;
            return;
        }
    }

    char* end;
    long int value = strtol(userInput, &end, context->sourceSystem);
    int maxDigitsCount = calculateMaxDigitsCount(context->sourceSystem);
    if (context->sourceSystem == OCT) {
        maxDigitsCount++;
    }
    if (context->sourceSystem == DEC && (*end != '\0' || value < MIN_INT || value > MAX_INT)) {
        context->errorType = BIG_NUM;
    } else if (context->sourceSystem != DEC && (strlen(userInput) > maxDigitsCount)) {
        context->errorType = BIG_NUM;
    } else {
        context->errorType = OK;
        strncpy(context->userInput, userInput, MAX_LEN - 1);
        context->userInput[MAX_LEN - 1] = '\0';
    }
}

int calculateMaxDigitsCount(int systemBase) {
    return 32 / (log(systemBase) / log(2)) ;
}

void fillWithZeros(char* buffer, int* index, int maxBufferSize) {
    while (*index < maxBufferSize) {
        buffer[(*index)++] = '0';
    }
}

void reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        str[i] = str[i] + str[len - i - 1];
        str[len - i - 1] = str[i] - str[len - i - 1];
        str[i] = str[i] - str[len - i - 1];
    }
}

void performConversion(AppContext* context) {
    if (context->sourceSystem == DEC && context->targetSystem == DEC) {
        strncpy(context->output, context->userInput, MAX_LEN);
    } else {
        char* buffer = convertDiffSystems(context->userInput, context->sourceSystem, context->targetSystem);
        if (buffer != NULL) {
            strncpy(context->output, buffer, MAX_LEN);
            free(buffer);
        } else {
            context->errorType = MALLOC_ERROR;
        }
    }
}

char* convertDiffSystems(char* userInput, int sourceSystem, int targetSystem) {
    bool isNegative = false;
    if (sourceSystem == DEC) {
        if (userInput[0] == '-') {
            isNegative = true;
            userInput++;
        }
    } else {
        int length = strlen(userInput);
        int maxSourceDigits = calculateMaxDigitsCount(sourceSystem);
        if (length == maxSourceDigits && userInput[0] != '0') {
            isNegative = true;
        }
    }
    unsigned int value = strtoul(userInput, NULL, sourceSystem);
    int maxTargetDigits = calculateMaxDigitsCount(targetSystem);
    if (targetSystem == OCT) {
        maxTargetDigits++;
    }
    char* buffer = (char*) calloc(maxTargetDigits + 1, sizeof(char));
    if (buffer != NULL) {
        if (isNegative && (sourceSystem == DEC || targetSystem == DEC)) {
            value = ~value + 1;
        }
        int index = 0;
        while (value > 0) {
            int rem = value % targetSystem;
            buffer[index++] = '0' + rem;
            value /= targetSystem;
        }
        if (targetSystem != DEC) {
           fillWithZeros(buffer, &index, maxTargetDigits);
        if (isNegative) {
            buffer[index++] = '-';
        }
        buffer[index] = '\0';
        reverseString(buffer);
    }
    return buffer;
    }
}
