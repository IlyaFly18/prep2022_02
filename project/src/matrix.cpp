#include "matrix.h"
#include "exceptions.h"
#include <algorithm>

namespace prep {
Matrix::Matrix(size_t rows, size_t cols): rows(rows), cols(cols), arr(new double[rows * cols]) {}

Matrix::Matrix(const Matrix& rhs): rows(rhs.rows), cols(rhs.cols), arr(new double[rows * cols]) {
    for (size_t i = 0; i < rows * cols; ++i) {
        arr[i] = rhs.arr[i];
    }
}

void swap(Matrix& l, Matrix& r)
{
    using std::swap;

    swap(l.rows, r.rows);
    swap(l.cols, r.cols);
    swap(l.arr, r.arr);
}

Matrix& Matrix::operator=(const Matrix& rhs) {
    Matrix tmp(rhs);

    prep::swap(*this, tmp);
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
