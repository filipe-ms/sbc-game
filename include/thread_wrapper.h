// THREAD_WRAPPER_H
#pragma once
#ifndef THREAD_WRAPPER_H
#define THREAD_WRAPPER_H

#include <stdbool.h>
#include <stddef.h>

// Defini��es de tipos independentes de windows.h
typedef void* ThreadFunc;
typedef void* ThreadParam;

// Estrutura para permitir aloca��o em stack
typedef struct Thread {
    void* handle;
    unsigned long id;
} Thread;

// API de cria��o e join
bool thread_create(Thread* t, ThreadFunc func, ThreadParam param);
void thread_join(Thread* t);
bool thread_valid(const Thread* t);

#endif // !THREAD_WRAPPER_H