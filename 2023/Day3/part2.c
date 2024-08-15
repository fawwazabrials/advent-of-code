#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct GearPos {
    int i;
    int j;
} GearPos;

typedef struct PartNumG { // Part Number that has a gear attached
    int value;
    GearPos g;
} PartNumG;

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isValid(char schematic[1024][1024], int size_s, int size_str, int i, int j, GearPos *g) {
    if (i-1 >= 0 && j-1 >= 0 && schematic[i-1][j-1]=='*' && !isDigit(schematic[i-1][j-1])) { 
        g->i=i-1;
        g->j=j-1;
        return true;
    }
    else if (i-1 >= 0 && schematic[i-1][j]=='*' && !isDigit(schematic[i-1][j])) { 
        g->i=i-1;
        g->j=j;
        return true;
    }
    else if (i-1 >= 0 && j+1 < size_str && schematic[i-1][j+1]=='*' && !isDigit(schematic[i-1][j+1])) { 
        g->i=i-1;
        g->j=j+1;
        return true;
    }

    else if (j-1 >= 0 && schematic[i][j-1]=='*' && !isDigit(schematic[i][j-1])) { 
        g->i=i;
        g->j=j-1;
        return true;
    }
    else if (j+1 < size_str && schematic[i][j+1]=='*' && !isDigit(schematic[i][j+1])) { 
        g->i=i;
        g->j=j+1;
        return true;
    }

    else if (i+1 < size_s && j-1 >= 0 && schematic[i+1][j-1]=='*' && !isDigit(schematic[i+1][j-1])) { 
        g->i=i+1;
        g->j=j-1;
        return true;
    }
    else if (i+1 < size_s && schematic[i+1][j]=='*' && !isDigit(schematic[i+1][j])) { 
        g->i=i+1;
        g->j=j;
        return true;
    }
    else if (i+1 < size_s && j+1 < size_str && schematic[i+1][j+1]=='*' && !isDigit(schematic[i+1][j+1])) { 
        g->i=i+1;
        g->j=j+1;
        return true;
    }
    return false;
}

int main(int argc, char** argv) {
    char schematic[1024][1024];
    int size_s=0;
    char line[1024];
    PartNumG parts[1024]; int partsc=0;
    while (scanf("%s", line) == 1) { // Take schematic and place it in the variable
        strcpy(schematic[size_s], line); size_s++;
    }


    int partnum=0;
    GearPos gear; gear.i = -1; gear.j = -1;
    for (int i=0; i<size_s; i++) {
        bool counting=false, parthasgear=false;
        for (int j=0; j<strlen(line); j++) {
            if (isDigit(schematic[i][j])) {
                if (!counting) {
                    counting = true; 
                    parthasgear = false;
                }
                if (isValid(schematic, size_s, strlen(line), i, j, &gear)) {
                    parthasgear = true;
                }
                partnum *= 10; partnum += schematic[i][j]-'0';
            }
            // printf("masuk %c   counting=%d parthasgear=%d\n", schematic[i][j], counting, parthasgear);

            if (counting && (!isDigit(schematic[i][j]) || j == strlen(line)-1)) {
                counting = false;
                if (parthasgear) {
                    PartNumG new;
                    new.value = partnum;
                    new.g = gear;
                    parts[partsc] = new;
                    partsc++;
                }
                partnum = 0;
            }
        } 
    }

    long long twicesum = 0;
    // printf("%d\n", partsc);

    for (int i=0; i<partsc; i++) {
        for (int j=0; j<partsc; j++) {
            if (i != j && parts[i].g.i == parts[j].g.i && parts[i].g.j == parts[j].g.j) {
                twicesum += parts[i].value * parts[j].value;
            }
        }
    }

    printf("%lld\n", twicesum/2);
}