#include "constants.h"
#include "transfer.h"

int scanf_transfer(FILE *stream, transfer *transfer) {
    if (stream == NULL || transfer == NULL)
        return NULL_PTR_IN_ARGS;

    int return_scanf = fscanf(stream, "%3d %6lf",
                              &transfer->number, &transfer->cash_payments);
    if (return_scanf == EOF || return_scanf != NUM_OF_FIELDS_TRANSFER)
        return WRONG_SCANF;
    return 0;
}

int print_transfer(FILE *stream, transfer *transfer) {
    if (stream == NULL || transfer == NULL)
        return NULL_PTR_IN_ARGS;

    fprintf(stream, "%-3d%-6.2f\n",
            transfer->number, transfer->cash_payments);
    return 0;
}

int print_transfer_pattern(FILE *stream) {
    if (stream == NULL)
        return NULL_PTR_IN_ARGS;

    return fprintf(stream, "%s\n%s\n",
                   "1 Number account:",
                   "2 Client cash payments: ");
}
