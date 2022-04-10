#include "client.h"
#include "utils.h"
#include "read_and_print_data.h"
#include "test_print_to_file.h"

#include <string.h>

enum ERROR_RETURN_CODES {
    ERR_READ_DATA = -1,
    ERR_PRINT_DATA = -2,
    WRONG_COMPARISON = -3,
    WRONG_COMPARISON_PERSONS = -4,
    WRONG_COMPARISON_TRANSACTIONS = -5,
    NULL_PTR_IN_ARGS_OF_FUNC = -6,
    ERR_UPDATE_DATA = -7,
    WRONG_COMPARISON_UPDATED_PERSONS = -8,
};

static int compare_persons(client *person1, client *person2) {
    if (person1 == NULL || person2 == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    if (person1->number != person2->number ||
        strcmp(person1->name, person2->name) != 0 ||
        strcmp(person1->surname, person2->surname) != 0 ||
        strcmp(person1->address, person2->address) != 0 ||
        strcmp(person1->tel_number, person2->tel_number) != 0 ||
        person1->indebtedness != person2->indebtedness ||
        person1->credit_limit != person2->credit_limit ||
        person1->cash_payments != person2->cash_payments) {
        return WRONG_COMPARISON_PERSONS;
    }

    return 0;
}

static int compare_transactions(client *transaction1, client *transaction2) {
    if (transaction1 == NULL || transaction2 == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    if (transaction1->number != transaction2->number ||
        transaction1->cash_payments != transaction2->cash_payments) {
        return WRONG_COMPARISON_TRANSACTIONS;
    }

    return 0;
}

static int test_print_data_to_file(client *data_expected,
                                   int (*print_data)(FILE *, client *),
                                   int (*read_data)(FILE *, client *),
                                   int (*compare_got_and_expected_data)(client *, client *)) {
    if (data_expected == NULL) {
        return NULL_PTR_IN_ARGS_OF_FUNC;
    }

    FILE *file = fopen("test_read_and_print_data.dat", "w+");

    if (print_data(file, data_expected) != 0) {
        fclose(file);
        return ERR_PRINT_DATA;
    }

    rewind(file);

    client data_got = {0};
    if (read_data(file, &data_got) != 0) {
        fclose(file);
        return ERR_READ_DATA;
    }

    if (compare_got_and_expected_data(data_expected, &data_got) != 0) {
        fclose(file);
        return WRONG_COMPARISON;
    }

    fclose(file);
    return 0;
}

int test_print_person() {
    client person_expected = {.number = 10,
            .name = "name",
            .surname = "surname",
            .address = "Moscow",
            .tel_number = "tel_number",
            .indebtedness = 2000,
            .credit_limit = 3000,
            .cash_payments = 4000};

    test_print_data_to_file(&person_expected,
                            print_person,
                            read_person,
                            compare_persons);

    return 0;
}

int test_print_transaction() {
    client transaction_expected = {.number = 10,
                                   .cash_payments = 4000};

    test_print_data_to_file(&transaction_expected,
                            print_transaction,
                            read_transaction,
                            compare_transactions);

    return 0;
}

int test_update_clients() {
    client person = {.number = 10,
            .name = "name",
            .surname = "surname",
            .address = "Moscow",
            .tel_number = "tel_number",
            .indebtedness = 2000,
            .credit_limit = 3000,
            .cash_payments = 4000};

    client transaction = {.number = 10,
            .cash_payments = 4000};

    client update_person_expected = person;
    update_person_expected.credit_limit = person.credit_limit + transaction.cash_payments;

    FILE* clients_file = fopen("record.dat", "w+");
    if (print_person(clients_file, &person) != 0) {
        fclose(clients_file);
        return ERR_PRINT_DATA;
    }
    FILE* transactions_file = fopen("transaction.dat", "w+");
    if (print_transaction(transactions_file, &transaction) != 0) {
        fclose(clients_file);
        fclose(transactions_file);
        return ERR_PRINT_DATA;
    }
    rewind(clients_file);
    rewind(transactions_file);

    FILE* clients_after_transactions = fopen("blackrecord.dat", "w+");
    if (update_clients(clients_file, transactions_file, clients_after_transactions) != 0) {
        fclose(clients_file);
        fclose(transactions_file);
        fclose(clients_after_transactions);
        return ERR_UPDATE_DATA;
    }
    rewind(clients_after_transactions);

    client update_person_got = {0};
    if (read_person(clients_after_transactions, &update_person_got) != 0) {
        fclose(clients_file);
        fclose(transactions_file);
        fclose(clients_after_transactions);
        return ERR_READ_DATA;
    }

    if (compare_persons(&update_person_expected, &update_person_got) != 0) {
        fclose(clients_file);
        fclose(transactions_file);
        fclose(clients_after_transactions);
        return WRONG_COMPARISON_UPDATED_PERSONS;
    }

    fclose(clients_file);
    fclose(transactions_file);
    fclose(clients_after_transactions);
    return 0;
}
