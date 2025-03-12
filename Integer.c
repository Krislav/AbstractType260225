#include "Integer.h"

void intAdd(const void* arg1, const void* arg2, void* result, int subtraction){
    if (subtraction == 1) *(int*)result = *(int*)arg1 - *(int*)arg2;
    else *(int*)result = *(int*)arg1 + *(int*)arg2;
}

void intMultiply(const void* arg1, const void* arg2, void* result){
    *(int*)result = *(int*)arg1 * *(int*)arg2;
}

void intPrint(const void* data){
    if (*(const int*)data >= 0) printf("+ %d", *(const int*)data);
    else printf("- %d", *(const int*)data);
}

void intInput(void* result){
    scanf("%d", (int*)result);
}

void intGetZero(void* data){
    *(int*)data = 0;
}

TypeInfo* GetIntTypeInfo(){
    if (INT_TYPE_INFO == NULL) {
        INT_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        INT_TYPE_INFO->size = sizeof(int);
        INT_TYPE_INFO->add = intAdd;
        INT_TYPE_INFO->multiply = intMultiply;
        INT_TYPE_INFO->print = intPrint;
        INT_TYPE_INFO->input = intInput;
        INT_TYPE_INFO->getZero = intGetZero;
    }
    return INT_TYPE_INFO;
}