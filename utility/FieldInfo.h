#pragma once
#include <stdio.h>


typedef struct {
    int elementSize;

    void (*inputElement)(void *element, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow);
    void (*printElement)(const void *element, FILE *outgoingFlow);

    void (*foldElements)(const void *firstElement, const void *secondElement, void *result);
    void (*multiplyElementByScalar)(const void *element, const void *scalar, void *result);

    void (*getInverseElementForAddition)(const void *element, void *result);
    void (*getInverseElementForMultiplication)(const void *element, void *result, FILE *exceptionFlow);

    void (*getNeutralElementForAddition)(void *result);
    void (*getNeutralElementForMultiplication)(void *result);

    int (*compareElements)(const void *firstElement, const void *secondElement);
} FieldInfo;
