#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    *returnSize = 0;
    if (root == NULL) return NULL;

    // Allocate an initial arbitrary buffer size for the results array
    int capacity = 100;
    int* result = (int*)malloc(capacity * sizeof(int));
    
    // Allocate space for our node-tracking pointer stack
    struct TreeNode** stack = (struct TreeNode**)malloc(capacity * sizeof(struct TreeNode*));
    int top = -1;

    struct TreeNode* curr = root;

    while (curr != NULL || top != -1) {
        // Step 1: Reach the leftmost node of the current node
        while (curr != NULL) {
            // Resize stack if capacity is exceeded
            if (top + 1 >= capacity) {
                capacity *= 2;
                result = (int*)realloc(result, capacity * sizeof(int));
                stack = (struct TreeNode**)realloc(stack, capacity * sizeof(struct TreeNode*));
            }
            stack[++top] = curr;
            curr = curr->left;
        }

        // Step 2: Current node must be NULL now, pop from stack
        curr = stack[top--];
        
        // Record the node value
        result[(*returnSize)++] = curr->val;

        // Step 3: We have visited the node and its left subtree. Now, it's the right subtree's turn
        curr = curr->right;
    }

    free(stack);
    return result;
}
