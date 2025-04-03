#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include <QString>
#include "appcontext.h"

enum Event {
    INITIALIZATION,
    BUTTON_CLICKED,
    SOURCE_BASE_CHANGED,
    TARGET_BASE_CHANGED
};

typedef struct {
    int selectedSystem;
    QString userInput;
} AppProperties;

void executeOperation(Event event, AppProperties* props, AppContext* context);

#endif // ENTRYPOINT_H
