#include "entrypoint.h"
#include "logic.h"

void executeOperation(Event event, AppProperties* props, AppContext* context) {
    switch (event) {
    case INITIALIZATION:
        initialization(context);
        break;
    case BUTTON_CLICKED:
        validateUserInput(props->userInput.toLocal8Bit().constData(), context);
        if (context->errorType == OK) {
            performConversion(context);
        }
        break;
    case SOURCE_BASE_CHANGED:
        setSourceNumberSystem(props->selectedSystem, context);
        break;
    case TARGET_BASE_CHANGED:
        setTargetNumberSystem(props->selectedSystem, context);
        break;
    }
}
