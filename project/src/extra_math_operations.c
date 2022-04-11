#include "matrix.h"
#include <stdio.h>

static Matrix *get_extra_minor(const Matrix *matrix, size_t rows, size_t cols, size_t row, size_t col) {
    if (matrix == NULL) {
        return NULL;
    }

    Matrix *extra_minor = create_matrix(rows - 1, cols - 1);
    if (extra_minor == NULL) {
        return NULL;
    }

    int flag = 0;
    for (size_t extra_minor_row = 0; extra_minor_row < rows; ++extra_minor_row) {
        if (extra_minor_row != row) {
            for (size_t extra_minor_col = 0; extra_minor_col < cols; ++extra_minor_col) {
                if (extra_minor_col != col) {
                    double val_in_matrix = 0;
                    if (get_elem(matrix, extra_minor_row, extra_minor_col, &val_in_matrix) != 0) {
                        flag = -1;
                    }
                    if (set_elem(extra_minor,
                                 extra_minor_row < row ? extra_minor_row : extra_minor_row - 1,
                                 extra_minor_col < col ? extra_minor_col : extra_minor_col - 1,
                                 val_in_matrix) != 0) {
                        flag = -1;
                    }
                }
            }
        }
    }
    if (flag != 0) {
        free_matrix(extra_minor);
        return NULL;
    }

    return extra_minor;
}


int det(const Matrix *matrix, double *val) {
    if (matrix == NULL || val == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    if (rows != cols) {
        return ERR_ROWS_AND_COLS_NOT_EQUAL;
    }

    if (rows == cols && rows == 1) {
        double el = 0;
        if (get_elem(matrix, 0, 0, &el) != 0) {
            return ERR_GET_ELEM;
        }
        *val = el;
        return 0;
    }

    int flag = 0;
    double det_res = 0;
    for (size_t i = 0; i < cols; ++i) {
        // printf("\n//// %lf ////\n", det_res);
        double val_in_matrix = 0;
        if (get_elem(matrix, 0, i, &val_in_matrix) != 0) {
            flag = -1;
        }
        // printf("\n//// %lf ////\n", val_in_matrix);
        Matrix *extra_minor = get_extra_minor(matrix, rows, cols, 0, i);
        if (extra_minor == NULL) {
            flag = -1;
            return flag;
        }
        // printf("\n//// %zu %zu %lf ////\n", extra_minor->rows, extra_minor->cols, extra_minor->arr[0]);
        double det_extra_minor = 0;
        if (det(extra_minor, &det_extra_minor) != 0) {
            flag = -1;
        }
        free_matrix(extra_minor);
        // printf("\n//// val_in_matrix: %lf   det_extra_minor: %lf ////\n", val_in_matrix, det_extra_minor);
        det_res += (1 - 2 * (double)(i % 2)) * val_in_matrix * det_extra_minor;
    }
    if (flag == -1) {
        return ERR_IN_CYCLE_IN_DET;
    }

    *val = det_res;
    // printf("\n//// %lf ////\n", det_res);
    return 0;
}

Matrix *adj(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return NULL;
    }

    Matrix *adj_matrix = create_matrix(rows, cols);
    if (adj_matrix == NULL) {
        return NULL;
    }

    int flag = 0;
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            Matrix *extra_minor = get_extra_minor(matrix, rows, cols, row, col);
            if (extra_minor == NULL) {
                flag = -1;
            }

            double det_extra_minor = 0;
            if (det(extra_minor, &det_extra_minor) != 0) {
                flag = -1;
            }
            free_matrix(extra_minor);
            // printf("\n//// det_extra_minor: %lf ////\n", det_extra_minor);
            double val_in_adj_matrix = (1 - 2 * (double)((row + col) % 2)) * det_extra_minor;
            if (set_elem(adj_matrix, col, row, val_in_adj_matrix) != 0) {
                flag = -1;
            }
        }
    }
    if (flag != 0) {
        free_matrix(adj_matrix);
        return NULL;
    }

    return adj_matrix;
}

Matrix *inv(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    double det_matrix = 0;
    if (det(matrix, &det_matrix) != 0) {
        return NULL;
    }

    Matrix *adj_matrix = adj(matrix);
    if (adj_matrix == NULL) {
        return NULL;
    }

    Matrix *inv_matrix = mul_scalar(adj_matrix, 1. / (double)det_matrix);
    printf("\n//// det_matrix: %lf ////\n", det_matrix);
    printf("\n//// %lf ////\n", adj_matrix->arr[0]);
    free_matrix(adj_matrix);
    if (inv_matrix == NULL) {
        return NULL;
    }

    return inv_matrix;
}

