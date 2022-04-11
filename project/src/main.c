#include "matrix.h"

#include <stdio.h>

int main(void) {
    Matrix* matrix = create_matrix_from_file("matrix.dat");
    if (matrix == NULL) {
        return -1;
    }
    Matrix *inv_matrix = inv(matrix);
    printf("////  %zu %zu %lf  ////", inv_matrix->rows, inv_matrix->cols, inv_matrix->arr[0]);
    free_matrix(matrix);
    free_matrix(inv_matrix);
    return 0;
}

