#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "Test.h"
#include "../utility/Exception.h"
#define outputStream stdout


void test() {
    //Test1: instance of abstract data type with integer numbers
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForIntegerTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3, *linearForm4, *linearForm5;
        initLinearForm(2, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(4, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(3, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm4, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(8, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm5, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        fprintf(outputStream, "[Test1 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        freeLinearForm(linearForm4);
        freeLinearForm(linearForm5);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test2: instance of abstract data type with real numbers
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForRealTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3, *linearForm4, *linearForm5;
        initLinearForm(2, getRealFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getRealFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(4, getRealFieldInfo(pseudoOutgoingFlow), &linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(3, getRealFieldInfo(pseudoOutgoingFlow), &linearForm4, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(8, getRealFieldInfo(pseudoOutgoingFlow), &linearForm5, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        fprintf(outputStream, "[Test2 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        freeLinearForm(linearForm4);
        freeLinearForm(linearForm5);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test3: instance of abstract data type with complex numbers
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForComplexTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3, *linearForm4, *linearForm5;
        initLinearForm(2, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(4, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(3, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm4, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(8, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm5, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        fprintf(outputStream, "[Test3 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        freeLinearForm(linearForm4);
        freeLinearForm(linearForm5);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test4: fold integer linear form
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForIntegerTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3, *linearForm4;
        initLinearForm(2, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(4, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(3, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm4, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        foldLinearForms(linearForm1, linearForm2, linearForm2, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        foldLinearForms(linearForm3, linearForm4, linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        long answerData1[5] = {-60, -140, -61, 66, 49};
        long answerData2[4] = {40, 84, 73, 49};
        for (int index = 0; index < linearForm2->size; index++) {
            assert(*(long *) linearForm2->baseDynamicArray[index] == answerData1[index]);
        }
        for (int index = 0; index < linearForm3->size; index++) {
            assert(*(long *) linearForm3->baseDynamicArray[index] == answerData2[index]);
        }
        fprintf(outputStream, "[Test4 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        freeLinearForm(linearForm4);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test5: fold real linear form
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForRealTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3, *linearForm4;
        initLinearForm(2, getRealFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getRealFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(4, getRealFieldInfo(pseudoOutgoingFlow), &linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(3, getRealFieldInfo(pseudoOutgoingFlow), &linearForm4, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        foldLinearForms(linearForm1, linearForm2, linearForm2, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        foldLinearForms(linearForm3, linearForm4, linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        double answerData1[5] = {-81.4471, -70.4818, -32.4575, -86.2672, 57.3122};
        double answerData2[4] = {3.2391, -23.085, 74.9664, 65.769};
        double delta = 0.000001;
        double intermediateResult;
        for (int index = 0; index < linearForm2->size; index++) {
            intermediateResult = *(double *) linearForm2->baseDynamicArray[index] - answerData1[index];
            assert(fabs(intermediateResult) < delta);
        }
        for (int index = 0; index < linearForm3->size; index++) {
            intermediateResult = *(double *) linearForm3->baseDynamicArray[index] - answerData2[index];
            assert(fabs(intermediateResult) < delta);
        }
        fprintf(outputStream, "[Test5 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        freeLinearForm(linearForm4);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test6: fold complex linear form
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForComplexTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3, *linearForm4;
        initLinearForm(2, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(4, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(3, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm4, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        foldLinearForms(linearForm1, linearForm2, linearForm2, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        foldLinearForms(linearForm3, linearForm4, linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        Complex answerData1[5] = {5, 139, 173, 100, -69, 5, -87, -70, -27, 34};
        Complex answerData2[4] = {78, 8, -22, -62, -23, 86, 3, 50};
        Complex intermediateResult;
        for (int index = 0; index < linearForm2->size; index++) {
            intermediateResult.real = ((Complex *) linearForm2->baseDynamicArray[index])->real;
            intermediateResult.imaginary = ((Complex *) linearForm2->baseDynamicArray[index])->imaginary;
            assert(intermediateResult.real == answerData1[index].real && intermediateResult.imaginary == answerData1[index].imaginary);
        }
        for (int index = 0; index < linearForm3->size; index++) {
            intermediateResult.real = ((Complex *) linearForm3->baseDynamicArray[index])->real;
            intermediateResult.imaginary = ((Complex *) linearForm3->baseDynamicArray[index])->imaginary;
            assert(intermediateResult.real == answerData2[index].real && intermediateResult.imaginary == answerData2[index].imaginary);
        }
        fprintf(outputStream, "[Test6 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        freeLinearForm(linearForm4);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test7: multiply integer linear form by scalar
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForIntegerTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3;
        initLinearForm(2, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(4, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm1, linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm2, linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm3, linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        long answerData1[2] = {-3840, -3440};
        long answerData2[5] = {3024, -4536, -5124, 5544, 4116};
        long answerData3[4] = {0, 0, 0, 0};
        for (int index = 0; index < linearForm1->size; index++) {
            assert(*(long *) linearForm1->baseDynamicArray[index] == answerData1[index]);
        }
        for (int index = 0; index < linearForm2->size; index++) {
            assert(*(long *) linearForm2->baseDynamicArray[index] == answerData2[index]);
        }
        for (int index = 0; index < linearForm3->size; index++) {
            assert(*(long *) linearForm3->baseDynamicArray[index] == answerData3[index]);
        }
        fprintf(outputStream, "[Test7 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test8: multiply real linear form by scalar
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForRealTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3;
        initLinearForm(2, getRealFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getRealFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(4, getRealFieldInfo(pseudoOutgoingFlow), &linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm1, linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm2, linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm3, linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        double answerData1[2] = {-207.396658, -24.493426};
        double answerData2[5] = {402.094530, 1452.508200, 749.281388, 1991.478312, -1323.052137};
        double answerData3[4] = {0, 0, 0, 0};
        double delta = 0.000001;
        double intermediateResult;
        for (int index = 0; index < linearForm1->size; index++) {
            intermediateResult = *(double *) linearForm1->baseDynamicArray[index] - answerData1[index];
            assert(fabs(intermediateResult) < delta);
        }
        for (int index = 0; index < linearForm2->size; index++) {
            intermediateResult = *(double *) linearForm2->baseDynamicArray[index] - answerData2[index];
            assert(fabs(intermediateResult) < delta);
        }
        for (int index = 0; index < linearForm3->size; index++) {
            intermediateResult = *(double *) linearForm3->baseDynamicArray[index] - answerData3[index];
            assert(fabs(intermediateResult) < delta);
        }
        fprintf(outputStream, "[Test8 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test9: multiply complex linear form by scalar
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForComplexTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3;
        initLinearForm(2, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(4, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm1, linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm2, linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        multiplyLinearFormByScalar(linearForm3, linearForm3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        Complex answerData1[2] = {-4772, 5028, 6354, 1834};
        Complex answerData2[5] = {2980, -5176, 3290, -7450, 1828, 4168, -2426, 6934, 2702, 926};
        Complex answerData3[4] = {0, 0, 0, 0, 0, 0, 0, 0};
        Complex intermediateResult;
        for (int index = 0; index < linearForm1->size; index++) {
            intermediateResult.real = ((Complex *) linearForm1->baseDynamicArray[index])->real;
            intermediateResult.imaginary = ((Complex *) linearForm1->baseDynamicArray[index])->imaginary;
            assert(intermediateResult.real == answerData1[index].real && intermediateResult.imaginary == answerData1[index].imaginary);
        }
        for (int index = 0; index < linearForm2->size; index++) {
            intermediateResult.real = ((Complex *) linearForm2->baseDynamicArray[index])->real;
            intermediateResult.imaginary = ((Complex *) linearForm2->baseDynamicArray[index])->imaginary;
            assert(intermediateResult.real == answerData2[index].real && intermediateResult.imaginary == answerData2[index].imaginary);
        }
        for (int index = 0; index < linearForm3->size; index++) {
            intermediateResult.real = ((Complex *) linearForm3->baseDynamicArray[index])->real;
            intermediateResult.imaginary = ((Complex *) linearForm3->baseDynamicArray[index])->imaginary;
            assert(intermediateResult.real == answerData3[index].real && intermediateResult.imaginary == answerData3[index].imaginary);
        }
        fprintf(outputStream, "[Test9 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test10: calculate value of integer linear form
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForIntegerTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3;
        void *resultOfCalculation1, *resultOfCalculation2, *resultOfCalculation3;
        initLinearForm(2, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(4, getIntegerFieldInfo(pseudoOutgoingFlow), &linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm1, &resultOfCalculation1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm2, &resultOfCalculation2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm3, &resultOfCalculation3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        long answerData1 = -3536;
        long answerData2 = -868;
        long answerData3 = 0;
        assert(*(long *) resultOfCalculation1 == answerData1);
        assert(*(long *) resultOfCalculation2 == answerData2);
        assert(*(long *) resultOfCalculation3 == answerData3);
        fprintf(outputStream, "[Test10 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        free(resultOfCalculation1);
        free(resultOfCalculation2);
        free(resultOfCalculation3);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test11: calculate value of real linear form
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForRealTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3;
        void *resultOfCalculation1, *resultOfCalculation2, *resultOfCalculation3;
        initLinearForm(2, getRealFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getRealFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(4, getRealFieldInfo(pseudoOutgoingFlow), &linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm1, &resultOfCalculation1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm2, &resultOfCalculation2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm3, &resultOfCalculation3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        double answerData1 = -88.522526;
        double answerData2 = -5288.185148;
        double answerData3 = 0.0;
        double delta = 0.000001;
        double intermediateResult1 = *(double *) resultOfCalculation1 - answerData1;
        double intermediateResult2 = *(double *) resultOfCalculation2 - answerData2;
        double intermediateResult3 = *(double *) resultOfCalculation3 - answerData3;
        assert(fabs(intermediateResult1) < delta);
        assert(fabs(intermediateResult2) < delta);
        assert(fabs(intermediateResult3) < delta);
        fprintf(outputStream, "[Test11 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
    //Test12: calculate value of complex linear form
    {
        FILE *pseudoOutgoingFlow = tmpfile();
        FILE *incomingFlow = fopen("../tests/dataForComplexTest.txt", "r");
        if (pseudoOutgoingFlow == NULL || incomingFlow == NULL) {
            fprintf(outputStream, "Something went wrong: critical error!");
            exit(1);
        }
        LinearForm *linearForm1, *linearForm2, *linearForm3;
        void *resultOfCalculation1, *resultOfCalculation2, *resultOfCalculation3;
        initLinearForm(2, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initLinearForm(5, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        initZeroLinearForm(4, getComplexFieldInfo(pseudoOutgoingFlow), &linearForm3, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm1, &resultOfCalculation1, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm2, &resultOfCalculation2, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        calculateValueOfLinearForm(linearForm3, &resultOfCalculation3, incomingFlow, pseudoOutgoingFlow, pseudoOutgoingFlow);
        assert(getExceptionCode() == NO_EXCEPTION);
        Complex answerData1 = {6300, 1904};
        Complex answerData2 = {5627, -14904};
        Complex answerData3 = {0, 0};
        Complex intermediateResult1 = *(Complex *) resultOfCalculation1;
        Complex intermediateResult2 = *(Complex *) resultOfCalculation2;
        Complex intermediateResult3 = *(Complex *) resultOfCalculation3;
        assert(intermediateResult1.real == answerData1.real && intermediateResult1.imaginary == answerData1.imaginary);
        assert(intermediateResult2.real == answerData2.real && intermediateResult2.imaginary == answerData2.imaginary);
        assert(intermediateResult3.real == answerData3.real && intermediateResult3.imaginary == answerData3.imaginary);
        fprintf(outputStream, "[Test12 passed]\n");
        freeLinearForm(linearForm1);
        freeLinearForm(linearForm2);
        freeLinearForm(linearForm3);
        fclose(pseudoOutgoingFlow);
        fclose(incomingFlow);
    }
}
