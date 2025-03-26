#include "Interface.h"

// system("clear") system("cls")
void Menu(){
    int exit_sign = 0;
    while (exit_sign == 0) {
        exit_sign = Home_Page();
    }
    printf("Goodbye\n");
}

int Home_Page(){
    int com;

    printf("\n");
    printf("Enter a number to select what you want to do.\n");
    printf("1 - Create a new linear form and fill it in.\n");
    printf("2 - Delete existing linear form\n");
    printf("3 - Add or subtract 2 linear forms and write in a third\n");
    printf("4 - Multiply all coefficients in linear form by a number\n");
    printf("5 - Calculate the linear form for the entered variable values\n");
    printf("6 - Print linear form to terminal\n");
    printf("7 - Print numbers of all existing linear forms\n");
    printf("8 - Print how many linar form exists\n");
    printf("9 - Exit\n");
    
    int continue_input = 1;
    while (continue_input == 1) {
        printf("Enter the selected number: "); // -------
        scanf("%d", &com);

        switch(com){
            case 1:
                CreateNewLF();
                continue_input = 0;
                break;
            case 2:
                DeleteExistingLF();
                continue_input = 0;
                break;
            case 3:
                AddLF();
                continue_input = 0;
                break;
            case 4:
                MultiplyLF();
                continue_input = 0;
                break;
            case 5:
                CalcLF();
                continue_input = 0;
                break;
            case 6:
                PrintLF();
                continue_input = 0;
                break;
            case 7:
                PrintLFNumbers();
                continue_input = 0;
                break;
            case 8:
                PrintQntLF();
                continue_input = 0;
                break;
            case 9:
                return 1;
                DeleteAllLF();
                break;
            default:
                printf("Incorrect input number\n");
        }
    }
    return 0;
}

void CreateNewLF(){
    if (NUMBER_OF_LINEAR_FORMS >= MAX_NUMBER_OF_LINEAR_FORMS) {printf("Can't create more linear forms.\n"); return;}
    if (NUMBER_OF_LINEAR_FORMS == 0) for (int i = 0; i < MAX_NUMBER_OF_LINEAR_FORMS; i++) CREATED_LF[i] = NULL;

    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    int n, continue_input;
    char type = 'i'; 
    printf("Enter the number of coefficients in linear form: ");
    scanf("%d", &n);
    continue_input = 1;
    while (continue_input == 1) {
        printf("Enter the coefficients type(i - integer, d - double): ");
        scanf("%c", &type); scanf("%c", &type);
        if (type != 'i' && type != 'd') printf("Invalid data type.\n");
        else continue_input = 0;
    }

    LinearForm* new_lf;
    if (type == 'i') {
        new_lf = CreateLinearForm(GetIntTypeInfo(), n, &operation_result);
    }
    else {
        new_lf = CreateLinearForm(GetDoubleTypeInfo(), n, &operation_result);
    }
    if (operation_result != LINEAR_FORM_OPERATION_OK) {puts(ERROR_MESSAGES[operation_result]); return;}
    operation_result = InputLinearForm(new_lf);
    if (operation_result != LINEAR_FORM_OPERATION_OK) {puts(ERROR_MESSAGES[operation_result]); return;}

    int lf_index = 0;
    while (CREATED_LF[lf_index] != NULL) lf_index++;
    CREATED_LF[lf_index] = new_lf;
    printf("Created linear form number %d.\n", lf_index + 1);
    NUMBER_OF_LINEAR_FORMS++;

    return;
}

void DeleteExistingLF(){
    int lf_number;
    int continue_input = 1;

    while (continue_input == 1) {
        printf("Enter the number of the linear form you want to delete: ");
        scanf("%d", &lf_number);
        if (lf_number > MAX_NUMBER_OF_LINEAR_FORMS || lf_number <= 0) printf("Linear form number out of limits.\n");
        else continue_input = 0;
    }

    if (CREATED_LF[lf_number - 1] == NULL) printf("Linear form number %d does not exist.\n", lf_number);
    else {
        freeLinearForm(CREATED_LF[lf_number - 1]);
        CREATED_LF[lf_number - 1] = NULL;
        printf("Linear form number %d successfully deleted.\n", lf_number);
    }

    NUMBER_OF_LINEAR_FORMS--;
    return;
}

void DeleteAllLF(){
    for (int i = 0; i < MAX_NUMBER_OF_LINEAR_FORMS; i++){
        freeLinearForm(CREATED_LF[i]);
    }
}

void AddLF(){
    int lf1_number, lf2_number, lfr_number, subtraction;
    int continue_input = 1;
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;

    while (continue_input == 1) {
        printf("Enter 0 or 1 if you want to add or subtract: ");
        scanf("%d", &subtraction);
        if (subtraction != 0 && subtraction != 1) printf("Incorrect input\n");
        else continue_input = 0;
    }

    continue_input = 1;
    while (continue_input == 1) {
        printf("Enter the number of the first linear form you want to add: ");
        scanf("%d", &lf1_number);
        if (lf1_number > MAX_NUMBER_OF_LINEAR_FORMS || lf1_number <= 0) printf("Linear form number out of limits.\n");
        else if (CREATED_LF[lf1_number - 1] == NULL) printf("Linear form number %d does not exist.\n", lf1_number);
             else continue_input = 0;
    }

    continue_input = 1;
    while (continue_input == 1) {
        printf("Enter the number of the second linear form you want to add: ");
        scanf("%d", &lf2_number);
        if (lf2_number > MAX_NUMBER_OF_LINEAR_FORMS || lf2_number <= 0) printf("Linear form number out of limits.\n");
        else if (CREATED_LF[lf2_number - 1] == NULL) printf("Linear form number %d does not exist.\n", lf2_number);
             else continue_input = 0;
    }

    continue_input = 1;
    while (continue_input == 1) {
        printf("Enter the number of the linear form you want to write the answer: ");
        scanf("%d", &lfr_number);
        if (lfr_number > MAX_NUMBER_OF_LINEAR_FORMS || lfr_number <= 0) printf("Linear form number out of limits.\n");
        else if (CREATED_LF[lfr_number - 1] == NULL) printf("Linear form number %d does not exist.\n", lfr_number);
             else continue_input = 0;
    }

    operation_result = addLinearForm(CREATED_LF[lf1_number - 1], CREATED_LF[lf2_number - 1], CREATED_LF[lfr_number - 1], subtraction);
    if (operation_result != LINEAR_FORM_OPERATION_OK) {puts(ERROR_MESSAGES[operation_result]); return;}
    if (subtraction == 0) printf("Linear form %d and Linear form %d was add and answer was written in %d linear form.\n", lf1_number, lf2_number, lfr_number);
    else printf("Linear form %d and Linear form %d was substract and answer was written in %d linear form.\n", lf1_number, lf2_number, lfr_number);
    
    return;
}

void MultiplyLF(){
    int lf_number, multiplier;
    int continue_input = 1;
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;

    
    while (continue_input == 1) {
        printf("Enter the number of the linear form you want to add: ");
        scanf("%d", &lf_number);
        if (lf_number > MAX_NUMBER_OF_LINEAR_FORMS || lf_number <= 0) printf("Linear form number out of limits.\n");
        else if (CREATED_LF[lf_number - 1] == NULL) printf("Linear form number %d does not exist.\n", lf_number);
             else continue_input = 0;
    }

    printf("Enter the number you want to multiply by: ");
    scanf("%d", &multiplier);

    operation_result = multiplyLinearForm(CREATED_LF[lf_number - 1], &multiplier);
    if (operation_result != LINEAR_FORM_OPERATION_OK) {puts(ERROR_MESSAGES[operation_result]); return;}
    printf("The linear form number %d was multiplied by a number.\n", lf_number);
}

void CalcLF(){
    int lf_number, result;
    int continue_input = 1;
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    
    while (continue_input == 1) {
        printf("Enter the number of the linear form you want to calculate: ");
        scanf("%d", &lf_number);
        if (lf_number > MAX_NUMBER_OF_LINEAR_FORMS || lf_number <= 0) printf("Linear form number out of limits.\n");
        else if (CREATED_LF[lf_number - 1] == NULL) printf("Linear form number %d does not exist.\n", lf_number);
             else continue_input = 0;
    }

    operation_result = countLinearForm(CREATED_LF[lf_number - 1], &result);
    if (operation_result != LINEAR_FORM_OPERATION_OK) {puts(ERROR_MESSAGES[operation_result]); return;}
    printf("Result of the calculation is %d.\n", result);
}

void PrintLF(){
    int lf_number;
    int continue_input = 1;
    LinearFormErrors operation_result = LINEAR_FORM_OPERATION_OK;
    
    while (continue_input == 1) {
        printf("Enter the number of the linear form you want to print: ");
        scanf("%d", &lf_number);
        if (lf_number > MAX_NUMBER_OF_LINEAR_FORMS || lf_number <= 0) printf("Linear form number out of limits.\n");
        else if (CREATED_LF[lf_number - 1] == NULL) printf("Linear form number %d does not exist.\n", lf_number);
             else continue_input = 0;
    }

    operation_result = printLinearForm(CREATED_LF[lf_number - 1]);
    if (operation_result != LINEAR_FORM_OPERATION_OK) {puts(ERROR_MESSAGES[operation_result]); return;}
}

void PrintLFNumbers(){
    printf("Numbers of all existing linear forms: ");

    for (int i = 0; i < MAX_NUMBER_OF_LINEAR_FORMS; i++){
        if (CREATED_LF[i] != NULL) printf("%d ", i + 1);
    }
    printf("\n");
}

void PrintQntLF(){
    if (NUMBER_OF_LINEAR_FORMS == 1) printf("Exist %d linear form\n", NUMBER_OF_LINEAR_FORMS);
    else printf("Exist %d linear forms.\n", NUMBER_OF_LINEAR_FORMS);
}