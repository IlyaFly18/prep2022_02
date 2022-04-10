#include "utils.h"


enum ERROR_RETURN_CODES {
    ERR_PRINT_TO_FILE_USING_FUNC = -1,
    ERR_PRINT_CLIENTS_TO_FILE = -2,
    ERR_PRINT_TRANSACTIONS_TO_FILE = -3,
    ERR_PRINT_CLIENT_OBJ_TEMPLATE_FOR_INPUT = -4,
    ERR_PRINT_CLIENT_OBJ = -5,
    NULL_DESCRIPTOR_OF_FILE = -6,
};

static int print_to_file_using_func(FILE *file,
                                    int (*read_obj)(FILE *, client *),
                                    int (*print_client_obj)(FILE *, client *),
                                    int (*print_client_obj_template_for_input)(FILE *)) {
    if (file == NULL) {
        return NULL_DESCRIPTOR_OF_FILE;
    }

    client client_obj = {0};  // client or transaction
    if (print_client_obj_template_for_input(stdout) != 0) {
        return ERR_PRINT_CLIENT_OBJ_TEMPLATE_FOR_INPUT;
    }
    while (read_obj(stdin, &client_obj) == 0) {
        if (print_client_obj(file, &client_obj) != 0) {
            return ERR_PRINT_CLIENT_OBJ;
        }
        if (print_client_obj_template_for_input(stdout) != 0) {
            return ERR_PRINT_CLIENT_OBJ_TEMPLATE_FOR_INPUT;
        }
    }

    return 0;
}

int print_clients_to_file(FILE *clients_file) {
    if (print_to_file_using_func(clients_file, read_person,
                                 print_person, print_person_template_for_input) != 0) {
        return ERR_PRINT_CLIENTS_TO_FILE;
    }

    return 0;
}

int print_transactions_to_file(FILE *transactions_file) {
    if (print_to_file_using_func(transactions_file, read_transaction,
                                 print_transaction, print_transaction_template_for_input) != 0) {
        return ERR_PRINT_TRANSACTIONS_TO_FILE;
    }

    return 0;
}

int update_clients(FILE *clients_file, FILE *transactions_file, FILE *clients_after_transactions_file) {
    if (clients_file == NULL || transactions_file == NULL || clients_after_transactions_file == NULL) {
        return NULL_DESCRIPTOR_OF_FILE;
    }

    client person = {0};
    client transaction = {0};
    while (read_person(clients_file, &person) == 0) {
        while (read_transaction(transactions_file, &transaction) == 0) {
            if (person.number == transaction.number && transaction.cash_payments != 0) {
                person.credit_limit += transaction.cash_payments;
            }
        }
        if (print_person(clients_after_transactions_file, &person) != 0) {
            return ERR_PRINT_CLIENT_OBJ;
        }
        rewind(transactions_file);
    }

    return 0;
}
