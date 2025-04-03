#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define MAX_LEN 33

#define MIN_INT -2147483648 //replace
#define MAX_INT 2147483647

enum ErrorType {
    NOT_ENTERED_TEXT,
    SYSTEM_NOT_SET,
    INVALID_INPUT,
    BIG_NUM,
    MALLOC_ERROR,
    OK
};

typedef struct {
    char userInput[MAX_LEN];
    char output[MAX_LEN];
    ErrorType errorType;
    int sourceSystem;
    int targetSystem;
} AppContext;

#endif // APPCONTEXT_H
