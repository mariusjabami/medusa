#include "../includes/server.h"
#include "../includes/parser.h" // contém read_file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#define BUFFER_SIZE 500000

// --- callback para capturar resposta do curl ---
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    strncat((char *)userdata, (char *)ptr, size * nmemb);
    return size * nmemb;
}

// --- salva texto em arquivo ---
void write_file(const char *filename, const char *text) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror(filename);
        return;
    }
    fputs(text, f);
    fclose(f);
}

// --- envia prompt para Gemini ---
char *send_to_gemini(const char *prompt, const char *api_key) {
    CURL *curl;
    CURLcode res;

    char *response = malloc(BUFFER_SIZE);
    if (!response) return NULL;
    response[0] = '\0';

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) return NULL;

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    char header_key[256];
    snprintf(header_key, sizeof(header_key), "x-goog-api-key: %s", api_key);
    headers = curl_slist_append(headers, header_key);

    curl_easy_setopt(curl, CURLOPT_URL,
        "https://generativelanguage.googleapis.com/v1beta/models/gemma-3-27b-it:generateContent");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Escapa aspas duplas e barras invertidas do prompt
    char *prompt_escaped = malloc(BUFFER_SIZE);
    if (!prompt_escaped) return NULL;
    size_t j = 0;
    for (size_t i = 0; i < strlen(prompt) && j < BUFFER_SIZE-1; i++) {
        if (prompt[i] == '\"') { prompt_escaped[j++] = '\\'; prompt_escaped[j++] = '"'; }
        else if (prompt[i] == '\\') { prompt_escaped[j++] = '\\'; prompt_escaped[j++] = '\\'; }
        else prompt_escaped[j++] = prompt[i];
    }
    prompt_escaped[j] = '\0';

    char json_body[BUFFER_SIZE];
    snprintf(json_body, sizeof(json_body),
        "{ \"contents\": [ { \"parts\": [ {\"text\": \"%s\"} ] } ] }",
        prompt_escaped);

    free(prompt_escaped);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Erro curl: %s\n", curl_easy_strerror(res));
        free(response);
        response = NULL;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return response;
}

// --- extrai texto limpo do JSON retornado pelo Gemini ---
char *extract_text_from_json(const char *json_text) {
    cJSON *root = cJSON_Parse(json_text);
    if (!root) return NULL;

    cJSON *candidates = cJSON_GetObjectItem(root, "candidates");
    if (!candidates) { cJSON_Delete(root); return NULL; }

    size_t len = 0;
    char *output = malloc(BUFFER_SIZE);
    if (!output) { cJSON_Delete(root); return NULL; }
    output[0] = '\0';

    cJSON *candidate = NULL;
    cJSON_ArrayForEach(candidate, candidates) {
        cJSON *content = cJSON_GetObjectItem(candidate, "content");
        if (!content) continue;

        cJSON *parts = cJSON_GetObjectItem(content, "parts");
        if (!parts) continue;

        cJSON *part = NULL;
        cJSON_ArrayForEach(part, parts) {
            cJSON *text = cJSON_GetObjectItem(part, "text");
            if (text && text->valuestring) {
                strncat(output, text->valuestring, BUFFER_SIZE - strlen(output) - 1);
            }
        }
    }

    cJSON_Delete(root);
    return output;
}

// --- função pública ---
void analyze_with_medusa(const char *input_file, const char *output_file, const char *api_key) {
    char text[100][100];
    int linhas = read_file((char *)input_file, text);
    if (linhas <= 0) {
        fprintf(stderr, "Erro ao ler %s\n", input_file);
        return;
    }

    // --- prompt da Medusa ---
    const char *prompt_padrao =
        "Você é Medusa, filha de Marius Jabami, usando todas as cobras do seu cabelo para encontrar erros. "
        "Analise friamente o código abaixo, critique de forma sarcástica e direta, "
        "identifique erros, gravidade, possíveis causas, agentes problemáticos, nível do programador, "
        "forneça dicas e sugestões de melhoria, e devolva o código corrigido. "
        "Interaja com o usuário, seja divertida, mas cruel quando o código estiver ruim. "
        "Produza um relatório textual limpo, sem Markdown.\n\n";

    char prompt[BUFFER_SIZE] = {0};
    strcpy(prompt, prompt_padrao);
    for (int i = 0; i < linhas; i++) {
        strcat(prompt, text[i]);
    }

    printf("Medusa está analisando %s...\n", input_file);

    char *json_response = send_to_gemini(prompt, api_key);
    if (!json_response) {
        fprintf(stderr, "Falha ao obter resposta da API.\n");
        return;
    }

    char *response_text = extract_text_from_json(json_response);
    free(json_response);

    if (!response_text) {
        fprintf(stderr, "Falha ao extrair texto do JSON.\n");
        return;
    }

    printf("\n--- Relatório Medusa ---\n%s\n", response_text);
    write_file(output_file, response_text);
    free(response_text);
}
