#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "../utility/Exception.h"
#include "Real.h"
#define BUFFER_SIZE 64


void inputDoubleElementForReal(double *element, FILE *incomingFlow, FILE *exceptionFlow);

static FieldInfo *REAL_FIELD_INFO = NULL;

FieldInfo* getRealFieldInfo(FILE *exceptionFlow) {
    if (REAL_FIELD_INFO == NULL) {
        REAL_FIELD_INFO = (FieldInfo *) malloc(sizeof(FieldInfo));
        if (REAL_FIELD_INFO == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for real fieldinfo]\n");
            fprintf(exceptionFlow, "[function: %s | file: %s ]\n", __func__, __FILE__);
            return NULL;
        }
        REAL_FIELD_INFO->elementSize = sizeof(double);
        REAL_FIELD_INFO->inputElement = inputRealElement;
        REAL_FIELD_INFO->printElement = printRealElement;
        REAL_FIELD_INFO->foldElements = foldRealElements;
        REAL_FIELD_INFO->multiplyElementByScalar = multiplyRealElementByScalar;
        REAL_FIELD_INFO->getInverseElementForAddition = getInverseRealElementForAddition;
        REAL_FIELD_INFO->getInverseElementForMultiplication = getInverseRealElementForMultiplication;
        REAL_FIELD_INFO->getNeutralElementForAddition = getNeutralRealElementForAddition;
        REAL_FIELD_INFO->getNeutralElementForMultiplication = getNeutralRealElementForMultiplication;
        REAL_FIELD_INFO->compareElements = compareRealElements;
    }
    return REAL_FIELD_INFO;
}

void inputDoubleElementForReal(double *element, FILE *incomingFlow, FILE *exceptionFlow) {
    int index = 1;
    int inputSymbolCode;
    int hasDecimalPoint = 0;
    char inputBuffer[BUFFER_SIZE];
    inputBuffer[0] = 43;
    while (isspace(inputSymbolCode = fgetc(incomingFlow)) && inputSymbolCode != EOF);
    while (index < BUFFER_SIZE - 1 && inputSymbolCode != EOF) {
        if (isspace(inputSymbolCode)) {
            break;
        } else if (inputSymbolCode == '.') {
            if (hasDecimalPoint) {
                setExceptionCode(INVALID_INPUT_EXCEPTION);
                fprintf(exceptionFlow, "[Input invalid character]\n");
                fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
                while (!(isspace(inputSymbolCode = fgetc(incomingFlow))) && inputSymbolCode != EOF);
                return;
            }
            hasDecimalPoint = 1;
        } else if (inputSymbolCode == '+') {
            inputSymbolCode = fgetc(incomingFlow);
            continue;
        } else if (inputSymbolCode == '-') {
            if (inputBuffer[0] == '+') {
                inputBuffer[0] = '-';
            } else {
                inputBuffer[0] = '+';
            }
            inputSymbolCode = fgetc(incomingFlow);
            continue;
        } else if (inputSymbolCode < '0' || inputSymbolCode > '9') {
            setExceptionCode(INVALID_INPUT_EXCEPTION);
            fprintf(exceptionFlow, "[Input invalid character]\n");
            fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
            while (!(isspace(inputSymbolCode = fgetc(incomingFlow))) && inputSymbolCode != EOF);
            return;
        }
        inputBuffer[index++] = (char) inputSymbolCode;
        inputSymbolCode = fgetc(incomingFlow);
    }
    inputBuffer[index] = '\0';
    if (index == 1) {
        setExceptionCode(EMPTY_INPUT_EXCEPTION);
        fprintf(exceptionFlow, "[Empty input]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    if (!isspace(inputSymbolCode) && inputSymbolCode != EOF) {
        setExceptionCode(BUFFER_OVERFLOW_EXCEPTION);
        fprintf(exceptionFlow, "[Input buffer overflow]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        while (!(isspace(inputSymbolCode = fgetc(incomingFlow))) && inputSymbolCode != EOF);
        return;
    }
    errno = 0;
    char *checkEndPointer;
    *element = strtod(inputBuffer, &checkEndPointer);
    if (errno == ERANGE || *checkEndPointer != '\0') {
        setExceptionCode(CONVERSATION_EXCEPTION);
        fprintf(exceptionFlow, "[Conversation error]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
}

void inputRealElement(void *element, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow) {
    double *realElement = (double *) element;
    double inputNumber = 0.0;
    fprintf(outgoingFlow, "Input real number:\n");
    inputDoubleElementForReal(&inputNumber, incomingFlow, exceptionFlow);
    if (getExceptionCode() != NO_EXCEPTION) {
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    *realElement = inputNumber;
}

void printRealElement(const void *element, FILE *outgoingFlow) {
    double *realElement = (double *) element;
    if (*realElement >= 0) {
        fprintf(outgoingFlow, "%e", *realElement);
    } else {
        fprintf(outgoingFlow, "(%e)", *realElement);
    }
}

void foldRealElements(const void *firstElement, const void *secondElement, void *result) {
    double *firstRealElement = (double *) firstElement;
    double *secondRealElement = (double *) secondElement;
    double *resultRealElement = (double *) result;
    *resultRealElement = *firstRealElement + *secondRealElement;
}

void multiplyRealElementByScalar(const void *element, const void *scalar, void *result) {
    double *realElement = (double *) element;
    double *realScalar = (double *) scalar;
    double *resultRealElement = (double *) result;
    *resultRealElement = *realElement * *realScalar;
}

void getInverseRealElementForAddition(const void *element, void *result) {
    double *realElement = (double *) element;
    double *resultRealElement = (double *) result;
    *resultRealElement = -1.0 * *realElement;
}

void getInverseRealElementForMultiplication(const void *element, void *result, FILE *exceptionFlow) {
    double delta = 0.000001;
    double *realElement = (double *) element;
    double *resultRealElement = (double *) result;
    if (fabs(*realElement) < delta) {
        setExceptionCode(INVALID_VALUE);
        fprintf(exceptionFlow, "[Does not exist inverse value]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    *resultRealElement = 1.0 / *realElement;
}

void getNeutralRealElementForAddition(void *result) {
    double *resultRealElement = (double *) result;
    *resultRealElement = 0.0;
}

void getNeutralRealElementForMultiplication(void *result) {
    double *resultRealElement = (double *) result;
    *resultRealElement = 1.0;
}

int compareRealElements(const void *firstElement, const void *secondElement) {
    double delta = 0.000001;
    double *firstRealElement = (double *) firstElement;
    double *secondRealElement = (double *) secondElement;
    double intermediateDifference = *firstRealElement - *secondRealElement;
    if (fabs(intermediateDifference) < delta) {
        return 1;
    } else {
        return 0;
    }
}
