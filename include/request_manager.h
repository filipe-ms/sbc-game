// File: RequestManager.h
#pragma once

#ifndef REQUEST_MANAGER_H
#define REQUEST_MANAGER_H

#include <stdbool.h>

typedef struct RequestManager RequestManager;

// Cria uma nova instância do gerenciador de requisições
RequestManager* request_manager_create(char* default_prompt);

// Atualiza o estado da requisição (deve ser chamado no loop principal)
void request_manager_update(RequestManager* manager);

// Obtém o texto atual para exibição
char* request_manager_get_text(const RequestManager* manager);

// Libera os recursos do gerenciador
void request_manager_destroy(RequestManager* manager);

// Define um novo prompt para a próxima requisição
void request_manager_set_prompt(RequestManager* manager, char* prompt);

// Força o início de uma nova requisição
bool request_manager_start_request(RequestManager* manager);

#endif // REQUEST_MANAGER_H