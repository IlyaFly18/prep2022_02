#include "matrix.h"
#include "exceptions.h"

namespace prep {
Matrix::Matrix(size_t rows, size_t cols) {
    this->rows = rows;
    this->cols = cols;
    this->arr = new double[rows * cols];
}

Matrix::Matrix(const Matrix& rhs) {
    rows = rhs.rows;
    cols = rhs.cols;
    arr = new double[rows * cols];
    for (size_t i = 0; i < rows * cols; ++i) {
        arr[i] = rhs.arr[i];
    }
}

Matrix& Matrix::operator=(const Matrix& rhs) {
    if (&rhs != this) {
        rows = rhs.rows;
        cols = rhs.cols;
        delete[] arr;
        arr = new double[rows * cols];
        for (size_t i = 0; i < rows * cols; ++i) {
            arr[i] = rhs.arr[i];
        }
    }
    return *this;
}

Matrix::Matrix(std::istream& is) {
    rows = 0;
    cols = 0;
    if (!(is >> rows >> cols)) {
        throw InvalidMatrixStream();
    }
    arr = new double[rows * cols];
    for (size_t i = 0; i < rows * cols; ++i) {
        if (!(is >> arr[i])) {
            delete[] arr;
            throw InvalidMatrixStream();
        }
    }
}

Matrix::~Matrix() {
    delete[] arr;
}
}  // namespace prep
