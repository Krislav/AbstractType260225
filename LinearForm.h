#ifndef LINEARFORM_H
#define LINEARFORM_H

#include "Integer.h"
#include "Double.h"
#include "TypeInfo.h"
#include "LinearFormErrors.h"

typedef struct Coef {
    void* coef;
    struct Coef* next_coef;
} Coef;

typedef struct {
    Coef* first_coef;
    int quantity;
    TypeInfo* type_info;
} LinearForm;

LinearForm* CreateLinearForm(TypeInfo* type_info, int quantity, LinearFormErrors* operation_result);
void freeLinearForm(LinearForm* linear_form);
LinearFormErrors InputLinearForm(LinearForm* linear_form);
LinearFormErrors ReplaceLinearForm(LinearForm* linear_form, const void* index, const void* data);
LinearFormErrors addLinearForm(const LinearForm* lf1, const LinearForm* lf2, LinearForm* result, int subtraction);
LinearFormErrors multiplyLinearForm(LinearForm* linear_form, const void* multiplier);
LinearFormErrors countLinearForm(const LinearForm* linear_form, void* result);
LinearFormErrors printLinearForm(const LinearForm* linear_form);

#endif