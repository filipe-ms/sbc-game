// REQUEST_THREAD_H
/*
#pragma once
#ifndef REQUEST_THREAD_H
#define REQUEST_THREAD_H

#include <stdbool.h>

typedef struct {
    char* prompt;
    char* response;
    int unit_id;
    volatile bool finished;
} RequestData;

typedef void* (*ThreadRoutine)(void*);
void* request_thread_func(void* param);

#endif // REQUEST_THREAD_H
*/