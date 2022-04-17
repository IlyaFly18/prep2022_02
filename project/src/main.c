#include "utils.h"

#include <stdio.h>

const char *CLIENTS_FILE = "record.dat",
        *TRANSACTIONS_FILE = "transaction.dat",
        *UPDATED_CLIENTS_FILE = "blackrecord.dat";


enum ERROR_RETURN_CODES {
    ERR_PRINT_TO_FILE_USING_FUNC = -1,
    ERR_UPDATE_CLIENTS_AFTER_TRANSACTIONS_FILE = -2,
    NULL_DESCRIPTOR_OF_FILE = -3,
};

int print_client_obj_to_file_wrapper(const char *file_name, int (*print_obj_to_file)(FILE *)) {
    FILE *file = fopen(file_name, "w");
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
    FILE *clients_file = fopen(CLIENTS_FILE, "r");
    FILE *transactions_file = fopen(TRANSACTIONS_FILE, "r");
    FILE *clients_after_transactions_file = fopen(UPDATED_CLIENTS_FILE, "w");
    if (clients_file == NULL ||
        transactions_file == NULL ||
        clients_after_transactions_file == NULL) {
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

static inline void print_actions() {
    printf("please enter action:\n"
           "1 - enter data client;\n"
           "2 - enter data transaction;\n"
           "3 - update base\n");
}

int main(void) {
    int choice = 0;
    print_actions();
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1: {
                if (print_client_obj_to_file_wrapper(CLIENTS_FILE, print_clients_to_file) != 0) {
                    puts("Process of writing to the clients_file failed");
                }
                break;
            }
            case 2: {
                if (print_client_obj_to_file_wrapper(TRANSACTIONS_FILE, print_transactions_to_file) != 0) {
                    puts("Process of writing to the transactions_file failed");
                }
                break;
            }
            case 3: {
                if (update_clients_wrapper() != 0) {
                    puts("Updating file failed");
                }
                break;
            }
            default: {
                puts("Invalid command");
                break;
            }
        }
        print_actions();
    }
    return 0;
}
