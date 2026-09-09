#include <stdio.h>
#include <string.h>

void nokiaToString(char *input) {
    char *keys[] = {
        " ",
        "",
        "ABC",
        "DEF",
        "GHI",
        "JKL",
        "MNO",
        "PQRS",
        "TUV",
        "WXYZ"
    };

    int n = strlen(input);
    int i = 0;

    while (i < n) {
        if (input[i] == ' ') {
            printf(" ");
            i++;
            continue;
        }

        char key = input[i];
        int count = 0;

        // Count consecutive presses of the same key
        while (i < n && input[i] == key) {
            count++;
            i++;
        }

        int digit = key - '0';

        if (digit >= 2 && digit <= 9) {
            int letters = strlen(keys[digit]);

            // Cycle if pressed more times than available letters
            count = (count - 1) % letters;

            printf("%c", keys[digit][count]);
        }
    }

    printf("\n");
}

int main() {
    char input[1000];

    printf("Enter keypad sequence: ");
    fgets(input, sizeof(input), stdin);

    nokiaToString(input);

    return 0;
}
