#include <stdlib.h>

// Helper function to find the largest rectangle in a single row's histogram
int largestRectangleArea(int* heights, int heightsSize) {
    int* stack = (int*)malloc((heightsSize + 1) * sizeof(int));
    int top = -1;
    int max_area = 0;
    
    for (int i = 0; i <= heightsSize; i++) {
        int current_height = (i == heightsSize) ? 0 : heights[i];
        
        while (top != -1 && heights[stack[top]] > current_height) {
            int height = heights[stack[top--]];
            int width = (top == -1) ? i : (i - stack[top] - 1);
            int area = height * width;
            if (area > max_area) {
                max_area = area;
            }
        }
        stack[++top] = i;
    }
    
    free(stack);
    return max_area;
}

// Main function to find the maximal rectangle area in the binary matrix
int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize == 0 || matrixColSize[0] == 0) {
        return 0;
    }
    
    int cols = matrixColSize[0];
    int* heights = (int*)calloc(cols, sizeof(int));
    int max_maximal_area = 0;
    
    // Traverse the matrix row by row
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < cols; j++) {
            // Update the histogram height for the current column
            if (matrix[i][j] == '1') {
                heights[j] += 1;
            } else {
                heights[j] = 0; // Broken sequence resets the bar height to 0
            }
        }
        
        // Calculate the maximum rectangle area for the current cumulative histogram row
        int area = largestRectangleArea(heights, cols);
        if (area > max_maximal_area) {
            max_maximal_area = area;
        }
    }
    
    free(heights);
    return max_maximal_area;
}
