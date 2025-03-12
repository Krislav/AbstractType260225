#ifndef INTEGER_H
#define INTEGER_H

#include "TypeInfo.h"

static TypeInfo* INT_TYPE_INFO = NULL;

void intAdd(const void* arg1, const void* arg2, void* result, int subtraction);
void intMultiply(const void* arg1, const void* arg2, void* result);
void intPrint(const void* data);
void intInput(void* result);
void intGetZero(void* data);
TypeInfo* GetIntTypeInfo();

#endif