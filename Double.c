#include "Double.h"

void doubleAdd(const void* arg1, const void* arg2, void* result, int subtraction){
    if (subtraction == 1) *(double*)result = *(double*)arg1 - *(double*)arg2;
    else *(double*)result = *(double*)arg1 + *(double*)arg2;
}

void doubleMultiply(const void* arg1, const void* arg2, void* result){
    *(double*)result = *(double*)arg1 * *(double*)arg2;
}

void doublePrint(const void* data){
    if (*(const double*)data >= 0) printf("+%lf", *(const double*)data);
    else printf("%lf", *(const double*)data);
}

void doubleInput(void* result){
    scanf("%lf", (double*)result);
}

void doubleGetZero(void* data){
    *(double*)data = 0;
}

TypeInfo* GetDoubleTypeInfo(){
    if (DOUBLE_TYPE_INFO == NULL) {
        DOUBLE_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        DOUBLE_TYPE_INFO->size = sizeof(double);
        DOUBLE_TYPE_INFO->add = doubleAdd;
        DOUBLE_TYPE_INFO->multiply = doubleMultiply;
        DOUBLE_TYPE_INFO->print = doublePrint;
        DOUBLE_TYPE_INFO->input = doubleInput;
        DOUBLE_TYPE_INFO->getZero = doubleGetZero;
    }
    return DOUBLE_TYPE_INFO;
}