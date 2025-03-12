#ifndef TESTS_H
#define TESTS_H

#include "LinearForm.h"

void TestResultPrint(const int* result_of_test, const int* test_group_number, const int* test_number);
void TestCreateLinearForm();   //Test group 1
void TestInputLinearForm();    //Test group 2
void TestReplaceLinearForm();  //Test group 3
void TestAddLinearForm();      //Test group 4
void TestMultiplyLinearForm(); //Test group 5
void TestCountLinearForm();    //Test group 6
void TestPrintLinearForm();    //Test group 7
void TestAll();

#endif