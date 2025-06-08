// LIST_H
#pragma once

#include <stddef.h>
#include "Function.h"

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef void (*DataFreen)(void*);

typedef struct List {
    Node* head;
    DataFreen free_data_func;
    size_t data_size;
} List;

List* List_Create(DataFreen free_data_func);

int List_AddToEnd(List* list, void* data);
int List_Add(List* list, void* data);

int List_Remove(List* list, void* data_to_remove);

void List_FreeAll();

void* List_Pop(List* list);
void* List_GetByIndex(List* list, int index);
void List_ForEach(List* list, Function_Arg1 function_arg1);
