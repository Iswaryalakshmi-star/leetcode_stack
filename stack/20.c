#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool isValid(char* s) {
    int len = strlen(s);
    
    // An odd length string can never be balanced
    if (len % 2 != 0) {
        return false;
    }

    // Allocate memory for the stack array
    char* stack = (char*)malloc(len * sizeof(char));
    int top = -1;

    for (int i = 0; i < len; i++) {
        char current = s[i];

        // If it's an opening bracket, push it to the stack
        if (current == '(' || current == '{' || current == '[') {
            stack[++top] = current;
        } 
        // If it's a closing bracket, check for a valid match
        else {
            // Found a closing bracket but the stack is empty
            if (top == -1) {
                free(stack);
                return false;
            }

            char match = stack[top--];
            if ((current == ')' && match != '(') ||
                (current == '}' && match != '{') ||
                (current == ']' && match != '[')) {
                free(stack);
                return false; // Mismatched brackets
            }
        }
    }

    // If the stack is empty, all brackets were matched correctly
    bool result = (top == -1);
    free(stack);
    return result;
}
