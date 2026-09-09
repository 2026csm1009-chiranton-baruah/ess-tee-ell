#include <stdio.h>
#include <string.h>

#define MAX 100

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void sortString(char str[]) {
    int n = strlen(str);

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (str[i] > str[j]) {
                swap(&str[i], &str[j]);
            }
        }
    }
}

void permute(char str[], int left, int right) {

    if (left == right) {
        printf("%s\n", str);
        return;
    }

    /*
     * Track which characters have already been
     * used at this position.
     */
    for (int i = left; i <= right; i++) {

        int duplicate = 0;

        for (int j = left; j < i; j++) {
            if (str[j] == str[i]) {
                duplicate = 1;
                break;
            }
        }

        if (duplicate)
            continue;

        swap(&str[left], &str[i]);

        permute(str, left + 1, right);

        /* Backtrack */
        swap(&str[left], &str[i]);
    }
}

int main() {
    char str[MAX];

    printf("Enter string: ");
    scanf("%s", str);

    sortString(str);

    printf("Permutations:\n");

    permute(str, 0, strlen(str) - 1);

    return 0;
}
