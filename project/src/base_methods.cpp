#include "matrix.h"
#include "exceptions.h"

#include <cmath>
#include <iomanip>
#include <limits>


namespace prep {
size_t Matrix::getRows() const {
    return this->rows;
}

size_t Matrix::getCols() const {
    return this->cols;
}

double Matrix::operator()(size_t i, size_t j) const {
    if (i >= rows || j >= cols) {
        throw OutOfRange(i, j, *this);
    }
    return arr[i * cols + j];
}

double& Matrix::operator()(size_t i, size_t j) {
    if (i >= rows || j >= cols) {
        throw OutOfRange(i, j, *this);
    }
    return arr[i * cols + j];
}

bool Matrix::operator==(const Matrix& rhs) const {
    if (cols != rhs.cols || rows != rhs.rows) {
        return false;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (fabs((*this)(i, j) - rhs(i, j)) >= 1e-07) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& rhs) const {
    return (!(*this == rhs));
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << matrix.rows << " " << matrix.cols << std::endl;

    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            os << std::setprecision(std::numeric_limits<double>::max_digits10) << matrix(i, j);
            if (j != matrix.cols - 1) {
                os << " ";
            }
        }
        os << std::endl;
    }
    return os;
}



}  // namespace prep
