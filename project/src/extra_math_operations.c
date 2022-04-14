#include "matrix.h"
#include <stdio.h>

static inline double pow_of_minus_one(size_t st) {
    return (1 - 2 * (double) (st % 2));
}

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
                        flag = ERR_GET_ELEM;
                    }
                    if (set_elem(extra_minor,
                                 extra_minor_row < row ? extra_minor_row : extra_minor_row - 1,
                                 extra_minor_col < col ? extra_minor_col : extra_minor_col - 1,
                                 val_in_matrix) != 0) {
                        flag = ERR_SET_ELEM;
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

    size_t rows = 0, cols = 0;
    if (get_rows_and_cols(matrix, &rows, &cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    if (rows != cols) {
        return ERR_ROWS_AND_COLS_NOT_EQUAL;
    }

    if (rows == 1) {
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
        double val_in_matrix = 0;
        if (get_elem(matrix, 0, i, &val_in_matrix) != 0) {
            flag = ERR_GET_ELEM;
        }

        Matrix *extra_minor = get_extra_minor(matrix, rows, cols, 0, i);
        if (extra_minor == NULL) {
            flag = NULL_EXTRA_MINOR;
            return flag;
        }

        double det_extra_minor = 0;
        if (det(extra_minor, &det_extra_minor) != 0) {
            flag = ERR_DET;
        }
        free_matrix(extra_minor);

        det_res += pow_of_minus_one(i) * val_in_matrix * det_extra_minor;
    }
    if (flag == -1) {
        return ERR_IN_CYCLE_IN_DET;
    }

    *val = det_res;

    return 0;
}

Matrix *adj(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    size_t rows = 0, cols = 0;
    if (get_rows_and_cols(matrix, &rows, &cols) != 0) {
        return NULL;
    }

    if (rows != cols) {
        return NULL;
    }

    Matrix *adj_matrix = create_matrix(rows, cols);
    if (adj_matrix == NULL) {
        return NULL;
    }

    if (rows == 1) {
        if (set_elem(adj_matrix, 0, 0, 1) != 0) {
            return NULL;
        }
        return adj_matrix;
    }

    int flag = 0;
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            Matrix *extra_minor = get_extra_minor(matrix, rows, cols, row, col);
            if (extra_minor == NULL) {
                flag = NULL_EXTRA_MINOR;
            }

            double det_extra_minor = 0;
            if (det(extra_minor, &det_extra_minor) != 0) {
                flag = ERR_DET;
            }
            free_matrix(extra_minor);

            double val_in_adj_matrix = pow_of_minus_one(row + col) * det_extra_minor;
            if (set_elem(adj_matrix, col, row, val_in_adj_matrix) != 0) {
                flag = ERR_SET_ELEM;
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

    Matrix *inv_matrix = mul_scalar(adj_matrix, 1 / det_matrix);
    free_matrix(adj_matrix);
    if (inv_matrix == NULL) {
        return NULL;
    }

    return inv_matrix;
}

