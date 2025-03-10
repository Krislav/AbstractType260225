#ifndef TESTS_H
#define TESTS_H

#include <LinarForm.h>

void TestResultPrint(const int* result_of_test, const int* test_group_number, const int* test_number);
void TestCreateLinarForm();   //Test group 1
void TestInputLinarForm();    //Test group 2
void TestReplaceLinarForm();  //Test group 3
void TestAddLinarForm();      //Test group 4
void TestMultiplyLinarForm(); //Test group 5
void TestCountLinarForm();    //Test group 6
void TestPrintLinarForm();    //Test group 7
void TestAll();

#endif