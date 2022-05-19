#include "utils.h"

#include <stdio.h>

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
