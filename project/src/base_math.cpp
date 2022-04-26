#include "matrix.h"
#include "exceptions.h"

namespace prep {
double add_double(double l, double r) {
    return l + r;
}

double sub_double(double l, double r) {
    return l - r;
}

Matrix Matrix::add_or_sub_matrix(const Matrix& rhs,
                                 double(*func)(double, double)) const {
    if (!func) {
        throw NullPtrInFuncArgs();
    }
    if (rows != rhs.rows || cols != rhs.cols) {
        throw DimensionMismatch(*this, rhs);
    }

    Matrix res(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            res(i, j) = func((*this)(i, j), rhs(i, j));
        }
    }

    return res;
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    Matrix res = add_or_sub_matrix(rhs, add_double);

    return res;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    Matrix res = add_or_sub_matrix(rhs, sub_double);

    return res;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    if (cols != rhs.rows) {
        throw DimensionMismatch(*this, rhs);
    }

    Matrix res(rows, rhs.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < rhs.cols; ++j) {
            double val_in_matrix = 0.0;
            for (size_t k = 0; k < cols; ++k) {
                val_in_matrix += (*this)(i, k) * rhs(k, j);
            }
            res(i, j) = val_in_matrix;
        }
    }

    return res;
}

Matrix Matrix::transp() const {
    Matrix res(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            res(j, i) = (*this)(i, j);
        }
    }

    return res;
}

Matrix Matrix::operator*(double val) const {
    Matrix res(*this);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            res(i, j) *= val;
        }
    }

    return res;
}

Matrix operator*(double val, const Matrix& matrix) {
    return matrix * val;
}
}  // namespace prep

