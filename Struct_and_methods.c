#include <Struct_and_methods.h>

LinarForm* CreateLinarForm(TypeInfo* type_info, int quantity, LinarFormErrors* operation_result) {
    LinarForm* linar_form = (LinarForm*)malloc(sizeof(LinarForm));
    if (linar_form == NULL) {
        *operation_result = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    linar_form->type_info = type_info;
    linar_form->quantity = quantity;
    linar_form->first_coef = NULL;

    if (quantity != 0){
        linar_form->first_coef = (Coef*)malloc(sizeof(Coef));
        
        Coef* previous_coef = linar_form->first_coef;
        linar_form->first_coef->coef = malloc(sizeof(type_info->size));
        linar_form->type_info->input(linar_form->first_coef->coef);
        linar_form->first_coef->next_coef = NULL;

        for (int i = 0; i < quantity-1; i++) {
            Coef* arg_i = (Coef*)malloc(sizeof(Coef));
            if (arg_i == NULL) {
                *operation_result = MEMORY_ALLOCATION_FAILED;
                return NULL;
            }

            arg_i->coef = malloc(sizeof(type_info->size));
            linar_form->type_info->input(arg_i->coef);
            arg_i->next_coef = NULL;
            previous_coef->next_coef = arg_i;
            previous_coef = arg_i;
        }
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
            free(previous_coef);
        }
        free(coef);
    }
    free(linar_form);
}

LinarFormErrors addLinarForm(const LinarForm* lf1, const LinarForm* lf2, LinarForm* result){
    if (lf1 == NULL || lf2 == NULL || result == NULL) return LINARFORM_NOT_DEFINED;
    if (lf1->type_info != lf2->type_info || lf1->type_info != result->type_info) return INCOMPATIBLE_LINARFORM_TYPES;
    if (lf1->type_info->add == NULL) return OPERATION_NOT_DEFINED;

    if (lf1->quantity >= lf2->quantity) {
        Coef* lf1_current_coef = lf1->first_coef;
        Coef* lf2_current_coef = lf2->first_coef;
        Coef* res_current_coef = result->first_coef;

        for (int i = 0; i < lf2->quantity; i++){
            lf1->type_info->add(lf1_current_coef->coef, lf2_current_coef->coef, res_current_coef->coef);

            lf1_current_coef = lf1_current_coef->next_coef;
            lf2_current_coef = lf2_current_coef->next_coef;
            res_current_coef = res_current_coef->next_coef;
        }
    }
    else {
        Coef* lf1_current_coef = lf1->first_coef;
        Coef* lf2_current_coef = lf2->first_coef;
        Coef* res_current_coef = result->first_coef;

        for (int i = 0; i < lf1->quantity; i++){
            lf1->type_info->add(lf1_current_coef->coef, lf2_current_coef->coef, res_current_coef->coef);

            lf1_current_coef = lf1_current_coef->next_coef;
            lf2_current_coef = lf2_current_coef->next_coef;
            res_current_coef = res_current_coef->next_coef;
        }
    }

    return LINARFORM_OPERATION_OK;
}

LinarFormErrors multiplyLinarForm(const LinarForm* linar_form, const void* multiplier, LinarForm* result){
    if (linar_form == NULL || result == NULL) return LINARFORM_NOT_DEFINED;
    if (linar_form->type_info != result->type_info) return INCOMPATIBLE_LINARFORM_TYPES;
    if (linar_form->type_info->multiply == NULL) return OPERATION_NOT_DEFINED;

    Coef* lf_current_coef = linar_form->first_coef;
    Coef* res_current_coef = result->first_coef;

    for (int i = 0; i < linar_form->quantity; i++){
        linar_form->type_info->multiply(lf_current_coef->coef, multiplier, res_current_coef->coef);

        lf_current_coef = lf_current_coef->next_coef;
        res_current_coef = res_current_coef->next_coef;
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
            linar_form->type_info->add(res, elem, res);

            lf_current_coef = lf_current_coef->next_coef;
        }

        result = res;
    }

    return LINARFORM_OPERATION_OK;
}

LinarFormErrors printLinarForm(const LinarForm* linar_form){
    if (linar_form == NULL) return LINARFORM_NOT_DEFINED;
    if (linar_form->type_info->print == NULL) return OPERATION_NOT_DEFINED;

    printf("Linar form: F=");
    if (linar_form->first_coef != NULL) {
        Coef* lf_current_coef = linar_form->first_coef;
        linar_form->type_info->print(lf_current_coef->coef);
        lf_current_coef = lf_current_coef->next_coef;
        for (int i = 1; i < linar_form->quantity; i++){
            linar_form->type_info->print(lf_current_coef->coef);
            printf("x%d ", i);
        }
    }
    else {
        printf(" Linar form is empty");
    }

    return LINARFORM_OPERATION_OK;
}