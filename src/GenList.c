// GEN_LIST_C
#include "GenList.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <Function.h>

typedef struct ListInfo{
	List* list;
    struct ListInfo* next;
} ListInfo;

ListInfo* lists = NULL;

List* List_Create(size_t data_size) {
	List* list = (List*)malloc(sizeof(List));
	if (!list) return NULL;

	if (list) {
		list->head = NULL;
		list->tail = NULL;
		list->size = 0;
		list->data_size = data_size;
	}

	ListInfo* new_info = (ListInfo*)malloc(sizeof(ListInfo));
	if (new_info) {
		new_info->list = list;
		new_info->next = lists;
		lists = new_info;
	}

	return list;
}
int List_Add(List* list, void* data) {
    if (!list || !data) return 0;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return 0;

    new_node->data = malloc(list->data_size);
    if (!new_node->data) {
        free(new_node);
        return 0;
    }

    memcpy(new_node->data, data, list->data_size);
    new_node->next = NULL;

    if (list->tail) list->tail->next = new_node;
    else list->head = new_node;
    list->tail = new_node;
    list->size++;
    return 1;
}
int List_Remove(List* list, void* data) {
    if (!list || !data || list->size == 0) return 0;

    Node* current = list->head;
    Node* previous = NULL;

    while (current) {
        if (memcmp(current->data, data, list->data_size) == 0) {
            
            if (previous) previous->next = current->next;
            else list->head = current->next;

            if (current == list->tail) list->tail = previous;

            free(current->data);
            free(current);
            list->size--;
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}
int List_Destroy(List* target) {
	if (!target) return 0;

	Node* current = target->head;
	while (current) {
		Node* next = current->next;
		free(current->data);
		free(current);
		current = next;
	}

	ListInfo* current_info = lists;
	ListInfo* previous_info = NULL;

	while (current_info) {
		if (current_info->list == target) {
			if (previous_info)
				previous_info->next = current_info->next;
			else
				lists = current_info->next;
			free(current_info);
			break;
		}
		previous_info = current_info;
		current_info = current_info->next;
	}

	free(target);
	return 1;
}
int List_FreeAll() {
	ListInfo* current_info = lists;
	while (current_info) {
		List* list = current_info->list;
		Node* current_node = list->head;
		while (current_node) {
			Node* next_node = current_node->next;
			free(current_node->data);
			free(current_node);
			current_node = next_node;
		}
		free(list);
		ListInfo* next_info = current_info->next;
		free(current_info);
		current_info = next_info;
	}
	lists = NULL;
	return 1;
}

void List_ForEach(List* list, Function_Arg1 function_arg1) {
	if (!list || !function_arg1) return;
	Node* current = list->head;
	while (current) {
		function_arg1(current->data);
		current = current->next;
	}
}

void* List_Get(List* list, size_t index) {
    if (!list || index >= list->size) return NULL;

    Node* current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current ? current->data : NULL;
}