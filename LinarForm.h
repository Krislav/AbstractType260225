#ifndef LINARFORM_H
#define LINARFORM_H

#include <Integer.h>
#include <Double.h>
#include <TypeInfo.h>
#include <LinarFormErrors.h>

typedef struct {
    void* coef;
    Coef* next_coef;
} Coef;

typedef struct {
    Coef* first_coef;
    int quantity;
    TypeInfo* type_info;
} LinarForm;

LinarForm* CreateLinarForm(TypeInfo* type_info, int quantity, LinarFormErrors* operation_result);
void freeLinarForm(LinarForm* linar_form);
LinarFormErrors InputLinarForm(LinarForm* linar_form);
LinarFormErrors ReplaceLinarForm(LinarForm* linar_form, const void* index, const void* data);
LinarFormErrors addLinarForm(const LinarForm* lf1, const LinarForm* lf2, LinarForm* result, int subtraction);
LinarFormErrors multiplyLinarForm(LinarForm* linar_form, const void* multiplier);
LinarFormErrors countLinarForm(const LinarForm* linar_form, void* result);
LinarFormErrors printLinarForm(const LinarForm* linar_form);

#endif