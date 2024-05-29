#pragma once
#include "../utility/FieldInfo.h"


FieldInfo* getRealFieldInfo(FILE *exceptionFlow);

void inputRealElement(void *element, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow);
void printRealElement(const void *element, FILE *outgoingFlow);

void foldRealElements(const void *firstElement, const void *secondElement, void *result);
void multiplyRealElementByScalar(const void *element, const void *scalar, void *result);

void getInverseRealElementForAddition(const void *element, void *result);
void getInverseRealElementForMultiplication(const void *element, void *result, FILE *exceptionFlow);

void getNeutralRealElementForAddition(void *result);
void getNeutralRealElementForMultiplication(void *result);

int compareRealElements(const void *firstElement, const void *secondElement);
