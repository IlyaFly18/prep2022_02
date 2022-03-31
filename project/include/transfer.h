#ifndef PROJECT_INCLUDE_TRANSFER_H_
#define PROJECT_INCLUDE_TRANSFER_H_

#include <stdio.h>

#define NUM_OF_FIELDS_TRANSFER 2

typedef struct {
    int number;
    double cash_payments;
} transfer;

int scanf_transfer(FILE*, transfer*);

int print_transfer(FILE*, transfer*);

int print_transfer_pattern(FILE*);

#endif  // PROJECT_INCLUDE_TRANSFER_H_
