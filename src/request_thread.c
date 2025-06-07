/*#include "request_thread.h"
#include "stdio.h"

void* request_thread_func(void* param) {
    RequestData* data = (RequestData*)param;
    data->response = Request(data->prompt);
    data->finished = true;
    return NULL;
}*/