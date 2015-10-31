#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// referenced from: https://www.quora.com/How-do-you-write-a-C-program-to-split-a-string-by-a-delimiteri, Costya Perepelitsa

char **strsplit(const char* str, const char* delim, size_t* numtokens) {
    // (don't do this if you don't need to keep the old line,
    // as this is less efficient)
    char *s = strdup(str);

    // these three variables are part of a very common idiom to
    // implement a dynamically-growing array
    size_t tokens_alloc = 1;
    size_t tokens_used = 0;
    char **tokens = calloc(tokens_alloc, sizeof(char*));
    char *token, *strtok_ctx;

    for (token = strtok_r(s, delim, &strtok_ctx);
            token != NULL;
            token = strtok_r(NULL, delim, &strtok_ctx)) {

        // check if we need to allocate more space for tokens
        if (tokens_used == tokens_alloc) {
            tokens_alloc *= 2;
            tokens = realloc(tokens, tokens_alloc * sizeof(char*));
        }
        tokens[tokens_used++] = strdup(token);
    }
    // cleanup

    if (tokens_used == 0) {
        free(tokens);
        tokens = NULL;
    } else {
        tokens = realloc(tokens, tokens_used * sizeof(char*));
    }

    *numtokens = tokens_used;
    free(s);
    return tokens;
}

