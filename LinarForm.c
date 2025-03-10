#include <LinarForm.h>

LinarForm* CreateLinarForm(TypeInfo* type_info, int quantity, LinarFormErrors* operation_result) {
    LinarForm* linar_form = (LinarForm*)malloc(sizeof(LinarForm));
    if (linar_form == NULL) {
        *operation_result = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    linar_form->type_info = type_info;
    linar_form->quantity = quantity;
    linar_form->first_coef = NULL;

    if (quantity > 0){
        linar_form->first_coef = (Coef*)malloc(sizeof(Coef));
        
        Coef* previous_coef = linar_form->first_coef;
        linar_form->first_coef->coef = malloc(sizeof(type_info->size));
        linar_form->first_coef->next_coef = NULL;

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
        free(linar_form);
        return NULL;
    }

    *operation_result = LINARFORM_OPERATION_OK;
    return linar_form;
}

void freeLinarForm(LinarForm* linar_form) {
    if (linar_form->first_coef != NULL) {
        Coef* coef = linar_form->first_coef;
        Coef* previous_coef = NULL;
        while (coef->next_coef != NULL) {
            previous_coef = coef;
            coef = coef->next_coef;
            free(previous_coef->coef);
            free(previous_coef);
        }
        free(coef);
    }
    free(linar_form);
}

LinarFormErrors InputLinarForm(LinarForm* linar_form){
    if (linar_form == NULL) return LINARFORM_NOT_DEFINED;
    if (linar_form->type_info->input == NULL) return OPERATION_NOT_DEFINED;

    Coef* current_coef = linar_form->first_coef;
    for (int i = 0; i < linar_form->quantity; i++) {
        printf("Input %d coefficient: ", i);
        linar_form->type_info->input(current_coef->coef);
        current_coef = current_coef->next_coef;
    }
    return LINARFORM_OPERATION_OK;
}

LinarFormErrors ReplaceLinarForm(LinarForm* linar_form, const void* index, const void* data){
    if (linar_form == NULL) return LINARFORM_NOT_DEFINED;
    if (index >= linar_form->quantity || index < 0) return INDEX_OUT_OF_BOUNDS;

    Coef* current_coef = linar_form->first_coef;
    for (int i = 0; i < index; i++) {
        current_coef = current_coef->next_coef;
    }
    current_coef->coef = data;

    return LINARFORM_OPERATION_OK;
}

LinarFormErrors addLinarForm(const LinarForm* lf1, const LinarForm* lf2, LinarForm* result, int subtraction){
    if (lf1 == NULL || lf2 == NULL || result == NULL) return LINARFORM_NOT_DEFINED;
    if (lf1->type_info != lf2->type_info || lf1->type_info != result->type_info) return INCOMPATIBLE_LINARFORM_TYPES;
    if (lf1->type_info->add == NULL) return OPERATION_NOT_DEFINED;
    if (lf1->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;
    if (!((result->quantity == lf1->quantity && lf1->quantity >= lf2->quantity) || (result->quantity == lf2->quantity && lf2->quantity >= lf1->quantity))) return RESULT_LENGHT_IS_INCORRECT;

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
        int x = -1;
        int* minus = &x;
        for (int i = 0; i < lf2->quantity - lf1->quantity; i++){
            if (subtraction == 0) memcpy(res_current_coef->coef, lf2_current_coef->coef, lf1->type_info->size);
            else {
                memcpy(res_current_coef->coef, lf2_current_coef->coef, lf1->type_info->size);
                lf1->type_info->multiply(res_current_coef->coef, minus, res_current_coef->coef);
            }

            lf2_current_coef = lf2_current_coef->next_coef;
            res_current_coef = res_current_coef->next_coef;
        }
    }

    return LINARFORM_OPERATION_OK;
}

LinarFormErrors multiplyLinarForm(LinarForm* linar_form, const void* multiplier){
    if (linar_form == NULL) return LINARFORM_NOT_DEFINED;
    if (linar_form->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;

    Coef* lf_current_coef = linar_form->first_coef;

    for (int i = 0; i < linar_form->quantity; i++){
        linar_form->type_info->multiply(lf_current_coef->coef, multiplier, lf_current_coef->coef);

        lf_current_coef = lf_current_coef->next_coef;
    }

    return LINARFORM_OPERATION_OK;
}

LinarFormErrors countLinarForm(const LinarForm* linar_form, void* result){
    if (linar_form == NULL) return LINARFORM_NOT_DEFINED;
    if (result == NULL) return RESULT_NOT_DEFINED;
    if (linar_form->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;
    if (linar_form->type_info->add == NULL) return OPERATION_NOT_DEFINED;

    void* res = malloc(linar_form->type_info->size);
    void* x = malloc(linar_form->type_info->size);
    void* elem = malloc(linar_form->type_info->size);
    if (res == NULL || x == NULL || elem == NULL) return MEMORY_ALLOCATION_FAILED;

    if (linar_form->first_coef != NULL) {
        Coef* lf_current_coef = linar_form->first_coef;
        linar_form->type_info->input(x);
        linar_form->type_info->multiply(linar_form->first_coef->coef, x, res);
        lf_current_coef = lf_current_coef->next_coef;

        for (int i = 0; i < linar_form->quantity-1; i++) {
            linar_form->type_info->input(x);
            linar_form->type_info->multiply(lf_current_coef->coef, x, elem);
            linar_form->type_info->add(res, elem, res, 0);

            lf_current_coef = lf_current_coef->next_coef;
        }

        result = res;
    }
    else result = NULL;

    return LINARFORM_OPERATION_OK;
}

LinarFormErrors printLinarForm(const LinarForm* linar_form){
    if (linar_form == NULL) return LINARFORM_NOT_DEFINED;
    if (linar_form->type_info->print == NULL) return OPERATION_NOT_DEFINED;

    if (linar_form->first_coef != NULL) {
        printf("Linar form: F= ");
        Coef* lf_current_coef = linar_form->first_coef;
        linar_form->type_info->print(lf_current_coef->coef);
        lf_current_coef = lf_current_coef->next_coef;
        for (int i = 1; i < linar_form->quantity; i++){
            printf(" ");
            linar_form->type_info->print(lf_current_coef->coef);
            printf("*X%d", i);
        }
    }
    else {
        printf("Linar form is empty");
    }

    return LINARFORM_OPERATION_OK;
}