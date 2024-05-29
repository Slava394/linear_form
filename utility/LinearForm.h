#pragma once
#include "FieldInfo.h"


typedef struct {
    const FieldInfo *fieldInfo;
    int size;
    void **baseDynamicArray;
} LinearForm;

void initLinearForm(int size, const FieldInfo *fieldInfo, LinearForm **linearFormPointer, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow);
void initZeroLinearForm(int size, const FieldInfo *fieldInfo, LinearForm **linearFormPointer, FILE *exceptionFlow);

void printLinearForm(const LinearForm *linearForm, FILE *outgoingFlow);

void foldLinearForms(const LinearForm *firstLinearForm, const LinearForm *secondLinearForm, LinearForm *resultLinearForm, FILE *exceptionFlow);
void multiplyLinearFormByScalar(const LinearForm *linearForm, LinearForm *resultLinearForm, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow);
void calculateValueOfLinearForm(const LinearForm *linearForm, void **resultPointer, FILE *incomingFlow, FILE *outgoingFlow, FILE *exceptionFlow);

void freeLinearForm(LinearForm *linearForm);
