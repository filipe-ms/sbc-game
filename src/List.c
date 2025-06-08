// LIST_C
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

#include "Function.h"


// Lista geral que inclui as demais para facilitar o free no final.

static List* g_all_lists = NULL;

List* List_Create(DataFreen free_data_func) {
    // Se a lista de gerenciamento ainda não existe, crie-a.
    // Ela não precisa de uma função de free para seus dados (que são outras listas),
    // pois free_all_lists tem uma lógica customizada para isso.
    if (g_all_lists == NULL) {
        // A lista de gerenciamento não precisa de um free_data_func,
        // pois a limpeza é feita manualmente em free_all_lists.
        g_all_lists = (List*)malloc(sizeof(List));
        if (g_all_lists == NULL) {
            perror("Falha ao alocar a lista de gerenciamento global");
            return NULL;
        }
        g_all_lists->head = NULL;
        g_all_lists->free_data_func = NULL; 
    }

    // Cria a nova lista para o usuário.
    List* new_list = (List*)malloc(sizeof(List));
    if (new_list == NULL) {
        perror("Falha ao alocar a nova lista");
        return NULL;
    }
    new_list->head = NULL;
    // Armazena a função de limpeza fornecida pelo usuário.
    new_list->free_data_func = free_data_func;

    // Adiciona a nova lista à lista de gerenciamento.
    if (List_AddToEnd(g_all_lists, new_list) != 0) {
        free(new_list);
        return NULL;
    }

    return new_list;
}

int List_AddToEnd(List* list, void* data) {
    if (list == NULL) return -1;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Falha ao alocar o novo nó");
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return 0;
}

void List_FreeAll() {
    if (g_all_lists == NULL) return;

    Node* manager_current = g_all_lists->head;
    while (manager_current != NULL) {
        List* user_list = (List*)manager_current->data;

        if (user_list != NULL) {
            Node* user_current = user_list->head;
            while (user_current != NULL) {
                Node* next_user_node = user_current->next;

                // *** NOVA LÓGICA DE LIMPEZA ***
                // Se uma função de limpeza de dados foi fornecida...
                if (user_list->free_data_func != NULL) {
                    // ...chame-a para liberar a memória dos dados.
                    user_list->free_data_func(user_current->data);
                }

                // Libera o nó da lista em si.
                free(user_current);
                user_current = next_user_node;
            }
            // Libera a estrutura da lista do usuário.
            free(user_list);
        }
        manager_current = manager_current->next;
    }

    // Limpa a lista de gerenciamento
    Node* current = g_all_lists->head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }

    free(g_all_lists);
    g_all_lists = NULL;
}

int List_Add(List* list, void* data) {
    if (list == NULL) return -1;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return -1;
    
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    
    return 0;
}

void* List_Pop(List* list) {
    if (list == NULL || list->head == NULL) return NULL;
    
    Node* node_to_remove = list->head;
    void* data = node_to_remove->data;
    list->head = node_to_remove->next;
    
    free(node_to_remove);
    
    return data;
}

void* List_GetByIndex(List* list, int index) {
    if (list == NULL || index < 0) return NULL;
    
    Node* current = list->head;
    int i = 0;
    while (current != NULL) {
        if (i == index) {
            return current->data;
        }
        current = current->next;
        i++;
    }
    
    return NULL; // Índice fora do alcance.
}

void List_ForEach(List* list, Function_Arg1 function_arg1) {
    if (list == NULL || function_arg1 == NULL) return;
    
    Node* current = list->head;
    while (current != NULL) {
        function_arg1(current->data);
        current = current->next;
    }
}

int List_Remove(List* list, void* data_to_remove) {
    if (list == NULL || data_to_remove == NULL || list->head == NULL) {
        return -1; // Lista ou dado inválido, ou lista vazia
    }

    Node* current = list->head;
    Node* prev = NULL;

    // Percorre a lista para encontrar o nó a ser removido
    while (current != NULL) {
        // Compara o conteúdo da memória do dado no nó com o dado a ser removido
        if (memcmp(current->data, data_to_remove, list->data_size) == 0) {
            // Item encontrado, agora vamos removê-lo
            if (prev == NULL) {
                // O item a ser removido é o primeiro da lista (head)
                list->head = current->next;
            } else {
                // O item está no meio ou no fim da lista
                prev->next = current->next;
            }

            // Libera a memória do dado e do nó
            if (list->free_data_func != NULL) {
                list->free_data_func(current->data);
            }
            free(current);

            return 0; // Sucesso
        }
        
        // Anda para o próximo nó
        prev = current;
        current = current->next;
    }

    return -1; // Item não encontrado na lista
}