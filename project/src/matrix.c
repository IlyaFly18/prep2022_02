#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

static int read_matrix_from_file(FILE *file, Matrix *matrix) {
    if (file == NULL || matrix == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    if (fscanf(file, "%zu %zu", &matrix->rows, &matrix->cols) != 2) {
        return BAD_READ_FROM_FILE;
    }

    size_t len_for_arr = matrix->rows * matrix->cols;
    matrix->arr = realloc(matrix->arr, len_for_arr * sizeof(double));

    int flag = 0;
    for (size_t i = 0; i < len_for_arr; ++i) {
        if (fscanf(file, "%lf", &matrix->arr[i]) != 1) {
            flag = -1;
        }
    }
    if (flag != 0) {
        return BAD_READ_FROM_FILE;
    }
    return 0;
}

Matrix *create_matrix_from_file(const char *path_file) {
    if (path_file == NULL) {
        return NULL;
    }

    FILE *file = fopen(path_file, "r");
    if (file == NULL) {
        return NULL;
    }

    Matrix *matrix = calloc(1, sizeof(Matrix));
    if (matrix == NULL) {
        fclose(file);
        return NULL;
    }

    if (read_matrix_from_file(file, matrix) != 0) {
        fclose(file);
        free_matrix(matrix);
        return NULL;
    }

    fclose(file);
    return matrix;
}

Matrix *create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = calloc(1, sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }

    matrix->arr = calloc(rows * cols, sizeof(double));
    if (matrix->arr == NULL) {
        free_matrix(matrix);
        return NULL;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    return matrix;
}

void free_matrix(Matrix *matrix) {
    if (matrix == NULL) {
        return;
    }
    if (matrix->arr != NULL) {
        free(matrix->arr);
    }
    free(matrix);
}


