#pragma once


typedef struct {
    int exceptionCode;
} Exception;

typedef enum {
    NO_EXCEPTION,
    ALLOCATION_MEMORY_EXCEPTION,
    INDEX_OUT_OF_BOUND_EXCEPTION,
    INCOMPATIBLE_TYPES_EXCEPTION,
    BUFFER_OVERFLOW_EXCEPTION,
    INVALID_INPUT_EXCEPTION,
    EMPTY_INPUT_EXCEPTION,
    CONVERSATION_EXCEPTION,
    INVALID_VALUE
} ErrorCode;

int getExceptionCode();
void setExceptionCode(int code);
