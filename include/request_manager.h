// File: RequestManager.h
#pragma once

#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include <stdbool.h>

typedef struct RequestManager RequestManager;

// Cria uma nova inst�ncia do gerenciador de requisi��es
RequestManager* request_manager_create(char* default_prompt);

// Atualiza o estado da requisi��o (deve ser chamado no loop principal)
void request_manager_update(RequestManager* manager);

// Obt�m o texto atual para exibi��o
char* request_manager_get_text(const RequestManager* manager);

// Libera os recursos do gerenciador
void request_manager_destroy(RequestManager* manager);

// Define um novo prompt para a pr�xima requisi��o
void request_manager_set_prompt(RequestManager* manager, char* prompt);

// For�a o in�cio de uma nova requisi��o
bool request_manager_start_request(RequestManager* manager);

#endif // REQUEST_MANAGER_H