#include <Tests.h>

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

void TestCreateLinarForm(){
    int test_group_number = 1;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    LinarFormErrors *operation_result = NULL;
    LinarForm* lf1 = CreateLinarForm(GetIntTypeInfo(), 10, operation_result);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    if (lf1 == NULL) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf1);

    result_of_test = 0; //TEST 2
    *operation_result = NULL;
    LinarForm* lf2 = CreateLinarForm(GetIntTypeInfo(), 10, operation_result);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
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
    freeLinarForm(lf2);

    result_of_test = 0; //TEST 3
    *operation_result = NULL;
    LinarForm* lf3 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    if (lf3 == NULL) result_of_test = 1;
    if (lf3->first_coef != NULL) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf3);

    result_of_test = 0; //TEST 4
    *operation_result = NULL;
    LinarForm* lf4 = CreateLinarForm(GetIntTypeInfo(), -1, operation_result);
    if (*operation_result != NEGATIVE_QUANTITY) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf4);

    result_of_test = 0; //TEST 5
    *operation_result = NULL;
    LinarForm* lf5 = CreateLinarForm(GetIntTypeInfo(), 1273, operation_result);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    if (lf5 == NULL) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf5);

    result_of_test = 0; //TEST 6
    *operation_result = NULL;
    LinarForm* lf6 = CreateLinarForm(GetIntTypeInfo(), 1273, operation_result);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
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
    freeLinarForm(lf6);
}

void TestInputLinarForm(){
    int test_group_number = 2;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    LinarFormErrors *operation_result = NULL;
    LinarForm* lf1 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    printf("Input numbers 1, 2, 3\n");
    *operation_result = InputLinarForm(lf1);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1->first_coef;
    for (int i = 1; i < 4; i++) {
        if (*(int*)current_coef->coef != i) result_of_test = 1;
        current_coef = current_coef->next_coef;
    }
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf1);

    result_of_test = 0; //TEST 2
    *operation_result = NULL;
    LinarForm* lf2 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    printf("Do not enter anything\n");
    *operation_result = InputLinarForm(lf2);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf2);

    result_of_test = 0; //TEST 3
    *operation_result = NULL;
    LinarForm* lf3 = NULL;
    *operation_result = InputLinarForm(lf3);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf3);
}

void TestReplaceLinarForm(){
    int test_group_number = 3;
    int test_number = 1;
    int result_of_test = 0;
    
    result_of_test = 0; //TEST 1
    LinarFormErrors *operation_result = NULL;
    LinarForm* lf1 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = ReplaceLinarForm(lf1, 0, 1);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    *operation_result = ReplaceLinarForm(lf1, 1, 2);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    *operation_result = ReplaceLinarForm(lf1, 2, 3);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1->first_coef;
    for (int i = 1; i < 4; i++) {
        if (*(int*)current_coef->coef != i) result_of_test = 1;
        current_coef = current_coef->next_coef;
    }
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf1);

    result_of_test = 0; //TEST 2
    *operation_result = NULL;
    LinarForm* lf2 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = ReplaceLinarForm(lf2, -1, 1);
    if (*operation_result != INDEX_OUT_OF_BOUNDS) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf2);

    result_of_test = 0; //TEST 3
    *operation_result = NULL;
    LinarForm* lf3 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = ReplaceLinarForm(lf3, 3, 1);
    if (*operation_result != INDEX_OUT_OF_BOUNDS) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf3);

    result_of_test = 0; //TEST 4
    *operation_result = NULL;
    LinarForm* lf4 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = ReplaceLinarForm(lf4, 7, 1);
    if (*operation_result != INDEX_OUT_OF_BOUNDS) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf4);

    result_of_test = 0; //TEST 5
    *operation_result = NULL;
    LinarForm* lf5 = NULL;
    InputLinarForm(lf5);
    *operation_result = ReplaceLinarForm(lf5, 0, 1);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf5);
}

void TestAddLinarForm(){
    int test_group_number = 4;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    LinarFormErrors *operation_result = NULL;
    LinarForm* lf11 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf11, 0, 1);
    ReplaceLinarForm(lf11, 1, 2);
    ReplaceLinarForm(lf11, 2, 3);
    LinarForm* lf12 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf12, 0, 2);
    ReplaceLinarForm(lf12, 1, 3);
    ReplaceLinarForm(lf12, 2, 4);
    LinarForm* lf1r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf11, lf12, lf1r, 0);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1r->first_coef;
    if (*(int*)current_coef->coef != 3) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 5) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 7) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf11); freeLinarForm(lf12); freeLinarForm(lf1r);

    result_of_test = 0; //TEST 2
    *operation_result = NULL;
    LinarForm* lf21 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf21, 0, 1);
    ReplaceLinarForm(lf21, 1, 2);
    ReplaceLinarForm(lf21, 2, 4);
    LinarForm* lf22 = CreateLinarForm(GetIntTypeInfo(), 2, operation_result);
    ReplaceLinarForm(lf22, 0, 2);
    ReplaceLinarForm(lf22, 1, 3);
    LinarForm* lf2r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf21, lf22, lf2r, 0);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf2r->first_coef;
    if (*(int*)current_coef->coef != 3) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 5) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf21); freeLinarForm(lf22); freeLinarForm(lf2r);

    result_of_test = 0; //TEST 3
    *operation_result = NULL;
    LinarForm* lf31 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf31, 0, 1);
    ReplaceLinarForm(lf31, 1, 2);
    LinarForm* lf32 = CreateLinarForm(GetIntTypeInfo(), 2, operation_result);
    ReplaceLinarForm(lf32, 0, 2);
    ReplaceLinarForm(lf32, 1, 3);
    ReplaceLinarForm(lf32, 2, 4);
    LinarForm* lf3r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf31, lf32, lf3r, 0);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf3r->first_coef;
    if (*(int*)current_coef->coef != 3) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 5) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf31); freeLinarForm(lf32); freeLinarForm(lf3r);

    result_of_test = 0; //TEST 4
    *operation_result = NULL;
    LinarForm* lf41 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf41, 0, 1);
    ReplaceLinarForm(lf41, 1, 2);
    ReplaceLinarForm(lf41, 2, 3);
    LinarForm* lf42 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf42, 0, 2);
    ReplaceLinarForm(lf42, 1, 3);
    ReplaceLinarForm(lf42, 2, 4);
    LinarForm* lf4r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf41, lf42, lf4r, 1);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf4r->first_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf41); freeLinarForm(lf42); freeLinarForm(lf4r);

    result_of_test = 0; //TEST 5
    *operation_result = NULL;
    LinarForm* lf51 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf51, 0, 1);
    ReplaceLinarForm(lf51, 1, 2);
    ReplaceLinarForm(lf51, 2, 4);
    LinarForm* lf52 = CreateLinarForm(GetIntTypeInfo(), 2, operation_result);
    ReplaceLinarForm(lf52, 0, 2);
    ReplaceLinarForm(lf52, 1, 3);
    LinarForm* lf5r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf51, lf52, lf5r, 1);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf5r->first_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf51); freeLinarForm(lf52); freeLinarForm(lf5r);

    result_of_test = 0; //TEST 6
    *operation_result = NULL;
    LinarForm* lf61 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf61, 0, 1);
    ReplaceLinarForm(lf61, 1, 2);
    LinarForm* lf62 = CreateLinarForm(GetIntTypeInfo(), 2, operation_result);
    ReplaceLinarForm(lf62, 0, 2);
    ReplaceLinarForm(lf62, 1, 3);
    ReplaceLinarForm(lf62, 2, 4);
    LinarForm* lf6r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf61, lf62, lf6r, 1);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf6r->first_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -1) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf61); freeLinarForm(lf62); freeLinarForm(lf6r);

    result_of_test = 0; //TEST 7
    *operation_result = NULL;
    LinarForm* lf71 = NULL;
    LinarForm* lf72 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf7r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf71, lf72, lf7r, 0);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf71); freeLinarForm(lf72); freeLinarForm(lf7r);
    
    result_of_test = 0; //TEST 8
    *operation_result = NULL;
    LinarForm* lf81 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf82 = NULL;
    LinarForm* lf8r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf81, lf82, lf8r, 0);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf81); freeLinarForm(lf82); freeLinarForm(lf8r);

    result_of_test = 0; //TEST 9
    *operation_result = NULL;
    LinarForm* lf91 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf92 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf9r = NULL;
    *operation_result = addLinarForm(lf91, lf92, lf9r, 0);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf91); freeLinarForm(lf92); freeLinarForm(lf9r);

    result_of_test = 0; //TEST 10
    *operation_result = NULL;
    LinarForm* lf101 = CreateLinarForm(GetDoubleTypeInfo(), 3, operation_result);
    LinarForm* lf102 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf10r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf101, lf102, lf10r, 0);
    if (*operation_result != INCOMPATIBLE_LINARFORM_TYPES) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf101); freeLinarForm(lf102); freeLinarForm(lf10r);

    result_of_test = 0; //TEST 11
    *operation_result = NULL;
    LinarForm* lf111 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf112 = CreateLinarForm(GetDoubleTypeInfo(), 3, operation_result);
    LinarForm* lf11r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf111, lf112, lf11r, 0);
    if (*operation_result != INCOMPATIBLE_LINARFORM_TYPES) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf111); freeLinarForm(lf112); freeLinarForm(lf11r);

    result_of_test = 0; //TEST 12
    *operation_result = NULL;
    LinarForm* lf121 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf122 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf12r = CreateLinarForm(GetDoubleTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf121, lf122, lf12r, 0);
    if (*operation_result != INCOMPATIBLE_LINARFORM_TYPES) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf121); freeLinarForm(lf122); freeLinarForm(lf12r);

    result_of_test = 0; //TEST 13
    *operation_result = NULL;
    LinarForm* lf131 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf132 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf13r = CreateLinarForm(GetIntTypeInfo(), 4, operation_result);
    *operation_result = addLinarForm(lf131, lf132, lf13r, 0);
    if (*operation_result != RESULT_LENGHT_IS_INCORRECT) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf131); freeLinarForm(lf132); freeLinarForm(lf13r);

    result_of_test = 0; //TEST 14
    *operation_result = NULL;
    LinarForm* lf141 = CreateLinarForm(GetIntTypeInfo(), 4, operation_result);
    LinarForm* lf142 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf14r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf141, lf142, lf14r, 0);
    if (*operation_result != RESULT_LENGHT_IS_INCORRECT) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf141); freeLinarForm(lf142); freeLinarForm(lf14r);

    result_of_test = 0; //TEST 15
    *operation_result = NULL;
    LinarForm* lf151 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    LinarForm* lf152 = CreateLinarForm(GetIntTypeInfo(), 4, operation_result);
    LinarForm* lf15r = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    *operation_result = addLinarForm(lf151, lf152, lf15r, 0);
    if (*operation_result != RESULT_LENGHT_IS_INCORRECT) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf151); freeLinarForm(lf152); freeLinarForm(lf15r);

    result_of_test = 0; //TEST 16
    *operation_result = NULL;
    LinarForm* lf161 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    LinarForm* lf162 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    LinarForm* lf16r = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    *operation_result = addLinarForm(lf161, lf162, lf16r, 0);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf161); freeLinarForm(lf162); freeLinarForm(lf16r);
}

void TestMultiplyLinarForm(){
    int test_group_number = 5;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    LinarFormErrors *operation_result = NULL;
    LinarForm* lf1 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf1, 0, 1);
    ReplaceLinarForm(lf1, 1, 2);
    ReplaceLinarForm(lf1, 2, 3);
    *operation_result = multiplyLinarForm(lf1, 2);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    Coef* current_coef = lf1->first_coef;
    if (*(int*)current_coef->coef != 2) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != 6) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf1);

    result_of_test = 0; //TEST 2
    *operation_result = NULL;
    LinarForm* lf2 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    *operation_result = multiplyLinarForm(lf2, 2);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf2);

    result_of_test = 0; //TEST 3
    *operation_result = NULL;
    LinarForm* lf3 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf3, 0, 1);
    ReplaceLinarForm(lf3, 1, 2);
    ReplaceLinarForm(lf3, 2, 3);
    *operation_result = multiplyLinarForm(lf3, -2);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    current_coef = lf3->first_coef;
    if (*(int*)current_coef->coef != -2) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -4) result_of_test = 1;
    current_coef = current_coef->next_coef;
    if (*(int*)current_coef->coef != -6) result_of_test = 1;
    current_coef = current_coef->next_coef;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf3);

    result_of_test = 0; //TEST 4
    *operation_result = NULL;
    LinarForm* lf4 = NULL;
    *operation_result = multiplyLinarForm(lf4, 2);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf4);
}

void TestCountLinarForm(){
    int test_group_number = 6;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    int* res1;
    LinarFormErrors *operation_result = NULL;
    LinarForm* lf1 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf1, 0, 1);
    ReplaceLinarForm(lf1, 1, 2);
    ReplaceLinarForm(lf1, 2, 3);
    printf("Input numbers 1, 2, 3\n");
    *operation_result = countLinarForm(lf1, res1);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    if (*(int*)res1 != 14) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf1);

    result_of_test = 0; //TEST 2
    int* res2;
    *operation_result = NULL;
    LinarForm* lf2 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    printf("Do not enter anything\n");
    *operation_result = countLinarForm(lf2, res2);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    if (res2 != NULL) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf2);

    result_of_test = 0; //TEST 3
    int* res3 = NULL;
    *operation_result = NULL;
    LinarForm* lf3 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    printf("Do not enter anything\n");
    *operation_result = countLinarForm(lf3, res3);
    if (*operation_result != RESULT_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf3);

    result_of_test = 0; //TEST 4
    int* res4;
    *operation_result = NULL;
    LinarForm* lf4 = NULL;
    printf("Do not enter anything\n");
    *operation_result = countLinarForm(lf4, res3);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf4);
}

void TestPrintLinarForm(){
    int test_group_number = 7;
    int test_number = 1;
    int result_of_test = 0;

    result_of_test = 0; //TEST 1
    LinarFormErrors *operation_result = NULL;
    LinarForm* lf1 = CreateLinarForm(GetIntTypeInfo(), 3, operation_result);
    ReplaceLinarForm(lf1, 0, 1);
    ReplaceLinarForm(lf1, 1, 2);
    ReplaceLinarForm(lf1, 2, 3);
    printf("Expected: 'Linar form: F= + 1 + 2*X1 + 3*X2'");
    *operation_result = printLinarForm(lf1);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf1);

    result_of_test = 0; //TEST 2
    *operation_result = NULL;
    LinarForm* lf2 = CreateLinarForm(GetIntTypeInfo(), 0, operation_result);
    printf("Expected: 'Linar form is empty'");
    *operation_result = printLinarForm(lf2);
    if (*operation_result != LINARFORM_OPERATION_OK) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf2);

    result_of_test = 0; //TEST 3
    *operation_result = NULL;
    LinarForm* lf3 = NULL;
    *operation_result = printLinarForm(lf3);
    if (*operation_result != LINARFORM_NOT_DEFINED) result_of_test = 1;
    TestResultPrint(&result_of_test, &test_group_number, &test_number);
    test_number++;
    freeLinarForm(lf3);
}

void TestAll(){
    TestCreateLinarForm();
    TestInputLinarForm();
    TestReplaceLinarForm();
    TestAddLinarForm();
    TestMultiplyLinarForm();
    TestCountLinarForm();
    TestPrintLinarForm();
}