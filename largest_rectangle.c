#include <stdio.h>
#include <stdlib.h>

int largestRectangle(int *heights, int n) {

    int *stack = malloc((n + 1) * sizeof(int));
    int top = -1;

    int maxArea = 0;

    for (int i = 0; i <= n; i++) {

        int currentHeight;

        if (i == n)
            currentHeight = 0;
        else
            currentHeight = heights[i];

        while (top >= 0 &&
               currentHeight < heights[stack[top]]) {

            int h = heights[stack[top--]];

            int width;

            if (top < 0)
                width = i;
            else
                width = i - stack[top] - 1;

            int area = h * width;

            if (area > maxArea)
                maxArea = area;
        }

        stack[++top] = i;
    }

    free(stack);

    return maxArea;
}

int main() {

    int n;
    scanf("%d", &n);

    int *heights = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &heights[i]);

    printf("%d\n", largestRectangle(heights, n));

    free(heights);

    return 0;
}
