#include "LinearForm.h"

LinearForm* CreateLinearForm(TypeInfo* type_info, int quantity, LinearFormErrors* operation_result) {
    LinearForm* linear_form = (LinearForm*)malloc(sizeof(LinearForm));
    if (linear_form == NULL) {
        *operation_result = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    linear_form->type_info = type_info;
    linear_form->quantity = quantity;
    linear_form->first_coef = NULL;

    if (quantity > 0){
        linear_form->first_coef = (Coef*)malloc(sizeof(Coef));
        
        Coef* previous_coef = linear_form->first_coef;
        linear_form->first_coef->coef = malloc(sizeof(type_info->size));
        linear_form->first_coef->next_coef = NULL;

        for (int i = 0; i < quantity-1; i++) {
            Coef* arg_i = (Coef*)malloc(sizeof(Coef));
            if (arg_i == NULL) {
                *operation_result = MEMORY_ALLOCATION_FAILED;
                return NULL;
            }

            arg_i->coef = malloc(sizeof(type_info->size));
            arg_i->next_coef = NULL;
            previous_coef->next_coef = arg_i;
            previous_coef = arg_i;
        }
    }
    else if (quantity < 0){
        *operation_result = NEGATIVE_QUANTITY;
        free(linear_form);
        return NULL;
    }

    *operation_result = LINEAR_FORM_OPERATION_OK;
    return linear_form;
}

void freeLinearForm(LinearForm* linear_form) {
    if (linear_form != NULL) {
        if (linear_form->first_coef != NULL) {
            Coef* coef = linear_form->first_coef;
            Coef* previous_coef = NULL;
            while (coef->next_coef != NULL) {
                previous_coef = coef;
                coef = coef->next_coef;
                free(previous_coef->coef);
                free(previous_coef);
            }
            free(coef);
        }
    }
    free(linear_form);
}

LinearFormErrors InputLinearForm(LinearForm* linear_form){
    if (linear_form == NULL) return LINEAR_FORM_NOT_DEFINED;
    if (linear_form->type_info->input == NULL) return OPERATION_NOT_DEFINED;

    Coef* current_coef = linear_form->first_coef;
    for (int i = 0; i < linear_form->quantity; i++) {
        printf("Input %d coefficient: ", i);
        linear_form->type_info->input(current_coef->coef);
        current_coef = current_coef->next_coef;
    }
    return LINEAR_FORM_OPERATION_OK;
}

LinearFormErrors ReplaceLinearForm(LinearForm* linear_form, const void* index, const void* data){
    if (linear_form == NULL) return LINEAR_FORM_NOT_DEFINED;
    if (*(int*)index >= linear_form->quantity || *(int*)index < 0) return INDEX_OUT_OF_BOUNDS;

    Coef* current_coef = linear_form->first_coef;
    for (int i = 0; i < *(int*)index; i++) {
        current_coef = current_coef->next_coef;
    }
    memcpy(current_coef->coef, data, linear_form->type_info->size);

    return LINEAR_FORM_OPERATION_OK;
}

LinearFormErrors addLinearForm(const LinearForm* lf1, const LinearForm* lf2, LinearForm* result, int subtraction){
    if (lf1 == NULL || lf2 == NULL || result == NULL) return LINEAR_FORM_NOT_DEFINED;
    if (lf1->type_info != lf2->type_info || lf1->type_info != result->type_info) return INCOMPATIBLE_LINEAR_FORM_TYPES;
    if (lf1->type_info->add == NULL) return OPERATION_NOT_DEFINED;
    if (lf1->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;
    if (!((result->quantity == lf1->quantity && lf1->quantity >= lf2->quantity) || (result->quantity == lf2->quantity && lf2->quantity >= lf1->quantity))) return RESULT_LENGTH_IS_INCORRECT;

    int x = -1;
    int* minus = &x;
    if (lf1->quantity >= lf2->quantity) {
        Coef* lf1_current_coef = lf1->first_coef;
        Coef* lf2_current_coef = lf2->first_coef;
        Coef* res_current_coef = result->first_coef;
        for (int i = 0; i < lf2->quantity; i++){
            lf1->type_info->add(lf1_current_coef->coef, lf2_current_coef->coef, res_current_coef->coef, subtraction);

            lf1_current_coef = lf1_current_coef->next_coef;
            lf2_current_coef = lf2_current_coef->next_coef;
            res_current_coef = res_current_coef->next_coef;
        }
        for (int i = 0; i < lf1->quantity - lf2->quantity; i++){
            memcpy(res_current_coef->coef, lf1_current_coef->coef, lf1->type_info->size);

            lf1_current_coef = lf1_current_coef->next_coef;
            res_current_coef = res_current_coef->next_coef;
        }
    }
    else {
        Coef* lf1_current_coef = lf1->first_coef;
        Coef* lf2_current_coef = lf2->first_coef;
        Coef* res_current_coef = result->first_coef;

        for (int i = 0; i < lf1->quantity; i++){
            lf1->type_info->add(lf1_current_coef->coef, lf2_current_coef->coef, res_current_coef->coef, subtraction);

            lf1_current_coef = lf1_current_coef->next_coef;
            lf2_current_coef = lf2_current_coef->next_coef;
            res_current_coef = res_current_coef->next_coef;
        }
        for (int i = 0; i < lf2->quantity - lf1->quantity; i++){
            if (subtraction == 0) memcpy(res_current_coef->coef, lf2_current_coef->coef, lf2->type_info->size);
            else {
                memcpy(res_current_coef->coef, lf2_current_coef->coef, lf2->type_info->size);
                lf1->type_info->multiply(res_current_coef->coef, minus, res_current_coef->coef);
            }

            lf2_current_coef = lf2_current_coef->next_coef;
            res_current_coef = res_current_coef->next_coef;
        }
    }

    return LINEAR_FORM_OPERATION_OK;
}

LinearFormErrors multiplyLinearForm(LinearForm* linear_form, const void* multiplier){
    if (linear_form == NULL) return LINEAR_FORM_NOT_DEFINED;
    if (linear_form->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;

    Coef* lf_current_coef = linear_form->first_coef;

    for (int i = 0; i < linear_form->quantity; i++){
        linear_form->type_info->multiply(lf_current_coef->coef, multiplier, lf_current_coef->coef);

        lf_current_coef = lf_current_coef->next_coef;
    }

    return LINEAR_FORM_OPERATION_OK;
}

LinearFormErrors countLinearForm(const LinearForm* linear_form, void* result){
    if (linear_form == NULL) return LINEAR_FORM_NOT_DEFINED;
    if (linear_form->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;
    if (linear_form->type_info->add == NULL) return OPERATION_NOT_DEFINED;

    void* res_cur = malloc(linear_form->type_info->size);
    void* res_next = malloc(linear_form->type_info->size);
    void* x = malloc(linear_form->type_info->size);
    void* elem = malloc(linear_form->type_info->size);
    if (res_cur == NULL || res_next == NULL || x == NULL || elem == NULL) return MEMORY_ALLOCATION_FAILED;

    if (linear_form->first_coef != NULL) {
        Coef* lf_current_coef = linear_form->first_coef;
        printf("Input %d variable: ", 1);
        linear_form->type_info->input(x);
        linear_form->type_info->multiply(linear_form->first_coef->coef, x, res_cur);
        lf_current_coef = lf_current_coef->next_coef;

        for (int i = 0; i < linear_form->quantity-1; i++) {
            printf("Input %d variable: ", i + 2);
            linear_form->type_info->input(x);
            linear_form->type_info->multiply(lf_current_coef->coef, x, elem);
            linear_form->type_info->add(res_cur, elem, res_next, 0);
            memcpy(res_cur, res_next, linear_form->type_info->size);

            lf_current_coef = lf_current_coef->next_coef;
        }
        memcpy(result, res_cur, linear_form->type_info->size);
    }
    else {
        linear_form->type_info->getZero(result);
    }

    free(res_cur); free(res_next); free(x); free(elem);
    return LINEAR_FORM_OPERATION_OK;
}

LinearFormErrors printLinearForm(const LinearForm* linear_form){
    if (linear_form == NULL) return LINEAR_FORM_NOT_DEFINED;
    if (linear_form->type_info->print == NULL) return OPERATION_NOT_DEFINED;

    if (linear_form->first_coef != NULL) {
        printf("Linear form: F= ");
        Coef* lf_current_coef = linear_form->first_coef;
        linear_form->type_info->print(lf_current_coef->coef);
        lf_current_coef = lf_current_coef->next_coef;
        for (int i = 1; i < linear_form->quantity; i++){
            printf(" ");
            linear_form->type_info->print(lf_current_coef->coef);
            printf("*X%d", i);
            lf_current_coef = lf_current_coef->next_coef;
        }
        printf("\n");
    }
    else {
        printf("Linear form is empty\n");
    }

    return LINEAR_FORM_OPERATION_OK;
}