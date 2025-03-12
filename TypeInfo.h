#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void (*BinaryOperation1)(const void* arg1, const void* arg2, void* result);
typedef void (*BinaryOperation2)(const void* arg1, const void* arg2, void* result, int subtraction);

typedef struct {
    size_t size;
    BinaryOperation2 add;
    BinaryOperation1 multiply;
    void (*print)(const void*);
    void (*input)(void* result);
    void (*getZero)(void* data);
} TypeInfo;

#endif