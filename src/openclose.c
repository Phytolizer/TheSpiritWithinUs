/*
Original code by Ruud Helderman ("How to program a text adventure in C")
*/

#include "match.h"
#include "object.h"
#include "reach.h"

#include <stdio.h>

int executeOpen(void) {
    OBJECT* obj = reachableObject("what you want to open", params[0]);
    if (obj != NULL)
        printf("%s", (*obj->open)());
    return true;
}

int executeClose(void) {
    OBJECT* obj = reachableObject("what you want to close", params[0]);
    if (obj != NULL)
        printf("%s", (*obj->close)());
    return true;
}

int executeLock(void) {
    OBJECT* obj = reachableObject("what you want to lock", params[0]);
    if (obj != NULL)
        printf("%s", (*obj->lock)());
    return true;
}

int executeUnlock(void) {
    OBJECT* obj = reachableObject("what you want to unlock", params[0]);
    if (obj != NULL)
        printf("%s", (*obj->unlock)());
    return true;
}
