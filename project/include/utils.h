#ifndef PROJECT_INCLUDE_UTILS_H_
#define PROJECT_INCLUDE_UTILS_H_

#include "client.h"
#include "read_and_print_data.h"

int print_clients_to_file(FILE *clients_file);

int print_transactions_to_file(FILE *transactions_file);

int update_clients(FILE *clients_file,
                   FILE *transactions_file,
                   FILE *clients_after_transactions_file);

#endif  // PROJECT_INCLUDE_UTILS_H_
