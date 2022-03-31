#include "operations.h"

#include <stdio.h>

void print_invite_message() {
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
}

int main(void) {
    person person = {0};
    transfer transfer = {0};
    int choice = 0;
    print_invite_message();
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1: {
                FILE *clients_file = fopen("clients.dat", "r+");
                if (clients_file == NULL) {
                    puts("Not access");
                } else {
                    clients_write(clients_file, person);
                    fclose(clients_file);
                }
                break;
            }
            case 2: {
                FILE *transactions_file = fopen("transactions.dat", "r+");
                if (transactions_file == NULL) {
                    puts("Not access");
                } else {
                    transactions_write(transactions_file, transfer);
                    fclose(transactions_file);
                }
                break;
            }
            case 3: {
                FILE *clients_file = fopen("clients.dat", "r");
                FILE *transactions_file = fopen("transactions.dat", "r");
                FILE *clients_after_transaction_file = fopen("clients_after_transaction.dat", "w");

                if (clients_file == NULL ||
                    transactions_file == NULL ||
                    clients_after_transaction_file == NULL) {
                    puts("exit");
                } else {
                    clients_after_transactions_write(
                            clients_file,
                            transactions_file,
                            clients_after_transaction_file,
                            person,
                            transfer);
                    fclose(clients_file);
                    fclose(transactions_file);
                    fclose(clients_after_transaction_file);
                }
                break;
            }
            default: {
                puts("error");
                break;
            }
        }
        print_invite_message();
    }
    return 0;
}
