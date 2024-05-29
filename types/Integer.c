#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "../utility/Exception.h"
#include "Integer.h"
#define bufferSize 26


void inputLongElementForInteger(long *element, FILE *incomingFlow, FILE *exceptionFlow);

static FieldInfo *integerFieldInfo = NULL;

FieldInfo* getIntegerFieldInfo(FILE *exceptionFlow) {
    if (integerFieldInfo == NULL) {
        integerFieldInfo = (FieldInfo *) malloc(sizeof(FieldInfo));
        if (integerFieldInfo == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for integer fieldinfo]\n");
            fprintf(exceptionFlow, "[function: %s | file: %s ]\n", __func__, __FILE__);
            return NULL;
        }
        integerFieldInfo->elementSize = sizeof(long);
        integerFieldInfo->inputElement = inputIntegerElement;
        integerFieldInfo->printElement = printIntegerElement;
        integerFieldInfo->foldElements = foldIntegerElements;
        integerFieldInfo->multiplyElementByScalar = multiplyIntegerElementByScalar;
        integerFieldInfo->getInverseElementForAddition = getInverseIntegerElementForAddition;
        integerFieldInfo->getInverseElementForMultiplication = getInverseIntegerElementForMultiplication;
        integerFieldInfo->getNeutralElementForAddition = getNeutralIntegerElementForAddition;
        integerFieldInfo->getNeutralElementForMultiplication = getNeutralIntegerElementForMultiplication;
        integerFieldInfo->compareElements = compareIntegerElements;
    }
    return integerFieldInfo;
}

void inputLongElementForInteger(long *element, FILE *incomingFlow, FILE *exceptionFlow) {
    int index = 1;
    int inputSymbolCode;
    char inputBuffer[bufferSize];
    inputBuffer[0] = 43;
    while (isspace(inputSymbolCode = fgetc(incomingFlow)) && inputSymbolCode != EOF);
    while (index < bufferSize - 1 && inputSymbolCode != EOF) {
        if (isspace(inputSymbolCode)) {
            break;
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
    *element = strtol(inputBuffer, &checkEndPointer, 10);
    if (errno == ERANGE || *checkEndPointer != '\0') {
        setExceptionCode(CONVERSATION_EXCEPTION);
        fprintf(exceptionFlow, "[Conversation error]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
}

void inputIntegerElement(void *element, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow) {
    long *integerElement = (long *) element;
    long inputNumber = 0;
    fprintf(outgoingFlow, "Input integer number:\n");
    inputLongElementForInteger(&inputNumber, incomingFlow, exceptionFlow);
    if (getExceptionCode() != NO_EXCEPTION) {
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    *integerElement = inputNumber;
}

void printIntegerElement(const void *element, FILE *outgoingFlow) {
    long *integerElement = (long *) element;
    if (*integerElement >= 0) {
        fprintf(outgoingFlow, "%li", *integerElement);
    } else {
        fprintf(outgoingFlow, "(%li)", *integerElement);
    }
}

void foldIntegerElements(const void *firstElement, const void *secondElement, void *result) {
    long *firstIntegerElement = (long *) firstElement;
    long *secondIntegerElement = (long *) secondElement;
    long *resultIntegerElement = (long *) result;
    *resultIntegerElement = *firstIntegerElement + *secondIntegerElement;
}

void multiplyIntegerElementByScalar(const void *element, const void *scalar, void *result) {
    long *integerElement = (long *) element;
    long *integerScalar = (long *) scalar;
    long *resultIntegerElement = (long *) result;
    *resultIntegerElement = *integerElement * *integerScalar;
}

void getInverseIntegerElementForAddition(const void *element, void *result) {
    long *integerElement = (long *) element;
    long *resultIntegerElement = (long *) result;
    *resultIntegerElement = -1 * *integerElement;
}

void getInverseIntegerElementForMultiplication(const void *element, void *result, FILE *exceptionFlow) {
    long *integerElement = (long *) element;
    long *resultIntegerElement = (long *) result;
    if (*integerElement == 0) {
        setExceptionCode(INVALID_VALUE);
        fprintf(exceptionFlow, "[Does not exist inverse value]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    *resultIntegerElement = 1 / *integerElement;
}

void getNeutralIntegerElementForAddition(void *result) {
    long *resultIntegerElement = (long *) result;
    *resultIntegerElement = 0;
}

void getNeutralIntegerElementForMultiplication(void *result) {
    long *resultIntegerElement = (long *) result;
    *resultIntegerElement = 1;
}

int compareIntegerElements(const void *firstElement, const void *secondElement) {
    long *firstIntegerElement = (long *) firstElement;
    long *secondIntegerElement = (long *) secondElement;
    if (*firstIntegerElement == *secondIntegerElement) {
        return 1;
    } else {
        return 0;
    }
}
