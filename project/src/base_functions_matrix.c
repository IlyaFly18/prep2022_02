#include "matrix.h"

int get_rows(const Matrix *matrix, size_t *rows) {
    if (matrix == NULL || rows == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    *rows = matrix->rows;

    return 0;
}

int get_cols(const Matrix *matrix, size_t *cols) {
    if (matrix == NULL || cols == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    *cols = matrix->cols;

    return 0;
}

int get_rows_and_cols(const Matrix *matrix, size_t *rows, size_t *cols) {
    if (matrix == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    if (get_rows(matrix, rows) != 0 ||
        get_cols(matrix, cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    return 0;
}

int get_elem(const Matrix *matrix, size_t row, size_t col, double *val) {
    if (matrix == NULL || val == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    size_t rows = 0, cols = 0;
    if (get_rows_and_cols(matrix, &rows, &cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    if (row >= rows || col >= cols) {
        return INDEX_OUT_OF_RANGE;
    }

    if (matrix->arr == NULL) {
        return NULL_MATRIX_ARR;
    }

    *val = matrix->arr[row * matrix->cols + col];

    return 0;
}

int set_elem(Matrix *matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    size_t rows = 0, cols = 0;
    if (get_rows_and_cols(matrix, &rows, &cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    if (row >= rows || col >= cols) {
        return INDEX_OUT_OF_RANGE;
    }

    if (matrix->arr == NULL) {
        return NULL_MATRIX_ARR;
    }

    matrix->arr[row * matrix->cols + col] = val;

    return 0;
}
