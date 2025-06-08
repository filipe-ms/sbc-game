// GEN_LIST_H
#pragma once

#include <stddef.h>
#include "Function.h"

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
	size_t size;
	size_t data_size;
} List;

List* List_Create(size_t data_size);
int List_Add(List* list, void* data);
int List_Remove(List* list, void* data);
int List_Destroy(List* target);
int List_FreeAll(void);
void List_ForEach(List* list, Function_Arg1 function_arg1);