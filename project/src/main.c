#include "utils.h"

#include <stdio.h>

#define CLIENTS_FILE "record.dat"
#define TRANSACTIONS_FILE "transaction.dat"
#define UPDATED_CLIENTS_FILE "blackrecord.dat"

enum ERROR_RETURN_CODES {
    ERR_PRINT_TO_FILE_USING_FUNC = -1,
    ERR_UPDATE_CLIENTS_AFTER_TRANSACTIONS_FILE = -2,
};

static int print_to_file_using_func(const char *file_name, int (*func_for_printing)(FILE *)) {
    FILE *file = fopen(file_name, "w");

    if (func_for_printing(file) != 0) {
        fclose(file);
        return ERR_PRINT_TO_FILE_USING_FUNC;
    }

    fclose(file);
    return 0;
}

static int update_clients_after_transactions_file() {
    FILE *clients_file = fopen(CLIENTS_FILE, "r");
    FILE *transactions_file = fopen(TRANSACTIONS_FILE, "r");
    FILE *clients_after_transactions_file = fopen(UPDATED_CLIENTS_FILE, "w");

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
                if (print_to_file_using_func(CLIENTS_FILE, print_clients_to_file) != 0) {
                    puts("Process of writing to the file failed(case #1)");
                }
                break;
            }
            case 2: {
                if (print_to_file_using_func(TRANSACTIONS_FILE, print_transactions_to_file) != 0) {
                    puts("Process of writing to the file failed(case #2)");
                }
                break;
            }
            case 3: {
                if (update_clients_after_transactions_file() != 0) {
                    puts("Updating file failed(case #3)");
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
