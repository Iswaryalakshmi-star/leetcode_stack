#include <stdlib.h>

int largestRectangleArea(int* heights, int heightsSize) {
    if (heightsSize == 0) return 0;

    // Allocate memory for the stack to store indices
    int* stack = (int*)malloc((heightsSize + 1) * sizeof(int));
    int top = -1;
    int max_area = 0;
    
    for (int i = 0; i <= heightsSize; i++) {
        // Use a virtual bar of height 0 at the end to flush out remaining elements in the stack
        int current_height = (i == heightsSize) ? 0 : heights[i];
        
        // While the current bar is shorter than the bar at the top of the stack
        while (top != -1 && heights[stack[top]] > current_height) {
            int height = heights[stack[top--]]; // Pop the highest bar
            
            // If stack is empty, width spans from index 0 to i
            // Otherwise, width is bounded between current index and the index below the popped one
            int width = (top == -1) ? i : (i - stack[top] - 1);
            
            int area = height * width;
            if (area > max_area) {
                max_area = area;
            }
        }
        
        // Push the current index onto the stack
        stack[++top] = i;
    }
    
    free(stack);
    return max_area;
}
