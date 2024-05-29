#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Exception.h"
#include "LinearForm.h"


int compareTypeOfLinearForms(const LinearForm *firstLinearForm, const LinearForm *secondLinearForm);


void initLinearForm(int size, const FieldInfo *fieldInfo, LinearForm **linearFormPointer, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow) {
    *linearFormPointer = (LinearForm *) malloc(sizeof(LinearForm));
    if (*linearFormPointer == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for linear form]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    (*linearFormPointer)->fieldInfo = fieldInfo;
    if (size <= 0) {
        setExceptionCode(INDEX_OUT_OF_BOUND_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for linear form type field]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        free((*linearFormPointer));
        return;
    }
    (*linearFormPointer)->size = size;
    (*linearFormPointer)->baseDynamicArray = (void **) malloc(size * sizeof(void *));
    if ((*linearFormPointer)->baseDynamicArray == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for linear form base array]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        free((*linearFormPointer));
        return;
    }
    for (int index = 0; index < size; index++) {
        (*linearFormPointer)->baseDynamicArray[index] = malloc((*linearFormPointer)->fieldInfo->elementSize);
        if ((*linearFormPointer)->baseDynamicArray[index] == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for linear form coefficient]\n");
            fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
            for (int newIndex = 0; newIndex < index; newIndex++) {
                free((*linearFormPointer)->baseDynamicArray[newIndex]);
            }
            free((*linearFormPointer)->baseDynamicArray);
            free((*linearFormPointer));
            return;
        }
        fprintf(outgoingFlow, "Enter coefficient <%d>\n", index);
        (*linearFormPointer)->fieldInfo->inputElement((*linearFormPointer)->baseDynamicArray[index], incomingFlow, outgoingFlow, exceptionFlow);
        if (getExceptionCode() != NO_EXCEPTION) {
            fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
            for (int newIndex = 0; newIndex < index + 1; newIndex++) {
                free((*linearFormPointer)->baseDynamicArray[newIndex]);
            }
            free((*linearFormPointer)->baseDynamicArray);
            free((*linearFormPointer));
            return;
        }
    }
}

void initZeroLinearForm(int size, const FieldInfo *fieldInfo, LinearForm **linearFormPointer, FILE *exceptionFlow) {
    *linearFormPointer = (LinearForm *) malloc(sizeof(LinearForm));
    if (*linearFormPointer == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for linear form]\n");
        return;
    }
    (*linearFormPointer)->fieldInfo = fieldInfo;
    if (size <= 0) {
        setExceptionCode(INDEX_OUT_OF_BOUND_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for linear form type field]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        free((*linearFormPointer));
        return;
    }
    (*linearFormPointer)->size = size;
    (*linearFormPointer)->baseDynamicArray = (void **) malloc(size * sizeof(void *));
    if ((*linearFormPointer)->baseDynamicArray == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for linear form base array]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        free((*linearFormPointer));
        return;
    }
    for (int index = 0; index < size; index++) {
        (*linearFormPointer)->baseDynamicArray[index] = malloc((*linearFormPointer)->fieldInfo->elementSize);
        if ((*linearFormPointer)->baseDynamicArray[index] == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for linear form coefficient]\n");
            fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
            for (int newIndex = 0; newIndex < index; newIndex++) {
                free((*linearFormPointer)->baseDynamicArray[newIndex]);
            }
            free((*linearFormPointer)->baseDynamicArray);
            free((*linearFormPointer));
            return;
        }
        (*linearFormPointer)->fieldInfo->getNeutralElementForAddition((*linearFormPointer)->baseDynamicArray[index]);
    }
}

void printLinearForm(const LinearForm *linearForm, FILE *outgoingFlow) {
    fprintf(outgoingFlow, "F = ");
    linearForm->fieldInfo->printElement(linearForm->baseDynamicArray[0], outgoingFlow);
    for (int index = 1; index < linearForm->size; index++) {
        fprintf(outgoingFlow, " + ");
        linearForm->fieldInfo->printElement(linearForm->baseDynamicArray[index], outgoingFlow);
        fprintf(outgoingFlow, " * X<%d>", index);
    }
    fprintf(outgoingFlow, "\n");
}

void foldLinearForms(const LinearForm *firstLinearForm, const LinearForm *secondLinearForm, LinearForm *resultLinearForm, FILE *exceptionFlow) {
    if (compareTypeOfLinearForms(firstLinearForm, secondLinearForm) != 1 || compareTypeOfLinearForms(firstLinearForm, resultLinearForm) != 1) {
        setExceptionCode(INCOMPATIBLE_TYPES_EXCEPTION);
        fprintf(exceptionFlow, "[Incompatible types of linear forms]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    int maximumSummandSize = (firstLinearForm->size > secondLinearForm->size) ? firstLinearForm->size : secondLinearForm->size;
    if (resultLinearForm->size != maximumSummandSize) {
        void **newBaseDynamicArray = (void **) malloc(maximumSummandSize * sizeof(void *));
        if (newBaseDynamicArray == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for linear form base array]\n");
            fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
            return;
        }
        for (int index = 0; index < maximumSummandSize; index++) {
            newBaseDynamicArray[index] = malloc(resultLinearForm->fieldInfo->elementSize);
            if (newBaseDynamicArray[index] == NULL) {
                setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
                fprintf(exceptionFlow, "[Memory allocation error for linear form coefficient]\n");
                fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
                for (int newIndex = 0; newIndex < index; newIndex++) {
                    free(newBaseDynamicArray[newIndex]);
                }
                free(newBaseDynamicArray);
                return;
            }
        }
        if (resultLinearForm == firstLinearForm || resultLinearForm == secondLinearForm) {
            for (int index = 0; index < resultLinearForm->size; index++) {
                memcpy(newBaseDynamicArray[index], resultLinearForm->baseDynamicArray[index], resultLinearForm->fieldInfo->elementSize);
            }
            for (int index = resultLinearForm->size; index < maximumSummandSize; index++) {
                resultLinearForm->fieldInfo->getNeutralElementForAddition(newBaseDynamicArray[index]);
            }
        } else {
            for (int index = 0; index < maximumSummandSize; index++) {
                resultLinearForm->fieldInfo->getNeutralElementForAddition(newBaseDynamicArray[index]);
            }
        }
        for (int index = 0; index < resultLinearForm->size; index++) {
            free(resultLinearForm->baseDynamicArray[index]);
        }
        free(resultLinearForm->baseDynamicArray);
        resultLinearForm->baseDynamicArray = newBaseDynamicArray;
        resultLinearForm->size = maximumSummandSize;
    }
    int minimalSummandSize = (firstLinearForm->size < secondLinearForm->size) ? firstLinearForm->size : secondLinearForm->size;
    for (int index = 0; index < minimalSummandSize; index++) {
        resultLinearForm->fieldInfo->foldElements(firstLinearForm->baseDynamicArray[index], secondLinearForm->baseDynamicArray[index], resultLinearForm->baseDynamicArray[index]);
    }
    if (firstLinearForm->size == maximumSummandSize && resultLinearForm == firstLinearForm || secondLinearForm->size == maximumSummandSize && resultLinearForm == secondLinearForm) {
        return;
    } else if (firstLinearForm->size == maximumSummandSize) {
        for (int index = minimalSummandSize; index < maximumSummandSize; index++) {
            memcpy(resultLinearForm->baseDynamicArray[index], firstLinearForm->baseDynamicArray[index], resultLinearForm->fieldInfo->elementSize);
        }
    } else {
        for (int index = minimalSummandSize; index < maximumSummandSize; index++) {
            memcpy(resultLinearForm->baseDynamicArray[index], secondLinearForm->baseDynamicArray[index], resultLinearForm->fieldInfo->elementSize);
        }
    }
}

void multiplyLinearFormByScalar(const LinearForm *linearForm, LinearForm *resultLinearForm, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow) {
    if (compareTypeOfLinearForms(linearForm, resultLinearForm) != 1) {
        setExceptionCode(INCOMPATIBLE_TYPES_EXCEPTION);
        fprintf(exceptionFlow, "[Incompatible types of linear forms]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    if (resultLinearForm->size != linearForm->size) {
        void **newBaseDynamicArray = (void **) malloc(linearForm->size * sizeof(void *));
        if (newBaseDynamicArray == NULL) {
            setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
            fprintf(exceptionFlow, "[Memory allocation error for linear form base array]\n");
            fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
            return;
        }
        for (int index = 0; index < linearForm->size; index++) {
            newBaseDynamicArray[index] = malloc(resultLinearForm->fieldInfo->elementSize);
            if (newBaseDynamicArray[index] == NULL) {
                setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
                fprintf(exceptionFlow, "[Memory allocation error for linear form coefficient]\n");
                fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
                for (int newIndex = 0; newIndex < index; newIndex++) {
                    free(newBaseDynamicArray[newIndex]);
                }
                free(newBaseDynamicArray);
                return;
            }
        }
        for (int index = 0; index < linearForm->size; index++) {
            resultLinearForm->fieldInfo->getNeutralElementForAddition(newBaseDynamicArray[index]);
        }
        for (int index = 0; index < resultLinearForm->size; index++) {
            free(resultLinearForm->baseDynamicArray[index]);
        }
        free(resultLinearForm->baseDynamicArray);
        resultLinearForm->baseDynamicArray = newBaseDynamicArray;
        resultLinearForm->size = linearForm->size;
    }
    void *scalar = malloc(linearForm->fieldInfo->elementSize);
    if (scalar == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for scalar]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    fprintf(outgoingFlow, "Enter scalar\n");
    linearForm->fieldInfo->inputElement(scalar, incomingFlow, outgoingFlow, exceptionFlow);
    if (getExceptionCode() != NO_EXCEPTION) {
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        free(scalar);
        return;
    }
    for (int index = 0; index < linearForm->size; index++) {
        resultLinearForm->fieldInfo->multiplyElementByScalar(linearForm->baseDynamicArray[index], scalar, resultLinearForm->baseDynamicArray[index]);
    }
    free(scalar);
}

void calculateValueOfLinearForm(const LinearForm *linearForm, void **resultPointer, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow) {
    *resultPointer = malloc(linearForm->fieldInfo->elementSize);
    if (*resultPointer == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for result]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        return;
    }
    linearForm->fieldInfo->getNeutralElementForAddition(*resultPointer);
    void *intermediateResult = malloc(linearForm->fieldInfo->elementSize);
    if (intermediateResult == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for intermediate result]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        free(*resultPointer);
        return;
    }
    void *inputElement = malloc(linearForm->fieldInfo->elementSize);
    if (inputElement == NULL) {
        setExceptionCode(ALLOCATION_MEMORY_EXCEPTION);
        fprintf(exceptionFlow, "[Memory allocation error for input element]\n");
        fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
        free(*resultPointer);
        free(intermediateResult);
        return;
    }
    linearForm->fieldInfo->foldElements(*resultPointer, linearForm->baseDynamicArray[0], *resultPointer);
    for (int index = 1; index < linearForm->size; index++) {
        void *currentCoefficient = linearForm->baseDynamicArray[index];
        fprintf(outgoingFlow, "Enter unknown <%d>\n", index);
        linearForm->fieldInfo->inputElement(inputElement, incomingFlow, outgoingFlow, exceptionFlow);
        if (getExceptionCode() != NO_EXCEPTION) {
            fprintf(exceptionFlow, "[function:%s|file:%s]\n", __func__, __FILE__);
            free(*resultPointer);
            free(intermediateResult);
            free(inputElement);
            return;
        }
        linearForm->fieldInfo->multiplyElementByScalar(currentCoefficient, inputElement, intermediateResult);
        linearForm->fieldInfo->foldElements(*resultPointer, intermediateResult, *resultPointer);
    }
    free(intermediateResult);
    free(inputElement);
}

void freeLinearForm(LinearForm *linearForm) {
    for (int index = 0; index < linearForm->size; index++) {
        free(linearForm->baseDynamicArray[index]);
    }
    free(linearForm->baseDynamicArray);
    free(linearForm);
}

int compareTypeOfLinearForms(const LinearForm *firstLinearForm, const LinearForm *secondLinearForm) {
    if (firstLinearForm->fieldInfo == secondLinearForm->fieldInfo) {
        return 1;
    } else {
        return 0;
    }
}
