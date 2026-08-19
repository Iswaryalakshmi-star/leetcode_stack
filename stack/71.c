#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* simplifyPath(char* path) {
    int len = strlen(path);
    // Allocate space to store pointers to directory names (our stack)
    char** stack = (char**)malloc(len * sizeof(char*));
    int top = 0;

    // Use strtok to split the path using '/' as a delimiter
    char* token = strtok(path, "/");
    while (token != NULL) {
        if (strcmp(token, ".") == 0 || strlen(token) == 0) {
            // Ignore current directory tokens or empty spaces
        } else if (strcmp(token, "..") == 0) {
            // Go to the parent directory: pop from stack if not empty
            if (top > 0) {
                top--;
            }
        } else {
            // Valid directory name (including "...", "....", etc.): push to stack
            stack[top++] = token;
        }
        token = strtok(NULL, "/");
    }

    // Allocate memory for the final output string
    // Absolute worst case length matches the input length + 1 for null terminator
    char* result = (char*)malloc((len + 2) * sizeof(char));
    result[0] = '\0';

    // Build the canonical path from the tokens stored in the stack
    if (top == 0) {
        strcpy(result, "/");
    } else {
        for (int i = 0; i < top; i++) {
            strcat(result, "/");
            strcat(result, stack[i]);
        }
    }

    // Free the stack tracker memory allocation
    free(stack);

    return result;
}
