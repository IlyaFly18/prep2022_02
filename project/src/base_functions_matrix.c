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

int get_elem(const Matrix *matrix, size_t row, size_t col, double *val) {
    if (matrix == NULL || val == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    if (row >= matrix->rows || col >= matrix->cols) {
        return INDEX_OUT_OF_RANGE;
    }

    *val = matrix->arr[row * matrix->cols + col];
    return 0;
}

int set_elem(Matrix *matrix, size_t row, size_t col, double val) {
    if (matrix == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    if (row >= matrix->rows || col >= matrix->cols) {
        return INDEX_OUT_OF_RANGE;
    }

    matrix->arr[row * matrix->cols + col] = val;

    return 0;
}
