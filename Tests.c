#include "Tests.h"

void TestResultPrint(const int* result_of_test, const int* test_group_number, const int* test_number){
    switch (*result_of_test)
    {
    case 0:
        printf("Test %d.%d passed [O]\n", *test_group_number, *test_number);
        break;
    case 1:
        printf("Test %d.%d failed [X]\n", *test_group_number, *test_number);
        break;
    default:
        printf("Result of test %d.%d uncorrect\n", *test_group_number, *test_number);
        break;
    }
}

void TestCreateLinearForm(){
    int test_group_number = 1;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf1 = CreateLinearForm(GetIntTypeInfo(), 10, &operation_result);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    if (lf1 == NULL) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf1);

    result_of_test = 0; //TEST 2
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf2 = CreateLinearForm(GetIntTypeInfo(), 10, &operation_result);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    if (lf2 == NULL) result_of_test = 1;
    Coef* current_coef = lf2->first_coef;
    int count = 0;
    if (current_coef != NULL) count++;
    while (current_coef->next_coef != NULL) {
        count++;
        current_coef = current_coef->next_coef;
    }
    if (count != 10) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf2);

    result_of_test = 0; //TEST 3
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf3 = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    if (lf3 == NULL) result_of_test = 1;
    if (lf3->first_coef != NULL) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf3);

    result_of_test = 0; //TEST 4
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf4 = CreateLinearForm(GetIntTypeInfo(), -1, &operation_result);
    if (operation_result != NEGATIVE_QUANTITY) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf4);

    result_of_test = 0; //TEST 5
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf5 = CreateLinearForm(GetIntTypeInfo(), 1273, &operation_result);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    if (lf5 == NULL) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf5);

    result_of_test = 0; //TEST 6
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf6 = CreateLinearForm(GetIntTypeInfo(), 1273, &operation_result);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    if (lf6 == NULL) result_of_test = 1;
    current_coef = lf6->first_coef;
    count = 0;
    if (current_coef != NULL) count++;
    while (current_coef->next_coef != NULL) {
        count++;
        current_coef = current_coef->next_coef;
    }
    if (count != 1273) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf6);
}

void TestInputLinearForm(){
    int test_group_number = 2;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf1 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    printf("Input numbers 1, 2, 3\n");
    operation_result = InputLinearForm(lf1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1->first_coef;
    for (int i = 1; i < 4; i++) {
        if (*(int*)current_coef->coef != i) result_of_test = 1;
        current_coef = current_coef->next_coef;
    }
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf1);

    result_of_test = 0; //TEST 2
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf2 = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    printf("Do not enter anything\n");
    operation_result = InputLinearForm(lf2);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf2);

    result_of_test = 0; //TEST 3
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf3 = NULL;
    operation_result = InputLinearForm(lf3);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf3);
}

void TestReplaceLinearForm(){
    int test_group_number = 3;
    int test_number = 1;
    int result_of_test = 0;
    int i1 = 0, i2 = 1, i3 = 2, i4 = -1, i5 = 3, i6 = 7;
    int x1 = 1, x2 = 2, x3 = 3;
    
    result_of_test = 0; //TEST 1
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf1 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = ReplaceLinearForm(lf1, &i1, &x1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    operation_result = ReplaceLinearForm(lf1, &i2, &x2);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    operation_result = ReplaceLinearForm(lf1, &i3, &x3);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1->first_coef;
    for (int i = 1; i < 4; i++) {
        if (*(int*)current_coef->coef != i) result_of_test = 1;
        current_coef = current_coef->next_coef;
    }
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf1);

    result_of_test = 0; //TEST 2
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf2 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = ReplaceLinearForm(lf2, &i4, &x1);
    if (operation_result != INDEX_OUT_OF_BOUNDS) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf2);

    result_of_test = 0; //TEST 3
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf3 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = ReplaceLinearForm(lf3, &i5, &x1);
    if (operation_result != INDEX_OUT_OF_BOUNDS) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf3);

    result_of_test = 0; //TEST 4
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf4 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = ReplaceLinearForm(lf4, &i6, &x1);
    if (operation_result != INDEX_OUT_OF_BOUNDS) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf4);

    result_of_test = 0; //TEST 5
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf5 = NULL;
    InputLinearForm(lf5);
    operation_result = ReplaceLinearForm(lf5, &i1, &x1);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf5);
}

void TestAddLinearForm(){
    int test_group_number = 4;
    int test_number = 1;
    int result_of_test = 0;
    int i1 = 0, i2 = 1, i3 = 2;
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4;

    result_of_test = 0; //TEST 1
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf11 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf11, &i1, &x1);
    ReplaceLinearForm(lf11, &i2, &x2);
    ReplaceLinearForm(lf11, &i3, &x3);
    LinearForm* lf12 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf12, &i1, &x2);
    ReplaceLinearForm(lf12, &i2, &x3);
    ReplaceLinearForm(lf12, &i3, &x4);
    LinearForm* lf1r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf11, lf12, lf1r, 0);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1r->first_coef;
    if (*(int*)current_coef->coef != 3) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 5) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 7) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf11); freeLinearForm(lf12); freeLinearForm(lf1r);

    result_of_test = 0; //TEST 2
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf21 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf21, &i1, &x1);
    ReplaceLinearForm(lf21, &i2, &x2);
    ReplaceLinearForm(lf21, &i3, &x4);
    LinearForm* lf22 = CreateLinearForm(GetIntTypeInfo(), 2, &operation_result);
    ReplaceLinearForm(lf22, &i1, &x2);
    ReplaceLinearForm(lf22, &i2, &x3);
    LinearForm* lf2r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf21, lf22, lf2r, 0);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf2r->first_coef;
    if (*(int*)current_coef->coef != 3) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 5) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf21); freeLinearForm(lf22); freeLinearForm(lf2r);

    result_of_test = 0; //TEST 3
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf31 = CreateLinearForm(GetIntTypeInfo(), 2, &operation_result);
    ReplaceLinearForm(lf31, &i1, &x1);
    ReplaceLinearForm(lf31, &i2, &x2);
    LinearForm* lf32 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf32, &i1, &x2);
    ReplaceLinearForm(lf32, &i2, &x3);
    ReplaceLinearForm(lf32, &i3, &x4);
    LinearForm* lf3r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf31, lf32, lf3r, 0);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf3r->first_coef;
    if (*(int*)current_coef->coef != 3) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 5) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf31); freeLinearForm(lf32); freeLinearForm(lf3r);

    result_of_test = 0; //TEST 4
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf41 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf41, &i1, &x1);
    ReplaceLinearForm(lf41, &i2, &x2);
    ReplaceLinearForm(lf41, &i3, &x3);
    LinearForm* lf42 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf42, &i1, &x2);
    ReplaceLinearForm(lf42, &i2, &x3);
    ReplaceLinearForm(lf42, &i3, &x4);
    LinearForm* lf4r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf41, lf42, lf4r, 1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf4r->first_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf41); freeLinearForm(lf42); freeLinearForm(lf4r);

    result_of_test = 0; //TEST 5
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf51 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf51, &i1, &x1);
    ReplaceLinearForm(lf51, &i2, &x2);
    ReplaceLinearForm(lf51, &i3, &x4);
    LinearForm* lf52 = CreateLinearForm(GetIntTypeInfo(), 2, &operation_result);
    ReplaceLinearForm(lf52, &i1, &x2);
    ReplaceLinearForm(lf52, &i2, &x3);
    LinearForm* lf5r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf51, lf52, lf5r, 1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf5r->first_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf51); freeLinearForm(lf52); freeLinearForm(lf5r);

    result_of_test = 0; //TEST 6
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf61 = CreateLinearForm(GetIntTypeInfo(), 2, &operation_result);
    ReplaceLinearForm(lf61, &i1, &x1);
    ReplaceLinearForm(lf61, &i2, &x2);
    LinearForm* lf62 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf62, &i1, &x2);
    ReplaceLinearForm(lf62, &i2, &x3);
    ReplaceLinearForm(lf62, &i3, &x4);
    LinearForm* lf6r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf61, lf62, lf6r, 1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf6r->first_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf61); freeLinearForm(lf62); freeLinearForm(lf6r);

    result_of_test = 0; //TEST 7
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf71 = NULL;
    LinearForm* lf72 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf7r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf71, lf72, lf7r, 0);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf71); freeLinearForm(lf72); freeLinearForm(lf7r);
    
    result_of_test = 0; //TEST 8
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf81 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf82 = NULL;
    LinearForm* lf8r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf81, lf82, lf8r, 0);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf81); freeLinearForm(lf82); freeLinearForm(lf8r);

    result_of_test = 0; //TEST 9
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf91 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf92 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf9r = NULL;
    operation_result = addLinearForm(lf91, lf92, lf9r, 0);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf91); freeLinearForm(lf92); freeLinearForm(lf9r);

    result_of_test = 0; //TEST 10
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf101 = CreateLinearForm(GetDoubleTypeInfo(), 3, &operation_result);
    LinearForm* lf102 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf10r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf101, lf102, lf10r, 0);
    if (operation_result != INCOMPATIBLE_LINEAR_FORM_TYPES) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf101); freeLinearForm(lf102); freeLinearForm(lf10r);

    result_of_test = 0; //TEST 11
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf111 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf112 = CreateLinearForm(GetDoubleTypeInfo(), 3, &operation_result);
    LinearForm* lf11r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf111, lf112, lf11r, 0);
    if (operation_result != INCOMPATIBLE_LINEAR_FORM_TYPES) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf111); freeLinearForm(lf112); freeLinearForm(lf11r);

    result_of_test = 0; //TEST 12
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf121 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf122 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf12r = CreateLinearForm(GetDoubleTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf121, lf122, lf12r, 0);
    if (operation_result != INCOMPATIBLE_LINEAR_FORM_TYPES) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf121); freeLinearForm(lf122); freeLinearForm(lf12r);

    result_of_test = 0; //TEST 13
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf131 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf132 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf13r = CreateLinearForm(GetIntTypeInfo(), 4, &operation_result);
    operation_result = addLinearForm(lf131, lf132, lf13r, 0);
    if (operation_result != RESULT_LENGTH_IS_INCORRECT) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf131); freeLinearForm(lf132); freeLinearForm(lf13r);

    result_of_test = 0; //TEST 14
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf141 = CreateLinearForm(GetIntTypeInfo(), 4, &operation_result);
    LinearForm* lf142 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf14r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf141, lf142, lf14r, 0);
    if (operation_result != RESULT_LENGTH_IS_INCORRECT) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf141); freeLinearForm(lf142); freeLinearForm(lf14r);

    result_of_test = 0; //TEST 15
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf151 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    LinearForm* lf152 = CreateLinearForm(GetIntTypeInfo(), 4, &operation_result);
    LinearForm* lf15r = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    operation_result = addLinearForm(lf151, lf152, lf15r, 0);
    if (operation_result != RESULT_LENGTH_IS_INCORRECT) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf151); freeLinearForm(lf152); freeLinearForm(lf15r);

    result_of_test = 0; //TEST 16
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf161 = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    LinearForm* lf162 = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    LinearForm* lf16r = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    operation_result = addLinearForm(lf161, lf162, lf16r, 0);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf161); freeLinearForm(lf162); freeLinearForm(lf16r);
}

void TestMultiplyLinearForm(){
    int test_group_number = 5;
    int test_number = 1;
    int result_of_test = 0;
    int i1 = 0, i2 = 1, i3 = 2;
    int x1 = 1, x2 = 2, x3 = 3;
    int y1 = 2, y2 = -2;

    result_of_test = 0; //TEST 1
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf1 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf1, &i1, &x1);
    ReplaceLinearForm(lf1, &i2, &x2);
    ReplaceLinearForm(lf1, &i3, &x3);
    operation_result = multiplyLinearForm(lf1, &y1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1->first_coef;
    if (*(int*)current_coef->coef != 2) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 6) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf1);

    result_of_test = 0; //TEST 2
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf2 = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    operation_result = multiplyLinearForm(lf2, &y1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf2);

    result_of_test = 0; //TEST 3
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf3 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf3, &i1, &x1);
    ReplaceLinearForm(lf3, &i2, &x2);
    ReplaceLinearForm(lf3, &i3, &x3);
    operation_result = multiplyLinearForm(lf3, &y2);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf3->first_coef;
    if (*(int*)current_coef->coef != -2) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -6) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf3);

    result_of_test = 0; //TEST 4
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf4 = NULL;
    operation_result = multiplyLinearForm(lf4, &y1);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf4);
}

void TestCountLinearForm(){
    int test_group_number = 6;
    int test_number = 1;
    int result_of_test = 0;
    int i1 = 0, i2 = 1, i3 = 2;
    int x1 = 1, x2 = 2, x3 = 3;    

    result_of_test = 0; //TEST 1
    int* res1 = malloc(sizeof(int));
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf1 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf1, &i1, &x1);
    ReplaceLinearForm(lf1, &i2, &x2);
    ReplaceLinearForm(lf1, &i3, &x3);
    printf("Input numbers 1, 2, 3\n");
    operation_result = countLinearForm(lf1, res1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) {result_of_test = 1; printf("%d\n", operation_result);}
    if (*(int*)res1 != 14) {result_of_test = 1; printf("%d\n", *(int*)res1);}
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    free(res1);
    freeLinearForm(lf1);

    result_of_test = 0; //TEST 2
    int* res2 = malloc(sizeof(int));
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf2 = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    printf("Do not enter anything\n");
    operation_result = countLinearForm(lf2, res2);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    if (*(int*)res2 != 0) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    free(res2);
    freeLinearForm(lf2);

    result_of_test = 0; //TEST 3
    int* res3 = malloc(sizeof(int));;
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf3 = NULL;
    printf("Do not enter anything\n");
    operation_result = countLinearForm(lf3, res3);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    free(res3);
    freeLinearForm(lf3);
}

void TestPrintLinearForm(){
    int test_group_number = 7;
    int test_number = 1;
    int result_of_test = 0;
    int i1 = 0, i2 = 1, i3 = 2;
    int x1 = 1, x2 = 2, x3 = 3;
    int y1 = -1, y2 = 0, y3 = -3;

    result_of_test = 0; //TEST 1
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf1 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf1, &i1, &x1);
    ReplaceLinearForm(lf1, &i2, &x2);
    ReplaceLinearForm(lf1, &i3, &x3);
    printf("Expected: 'Linear form: F= +1 +2*X1 +3*X2'\n");
    operation_result = printLinearForm(lf1);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf1);

    result_of_test = 0; //TEST 2
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf2 = CreateLinearForm(GetIntTypeInfo(), 0, &operation_result);
    printf("Expected: 'Linear form is empty'\n");
    operation_result = printLinearForm(lf2);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf2);

    result_of_test = 0; //TEST 3
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf3 = NULL;
    operation_result = printLinearForm(lf3);
    if (operation_result != LINEAR_FORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf3);

    result_of_test = 0; //TEST 4
    operation_result = LINEAR_FORM_OPERATION_OK;
    LinearForm* lf4 = CreateLinearForm(GetIntTypeInfo(), 3, &operation_result);
    ReplaceLinearForm(lf4, &i1, &y1);
    ReplaceLinearForm(lf4, &i2, &y2);
    ReplaceLinearForm(lf4, &i3, &y3);
    printf("Expected: 'Linear form: F= -1 +0*X1 -3*X2'\n");
    operation_result = printLinearForm(lf4);
    if (operation_result != LINEAR_FORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinearForm(lf4);
}

void TestAll(){
    TestCreateLinearForm();
    TestInputLinearForm();
    TestReplaceLinearForm();
    TestAddLinearForm();
    TestMultiplyLinearForm();
    TestCountLinearForm();
    TestPrintLinearForm();
}