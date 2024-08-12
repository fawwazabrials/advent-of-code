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
    int game_num, sum = 0;
    bool valid;

    while (fgets(line, 1000, stdin)) {
        // printf("%s", line);
        game_num = 0;
        valid = true;
        for (int i=5; i<strlen(line); i++) {
            if (line[i] < '0' || line[i] > '9') break;
            game_num *= 10; game_num += line[i]-'0';
        }

        int first_iter_idx = strfind(line, ": ");
        if (first_iter_idx == -1) continue;
        else first_iter_idx += 2;

        // printf("first_iter_idx=%d\n", first_iter_idx);
        int green=1, blue=1, red=1, buffer=0;
        for (int i=first_iter_idx; i<strlen(line); i++) {
            if (line[i] == ';') {
                green=0; blue=0; red=0;
            }

            if (line[i] >= '0' && line[i] <= '9') {buffer *= 10; buffer += line[i]-'0';}

            if (strncmp(line+i, "green", 5) == 0) {
                // printf("idx=%d  assigned to green: %d\n", i, buffer);
                green = buffer; buffer = 0;
            } else if (strncmp(line+i, "red", 3) == 0) {
                // printf("idx=%d  assigned to red: %d\n", i, buffer);
                red = buffer; buffer = 0;
            } else if (strncmp(line+i, "blue", 4) == 0) {
                // printf("idx=%d  assigned to blue: %d\n", i, buffer);
                blue = buffer; buffer = 0;
            }

            if (green > 13 || red > 12 || blue > 14) {
                // printf("red=%d  green=%d   blue=%d\n", red, green, blue);
                valid = false; break;
            }
        }

        // printf("Game %d: %d\n", game_num, valid);
        if (valid) sum += game_num;
    }

    printf("%d\n", sum);   
}