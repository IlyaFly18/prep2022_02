#include "matrix.h"

#include <stdbool.h>
#include <stdlib.h>

static double pow_of_minus_one(size_t exp) {
    return (1 - 2 * (double) (exp % 2));
}

static int det_with_excluded_rows_and_cols(const Matrix *matrix,
                                           bool *used_rows, bool *used_cols,
                                           size_t used_cnt,
                                           double *val) {
    if (!matrix || !used_rows || !used_cols || !val) {
        return NULL_ARG_IN_FUNC;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return ERR_GET_ROWS_OR_COLS;
    }

    if (rows - 1 == used_cnt) {
        for (size_t i = 0; i < rows; ++i) {
            if (!used_rows[i]) {
                for (size_t j = 0; j < cols; ++j) {
                    if (!used_cols[j]) {
                        double val_in_matrix = 0.0;

                        if (get_elem(matrix, i, j, &val_in_matrix) != 0) {
                            return ERR_GET_ELEM;
                        }

                        *val = val_in_matrix;
                        return 0;
                    }
                }
            }
        }
    }

    size_t i = 0;
    while (used_rows[i]) {
        ++i;
    }

    double det_res = 0.0;
    size_t new_ind_j = 0;
    for (size_t j = 0; j < cols; ++j) {
        if (!used_cols[j]) {
            used_rows[i] = 1;
            used_cols[j] = 1;

            double val_in_matrix = 0.0;
            if (get_elem(matrix, i, j, &val_in_matrix) != 0) {
                return ERR_GET_ELEM;
            }

            double new_det = 0.0;
            if (det_with_excluded_rows_and_cols(matrix,
                                                used_rows, used_cols,
                                                used_cnt + 1,
                                                &new_det) != 0) {
                return ERR_DET;
            }

            used_rows[i] = 0;
            used_cols[j] = 0;

            det_res += pow_of_minus_one(new_ind_j) * val_in_matrix * new_det;

            new_ind_j++;
        }
    }

    *val = det_res;

    return 0;
}


int det(const Matrix *matrix, double *val) {
    if (!matrix || !val) {
        return NULL_ARG_IN_FUNC;
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

    if (rows == 1) {
        double el = 0.0;
        if (get_elem(matrix, 0, 0, &el) != 0) {
            return ERR_GET_ELEM;
        }
        *val = el;
        return 0;
    }

    bool *used_rows = calloc(rows, sizeof(bool));
    if (!used_rows) {
        return ERR_CALLOC;
    }
    bool *used_cols = calloc(cols, sizeof(bool));
    if (!used_cols) {
        free(used_rows);
        return ERR_CALLOC;
    }

    double det_res = 0.0;
    if (det_with_excluded_rows_and_cols(matrix, used_rows, used_cols, 0, &det_res) != 0) {
        free(used_rows);
        free(used_cols);
        return ERR_DET;
    }

    *val = det_res;

    free(used_rows);
    free(used_cols);
    return 0;
}

Matrix *adj(const Matrix *matrix) {
    if (!matrix) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return NULL;
    }

    if (rows != cols) {
        return NULL;
    }

    Matrix *adj_matrix = create_matrix(rows, cols);
    if (!adj_matrix) {
        return NULL;
    }

    if (rows == 1) {
        if (set_elem(adj_matrix, 0, 0, 1) != 0) {
            return NULL;
        }
        return adj_matrix;
    }

    bool *used_rows = calloc(rows, sizeof(bool));
    if (!used_rows) {
        free_matrix(adj_matrix);
        return NULL;
    }
    bool *used_cols = calloc(cols, sizeof(bool));
    if (!used_cols) {
        free(used_rows);
        free_matrix(adj_matrix);
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            used_rows[i] = 1;
            used_cols[j] = 1;

            double new_det = 0.0;
            if (det_with_excluded_rows_and_cols(matrix, used_rows, used_cols, 1, &new_det) != 0) {
                free(used_rows);
                free(used_cols);
                return NULL;
            }

            used_rows[i] = 0;
            used_cols[j] = 0;

            double val_in_adj_matrix = pow_of_minus_one(i + j) * new_det;
            if (set_elem(adj_matrix, j, i, val_in_adj_matrix) != 0) {
                free_matrix(adj_matrix);
                free(used_rows);
                free(used_cols);
                return NULL;
            }
        }
    }

    free(used_rows);
    free(used_cols);
    return adj_matrix;
}

Matrix *inv(const Matrix *matrix) {
    if (!matrix) {
        return NULL;
    }

    double det_matrix = 0.0;
    if (det(matrix, &det_matrix) != 0) {
        return NULL;
    }

    Matrix *adj_matrix = adj(matrix);
    if (!adj_matrix) {
        return NULL;
    }

    Matrix *inv_matrix = mul_scalar(adj_matrix, 1 / det_matrix);
    free_matrix(adj_matrix);
    if (!inv_matrix) {
        return NULL;
    }

    return inv_matrix;
}
