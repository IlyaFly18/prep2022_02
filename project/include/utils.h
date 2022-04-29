#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include <stdio.h>

#define CLIENTS_FILE "record.dat"
#define TRANSACTIONS_FILE "transaction.dat"
#define UPDATED_CLIENTS_FILE "blackrecord.dat"

int print_client_obj_to_file_wrapper(const char* file_name, int (* print_obj_to_file)(FILE*));
int update_clients_wrapper();

int print_clients_to_file(FILE* clients_file);
int print_transactions_to_file(FILE* transactions_file);
int update_clients(FILE* clients_file,
                   FILE* transactions_file,
                   FILE* clients_after_transactions_file);

#endif  // PROJECT_INCLUDE_UTILS_H_
