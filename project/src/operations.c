#include "operations.h"

void clients_write(FILE *clients_file, person person) {
    print_person_pattern(stdout);
    while (scanf_person(stdin, &person) == 0) {
        print_person(clients_file, &person);
        print_person_pattern(stdout);
    }
}

void transactions_write(FILE *clients_file, transfer transfer) {
    print_transfer_pattern(stdout);
    while (scanf_transfer(stdin, &transfer) == 0) {
        print_transfer(clients_file, &transfer);
        print_transfer_pattern(stdout);
    }
}

void clients_after_transactions_write(FILE *clients_file,
                                      FILE *transactions_file,
                                      FILE *clients_after_transactions_file,
                                      person person,
                                      transfer transfer) {
    while (scanf_person(clients_file, &person) == 0) {
        while (scanf_transfer(transactions_file, &transfer) == 0) {
            if (person.number == transfer.number && transfer.cash_payments != 0) {
                person.credit_limit += transfer.cash_payments;
            }
        }
        print_person(clients_after_transactions_file, &person);
        rewind(transactions_file);
    }
}
