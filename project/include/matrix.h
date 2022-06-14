#pragma once // NOLINT

#include <istream>
#include <functional>
#include <vector>


namespace prep {
static constexpr double EPS = 1e-07;

class Matrix {
 private:
    size_t rows;
    size_t cols;
    double* arr;

    Matrix add_or_sub_matrix(const Matrix& rhs,
                             std::function<double(double, double)>(func)) const;
    double det_without_used_cells(std::vector<bool> used_rows, std::vector<bool> used_cols) const;

 public:
    explicit Matrix(size_t rows = 0, size_t cols = 0);
    explicit Matrix(std::istream& is);
    Matrix(const Matrix& rhs);
    Matrix& operator=(const Matrix& rhs);
    ~Matrix();

    size_t getRows() const;
    size_t getCols() const;
    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);

    bool operator==(const Matrix& rhs) const;
    bool operator!=(const Matrix& rhs) const;

    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(double val) const;

    friend Matrix operator*(double val, const Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend void swap(Matrix& l, Matrix& r);

    Matrix transp() const;
    double det() const;
    Matrix adj() const;
    Matrix inv() const;
};

double minus_one_pow(size_t deg);


Matrix operator*(double val, const Matrix& matrix);


std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}  // namespace prep
