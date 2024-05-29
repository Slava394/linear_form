#pragma once
#include "../utility/FieldInfo.h"


typedef struct {
    long real;
    long imaginary;
} Complex;

FieldInfo* getComplexFieldInfo(FILE *exceptionFlow);

void inputComplexElement(void *element, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow);
void printComplexElement(const void *element, FILE *outgoingFlow);

void foldComplexElements(const void *firstElement, const void *secondElement, void *result);
void multiplyComplexElementByScalar(const void *element, const void *scalar, void *result);

void getInverseComplexElementForAddition(const void *element, void *result);
void getInverseComplexElementForMultiplication(const void *element, void *result, FILE *exceptionFlow);

void getNeutralComplexElementForAddition(void *result);
void getNeutralComplexElementForMultiplication(void *result);

int compareComplexElements(const void *firstElement, const void *secondElement);
