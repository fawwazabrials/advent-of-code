#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>
#include "matrix.h"

matrix matrix_new(unsigned int num_rows, unsigned int num_cols) {
    matrix mt;

    mt.num_rows = num_rows;
    mt.num_cols = num_cols;
    mt.contents = (double**) malloc(num_rows * sizeof(double*));
    for (int i=0; i<num_rows; i++) {
        mt.contents[i] = (double*) malloc(num_cols * sizeof(double));
    }

    return mt;
}

void matrix_free(matrix* mt) {
    if (mt->contents != NULL) {
        for (int i=0; i<mt->num_rows; i++) {
            free(mt->contents[i]);
        } 
        free(mt->contents);
        mt->contents = NULL;  // Set to NULL after freeing
    }
}

void matrix_freeall(matrix* mt) {
    matrix_free(mt);
    free(mt);
}

void matrix_cpy(matrix *dest, matrix *source) {
    if (dest->contents != NULL) {
        matrix_free(dest);
    }
    *dest = matrix_new(source->num_rows, source->num_cols);
    for (int i=0; i<source->num_rows; i++) {
        for (int j=0; j<source->num_cols; j++) {
            dest->contents[i][j] = source->contents[i][j];
        }
    }
}


matrix matrix_get_row(matrix *mt, unsigned int row) {
    matrix mat_row = matrix_new(1, mt->num_cols);
    for (int i=0; i<mt->num_cols; i++) {
        mat_row.contents[0][i] = mt->contents[row][i];
    } return mat_row;
}

matrix matrix_get_col(matrix *mt, unsigned int col) {
    matrix mat_col = matrix_new(mt->num_rows, 1);
    for (int i=0; i<mt->num_rows; i++) {
        mat_col.contents[i][0] = mt->contents[i][col];
    } return mat_col;
}

double matrix_get_cell(matrix *mt, unsigned int row, unsigned int col) {
    return mt->contents[row][col];
}

bool matrix_eqdim(matrix *mt1, matrix *mt2) {
    return mt1->num_cols == mt2->num_cols && mt1->num_rows == mt2->num_rows;
}

bool matrix_eq(matrix *mt1, matrix *mt2, double tolerance) {
    if (!matrix_eqdim(mt1, mt2)) return 0;

    for (int i=0; i<mt1->num_rows; i++) {
        for (int j=0; j<mt1->num_cols; j++) {
            if (fabs(mt1->contents[i][j] - mt2->contents[i][j]) > tolerance) return 0;
        }
    }
    return 1;
}

bool matrix_square(matrix *mt) {
    return mt->num_cols == mt->num_rows;
}

void matrix_printf(matrix *mt) {
    for (int i=0; i<mt->num_rows; i++) {
        for (int j=0; j<mt->num_cols; j++) {
            printf("%lf\t", matrix_get_cell(mt, i, j));
        } printf("\n");
    } printf("\n");
}

int matrix_add(matrix *mt1, matrix *mt2) {
    if (!matrix_eqdim(mt1, mt2)) return 0;

    for (int i=0; i<mt1->num_rows; i++) {
        for (int j=0; j<mt1->num_cols; j++) {
            mt1->contents[i][j] += mt2->contents[i][j];
        }
    }
    return 1;
}

int matrix_subtr(matrix *mt1, matrix *mt2) {
    if (!matrix_eqdim(mt1, mt2)) return 0;

    for (int i=0; i<mt1->num_rows; i++) {
        for (int j=0; j<mt1->num_cols; j++) {
            mt1->contents[i][j] -= mt2->contents[i][j];
        }
    }
    return 1;
}

int matrix_smult(matrix *mt, double n) {
    for (int i=0; i<mt->num_rows; i++) {
        for (int j=0; j<mt->num_cols; j++) {
            mt->contents[i][j] *= n;
        }
    }
    return 1;
}

int matrix_mult(matrix *mt1, matrix *mt2) {
    if (mt1->num_cols != mt2->num_rows) return 0;

    matrix tmp = matrix_new(mt1->num_rows, mt2->num_cols);

    for (int i=0; i<mt1->num_rows; i++) {
        for (int j=0; j<mt1->num_cols; j++) {
            tmp.contents[i][j] = 0;
            for (int k=0; k<mt1->num_cols; k++) {
                tmp.contents[i][j] += mt1->contents[i][k] * mt2->contents[k][j];
            }
        }
    }

    matrix_cpy(mt1, &tmp);
    matrix_free(&tmp);
    return 1;
}

double matrix_determnt(matrix *mt) {
    if (!matrix_square(mt)) return INVALID_DETERMINANT;
    if (mt->num_rows == 1) return mt->contents[0][0];
    if (mt->num_rows == 2) return mt->contents[0][0] * mt->contents[1][1] - mt->contents[1][0] * mt->contents[0][1];

    matrix minor = matrix_new(mt->num_rows-1, mt->num_cols-1);
    double det = 0;
    for (int i=0; i<mt->num_cols; i++) {
        if (mt->contents[0][i] == 0) continue;
        matrix_minor_mt(&minor, mt, 0, i);

        double mindet = matrix_determnt(&minor);
        if (mindet == INVALID_DETERMINANT) {
            matrix_free(&minor);
            return INVALID_DETERMINANT;
        }
        det += pow(-1, i) * mt->contents[0][i] * mindet;
    }

    matrix_free(&minor);
    return det;
}

int matrix_minor_mt(matrix *dest, matrix *mt, int row, int col) {
    if (!matrix_square(mt)) return 0;
    if (row >= mt->num_rows || mt->num_rows < 0 || col >= mt->num_cols || mt->num_cols < 0) return 0;

    matrix tmp = matrix_new(mt->num_rows-1, mt->num_cols-1);

    int row_idx = 0;
    for (int i = 0; i < mt->num_rows; i++) {
        if (i == row) continue;
        
        int col_idx = 0;
        for (int j = 0; j < mt->num_cols; j++) {
            if (j == col) continue; 

            tmp.contents[row_idx][col_idx] = mt->contents[i][j];
            col_idx++;
        } row_idx++;
    }

    matrix_cpy(dest, &tmp);
    matrix_free(&tmp);
    return 1;
}

int matrix_cofactor_mt(matrix *dest, matrix *mt) {
    if (!matrix_square(mt)) return 0;

    matrix tmp = matrix_new(mt->num_rows, mt->num_cols);
    matrix minor = matrix_new(mt->num_rows-1, mt->num_cols-1);
    for (int i=0; i<mt->num_rows; i++) {
        for (int j=0; j<mt->num_cols; j++) {
            matrix_minor_mt(&minor, mt, i, j);
            tmp.contents[i][j] = pow(-1, i+j) * matrix_determnt(&minor);
        }
    }
    matrix_free(&minor);
    matrix_cpy(dest, &tmp);
    matrix_free(&tmp);
    return 1;
}

int matrix_adjoint_mt(matrix *dest, matrix *mt) {
    if (!matrix_square(mt)) return 0;

    matrix tmp = matrix_new(mt->num_rows, mt->num_cols);
    if (!matrix_cofactor_mt(&tmp, mt)) return 0;

    matrix_transpose(&tmp);
    matrix_cpy(dest, &tmp);
    matrix_free(&tmp);
    return 1;
}

int matrix_transpose(matrix *mt) {
    matrix tmp = matrix_new(mt->num_cols, mt->num_rows);
    for (int i=0; i<mt->num_rows; i++) {
        for (int j=0; j<mt->num_cols; j++) {
            tmp.contents[j][i] = mt->contents[i][j];
        }
    }

    matrix_cpy(mt, &tmp);
    matrix_free(&tmp);
    return 1;
}

int matrix_invrs(matrix *mt) {
    double det = matrix_determnt(mt);
    if (det == 0) {
        return 0;
    }

    matrix tmp = matrix_new(mt->num_rows, mt->num_cols);
    matrix_adjoint_mt(&tmp, mt);
    matrix_smult(&tmp, 1/det);
    matrix_cpy(mt, &tmp);
    matrix_free(&tmp);
    return 1;
}