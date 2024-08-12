#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv) {
    char text[1000];
    int first, last, sum=0;

    while (scanf("%s", text) == 1) { // Continue taking input while not EOF
        for (int i=0; i<strlen(text); i++) { // Get first digit in string
            if (text[i] >= '0' && text[i] <= '9') {
                first = text[i] - '0';
                break;
            }
        }

        for (int i=strlen(text)-1; i>=0; i--) { // Get last digit in string
            if (text[i] >= '0' && text[i] <= '9') {
                last = text[i] - '0';
                break;
            }
        }

        sum += first*10+last; // Concatenate first and last digit
    }

    printf("%d\n", sum);
    return 0;
}