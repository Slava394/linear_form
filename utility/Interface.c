#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include "Interface.h"
#include "Exception.h"
#define inputStream stdin
#define outputStream stdout
#define developerExceptionStream stderr
#define bufferSize 26


void inputLongElementForMenu(long *element, FILE *incomingFlow, FILE *exceptionFlow);

void enablingStacktrace(FILE **exceptionStream, long *userChoice, int *exceptionCount);

void selectionOfTheNumberOfLinearForms(FILE *exceptionStream, long *userChoice, int *exceptionCount, long *sizeOfLinearFormArray);

void menu() {
    FILE *exceptionStream = tmpfile();
    if (exceptionStream == NULL) {
        fprintf(outputStream, "Something went wrong: critical error\n");
        exit(1);
    }
    long userChoice;
    int exceptionCount = 0;
    long sizeOfLinearFormArray;
    fprintf(outputStream, "Do you want to see enablingStacktrace? ('1' = Yes, '2' = No)\n");
    enablingStacktrace(&exceptionStream, &userChoice, &exceptionCount);
    fprintf(outputStream, "Hello, user\n");
    fprintf(outputStream, "Select the number of linear forms from 1 to 100:\n");
    selectionOfTheNumberOfLinearForms(exceptionStream, &userChoice, &exceptionCount, &sizeOfLinearFormArray);
    LinearForm **linearFormArray = (LinearForm **) malloc(sizeOfLinearFormArray * sizeof(LinearForm *));
    if (linearFormArray == NULL) {
        fprintf(outputStream, "Something went wrong: critical error\n");
        exit(1);
    }
    long currentIndex = 0;
    long inputMethod;
    long sizeOfLinearForm;
    long typeOfLinearForm;
    long leftBorder;
    long rightBorder;
    while (1) {
        leftBorder = 1;
        rightBorder = 2;
        while (1) {
            fprintf(outputStream, "Enter '1' to create a linear form <%li> as form with integer coefficients, '2' - with real, '3' - with complex:\n", currentIndex + 1);
            inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
            if (getExceptionCode() != NO_EXCEPTION || userChoice < leftBorder || userChoice > rightBorder) {
                exceptionCount++;
                if (exceptionCount > 4) {
                    for (int index = 0; index < (int) currentIndex; index++) {
                        freeLinearForm(linearFormArray[index]);
                    }
                    free(linearFormArray);
                    fprintf(outputStream, "Too many tries\n");
                    exit(1);
                }
                setExceptionCode(NO_EXCEPTION);
                fprintf(outputStream, "Something went wrong, try again\n");
                continue;
            }
            break;
        }
        typeOfLinearForm = userChoice;
        exceptionCount = 0;
        fprintf(outputStream, "Enter size of linear form <%li> (from 1 to 20):\n", currentIndex + 1);
        while (1) {
            inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
            if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > 20) {
                exceptionCount++;
                if (exceptionCount > 4) {
                    for (int index = 0; index < (int) currentIndex; index++) {
                        freeLinearForm(linearFormArray[index]);
                    }
                    free(linearFormArray);
                    fprintf(outputStream, "Too many tries\n");
                    exit(1);
                }
                setExceptionCode(NO_EXCEPTION);
                fprintf(outputStream, "Something went wrong, try again\n");
                continue;
            }
            sizeOfLinearForm = userChoice;
            exceptionCount = 0;
            break;
        }
        fprintf(outputStream, "Enter '1' to fill linear form <%li> manually and '2' to initialize it as empty linear form:\n", currentIndex + 1);
        while (1) {
            inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
            if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > 3) {
                exceptionCount++;
                if (exceptionCount > 4) {
                    for (int index = 0; index < (int) currentIndex; index++) {
                        freeLinearForm(linearFormArray[index]);
                    }
                    free(linearFormArray);
                    fprintf(outputStream, "Too many tries\n");
                    exit(1);
                }
                setExceptionCode(NO_EXCEPTION);
                fprintf(outputStream, "Something went wrong, try again\n");
                continue;
            }
            inputMethod = userChoice;
            exceptionCount = 0;
            break;
        }
        while (1) {
            switch (typeOfLinearForm) {
                case 1:
                    if (inputMethod == 1) {
                        fprintf(outputStream, "Enter linear form\n");
                        initLinearForm((int) sizeOfLinearForm, getIntegerFieldInfo(exceptionStream), &linearFormArray[currentIndex], inputStream, outputStream, exceptionStream);
                    } else {
                        initZeroLinearForm((int) sizeOfLinearForm, getIntegerFieldInfo(exceptionStream), &linearFormArray[currentIndex], exceptionStream);
                    }
                    if (getExceptionCode() != NO_EXCEPTION) {
                        exceptionCount++;
                        if (exceptionCount > 4) {
                            for (int index = 0; index < (int) currentIndex; index++) {
                                freeLinearForm(linearFormArray[index]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Too many tries\n");
                            exit(1);
                        }
                        setExceptionCode(NO_EXCEPTION);
                        fprintf(outputStream, "Something went wrong, try again\n");
                        continue;
                    }
                    break;
                case 2:
                    if (inputMethod == 1) {
                        fprintf(outputStream, "Enter linear form\n");
                        initLinearForm((int) sizeOfLinearForm, getRealFieldInfo(exceptionStream), &linearFormArray[currentIndex], inputStream, outputStream, exceptionStream);
                    } else {
                        initZeroLinearForm((int) sizeOfLinearForm, getRealFieldInfo(exceptionStream), &linearFormArray[currentIndex], exceptionStream);
                    }
                    if (getExceptionCode() != NO_EXCEPTION) {
                        exceptionCount++;
                        if (exceptionCount > 4) {
                            for (int index = 0; index < (int) currentIndex; index++) {
                                freeLinearForm(linearFormArray[index]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Too many tries\n");
                            exit(1);
                        }
                        setExceptionCode(NO_EXCEPTION);
                        fprintf(outputStream, "Something went wrong, try again\n");
                        continue;
                    }
                    break;
                case 3:
                    if (inputMethod == 1) {
                        fprintf(outputStream, "Enter linear form\n");
                        initLinearForm((int) sizeOfLinearForm, getComplexFieldInfo(exceptionStream), &linearFormArray[currentIndex], inputStream, outputStream, exceptionStream);
                    } else {
                        initZeroLinearForm((int) sizeOfLinearForm, getComplexFieldInfo(exceptionStream), &linearFormArray[currentIndex], exceptionStream);
                    }
                    if (getExceptionCode() != NO_EXCEPTION) {
                        exceptionCount++;
                        if (exceptionCount > 4) {
                            for (int index = 0; index < (int) currentIndex; index++) {
                                freeLinearForm(linearFormArray[index]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Too many tries\n");
                            exit(1);
                        }
                        setExceptionCode(NO_EXCEPTION);
                        fprintf(outputStream, "Something went wrong, try again\n");
                        continue;
                    }
                    break;
                default:
                    for (int index = 0; index < (int) currentIndex; index++) {
                        freeLinearForm(linearFormArray[index]);
                    }
                    free(linearFormArray);
                    fprintf(outputStream, "Something went wrong: critical error\n");
                    exit(1);
            }
            exceptionCount = 0;
            break;
        }
        currentIndex++;
        if (currentIndex == (int) sizeOfLinearFormArray) {
            break;
        }
    }
    long i, j, k;
    fprintf(outputStream, "----------------------------------\n");
    for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
        if (linearFormArray[index]->fieldInfo == getIntegerFieldInfo(exceptionStream)) {
            fprintf(outputStream, "<%d> [Integer] ", index + 1);
        } else if (linearFormArray[index]->fieldInfo == getRealFieldInfo(exceptionStream)) {
            fprintf(outputStream, "<%d> [Real] ", index + 1);
        } else if (linearFormArray[index]->fieldInfo == getComplexFieldInfo(exceptionStream)) {
            fprintf(outputStream, "<%d> [Complex] ", index + 1);
        } else {
            for (int newIndex = 0; newIndex < (int) sizeOfLinearFormArray; newIndex++) {
                freeLinearForm(linearFormArray[newIndex]);
            }
            free(linearFormArray);
            fprintf(outputStream, "Something went wrong: critical error\n");
            exit(1);
        }
        printLinearForm(linearFormArray[index], outputStream);
    }
    fprintf(outputStream, "----------------------------------\n");
    fprintf(outputStream, "Enter the command number for further actions:\n");
    while (1) {
        fprintf(outputStream, "'1': add form i to j and save as k (if the same type of each form)\n");
        fprintf(outputStream, "'2': subtract form i from j and as form k (if the same type of each form)\n");
        fprintf(outputStream, "'3': multiply form i by field element\n");
        fprintf(outputStream, "'4': calculate value of form i\n");
        fprintf(outputStream, "'5': complete the program\n");
        fprintf(outputStream, "You choose:\n");
        inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
        if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > 5) {
            exceptionCount++;
            if (exceptionCount > 4) {
                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                    freeLinearForm(linearFormArray[index]);
                }
                free(linearFormArray);
                fprintf(outputStream, "Too many tries\n");
                exit(1);
            }
            setExceptionCode(NO_EXCEPTION);
            fprintf(outputStream, "Something went wrong, try again\n");
            continue;
        }
        exceptionCount = 0;
        switch (userChoice) {
            case 1:
                fprintf(outputStream, "Input number of the first term:\n");
                while (1) {
                    inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                    if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                        exceptionCount++;
                        if (exceptionCount > 4) {
                            for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                freeLinearForm(linearFormArray[index]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Too many tries\n");
                            exit(1);
                        }
                        setExceptionCode(NO_EXCEPTION);
                        fprintf(outputStream, "Something went wrong, try again\n");
                        continue;
                    }
                    i = userChoice;
                    exceptionCount = 0;
                    fprintf(outputStream, "Input number of the second term:\n");
                    while (1) {
                        inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                        if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                            exceptionCount++;
                            if (exceptionCount > 4) {
                                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                    freeLinearForm(linearFormArray[index]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Too many tries\n");
                                exit(1);
                            }
                            setExceptionCode(NO_EXCEPTION);
                            fprintf(outputStream, "Something went wrong, try again\n");
                            continue;
                        }
                        j = userChoice;
                        exceptionCount = 0;
                        break;
                    }
                    fprintf(outputStream, "Enter the number of the form in which to save the result:\n");
                    while (1) {
                        inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                        if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                            exceptionCount++;
                            if (exceptionCount > 4) {
                                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                    freeLinearForm(linearFormArray[index]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Too many tries\n");
                                exit(1);
                            }
                            setExceptionCode(NO_EXCEPTION);
                            fprintf(outputStream, "Something went wrong, try again\n");
                            continue;
                        }
                        k = userChoice;
                        exceptionCount = 0;
                        break;
                    }
                    foldLinearForms(linearFormArray[i-1], linearFormArray[j-1], linearFormArray[k-1], exceptionStream);
                    if (getExceptionCode() != NO_EXCEPTION) {
                        if (getExceptionCode() == INCOMPATIBLE_TYPES_EXCEPTION) {
                            fprintf(outputStream, "The result form and the folded forms must be of the same type\n");
                        } else if (getExceptionCode() == ALLOCATION_MEMORY_EXCEPTION) {
                            fprintf(outputStream, "System error, try again\n");
                        }
                        setExceptionCode(NO_EXCEPTION);
                    }
                    fprintf(outputStream, "----------------------------------\n");
                    fprintf(outputStream, "Linear forms:\n");
                    for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                        if (linearFormArray[index]->fieldInfo == getIntegerFieldInfo(exceptionStream)) {
                            fprintf(outputStream, "<%d> [Integer] ", index + 1);
                        } else if (linearFormArray[index]->fieldInfo == getRealFieldInfo(exceptionStream)) {
                            fprintf(outputStream, "<%d> [Real] ", index + 1);
                        } else if (linearFormArray[index]->fieldInfo == getComplexFieldInfo(exceptionStream)) {
                            fprintf(outputStream, "<%d> [Complex] ", index + 1);
                        } else {
                            for (int newIndex = 0; newIndex < (int) sizeOfLinearFormArray; newIndex++) {
                                freeLinearForm(linearFormArray[newIndex]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Something went wrong: critical error\n");
                            exit(1);
                        }
                        printLinearForm(linearFormArray[index], outputStream);
                    }
                    fprintf(outputStream, "----------------------------------\n");
                    break;
                }
                continue;
            case 2:
                fprintf(outputStream, "Input number of the minuend:\n");
                while (1) {
                    inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                    if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                        exceptionCount++;
                        if (exceptionCount > 4) {
                            for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                freeLinearForm(linearFormArray[index]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Too many tries\n");
                            exit(1);
                        }
                        setExceptionCode(NO_EXCEPTION);
                        fprintf(outputStream, "Something went wrong, try again\n");
                        continue;
                    }
                    i = userChoice;
                    exceptionCount = 0;
                    fprintf(outputStream, "Input number of the subtrahend:\n");
                    while (1) {
                        inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                        if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                            exceptionCount++;
                            if (exceptionCount > 4) {
                                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                    freeLinearForm(linearFormArray[index]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Too many tries\n");
                                exit(1);
                            }
                            setExceptionCode(NO_EXCEPTION);
                            fprintf(outputStream, "Something went wrong, try again\n");
                            continue;
                        }
                        j = userChoice;
                        exceptionCount = 0;
                        break;
                    }
                    fprintf(outputStream, "Enter the number of the form in which to save the result:\n");
                    while (1) {
                        inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                        if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                            exceptionCount++;
                            if (exceptionCount > 4) {
                                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                    freeLinearForm(linearFormArray[index]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Too many tries\n");
                                exit(1);
                            }
                            setExceptionCode(NO_EXCEPTION);
                            fprintf(outputStream, "Something went wrong, try again\n");
                            continue;
                        }
                        k = userChoice;
                        exceptionCount = 0;
                        break;
                    }
                    FILE *systemConstants = fopen("../utility/systemConstants.txt", "r");
                    if (systemConstants == NULL) {
                        fprintf(outputStream, "System error, try again\n");
                        break;
                    }
                    FILE *trashHolder = tmpfile();
                    if (trashHolder == NULL) {
                        fprintf(outputStream, "System error, try again\n");
                        fclose(systemConstants);
                        break;
                    }
                    multiplyLinearFormByScalar(linearFormArray[j-1], linearFormArray[j-1], systemConstants, trashHolder, exceptionStream);
                    foldLinearForms(linearFormArray[i-1], linearFormArray[j-1], linearFormArray[k-1], exceptionStream);
                    multiplyLinearFormByScalar(linearFormArray[j-1], linearFormArray[j-1], systemConstants, trashHolder, exceptionStream);
                    if (getExceptionCode() != NO_EXCEPTION) {
                        if (getExceptionCode() == INCOMPATIBLE_TYPES_EXCEPTION) {
                            fprintf(outputStream, "The result form and the folded forms must be of the same type\n");
                        } else if (getExceptionCode() == ALLOCATION_MEMORY_EXCEPTION) {
                            fprintf(outputStream, "System error, try again\n");
                        }
                        setExceptionCode(NO_EXCEPTION);
                    }
                    fclose(systemConstants);
                    fclose(trashHolder);
                    fprintf(outputStream, "----------------------------------\n");
                    fprintf(outputStream, "Linear forms:\n");
                    for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                        if (linearFormArray[index]->fieldInfo == getIntegerFieldInfo(exceptionStream)) {
                            fprintf(outputStream, "<%d> [Integer] ", index + 1);
                        } else if (linearFormArray[index]->fieldInfo == getRealFieldInfo(exceptionStream)) {
                            fprintf(outputStream, "<%d> [Real] ", index + 1);
                        } else if (linearFormArray[index]->fieldInfo == getComplexFieldInfo(exceptionStream)) {
                            fprintf(outputStream, "<%d> [Complex] ", index + 1);
                        } else {
                            for (int newIndex = 0; newIndex < (int) sizeOfLinearFormArray; newIndex++) {
                                freeLinearForm(linearFormArray[newIndex]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Something went wrong: critical error\n");
                            exit(1);
                        }
                        printLinearForm(linearFormArray[index], outputStream);
                    }
                    fprintf(outputStream, "----------------------------------\n");
                    break;
                }
                continue;
            case 3:
                fprintf(outputStream, "Enter the number of the form to be multiplied:\n");
                while (1) {
                    inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                    if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                        exceptionCount++;
                        if (exceptionCount > 4) {
                            for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                freeLinearForm(linearFormArray[index]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Too many tries\n");
                            exit(1);
                        }
                        setExceptionCode(NO_EXCEPTION);
                        fprintf(outputStream, "Something went wrong, try again\n");
                        continue;
                    }
                    i = userChoice;
                    exceptionCount = 0;
                    while (1) {
                        multiplyLinearFormByScalar(linearFormArray[i - 1], linearFormArray[i - 1], inputStream, outputStream, exceptionStream);
                        if (getExceptionCode() != NO_EXCEPTION) {
                            exceptionCount++;
                            if (exceptionCount > 4) {
                                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                    freeLinearForm(linearFormArray[index]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Too many tries\n");
                                exit(1);
                            }
                            setExceptionCode(NO_EXCEPTION);
                            fprintf(outputStream, "Something went wrong, try again\n");
                            continue;
                        }
                        exceptionCount = 0;
                        fprintf(outputStream, "----------------------------------\n");
                        fprintf(outputStream, "Linear forms:\n");
                        for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                            if (linearFormArray[index]->fieldInfo == getIntegerFieldInfo(exceptionStream)) {
                                fprintf(outputStream, "<%d> [Integer] ", index + 1);
                            } else if (linearFormArray[index]->fieldInfo == getRealFieldInfo(exceptionStream)) {
                                fprintf(outputStream, "<%d> [Real] ", index + 1);
                            } else if (linearFormArray[index]->fieldInfo == getComplexFieldInfo(exceptionStream)) {
                                fprintf(outputStream, "<%d> [Complex] ", index + 1);
                            } else {
                                for (int newIndex = 0; newIndex < (int) sizeOfLinearFormArray; newIndex++) {
                                    freeLinearForm(linearFormArray[newIndex]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Something went wrong: critical error\n");
                                exit(1);
                            }
                            printLinearForm(linearFormArray[index], outputStream);
                        }
                        fprintf(outputStream, "----------------------------------\n");
                        break;
                    }
                    break;
                }
                continue;
            case 4:
                fprintf(outputStream, "Enter the number of the form you want to calculate:\n");
                while (1) {
                    inputLongElementForMenu(&userChoice, inputStream, exceptionStream);
                    if (getExceptionCode() != NO_EXCEPTION || userChoice < 1 || userChoice > sizeOfLinearFormArray) {
                        exceptionCount++;
                        if (exceptionCount > 4) {
                            for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                freeLinearForm(linearFormArray[index]);
                            }
                            free(linearFormArray);
                            fprintf(outputStream, "Too many tries\n");
                            exit(1);
                        }
                        setExceptionCode(NO_EXCEPTION);
                        fprintf(outputStream, "Something went wrong, try again\n");
                        continue;
                    }
                    i = userChoice;
                    exceptionCount = 0;
                    void *resultOfCalculation = malloc(linearFormArray[i-1]->fieldInfo->elementSize);
                    if (resultOfCalculation == NULL) {
                        fprintf(outputStream, "System error, try again\n");
                        break;
                    }
                    while (1) {
                        calculateValueOfLinearForm(linearFormArray[i-1], &resultOfCalculation, inputStream, outputStream, exceptionStream);
                        if (getExceptionCode() != NO_EXCEPTION) {
                            exceptionCount++;
                            if (exceptionCount > 4) {
                                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                                    freeLinearForm(linearFormArray[index]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Too many tries\n");
                                exit(1);
                            }
                            setExceptionCode(NO_EXCEPTION);
                            fprintf(outputStream, "Something went wrong, try again\n");
                            continue;
                        }
                        exceptionCount = 0;
                        fprintf(outputStream, "----------------------------------\n");
                        fprintf(outputStream, "Result of form <%li> = ", i-1);
                        linearFormArray[i-1]->fieldInfo->printElement(resultOfCalculation, outputStream);
                        fprintf(outputStream, "\n");
                        free(resultOfCalculation);
                        fprintf(outputStream, "----------------------------------\n");
                        fprintf(outputStream, "Linear forms:\n");
                        for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                            if (linearFormArray[index]->fieldInfo == getIntegerFieldInfo(exceptionStream)) {
                                fprintf(outputStream, "<%d> [Integer] ", index + 1);
                            } else if (linearFormArray[index]->fieldInfo == getRealFieldInfo(exceptionStream)) {
                                fprintf(outputStream, "<%d> [Real] ", index + 1);
                            } else if (linearFormArray[index]->fieldInfo == getComplexFieldInfo(exceptionStream)) {
                                fprintf(outputStream, "<%d> [Complex] ", index + 1);
                            } else {
                                for (int newIndex = 0; newIndex < (int) sizeOfLinearFormArray; newIndex++) {
                                    freeLinearForm(linearFormArray[newIndex]);
                                }
                                free(linearFormArray);
                                fprintf(outputStream, "Something went wrong: critical error\n");
                                exit(1);
                            }
                            printLinearForm(linearFormArray[index], outputStream);
                        }
                        fprintf(outputStream, "----------------------------------\n");
                        break;
                    }
                    break;
                }
                continue;
            case 5:
                fprintf(outputStream, "Goodbye, see you soon\n");
                break;
            default:
                for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
                    freeLinearForm(linearFormArray[index]);
                }
                free(linearFormArray);
                fprintf(outputStream, "Something went wrong: critical error\n");
                exit(1);
        }
        break;
    }
    if (exceptionStream != developerExceptionStream) {
        free(exceptionStream);
    }
    for (int index = 0; index < (int) sizeOfLinearFormArray; index++) {
        freeLinearForm(linearFormArray[index]);
    }
    free(linearFormArray);
}

void selectionOfTheNumberOfLinearForms(FILE *exceptionStream, long *userChoice, int *exceptionCount, long *sizeOfLinearFormArray) {
    while (1) {
        inputLongElementForMenu(userChoice, inputStream, exceptionStream);
        if (getExceptionCode() != NO_EXCEPTION || (*userChoice) < 1 || (*userChoice) > 100) {
            (*exceptionCount)++;
            if ((*exceptionCount) > 4) {
                fprintf(outputStream, "Too many tries\n");
                exit(1);
            }
            setExceptionCode(NO_EXCEPTION);
            fprintf(outputStream, "Something went wrong, try again\n");
            continue;
        }
        (*sizeOfLinearFormArray) = (*userChoice);
        (*exceptionCount) = 0;
        break;
    }
}

void enablingStacktrace(FILE **exceptionStream, long *userChoice, int *exceptionCount) {
    while (1) {
        inputLongElementForMenu(userChoice, inputStream, (*exceptionStream));
        if (getExceptionCode() != NO_EXCEPTION || (*userChoice) < 1 || (*userChoice) > 2) {
            (*exceptionCount)++;
            if ((*exceptionCount) > 4) {
                fprintf(outputStream, "Too many tries\n");
                exit(1);
            }
            setExceptionCode(NO_EXCEPTION);
            fprintf(outputStream, "Something went wrong, try again\n");
            continue;
        }
        if ((*userChoice) == 1) {
            fclose((*exceptionStream));
            (*exceptionStream) = developerExceptionStream;
        }
        (*exceptionCount) = 0;
        break;
    }
}

void inputLongElementForMenu(long *element, FILE *incomingFlow, FILE *exceptionFlow) {
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
