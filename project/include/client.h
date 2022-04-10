#ifndef PROJECT_INCLUDE_CLIENT_H_
#define PROJECT_INCLUDE_CLIENT_H_

#include <stdio.h>

enum BUF_SIZE_FOR_CLIENT {
    TOTAL_BUF_SIZE = 200,
    BUF_SIZE_FOR_NAME = 20,
    BUF_SIZE_FOR_SURNAME = 20,
    BUF_SIZE_FOR_ADDRESS = 20,
    BUF_SIZE_FOR_TEL_NUMBER = 15,
};

typedef struct {
    int number;
    char name[BUF_SIZE_FOR_NAME];
    char surname[BUF_SIZE_FOR_SURNAME];
    char address[BUF_SIZE_FOR_ADDRESS];
    char tel_number[BUF_SIZE_FOR_TEL_NUMBER];
    double indebtedness;
    double credit_limit;
    double cash_payments;
} client;

#endif  // PROJECT_INCLUDE_CLIENT_H_
