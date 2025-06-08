#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>  // For memcmp in generic comparison

#ifndef ERROR
#define ERROR -1
#endif

// Macro to create a type-specific list
#define CREATE_LIST(T) \
\
typedef struct List_Node_##T { \
    T data; \
    struct List_Node_##T* next; \
} List_Node_##T; \
\
typedef struct List_##T { \
    List_Node_##T* head; \
    List_Node_##T* tail; \
    size_t count; \
} List_##T; \
\
/* Function declarations */ \
List_##T* List_Create_##T(); \
int List_Add_##T(List_##T* list, T data); \
int List_AddToEnd_##T(List_##T* list, T data); \
T* List_GetByIndex_##T(List_##T* list, int index); \
int List_Remove_##T(List_##T* list, T data, int (*compare)(const T*, const T*)); \
void List_Destroy_##T(List_##T* list); \
\
/* Function implementations */ \
List_##T* List_Create_##T() { \
    List_##T* list = (List_##T*)malloc(sizeof(List_##T)); \
    if (!list) return NULL; \
    list->head = list->tail = NULL; \
    list->count = 0; \
    return list; \
} \
\
int List_Add_##T(List_##T* list, T data) { \
    if (!list) return ERROR; \
    List_Node_##T* node = (List_Node_##T*)malloc(sizeof(List_Node_##T)); \
    if (!node) return ERROR; \
    node->data = data; \
    node->next = list->head; \
    list->head = node; \
    if (!list->tail) list->tail = node; \
    list->count++; \
    return 0; \
} \
\
int List_AddToEnd_##T(List_##T* list, T data) { \
    if (!list) return ERROR; \
    List_Node_##T* node = (List_Node_##T*)malloc(sizeof(List_Node_##T)); \
    if (!node) return ERROR; \
    node->data = data; \
    node->next = NULL; \
    if (!list->head) { \
        list->head = list->tail = node; \
    } else { \
        list->tail->next = node; \
        list->tail = node; \
    } \
    list->count++; \
    return 0; \
} \
\
T* List_GetByIndex_##T(List_##T* list, int index) { \
    if (!list || index < 0 || (size_t)index >= list->count) return NULL; \
    List_Node_##T* current = list->head; \
    for (int i = 0; i < index && current; i++) { \
        current = current->next; \
    } \
    return current ? &(current->data) : NULL; \
} \
\
int List_Remove_##T(List_##T* list, T data, int (*compare)(const T*, const T*)) { \
    if (!list || !list->head) return ERROR; \
    List_Node_##T* prev = NULL; \
    List_Node_##T* current = list->head; \
    while (current) { \
        if (compare ? compare(&current->data, &data) : memcmp(&current->data, &data, sizeof(T)) == 0) { \
            if (prev) { \
                prev->next = current->next; \
            } else { \
                list->head = current->next; \
            } \
            if (current == list->tail) { \
                list->tail = prev; \
            } \
            free(current); \
            list->count--; \
            return 0; \
        } \
        prev = current; \
        current = current->next; \
    } \
    return ERROR; \
} \
\
void List_Destroy_##T(List_##T* list) { \
    if (!list) return; \
    List_Node_##T* current = list->head; \
    while (current) { \
        List_Node_##T* next = current->next; \
        free(current); \
        current = next; \
    } \
    free(list); \
}