#include "matrix.h"

Matrix *mul_scalar(const Matrix *matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 || get_cols(matrix, &cols) != 0) {
        return NULL;
    }

    Matrix *new_matrix = create_matrix(rows, cols);
    if (new_matrix == NULL) {
        return NULL;
    }

    int flag = 0;
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            double val_in_matrix = 0;
            if (get_elem(matrix, r, c, &val_in_matrix) != 0) {
                flag = -1;
            }
            if (set_elem(new_matrix, r, c, val_in_matrix * val) != 0) {
                flag = -1;
            }
        }
    }
    if (flag != 0) {  // TODO(Ilya): Везде прописать удаление матрицы.
        return NULL;
    }

    return new_matrix;
}

Matrix *transp(const Matrix *matrix) {
    if (matrix == NULL) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (get_rows(matrix, &rows) != 0 || get_cols(matrix, &cols) != 0) {
        return NULL;
    }

    Matrix *new_matrix = create_matrix(cols, rows);
    if (new_matrix == NULL) {
        return NULL;
    }

    int flag = 0;
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            double val_in_matrix = 0;
            if (get_elem(matrix, r, c, &val_in_matrix) != 0) {
                flag = -1;
            }
            if (set_elem(new_matrix, c, r, val_in_matrix) != 0) {
                flag = -1;
            }
        }
    }
    if (flag != 0) {
        return NULL;
    }

    return new_matrix;
}

Matrix *sum(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL) {
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

    Matrix *new_matrix = create_matrix(rows_l, cols_l);
    if (new_matrix == NULL) {
        return NULL;
    }

    int flag = 0;
    for (size_t i = 0; i < rows_l; ++i) {
        for (size_t j = 0; j < cols_l; ++j) {
            double val_in_matrix_l = 0;
            double val_in_matrix_r = 0;
            if (get_elem(l, i, j, &val_in_matrix_l) != 0 ||
                get_elem(r, i, j, &val_in_matrix_r) != 0) {
                flag = -1;
            }
            if (set_elem(new_matrix, i, j, val_in_matrix_l + val_in_matrix_r) != 0) {
                flag = -1;
            }
        }
    }
    if (flag != 0) {
        return NULL;
    }

    return new_matrix;
}

Matrix *sub(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL) {
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

    Matrix *new_matrix = create_matrix(rows_l, cols_l);
    if (new_matrix == NULL) {
        return NULL;
    }

    int flag = 0;
    for (size_t i = 0; i < rows_l; ++i) {
        for (size_t j = 0; j < cols_l; ++j) {
            double val_in_matrix_l = 0;
            double val_in_matrix_r = 0;
            if (get_elem(l, i, j, &val_in_matrix_l) != 0 ||
                get_elem(r, i, j, &val_in_matrix_r) != 0) {
                flag = -1;
            }
            if (set_elem(new_matrix, i, j, val_in_matrix_l - val_in_matrix_r) != 0) {
                flag = -1;
            }
        }
    }
    if (flag != 0) {
        return NULL;
    }

    return new_matrix;
}

Matrix *mul(const Matrix *l, const Matrix *r) {
    if (l == NULL || r == NULL) {
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

    Matrix *new_matrix = create_matrix(rows_l, cols_r);
    if (new_matrix == NULL) {
        return NULL;
    }

    int flag = 0;
    for (size_t row_l = 0; row_l < rows_l; ++row_l) {
        for (size_t col_r = 0; col_r < cols_r; ++col_r) {
            double new_elem = 0;
            for (size_t ind = 0; ind < cols_l; ++ind) {
                double val_in_matrix_l = 0;
                double val_in_matrix_r = 0;
                if (get_elem(l, row_l, ind, &val_in_matrix_l) != 0 ||
                    get_elem(r, ind, col_r, &val_in_matrix_r) != 0) {
                    flag = -1;
                }
                new_elem += val_in_matrix_l * val_in_matrix_r;
            }
            if (set_elem(new_matrix, row_l, col_r, new_elem) != 0) {
                flag = -1;
            }
        }
    }
    if (flag != 0) {
        return NULL;
    }

    return new_matrix;
}
