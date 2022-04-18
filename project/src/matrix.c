#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

Matrix *create_matrix_from_file(const char *path_file) {
    if (!path_file) {
        return NULL;
    }

    FILE *file = fopen(path_file, "r");
    if (!file) {
        return NULL;
    }

    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(file, "%zu %zu", &rows, &cols) != 2) {
        fclose(file);
        return NULL;
    }

    Matrix *matrix = create_matrix(rows, cols);
    if (matrix == NULL) {
        fclose(file);
        return NULL;
    }

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            double val = 0;
            if (fscanf(file, "%lf", &val) != 1) {
                free_matrix(matrix);
                fclose(file);
                return NULL;
            }

            if (set_elem(matrix, i, j, val) != 0) {
                free_matrix(matrix);
                fclose(file);
                return NULL;
            }
        }
    }
    fclose(file);
    return matrix;
}

Matrix *create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = calloc(1, sizeof(Matrix) + (rows * cols) * sizeof(double));
    if (!matrix) {
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;

    return matrix;
}

void free_matrix(Matrix *matrix) {
    free(matrix);
}
