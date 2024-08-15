#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isValid(char schematic[1024][1024], int size_s, int size_str, int i, int j) {
    if (i-1 >= 0 && j-1 >= 0 && schematic[i-1][j-1]!='.' && !isDigit(schematic[i-1][j-1])) { 
        // printf("kiri atas %d %d %d %d\n", i, j, i-1, j-1) ;
        return true;
    }
    else if (i-1 >= 0 && schematic[i-1][j]!='.' && !isDigit(schematic[i-1][j])) { 
        // printf("atas %d %d %d %d\n", i, j, i-1, j) ;
        return true;
    }
    else if (i-1 >= 0 && j+1 < size_str && schematic[i-1][j+1]!='.' && !isDigit(schematic[i-1][j+1])) { 
        // printf("kanan atas %d %d %d %d\n", i, j, i-1, j+1) ;
        return true;
    }

    else if (j-1 >= 0 && schematic[i][j-1]!='.' && !isDigit(schematic[i][j-1])) { 
        // printf("kiri %d %d %d %d\n", i, j, i, j-1) ;
        return true;
    }
    else if (j+1 < size_str && schematic[i][j+1]!='.' && !isDigit(schematic[i][j+1])) { 
        // printf("kanan %d %d %d %d\n", i, j, i, j+1) ;
        return true;
    }

    else if (i+1 < size_s && j-1 >= 0 && schematic[i+1][j-1]!='.' && !isDigit(schematic[i+1][j-1])) { 
        // printf("kanan bawah %d %d %d %d\n", i, j, i+1, j-1) ;
        return true;
    }
    else if (i+1 < size_s && schematic[i+1][j]!='.' && !isDigit(schematic[i+1][j])) { 
        // printf("bawah %d %d %d %d\n", i, j, i+1, j) ;
        return true;
    }
    else if (i+1 < size_s && j+1 < size_str && schematic[i+1][j+1]!='.' && !isDigit(schematic[i+1][j+1])) { 
        // printf("kanan bawah %d %d %d %d\n", i, j, i+1, j+1) ;
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    char schematic[1024][1024];
    char line[1024];
    int row = 0;
    
    while (scanf("%s", line) == 1) { // Take schematic and place it in the variable
        strcpy(schematic[row], line); row++;
    }
    
    int partnum=0, sum=0;
    for (int i=0; i<row; i++) {
        bool counting=false, partvalid=false;
        // printf("Line %d     \n", i+1);
        for (int j=0; j<strlen(line); j++) {
            // printf("%c counting=%d partvalid=%d partnum=%d\n", schematic[i][j], counting, partvalid, partnum);


            if (isDigit(schematic[i][j])) {
                if (!counting) {
                    counting = true; 
                    partvalid = false;
                }
                // printf("i=%d    j=%d    isValid=%d\n", i, j, isValid(schematic, row, strlen(line), i, j));
                // printf("schematic=%d    row=%d    strlen(line)=%d   i=%d    j=%d\n", schematic, row, strlen(line), i, j);
                if (isValid(schematic, row, strlen(line), i, j)) {
                    partvalid = true;
                }
                partnum *= 10; partnum += schematic[i][j]-'0';
            }

            if (counting && (!isDigit(schematic[i][j]) || j == strlen(line)-1)) {
                counting = false;
                if (partvalid) {
                    sum += partnum; 
                    // printf("%d ", partnum);
                }
                partnum = 0;
            }
        } 
        // printf("\n");
    }

    printf("%d\n", sum);

    return 0; 
}