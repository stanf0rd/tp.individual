#define ERROR printf("[error]\n")
#define STR_ALLOC_INC 20
#define ARR_ALLOC_INC 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getString();
int getArray(char***);
int filterLines(const char**, const int, char***);

int main() {
    int inStrCount = 0, outStrCount = 0;
    char **inputArray = NULL;
    char **outputArray = NULL;

    inStrCount = getArray(&inputArray);

    if (inStrCount) {
        outStrCount = filterLines(
            (const char**)inputArray,
            (const int)inStrCount,
            &outputArray);

        if (outStrCount) {
            for (int i = 0; i < outStrCount; i++)
                printf("%s\n", outputArray[i]);
            free(outputArray);
        } else {
            ERROR;
        }
        for (int i = 0; i < inStrCount; i++)
            free(inputArray[i]);
        free(inputArray);
    } else {
        ERROR;
    }
    return 0;
}

int filterLines(const char **inArr, const int numCount, char ***outputArray) {
    if (!inArr || !outputArray || numCount < 1) return 0;

    int correctStr = 0, allocSize = 0;
    char **outArr = NULL, **temp = NULL;

    for (int i = 0; i < numCount; i++) {
        int openBr = 0, closeBr = 0;

        for (int j = 0; inArr[i][j] != '\0'; j++) {
            if (inArr[i][j] == '(') openBr++;
            else if (inArr[i][j] == ')') closeBr++;
        }

        if (openBr == closeBr) {
            if (correctStr == allocSize) {
                allocSize += ARR_ALLOC_INC;
                temp = realloc(outArr, allocSize * sizeof(*outArr));
                if (!temp) {
                    free(outArr);
                    return 0;
                }
                outArr = temp;
            }
            outArr[correctStr++] = (char *)inArr[i];
        }
    }
    *outputArray = outArr;
    return correctStr;
}

int getArray(char ***outputArray) {
    if (!outputArray) return 0;

    int allocSize = 0, strCount = 0;
    char **strArray = NULL, **temp = NULL;

    char *str = NULL;
    while ((str = getString()) != NULL) {
        if (strCount == allocSize) {
            allocSize += ARR_ALLOC_INC;
            temp = realloc(strArray, allocSize * sizeof(*strArray));
            if (!temp) {
                for (int i = 0; i < strCount; i++)
                    free(strArray[i]);
                free(str);
                free(strArray);
                return 0;
            }
            strArray = temp;
        }
        strArray[strCount++] = str;
    }
    *outputArray = strArray;
    return strCount;
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
