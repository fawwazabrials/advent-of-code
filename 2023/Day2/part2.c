#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int strfind(char *str, char *f) {
    for (int i=0; i<strlen(str); i++) {
        if (strncmp(str+i, f, strlen(f)) == 0) return i;
    } return -1;
}


int main(int argc, char **argv) {
    char line[1000];
    int sum = 0;

    while (fgets(line, 1000, stdin)) {
        int first_iter_idx = strfind(line, ": ");
        if (first_iter_idx == -1) continue;
        else first_iter_idx += 2;

        // printf("first_iter_idx=%d\n", first_iter_idx);
        int green=0, blue=0, red=0, buffer=0;
        for (int i=first_iter_idx; i<strlen(line); i++) {
            if (line[i] >= '0' && line[i] <= '9') {buffer *= 10; buffer += line[i]-'0';}

            if (strncmp(line+i, "green", 5) == 0) {
                // printf("idx=%d  assigned to green: %d\n", i, buffer);
                if (buffer > green) green = buffer; 
                buffer = 0;
            } else if (strncmp(line+i, "red", 3) == 0) {
                // printf("idx=%d  assigned to red: %d\n", i, buffer);
                if (buffer > red) red = buffer; 
                buffer = 0;
            } else if (strncmp(line+i, "blue", 4) == 0) {
                // printf("idx=%d  assigned to blue: %d\n", i, buffer);
                if (buffer > blue) blue = buffer; 
                buffer = 0;
            }

        }

        // printf("red=%d, green=%d, blue=%d\n", red, green, blue);
        sum += green * red * blue;
    }

    printf("%d\n", sum);   
}