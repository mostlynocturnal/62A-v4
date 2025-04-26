#pragma once
#include "api.h"
#include "main.h"

void writeSettings();
enum saveState {
    RUNNING,
    COMPLETE
};
inline saveState runState;
void readSettings();
enum filterSettings{
    UPDATED,
    OLD
};
inline filterSettings updateState;
void checkSettings();