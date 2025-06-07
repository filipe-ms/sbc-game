// thread_wrapper.c
#include "thread_wrapper.h"

#define WIN32_LEAN_AND_MEAN // Exclui aplicativos e APIs não essenciais de windows.h
#include <windows.h>



bool thread_create(Thread* t, ThreadFunc func, ThreadParam param) {
    if (!t) return false;
    HANDLE h = CreateThread(
        NULL, 0,
        (LPTHREAD_START_ROUTINE)func,
        (LPVOID)param,
        0, &t->id
    );
    t->handle = h;
    return h != NULL;
}

void thread_join(Thread* t) {
    if (t && t->handle) {
        WaitForSingleObject((HANDLE)t->handle, INFINITE);
        CloseHandle((HANDLE)t->handle);
        t->handle = NULL;
    }
}

bool thread_valid(const Thread* t) {
    return t && t->handle != NULL;
}