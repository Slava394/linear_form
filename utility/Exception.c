#include <stdlib.h>
#include <stdio.h>
#include "Exception.h"
#define exceptionStream stderr


static Exception *EXCEPTION = NULL;

int getExceptionCode() {
    if (EXCEPTION == NULL) {
        EXCEPTION = (Exception *) malloc(sizeof(Exception));
        if (EXCEPTION == NULL) {
            fprintf(exceptionStream, "Something went wrong: critical error\n");
            exit(1);
        }
        EXCEPTION->exceptionCode = NO_EXCEPTION;
    }
    return EXCEPTION->exceptionCode;
}

void setExceptionCode(int code) {
    if (EXCEPTION == NULL) {
        EXCEPTION = (Exception *) malloc(sizeof(Exception));
        if (EXCEPTION == NULL) {
            fprintf(exceptionStream, "Something went wrong: critical error\n");
            exit(1);
        }
        EXCEPTION->exceptionCode = NO_EXCEPTION;
    }
    EXCEPTION->exceptionCode = code;
}
