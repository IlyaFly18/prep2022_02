#include "matrix.h"

Matrix *mul_scalar(const Matrix *matrix, double val) {
    if (!matrix) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return NULL;
    }

    Matrix *res_matrix = create_matrix(rows, cols);
    if (!res_matrix) {
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            double val_in_matrix = 0.0;

            if (get_elem(matrix, i, j, &val_in_matrix) != 0) {
                free_matrix(res_matrix);
                return NULL;
            }

            if (set_elem(res_matrix, i, j, val_in_matrix * val) != 0) {
                free_matrix(res_matrix);
                return NULL;
            }
        }
    }

    return res_matrix;
}

Matrix *transp(const Matrix *matrix) {
    if (!matrix) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 ||
        get_cols(matrix, &cols) != 0) {
        return NULL;
    }

    Matrix *res_matrix = create_matrix(cols, rows);
    if (!res_matrix) {
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            double val_in_matrix = 0.0;

            if (get_elem(matrix, i, j, &val_in_matrix) != 0) {
                free_matrix(res_matrix);
                return NULL;
            }

            if (set_elem(res_matrix, j, i, val_in_matrix) != 0) {
                free_matrix(res_matrix);
                return NULL;
            }
        }
    }

    return res_matrix;
}

static inline double sum_double(double a, double b) {
    return a + b;
}

static inline double sub_double(double a, double b) {
    return a - b;
}

static Matrix *sum_or_sub_matrix(const Matrix *l, const Matrix *r,
                                 double (*sum_or_sub_double_func)(double, double)) {
    if (!l || !r) {
        return NULL;
    }

    size_t rows_l = 0;
    size_t cols_l = 0;
    size_t rows_r = 0;
    size_t cols_r = 0;
    if (get_rows(l, &rows_l) != 0 ||
        get_cols(l, &cols_l) != 0 ||
        get_rows(r, &rows_r) != 0 ||
        get_cols(r, &cols_r) != 0) {
        return NULL;
    }

    if (cols_l != cols_r || rows_l != rows_r) {
        return NULL;
    }

    Matrix *res_matrix = create_matrix(rows_l, cols_l);
    if (!res_matrix) {
        return NULL;
    }

    for (size_t i = 0; i < rows_l; ++i) {
        for (size_t j = 0; j < cols_l; ++j) {
            double val_in_matrix_l = 0.0;
            double val_in_matrix_r = 0.0;

            if (get_elem(l, i, j, &val_in_matrix_l) != 0 ||
                get_elem(r, i, j, &val_in_matrix_r) != 0) {
                free_matrix(res_matrix);
                return NULL;
            }

            if (set_elem(res_matrix, i, j,
                         sum_or_sub_double_func(val_in_matrix_l, val_in_matrix_r)) != 0) {
                free_matrix(res_matrix);
                return NULL;
            }
        }
    }

    return res_matrix;
}

Matrix *sum(const Matrix *l, const Matrix *r) {
    Matrix *res_matrix = sum_or_sub_matrix(l, r, sum_double);
    if (!res_matrix) {
        return NULL;
    }

    return res_matrix;
}

Matrix *sub(const Matrix *l, const Matrix *r) {
    Matrix *res_matrix = sum_or_sub_matrix(l, r, sub_double);
    if (!res_matrix) {
        return NULL;
    }

    return res_matrix;
}

Matrix *mul(const Matrix *l, const Matrix *r) {
    if (!l || !r) {
        return NULL;
    }

    size_t rows_l = 0;
    size_t cols_l = 0;
    size_t rows_r = 0;
    size_t cols_r = 0;
    if (get_rows(l, &rows_l) != 0 ||
        get_cols(l, &cols_l) != 0 ||
        get_rows(r, &rows_r) != 0 ||
        get_cols(r, &cols_r) != 0) {
        return NULL;
    }

    if (rows_l != cols_r) {
        return NULL;
    }

    Matrix *res_matrix = create_matrix(rows_l, cols_r);
    if (!res_matrix) {
        return NULL;
    }

    for (size_t row_l = 0; row_l < rows_l; ++row_l) {
        for (size_t col_r = 0; col_r < cols_r; ++col_r) {
            double new_elem = 0.0;

            for (size_t ind = 0; ind < cols_l; ++ind) {
                double val_in_matrix_l = 0.0;
                double val_in_matrix_r = 0.0;

                if (get_elem(l, row_l, ind, &val_in_matrix_l) != 0 ||
                    get_elem(r, ind, col_r, &val_in_matrix_r) != 0) {
                    free_matrix(res_matrix);
                    return NULL;
                }

                new_elem += val_in_matrix_l * val_in_matrix_r;
            }

            if (set_elem(res_matrix, row_l, col_r, new_elem) != 0) {
                free_matrix(res_matrix);
                return NULL;
            }
        }
    }

    return res_matrix;
}
