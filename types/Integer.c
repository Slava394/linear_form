#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "../utility/Exception.h"
#include "Integer.h"
#define BUFFER_SIZE 26


void inputLongElementForInteger(long *element, FILE *incomingFlow, FILE *exceptionFlow);

static FieldInfo *INTEGER_FIELD_INFO = NULL;

FieldInfo* getIntegerFieldInfo(FILE *exceptionFlow) {
    if (INTEGER_FIELD_INFO == NULL) {
        INTEGER_FIELD_INFO = (FieldInfo *) malloc(sizeof(FieldInfo));
        if (INTEGER_FIELD_INFO == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for integer fieldinfo]\n");
            fprintf(exceptionFlow, "[function: %s | file: %s ]\n", __func__, __FILE__);
            return NULL;
        }
        INTEGER_FIELD_INFO->elementSize = sizeof(long);
        INTEGER_FIELD_INFO->inputElement = inputIntegerElement;
        INTEGER_FIELD_INFO->printElement = printIntegerElement;
        INTEGER_FIELD_INFO->foldElements = foldIntegerElements;
        INTEGER_FIELD_INFO->multiplyElementByScalar = multiplyIntegerElementByScalar;
        INTEGER_FIELD_INFO->getInverseElementForAddition = getInverseIntegerElementForAddition;
        INTEGER_FIELD_INFO->getInverseElementForMultiplication = getInverseIntegerElementForMultiplication;
        INTEGER_FIELD_INFO->getNeutralElementForAddition = getNeutralIntegerElementForAddition;
        INTEGER_FIELD_INFO->getNeutralElementForMultiplication = getNeutralIntegerElementForMultiplication;
        INTEGER_FIELD_INFO->compareElements = compareIntegerElements;
    }
    return INTEGER_FIELD_INFO;
}

void inputLongElementForInteger(long *element, FILE *incomingFlow, FILE *exceptionFlow) {
    int index = 1;
    int inputSymbolCode;
    char inputBuffer[BUFFER_SIZE];
    inputBuffer[0] = 43;
    while (isspace(inputSymbolCode = fgetc(incomingFlow)) && inputSymbolCode != EOF);
    while (index < BUFFER_SIZE - 1 && inputSymbolCode != EOF) {
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
