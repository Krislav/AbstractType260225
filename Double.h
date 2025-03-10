#ifndef DOUBLE_H
#define DOUBLE_H

#include "TypeInfo.h"

static TypeInfo* DOUBLE_TYPE_INFO = NULL;

void doubleAdd(const void* arg1, const void* arg2, void* result, int subtraction);
void doubleMultiply(const void* arg1, const void* arg2, void* result);
void doublePrint(const void* data);
void doubleInput(void* result);
TypeInfo* GetDoubleTypeInfo();

#endif