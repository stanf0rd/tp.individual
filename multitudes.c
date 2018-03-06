#define ERROR printf("[error]\n")
#define STR_ALLOC_INC 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString();
char* getPriorProc(char*);

int main() {
    char* str = getString();
    if (!str) {
        ERROR;
        return 0;
    }

// !!!    while (str = getPriorProc(str)) {
        printf("%s\n", str);
    }
    return 0;

}

char* getPriorProc(char *str) {
    if (!str) return NULL;
    
    char *priorProc = str;

    while (*str != '(') {
        if (*str == '\0') return priorProc;
        str++;
    }
    
    priorProc = str;
    
    
}

char* getString() {
    if (feof(stdin)) return NULL;

    int allocSize = STR_ALLOC_INC;
    char *str = NULL,
        *endStr = NULL,
        *temp = NULL;

    str = malloc(sizeof(*str) * allocSize);
    if (!str) return NULL;
    str[0] = '\0';

    do {
        endStr = strchr(str, '\n');
        if (endStr) {
            if (endStr == &str[0]) break;
            *endStr = '\0';
            return str;  // success
        } else if (feof(stdin)) {
            return str;  // success
        } else {
            allocSize += STR_ALLOC_INC;
            temp = realloc(str, sizeof(*str) * allocSize);
            if (!temp) break;
            str = temp;
        }
    } while (fgets(strchr(str, '\0'), STR_ALLOC_INC, stdin));

    free(str);
    return NULL;
}