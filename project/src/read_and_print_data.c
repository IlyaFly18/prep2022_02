#include "client.h"
#include "read_and_print_data.h"

#include <stdlib.h>
#include <string.h>

#define TEMPLATE_FOR_INPUT_CLIENT_PERSON \
"1 Number account:\n" \
"2 Client name:\n" \
"3 Surname:\n" \
"4 Address client:\n" \
"5 Client telephone number:\n" \
"6 Client indebtedness:\n" \
"7 Client credit limit:\n" \
"8 Client cash payments:\n\n"

#define TEMPLATE_FOR_INPUT_CLIENT_TRANSACTION \
"1 Number account:\n" \
"2 Client cash payments:\n"

enum ERROR_RETURN_CODES {
    NULL_PTR_IN_ARGS_OF_FUNC = -1,
    BAD_SCAN_IN_READ_TRANSACTION = -2,
    BAD_SCAN_IN_READ_PERSON = -3,
    BAD_PRINT_IN_PRINT_PERSON = -4,
    BAD_PRINT_IN_PRINT_TRANSACTION = -5,
    ERR_IN_MALLOC = -6,
};

enum BUF_FOR_PRINT_PERSON_FIELDS {
    BUF_FOR_PRINT_PERSON_NUMBER = 12,
    BUF_FOR_PRINT_PERSON_NAME = 11,
    BUF_FOR_PRINT_PERSON_SURNAME = 11,
    BUF_FOR_PRINT_PERSON_ADDRESS = 16,
    BUF_FOR_PRINT_PERSON_TEL_NUMBER = 20,
    BUF_FOR_PRINT_PERSON_INDEBTEDNESS = 12,
    BUF_FOR_PRINT_PERSON_INDEBTEDNESS_AFTER_POINT = 2,
    BUF_FOR_PRINT_PERSON_CREDIT_LIMIT = 12,
    BUF_FOR_PRINT_PERSON_CREDIT_LIMIT_AFTER_POINT = 2,
    BUF_FOR_PRINT_PERSON_CASH_PAYMENTS = 12,
    BUF_FOR_PRINT_PERSON_CASH_PAYMENTS_AFTER_POINT = 2,
};

enum BUF_FOR_TRANSACTION_FIELDS {
    BUF_FOR_PRINT_TRANSACTION_NUMBER = 3,
    BUF_FOR_PRINT_TRANSACTION_CASH_PAYMENTS = 6,
    BUF_FOR_PRINT_TRANSACTION_CASH_PAYMENTS_AFTER_POINT = 2,
};

int read_person(FILE *stream, client *person) {
    if (stream == NULL || person == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    int scan_return_value = fscanf(stream, "%d%20s%20s%20s%15s%lf%lf%lf",
                                   &person->number,
                                   person->name,
                                   person->surname,
                                   person->address,
                                   person->tel_number,
                                   &person->indebtedness,
                                   &person->credit_limit,
                                   &person->cash_payments);

    if (scan_return_value != 8) {
        return BAD_SCAN_IN_READ_PERSON;
    }

    return 0;
}

int read_transaction(FILE *stream, client *transaction) {
    if (stream == NULL || transaction == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    int scan_return_value = fscanf(stream, "%d %lf",
                                   &transaction->number, &transaction->cash_payments);

    if (scan_return_value != 2) {
        return BAD_SCAN_IN_READ_TRANSACTION;
    }

    return 0;
}

static int generate_format_string_for_print_person(char *str, client *person) {
    int cnt_of_printed_symbols =
            snprintf(str, TOTAL_BUF_SIZE,
                     "%-*d%-*s%-*s%-*s%*s%*.*lf%*.*lf%*.*lf\n",
                     BUF_FOR_PRINT_PERSON_NUMBER, person->number,
                     BUF_FOR_PRINT_PERSON_NAME, person->name,
                     BUF_FOR_PRINT_PERSON_SURNAME, person->surname,
                     BUF_FOR_PRINT_PERSON_ADDRESS, person->address,
                     BUF_FOR_PRINT_PERSON_TEL_NUMBER, person->tel_number,
                     BUF_FOR_PRINT_PERSON_INDEBTEDNESS,
                     BUF_FOR_PRINT_PERSON_INDEBTEDNESS_AFTER_POINT, person->indebtedness,
                     BUF_FOR_PRINT_PERSON_CREDIT_LIMIT,
                     BUF_FOR_PRINT_PERSON_CREDIT_LIMIT_AFTER_POINT, person->credit_limit,
                     BUF_FOR_PRINT_PERSON_CASH_PAYMENTS,
                     BUF_FOR_PRINT_PERSON_CASH_PAYMENTS_AFTER_POINT, person->cash_payments);

    return cnt_of_printed_symbols;
}

static int generate_format_string_for_print_transaction(char *str, client *transaction) {
    int cnt_of_printed_symbols =
            snprintf(str, TOTAL_BUF_SIZE,
                     "%-*d%-*.*f\n",
                     BUF_FOR_PRINT_TRANSACTION_NUMBER, transaction->number,
                     BUF_FOR_PRINT_TRANSACTION_CASH_PAYMENTS,
                     BUF_FOR_PRINT_TRANSACTION_CASH_PAYMENTS_AFTER_POINT, transaction->cash_payments);

    return cnt_of_printed_symbols;
}

int print_person(FILE *stream, client *person) {
    if (stream == NULL || person == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    char *format_str = malloc(TOTAL_BUF_SIZE);
    if (format_str == NULL) {
        return ERR_IN_MALLOC;
    }

    if (fprintf(stream, "%-*s",
                generate_format_string_for_print_person(format_str, person),
                format_str) == -1) {
        free(format_str);
        return BAD_PRINT_IN_PRINT_PERSON;
    }
    free(format_str);
    return 0;
}

int print_transaction(FILE *stream, client *transaction) {
    if (stream == NULL || transaction == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    char *format_str = malloc(TOTAL_BUF_SIZE);
    if (format_str == NULL) {
        return ERR_IN_MALLOC;
    }

    if (fprintf(stream, "%-*s",
                generate_format_string_for_print_transaction(format_str, transaction), format_str) == -1) {
        free(format_str);
        return BAD_PRINT_IN_PRINT_TRANSACTION;
    }

    free(format_str);
    return 0;
}

int print_person_template_for_input(FILE *stream) {
    if (stream == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    fprintf(stream, TEMPLATE_FOR_INPUT_CLIENT_PERSON);

    return 0;
}

int print_transaction_template_for_input(FILE *stream) {
    if (stream == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    fprintf(stream, TEMPLATE_FOR_INPUT_CLIENT_TRANSACTION);

    return 0;
}
