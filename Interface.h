#ifndef INTERFACE_H
#define INTERFACE_H

#include "Tests.h"
#include "LinearForm.h"

static int NUMBER_OF_LINEAR_FORMS = 0;
#define MAX_NUMBER_OF_LINEAR_FORMS 5
static LinearForm* CREATED_LF[MAX_NUMBER_OF_LINEAR_FORMS];
static char ERROR_MESSAGES[8][60] = {"The operation was successfull.", "Memory allocation failed.", "Incompatible types of linear forms.", "Linear forms does not exist.", "Operation does not exist.", "The number of coefficients cannot be negative.", "Index out of bounds.", "The length of the resulting linear form is incorrect."};

void Menu();
int Home_Page();
void CreateNewLF();
void DeleteExistingLF();
void DeleteAllLF();
void AddLF();
void MultiplyLF();
void CalcLF();
void PrintLF();
void PrintLFNumbers();
void PrintQntLF();

#endif