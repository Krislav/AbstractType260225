#include <Double.h>

void doubleAdd(const void* arg1, const void* arg2, void* result){
    *(int*)result = *(int*)arg1 + *(int*)arg1;
}

void doubleMultiply(const void* arg1, const void* arg2, void* result){
    *(int*)result = *(int*)arg1 * *(int*)arg1;
}

void doublePrint(const void* data){
    printf("%d", *(const int*)data);
}

void doubleInput(void* result){
    scanf("%d", *(int*)result);
}

TypeInfo* GetDoubleTypeInfo(){
    if (DOUBLE_TYPE_INFO == NULL) {
        DOUBLE_TYPE_INFO = (TypeInfo*)malloc(sizeof(TypeInfo));
        DOUBLE_TYPE_INFO->size = sizeof(double);
        DOUBLE_TYPE_INFO->add = doubleAdd;
        DOUBLE_TYPE_INFO->multiply = doubleMultiply;
        DOUBLE_TYPE_INFO->print = doublePrint;
        DOUBLE_TYPE_INFO->input = doubleInput;
    }
    return DOUBLE_TYPE_INFO;
}