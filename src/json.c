#include <stdlib.h>
#include <string.h>
#include <jsmn.h>

char *json_get_string_field(const char *field, const char *json, int json_sz) {
    char buffer[512];
    jsmn_parser parser;
    jsmntok_t tokens[512];

    char *ret;

    jsmn_init(&parser);

    jsmn_parse(&parser, json, json_sz, tokens, 512);

    for (int i = 0; i < sizeof(tokens) / sizeof(jsmntok_t); i++) {
        int size = tokens[i].end - tokens[i].start;

        memcpy(buffer, json + tokens[i].start, size);
        buffer[size] = '\0';

        if (strcmp(field, buffer) == 0) {
            size = tokens[i + 1].end - tokens[i + 1].start;

            ret = malloc(size + 1);

            memcpy(ret, json + tokens[i + 1].start, size);
            ret[size] = '\0';

            return ret;
        }
    }

    return NULL;
}