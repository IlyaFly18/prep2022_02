#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>

enum ERRORS {
    NULL_ARG_IN_FUNC = -2,
    INDEX_OUT_OF_RANGE = -3,
    ERR_GET_ROWS_OR_COLS = -4,
    ERR_ROWS_AND_COLS_NOT_EQUAL = -5,
    ERR_GET_ELEM = -6,
    ERR_DET = -12,
    ERR_CALLOC = -13,
};

typedef struct Matrix {
    size_t rows;
    size_t cols;
    double arr[];
} Matrix;

// Init/release operations
Matrix *create_matrix_from_file(const char *path_file);
Matrix *create_matrix(size_t rows, size_t cols);
void free_matrix(Matrix *matrix);

// Basic operations
int get_rows(const Matrix *matrix, size_t *rows);
int get_cols(const Matrix *matrix, size_t *cols);
int get_elem(const Matrix *matrix, size_t row, size_t col, double *val);
int set_elem(Matrix *matrix, size_t row, size_t col, double val);

// Math operations
Matrix *mul_scalar(const Matrix *matrix, double val);
Matrix *transp(const Matrix *matrix);
Matrix *sum(const Matrix *l, const Matrix *r);
Matrix *sub(const Matrix *l, const Matrix *r);
Matrix *mul(const Matrix *l, const Matrix *r);

// Extra operations
int det(const Matrix *matrix, double *val);
Matrix *adj(const Matrix *matrix);
Matrix *inv(const Matrix *matrix);

#endif  // PROJECT_INCLUDE_MATRIX_H_
