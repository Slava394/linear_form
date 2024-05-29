#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "../utility/Exception.h"
#include "Complex.h"
#define bufferSize 26


void inputLongElementForComplex(long *element, FILE *incomingFlow, FILE *exceptionFlow);

static FieldInfo *complexFieldInfo = NULL;

FieldInfo* getComplexFieldInfo(FILE *exceptionFlow) {
    if (complexFieldInfo == NULL) {
        complexFieldInfo = (FieldInfo *) malloc(sizeof(FieldInfo));
        if (complexFieldInfo == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for complex fieldinfo]\n");
            fprintf(exceptionFlow, "[function: %s | file: %s ]\n", __func__, __FILE__);
            return NULL;
        }
        complexFieldInfo->elementSize = sizeof(Complex);
        complexFieldInfo->inputElement = inputComplexElement;
        complexFieldInfo->printElement = printComplexElement;
        complexFieldInfo->foldElements = foldComplexElements;
        complexFieldInfo->multiplyElementByScalar = multiplyComplexElementByScalar;
        complexFieldInfo->getInverseElementForAddition = getInverseComplexElementForAddition;
        complexFieldInfo->getInverseElementForMultiplication = getInverseComplexElementForMultiplication;
        complexFieldInfo->getNeutralElementForAddition = getNeutralComplexElementForAddition;
        complexFieldInfo->getNeutralElementForMultiplication = getNeutralComplexElementForMultiplication;
        complexFieldInfo->compareElements = compareComplexElements;
    }
    return complexFieldInfo;
}

void inputLongElementForComplex(long *element, FILE *incomingFlow, FILE *exceptionFlow) {
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

void inputComplexElement(void *element, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow) {
    Complex *complexElement = (Complex *) element;
    long real = 0, imaginary = 0;
    fprintf(outgoingFlow, "Input real part:\n");
    inputLongElementForComplex(&real, incomingFlow, exceptionFlow);
    if (getExceptionCode() != NO_EXCEPTION) {
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    fprintf(outgoingFlow, "Input imaginary part:\n");
    inputLongElementForComplex(&imaginary, incomingFlow, exceptionFlow);
    if (getExceptionCode() != NO_EXCEPTION) {
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    complexElement->real = real;
    complexElement->imaginary = imaginary;
}

void printComplexElement(const void *element, FILE *outgoingFlow) {
    Complex *complexElement = (Complex *) element;
    if (complexElement->real == 0 && complexElement->imaginary == 0) {
        fprintf(outgoingFlow, "0");
    } else if (complexElement->real == 0 && complexElement->imaginary == 1) {
        fprintf(outgoingFlow, "i");
    } else if (complexElement->real == 0 && complexElement->imaginary == -1) {
        fprintf(outgoingFlow, "(-i)");
    } else if (complexElement->real == 0 && complexElement->imaginary > 0) {
        fprintf(outgoingFlow, "%lii", complexElement->imaginary);
    } else if (complexElement->real == 0 && complexElement->imaginary < 0) {
        fprintf(outgoingFlow, "(%lii)", complexElement->imaginary);
    } else if (complexElement->real > 0 && complexElement->imaginary == 0) {
        fprintf(outgoingFlow, "%li", complexElement->real);
    } else if (complexElement->real < 0 && complexElement->imaginary == 0) {
        fprintf(outgoingFlow, "(%li)", complexElement->real);
    } else if (complexElement->imaginary == 1) {
        fprintf(outgoingFlow, "(%li+i)", complexElement->real);
    } else if (complexElement->imaginary == -1) {
        fprintf(outgoingFlow, "(%li-i)", complexElement->real);
    } else {
        fprintf(outgoingFlow, "(%li%+lii)", complexElement->real, complexElement->imaginary);
    }
}

void foldComplexElements(const void *firstElement, const void *secondElement, void *result) {
    Complex *firstComplexElement = (Complex *) firstElement;
    Complex *secondComplexElement = (Complex *) secondElement;
    Complex *resultComplexElement = (Complex *) result;
    resultComplexElement->real = firstComplexElement->real + secondComplexElement->real;
    resultComplexElement->imaginary = firstComplexElement->imaginary + secondComplexElement->imaginary;
}

void multiplyComplexElementByScalar(const void *element, const void *scalar, void *result) {
    Complex *complexElement = (Complex *) element;
    Complex *complexScalar = (Complex *) scalar;
    Complex *resultComplexElement = (Complex *) result;
    long intermediateResultOfReal = complexScalar->real * complexElement->real - complexScalar->imaginary * complexElement->imaginary;
    long intermediateResultOfImaginary = complexScalar->real * complexElement->imaginary + complexScalar->imaginary * complexElement->real;
    resultComplexElement->real = intermediateResultOfReal;
    resultComplexElement->imaginary = intermediateResultOfImaginary;
}

void getInverseComplexElementForAddition(const void *element, void *result) {
    Complex *complexElement = (Complex *) element;
    Complex *resultComplexElement = (Complex *) result;
    resultComplexElement->real = -1 * complexElement->real;
    resultComplexElement->imaginary = -1 * complexElement->imaginary;
}

void getInverseComplexElementForMultiplication(const void *element, void *result, FILE *exceptionFlow) {
    Complex *complexElement = (Complex *) element;
    Complex *resultComplexElement = (Complex *) result;
    if (complexElement->real == 0 && complexElement->imaginary == 0) {
        setExceptionCode(INVALID_VALUE);
        fprintf(exceptionFlow, "[Does not exist inverse value]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    long modulusSquare = complexElement->real * complexElement->real + complexElement->imaginary * complexElement->imaginary;
    resultComplexElement->real = complexElement->real / modulusSquare;
    resultComplexElement->imaginary = -1 * complexElement->imaginary / modulusSquare;
}

void getNeutralComplexElementForAddition(void *result) {
    Complex *resultComplexElement = (Complex *) result;
    resultComplexElement->real = 0;
    resultComplexElement->imaginary = 0;
}

void getNeutralComplexElementForMultiplication(void *result) {
    Complex *resultComplexElement = (Complex *) result;
    resultComplexElement->real = 1;
    resultComplexElement->imaginary = 1;
}

int compareComplexElements(const void *firstElement, const void *secondElement) {
    Complex *firstComplexElement = (Complex *) firstElement;
    Complex *secondComplexElement = (Complex *) secondElement;
    if (firstComplexElement->real == secondComplexElement->real && firstComplexElement->imaginary == secondComplexElement->imaginary) {
        return 1;
    } else {
        return 0;
    }
}
