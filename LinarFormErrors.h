#ifndef LINAR_FORM_ERRORS_H
#define LINAR_FORM_ERRORS_H

typedef enum {
    LINARFORM_OPERATION_OK = 0,
    MEMORY_ALLOCATION_FAILED = 100,
    INCOMPATIBLE_LINARFORM_TYPES = 200,
    LINARFORM_NOT_DEFINED = 301,
    OPERATION_NOT_DEFINED = 302,
    RESULT_NOT_DEFINED = 303,
    NEGATIVE_QUANTITY = 401,
    INDEX_OUT_OF_BOUNDS = 402,
    RESULT_LENGHT_IS_INCORRECT = 403
} LinarFormErrors;

#endif