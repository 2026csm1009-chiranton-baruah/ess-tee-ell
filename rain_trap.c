#include <stdio.h>
#include <stdlib.h>

int trapRainWater(int *height, int n) {
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;
    int water = 0;

    for (int i = 0; i < n; i++) {

        while (top >= 0 && height[i] > height[stack[top]]) {

            int bottom = stack[top--];

            if (top < 0)
                break;

            int left = stack[top];

            int width = i - left - 1;

            int boundedHeight =
                (height[left] < height[i] ? height[left] : height[i])
                - height[bottom];

            water += width * boundedHeight;
        }

        stack[++top] = i;
    }

    free(stack);
    return water;
}

int main() {
    int n;
    scanf("%d", &n);

    int *height = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        scanf("%d", &height[i]);

    printf("%d\n", trapRainWater(height, n));

    free(height);

    return 0;
}
