#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <string.h>

typedef void (*BinaryOperation)(const void* arg1, const void* arg2, void* result);

typedef struct {
    size_t size;
    BinaryOperation add;
    BinaryOperation multiply;
    void (*count)(const void* arg, void* result);
    void (*print)(const void*);
} TypeInfo;

#endif