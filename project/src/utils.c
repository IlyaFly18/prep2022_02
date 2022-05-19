#include "utils.h"
#include "read_and_print_data.h"

enum ERROR_RETURN_CODES {
    ERR_PRINT_TO_FILE_USING_FUNC = -1,
    ERR_PRINT_CLIENTS_TO_FILE = -2,
    ERR_PRINT_TRANSACTIONS_TO_FILE = -3,
    ERR_PRINT_CLIENT_OBJ_TEMPLATE_FOR_INPUT = -4,
    ERR_PRINT_CLIENT_OBJ = -5,
    NULL_DESCRIPTOR_OF_FILE = -6,
    NULL_PTR_ON_FUNC = -7,
    ERR_UPDATE_CLIENTS_AFTER_TRANSACTIONS_FILE = -8,
};

int print_client_obj_to_file_wrapper(const char* file_name, int (* print_obj_to_file)(FILE*)) {
    FILE* file = fopen(file_name, "w");
    if (file == NULL) {
        return NULL_DESCRIPTOR_OF_FILE;
    }

    if (print_obj_to_file(file) != 0) {
        fclose(file);
        return ERR_PRINT_TO_FILE_USING_FUNC;
    }

    fclose(file);
    return 0;
}

int update_clients_wrapper() {
    FILE* clients_file = fopen(CLIENTS_FILE, "r");
    if (!clients_file) {
        return NULL_DESCRIPTOR_OF_FILE;
    }
    FILE* transactions_file = fopen(TRANSACTIONS_FILE, "r");
    if (!transactions_file) {
        fclose(clients_file);
        return NULL_DESCRIPTOR_OF_FILE;
    }
    FILE* clients_after_transactions_file = fopen(UPDATED_CLIENTS_FILE, "w");
    if (!clients_after_transactions_file) {
        fclose(clients_file);
        fclose(transactions_file);
        return NULL_DESCRIPTOR_OF_FILE;
    }

    if (update_clients(clients_file, transactions_file, clients_after_transactions_file) != 0) {
        fclose(clients_file);
        fclose(transactions_file);
        fclose(clients_after_transactions_file);
        return ERR_UPDATE_CLIENTS_AFTER_TRANSACTIONS_FILE;
    }

    fclose(clients_file);
    fclose(transactions_file);
    fclose(clients_after_transactions_file);
    return 0;
}

static int print_client_obj_to_file(FILE* file,
                                    int (* read_client_obj)(FILE*, client*),
                                    int (* print_client_obj)(FILE*, client*),
                                    int (* print_client_obj_template_for_input)(FILE*)) {
    if (file == NULL) {
        return NULL_DESCRIPTOR_OF_FILE;
    }
    if (read_client_obj == NULL || print_client_obj == NULL || print_client_obj_template_for_input == NULL) {
        return NULL_PTR_ON_FUNC;
    }

    client client_obj = {0};  // client or transaction
    if (print_client_obj_template_for_input(stdout) != 0) {
        return ERR_PRINT_CLIENT_OBJ_TEMPLATE_FOR_INPUT;
    }
    while (read_client_obj(stdin, &client_obj) == 0) {
        if (print_client_obj(file, &client_obj) != 0) {
            return ERR_PRINT_CLIENT_OBJ;
        }
        if (print_client_obj_template_for_input(stdout) != 0) {
            return ERR_PRINT_CLIENT_OBJ_TEMPLATE_FOR_INPUT;
        }
    }

    return 0;
}

int print_clients_to_file(FILE* clients_file) {
    if (clients_file == NULL) {
        return NULL_DESCRIPTOR_OF_FILE;
    }

    if (print_client_obj_to_file(clients_file, read_person,
                                 print_person, print_person_template_for_input) != 0) {
        return ERR_PRINT_CLIENTS_TO_FILE;
    }

    return 0;
}

int print_transactions_to_file(FILE* transactions_file) {
    if (transactions_file == NULL) {
        return NULL_DESCRIPTOR_OF_FILE;
    }

    if (print_client_obj_to_file(transactions_file, read_transaction,
                                 print_transaction, print_transaction_template_for_input) != 0) {
        return ERR_PRINT_TRANSACTIONS_TO_FILE;
    }

    return 0;
}

int update_clients(FILE* clients_file, FILE* transactions_file, FILE* clients_after_transactions_file) {
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
