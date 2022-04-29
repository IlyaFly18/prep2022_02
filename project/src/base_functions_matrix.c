#include "matrix.h"

int get_rows(const Matrix *matrix, size_t *rows) {
    if (!matrix || !rows) {
        return NULL_ARG_IN_FUNC;
    }

    *rows = matrix->rows;

    return 0;
}

int get_cols(const Matrix *matrix, size_t *cols) {
    if (!matrix || !cols) {
        return NULL_ARG_IN_FUNC;
    }

    *cols = matrix->cols;

    return 0;
}

int get_elem(const Matrix *matrix, size_t row, size_t col, double *val) {
    if (!matrix || !val) {
        return NULL_ARG_IN_FUNC;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    if (row >= rows || col >= cols) {
        return INDEX_OUT_OF_RANGE;
    }

    *val = matrix->arr[row * matrix->cols + col];

    return 0;
}

int set_elem(Matrix *matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return NULL_ARG_IN_FUNC;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    if (row >= rows || col >= cols) {
        return INDEX_OUT_OF_RANGE;
    }

    matrix->arr[row * matrix->cols + col] = val;

    return 0;
}
