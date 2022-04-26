#include "matrix.h"
#include "exceptions.h"

#include <cmath>


namespace prep {
double minus_one_pow(size_t exp) {
    return 1 - 2 * (double)(exp % 2);
}


double Matrix::det_without_used_cells(bool* used_rows, bool* used_cols) const {
    if (!used_rows || !used_cols) {
        throw NullPtrInFuncArgs();
    }

    if (rows != cols) {
        throw DimensionMismatch(*this);
    }

    size_t cnt_used_rows = 0;
    for (size_t i = 0; i < rows; ++i) {
        if (used_rows[i]) {
            cnt_used_rows++;
        }
    }
    if (cnt_used_rows == rows - 1) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (!used_rows[i] && !used_cols[j]) {
                    return (*this)(i, j);
                }
            }
        }
    }

    size_t i = 0;
    while (used_rows[i]) {
        i++;
    }
    used_rows[i] = true;

    double det_ans = 0.0;
    for (size_t j = 0, j_in_submatrix = 0; j < cols; ++j) {
        if (!used_cols[j]) {
            used_cols[j] = true;

            double det_res = (*this).det_without_used_cells(used_rows, used_cols);
            det_ans += minus_one_pow(j_in_submatrix) * (*this)(i, j) * det_res;

            used_cols[j] = false;
            j_in_submatrix++;
        }
    }

    return det_ans;
}

double Matrix::det() const {
    if (rows != cols) {
        throw DimensionMismatch(*this);
    }

    bool* used_rows = new bool[rows];
    bool* used_cols = new bool[cols];
    double det_ans = det_without_used_cells(used_rows, used_cols);

    delete[] used_rows;
    delete[] used_cols;
    return det_ans;
}

Matrix Matrix::adj() const {
    if (cols != rows) {
        throw DimensionMismatch(*this);
    }

    Matrix res = Matrix(rows, cols);
    if (rows == 1) {
        res(0, 0) = 1;
        return res;
    }

    bool* used_rows = new bool[rows];
    bool* used_cols = new bool[cols];

    for (size_t i = 0; i < rows; ++i) {
        used_rows[i] = true;
        for (size_t j = 0; j < cols; ++j) {
            used_cols[j] = true;

            double det_dop = det_without_used_cells(used_rows, used_cols);
            res(i, j) = minus_one_pow(i + j) * det_dop;

            used_cols[j] = false;
        }
        used_rows[i] = false;
    }

    delete[] used_rows;
    delete[] used_cols;
    return res;
}

Matrix Matrix::inv() const {
    if (rows != cols) {
        throw DimensionMismatch(*this);
    }

    Matrix adj_matrix = this->adj();
    double det = this->det();
    if (det < EPS) {
        throw SingularMatrix();
    }

    return adj_matrix * (1 / det);
}

}  // namespace prep
