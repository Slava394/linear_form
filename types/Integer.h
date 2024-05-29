#pragma once
#include "../utility/FieldInfo.h"


FieldInfo* getIntegerFieldInfo(FILE *exceptionFlow);

void inputIntegerElement(void *element, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow);
void printIntegerElement(const void *element, FILE *outgoingFlow);

void foldIntegerElements(const void *firstElement, const void *secondElement, void *result);
void multiplyIntegerElementByScalar(const void *element, const void *scalar, void *result);

void getInverseIntegerElementForAddition(const void *element, void *result);
void getInverseIntegerElementForMultiplication(const void *element, void *result, FILE *exceptionFlow);

void getNeutralIntegerElementForAddition(void *result);
void getNeutralIntegerElementForMultiplication(void *result);

int compareIntegerElements(const void *firstElement, const void *secondElement);
