#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void checkNumber(char *text, int idx, int *res, int *res_len) {
    if (strncmp(text+idx, "one", 3) == 0) {
        *res = 1;
        *res_len = 3;
    } else if (strncmp(text+idx, "two", 3) == 0) {
        *res = 2;
        *res_len = 3;
    } else if (strncmp(text+idx, "three", 5) == 0) {
        *res = 3;
        *res_len = 5;
    } else if (strncmp(text+idx, "four", 4) == 0) {
        *res = 4;
        *res_len = 4;
    } else if (strncmp(text+idx, "five", 4) == 0) {
        *res = 5;
        *res_len = 4;
    } else if (strncmp(text+idx, "six", 3) == 0) {
        *res = 6;
        *res_len = 3;
    } else if (strncmp(text+idx, "seven", 5) == 0) {
        *res = 7;
        *res_len = 5;
    } else if (strncmp(text+idx, "eight", 5) == 0) {
        *res = 8;
        *res_len = 5;
    } else if (strncmp(text+idx, "nine", 4) == 0) {
        *res = 9;
        *res_len = 4;
    } else {
        *res = 0;
        *res_len = 0;
    }
}

int main(int argc, char **argv) {
    char text[1000];
    int first, last, checkDigit, sum=0;

    while (scanf("%s", text) == 1) { // Continue taking input while not EOF
        int parsed, parsed_len;
        for (int i=0; i<strlen(text); i++) {
            if (text[i] >= '0' && text[i] <= '9') {
                first = text[i]-'0'; break;
            }
            checkNumber(text, i, &parsed, &parsed_len);
            if (parsed != 0) {
                first=parsed; break;
            }
        }

        for (int i=strlen(text)-1; i>=0; i--) {
            if (text[i] >= '0' && text[i] <= '9') {
                last = text[i]-'0'; break;
            }
            checkNumber(text, i, &parsed, &parsed_len);
            if (parsed != 0) {
                last=parsed; break;
            }
        }

        // printf("%d %d %d\n", first, last, first*10+last);
        sum += first*10+last; // Concatenate first and last digit
    }

    printf("%d\n", sum);
    return 0;
}