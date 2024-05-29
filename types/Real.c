#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include "../utility/Exception.h"
#include "Real.h"
#define bufferSize 64


void inputDoubleElementForReal(double *element, FILE *incomingFlow, FILE *exceptionFlow);

static FieldInfo *realFieldInfo = NULL;

FieldInfo* getRealFieldInfo(FILE *exceptionFlow) {
    if (realFieldInfo == NULL) {
        realFieldInfo = (FieldInfo *) malloc(sizeof(FieldInfo));
        if (realFieldInfo == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for real fieldinfo]\n");
            fprintf(exceptionFlow, "[function: %s | file: %s ]\n", __func__, __FILE__);
            return NULL;
        }
        realFieldInfo->elementSize = sizeof(double);
        realFieldInfo->inputElement = inputRealElement;
        realFieldInfo->printElement = printRealElement;
        realFieldInfo->foldElements = foldRealElements;
        realFieldInfo->multiplyElementByScalar = multiplyRealElementByScalar;
        realFieldInfo->getInverseElementForAddition = getInverseRealElementForAddition;
        realFieldInfo->getInverseElementForMultiplication = getInverseRealElementForMultiplication;
        realFieldInfo->getNeutralElementForAddition = getNeutralRealElementForAddition;
        realFieldInfo->getNeutralElementForMultiplication = getNeutralRealElementForMultiplication;
        realFieldInfo->compareElements = compareRealElements;
    }
    return realFieldInfo;
}

void inputDoubleElementForReal(double *element, FILE *incomingFlow, FILE *exceptionFlow) {
    int index = 1;
    int inputSymbolCode;
    int hasDecimalPoint = 0;
    char inputBuffer[bufferSize];
    inputBuffer[0] = 43;
    while (isspace(inputSymbolCode = fgetc(incomingFlow)) && inputSymbolCode != EOF);
    while (index < bufferSize - 1 && inputSymbolCode != EOF) {
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
