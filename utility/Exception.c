#include <stdlib.h>
#include <stdio.h>
#include "Exception.h"
#define exceptionStream stderr


static Exception *exception = NULL;

int getExceptionCode() {
    if (exception == NULL) {
        exception = (Exception *) malloc(sizeof(Exception));
        if (exception == NULL) {
            fprintf(exceptionStream, "Something went wrong: critical error\n");
            exit(1);
        }
        exception->exceptionCode = NO_EXCEPTION;
    }
    return exception->exceptionCode;
}

void setExceptionCode(int code) {
    if (exception == NULL) {
        exception = (Exception *) malloc(sizeof(Exception));
        if (exception == NULL) {
            fprintf(exceptionStream, "Something went wrong: critical error\n");
            exit(1);
        }
        exception->exceptionCode = NO_EXCEPTION;
    }
    exception->exceptionCode = code;
}
