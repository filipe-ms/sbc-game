// request_manager.c
/*
#include "request_manager.h"
#include "request_thread.h"
#include "thread_wrapper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_ERROR_MSG "Erro na requisição"

struct RequestManager {
    char* prompt;
    char* response;
    bool finished;
    bool request_initiated;
    Thread reqThread;
    char* text_to_display;
};

RequestManager* request_manager_create(char* default_prompt) {
    RequestManager* manager = malloc(sizeof(RequestManager));
    if (!manager) return NULL;

    manager->prompt = strdup(default_prompt);
    manager->response = NULL;
    manager->finished = false;
    manager->request_initiated = false;
    manager->text_to_display = "Aguardando...";
    manager->reqThread = (Thread){ 0 };

    return manager;
}

void request_manager_update(RequestManager* manager) {
    if (!manager) return;

    if (manager->finished) {
        thread_join(&manager->reqThread);
        manager->text_to_display = manager->response ? manager->response : DEFAULT_ERROR_MSG;
        manager->finished = false;
        manager->request_initiated = false;

        if (manager->response) {
            FreeResponse(manager->response);
            manager->response = NULL;
        }
    }
}

char* request_manager_get_text(const RequestManager* manager) {
    return manager ? manager->text_to_display : DEFAULT_ERROR_MSG;
}

void request_manager_destroy(RequestManager* manager) {
    if (!manager) return;

    if (manager->request_initiated && !manager->finished) {
        thread_join(&manager->reqThread);
    }

    free(manager->prompt);
    if (manager->response) FreeResponse(manager->response);
    free(manager);
}

void request_manager_set_prompt(RequestManager* manager, char* prompt) {
    if (!manager || !prompt) return;

    free(manager->prompt);
    manager->prompt = strdup(prompt);
}

bool request_manager_start_request(RequestManager* manager) {
    if (!manager || manager->request_initiated) return false;

    manager->request_initiated = true;
    manager->finished = false;
    manager->text_to_display = "Fazendo requisição...";

    RequestData reqData = {
        .prompt = manager->prompt,
        .response = NULL,
        .finished = false
    };

    if (!thread_create(&manager->reqThread, request_thread_func, &reqData)) {
        manager->text_to_display = DEFAULT_ERROR_MSG;
        manager->finished = true;
        return false;
    }

    return true;
}*/