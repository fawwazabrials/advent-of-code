#ifndef _MATRIX_H
#define _MATRIX_H

#include <limits.h>
#include <stdbool.h>

#define INVALID_DETERMINANT INT_MIN

typedef struct matrix_s {
    unsigned int num_rows;
    unsigned int num_cols;
    double **contents;
} matrix;

/* Constructor & Destructors */
matrix matrix_new(unsigned int num_rows, unsigned int num_cols);
void matrix_free(matrix* mt);
void matrix_freeall(matrix* mt);
void matrix_cpy(matrix *dest, matrix *source);

/* Selectors */
matrix matrix_get_row(matrix *mt, unsigned int row);
matrix matrix_get_col(matrix *mt, unsigned int col);
double matrix_get_cell(matrix *mt, unsigned int row, unsigned int col);

/* Equality Check */
bool matrix_eqdim(matrix *mt1, matrix *mt2);
bool matrix_eq(matrix *mt1, matrix *mt2, double tolerance);
bool matrix_square(matrix *mt);

/* Output */
void matrix_printf(matrix *m1);

/* Operations */
int matrix_add(matrix *mt1, matrix *mt2);
int matrix_subtr(matrix *mt1, matrix *mt2);
int matrix_smult(matrix *mt, double n);
int matrix_mult(matrix *mt1, matrix *mt2);
double matrix_determnt(matrix *mt);

/* Transformation */
int matrix_minor_mt(matrix *dest, matrix *mt, int row, int col);
int matrix_cofactor_mt(matrix *dest, matrix *mt);
int matrix_adjoint_mt(matrix *dest, matrix *mt);
int matrix_transpose(matrix *mt);
int matrix_invrs(matrix *mt);

#endif