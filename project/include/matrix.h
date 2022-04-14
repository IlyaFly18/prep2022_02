#ifndef PROJECT_INCLUDE_MATRIX_H_
#define PROJECT_INCLUDE_MATRIX_H_

#include <stddef.h>

enum ERRORS {
    BAD_READ_FROM_FILE = -1,
    NULL_PTR_IN_ARGS_OF_FUNC = -2,
    INDEX_OUT_OF_RANGE = -3,
    ERR_GET_ROWS_OR_COLS = -4,
    ERR_ROWS_AND_COLS_NOT_EQUAL = -5,
    ERR_GET_ELEM = -6,
    ERR_IN_CYCLE_IN_DET = -7,
    ERR_REALLOC = -8,
    NULL_MATRIX_ARR = -9,
    ERR_SET_ELEM = -10,
    NULL_EXTRA_MINOR = -11,
    ERR_DET = -12,
};


typedef struct Matrix {
    size_t rows;
    size_t cols;
    double *arr;
} Matrix;

// Init/release operations
Matrix *create_matrix_from_file(const char *path_file);
Matrix *create_matrix(size_t rows, size_t cols);
void free_matrix(Matrix *matrix);

// Basic operations
int get_rows(const Matrix *matrix, size_t *rows);
int get_cols(const Matrix *matrix, size_t *cols);
int get_rows_and_cols(const Matrix *matrix, size_t *rows, size_t *cols);
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
