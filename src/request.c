// request.c
/*
#include "request.h"
#include "request_constants.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_URL_LENGTH 256
#define MAX_JSON_LENGTH 2048 // Be mindful of prompt length + JSON overhead

// Memory structure for curl callback
typedef struct {
    char* buffer;
    size_t size;
} MemoryStruct;

// Callback function to write data received from curl into memory
static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    MemoryStruct* mem = (MemoryStruct*)userp;

    // Use realloc to expand buffer. Check for NULL for safety.
    char* ptr = realloc(mem->buffer, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "ERRO: realloc() falhou em WriteMemoryCallback\n");
        // If realloc fails, the original mem->buffer is still valid but untouched.
        // Returning 0 signals an error to curl.
        return 0;
    }

    mem->buffer = ptr;
    memcpy(&(mem->buffer[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->buffer[mem->size] = '\0'; // Null-terminate the buffer

    return realsize;
}

// --- Global Curl Initialization ---
int InitRequestSystem() {
    CURLcode res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (res != CURLE_OK) {
        fprintf(stderr, "ERRO: curl_global_init() falhou: %s\n", curl_easy_strerror(res));
        return 1; // Indicate failure
    }
    printf("Request system initialized.\n"); // Optional: Confirmation
    return 0; // Indicate success
}

// --- Global Curl Cleanup ---
void CleanupRequestSystem() {
    curl_global_cleanup();
    printf("Request system cleaned up.\n"); // Optional: Confirmation
}


// --- Send Request ---
char* Request(char* prompt) {
    CURL* curl = NULL;
    CURLcode res;
    MemoryStruct chunk = { 0 }; // Initialize struct members to 0/NULL
    chunk.buffer = malloc(1);   // Start with 1 byte, will be realloc'd
    if (chunk.buffer == NULL) {
         fprintf(stderr, "ERRO: Falha ao alocar memória inicial para o chunk.\n");
         return NULL;
    }
    chunk.size = 0;

    char* response_text = NULL;
    struct curl_slist* headers = NULL;
    long http_code = 0; // To store the HTTP status code

    // Validate API Key presence (basic check)
    if (API_KEY == NULL || strcmp(API_KEY, "YOUR_API_KEY_HERE") == 0 || strcmp(API_KEY, "") == 0) {
        fprintf(stderr, "ERRO: API_KEY não configurada ou inválida em request.h\n");
        free(chunk.buffer); // Free allocated memory before returning
        return NULL;
    }

    // Construct API URL
    char api_url[MAX_URL_LENGTH];
    int url_len = snprintf(api_url, sizeof(api_url), API_URL_FORMAT, MODEL, API_KEY);
    if (url_len < 0 || url_len >= sizeof(api_url)) {
        fprintf(stderr, "ERRO: Falha ao construir URL ou buffer pequeno demais.\n");
        free(chunk.buffer);
        return NULL;
    }

    // Construct JSON Payload
    // WARNING: This is unsafe if 'prompt' contains " or \ characters.
    // Consider using a JSON library like cJSON for robust escaping.
    char json_payload[MAX_JSON_LENGTH];
    int payload_len = snprintf(json_payload, sizeof(json_payload),
        "{\"contents\":[{\"parts\":[{\"text\":\"%s\"}]}]}", prompt);

    if (payload_len < 0 || payload_len >= sizeof(json_payload)) {
        fprintf(stderr, "ERRO: Prompt muito longo ou falha na formatação do JSON.\n");
        free(chunk.buffer);
        return NULL;
    }

    // Initialize CURL easy handle for this request
    // Assumes InitRequestSystem() was called successfully before this.
    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "ERRO: Falha ao inicializar o handle CURL (curl_easy_init).\n");
        if (curl) curl_easy_cleanup(curl);
        if (headers) curl_slist_free_all(headers);
        free(chunk.buffer);
        return response_text;
    }

    // Set HTTP headers
    headers = curl_slist_append(headers, "Content-Type: application/json");
    if (!headers) {
         fprintf(stderr, "ERRO: Falha ao alocar memória para cabeçalhos HTTP.\n");
         if (curl) curl_easy_cleanup(curl);
         if (headers) curl_slist_free_all(headers);
         free(chunk.buffer);
         return response_text;
    }

    // Set CURL options
    curl_easy_setopt(curl, CURLOPT_URL, api_url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Raylib-Gemini-Client/1.0");
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L); // Set timeout (e.g., 30 seconds)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Verify SSL certificate
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); // Uncomment for debug info

    // Perform the request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "ERRO na requisição CURL: %s\n", curl_easy_strerror(res));
        if (curl) curl_easy_cleanup(curl);
        if (headers) curl_slist_free_all(headers);
        free(chunk.buffer);
        return response_text;
    }

    // Check HTTP response code
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    if (http_code != 200) {
        fprintf(stderr, "ERRO: API retornou código HTTP %ld\n", http_code);
        fprintf(stderr, "API Response Body: %s\n", chunk.buffer ? chunk.buffer : "(nenhum)");
        if (curl) curl_easy_cleanup(curl);
        if (headers) curl_slist_free_all(headers);
        free(chunk.buffer);
        return response_text;
    }

    // Process the response - find the "text" field
    // NOTE: This is basic string searching, fragile if JSON structure changes.
    // A proper JSON parser (like cJSON) is recommended for robustness.
    if (chunk.buffer && chunk.size > 0) {
        char* start = strstr(chunk.buffer, "\"text\": \"");
        if (start) {
            start += 9; // Move pointer past "\"text\": \""
            char* end = strchr(start, '"'); // Find the closing quote
            if (end) {
                size_t text_len = end - start;
                response_text = malloc(text_len + 1);
                if (response_text) {
                    strncpy(response_text, start, text_len);
                    response_text[text_len] = '\0';

                    // Basic unescaping for \n and \" (add more if needed)
                    char *read_ptr = response_text, *write_ptr = response_text;
                    while (*read_ptr) {
                        if (*read_ptr == '\\' && *(read_ptr + 1) == 'n') {
                            *write_ptr++ = '\n';
                            read_ptr += 2;
                        } else if (*read_ptr == '\\' && *(read_ptr + 1) == '"') {
                            *write_ptr++ = '"';
                            read_ptr += 2;
                        } else if (*read_ptr == '\\' && *(read_ptr + 1) == '\\') {
                             *write_ptr++ = '\\';
                             read_ptr += 2;
                        } else {
                            *write_ptr++ = *read_ptr++;
                        }
                    }
                    *write_ptr = '\0'; // Null-terminate the potentially shorter string
                } else {
                    fprintf(stderr, "ERRO: Falha ao alocar memória para o texto da resposta.\n");
                }
            } else {
                 fprintf(stderr, "AVISO: Não foi possível encontrar o fim do texto na resposta JSON.\nRaw Response: %s\n", chunk.buffer);
            }
        } else {
             fprintf(stderr, "AVISO: Campo 'text' não encontrado na resposta JSON.\nRaw Response: %s\n", chunk.buffer);
        }
    } else {
        fprintf(stderr, "AVISO: Nenhum dado recebido da API ou HTTP status não foi 200.\n");
    }

    // Clean up resources for this specific request
    if (curl) curl_easy_cleanup(curl);
    if (headers) curl_slist_free_all(headers);
    free(chunk.buffer);

    return response_text;
}

// --- Free Response Memory ---
void FreeResponse(char* response) {
    free(response); // free(NULL) is safe
}*/