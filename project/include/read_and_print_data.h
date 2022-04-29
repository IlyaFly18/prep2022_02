#ifndef PROJECT_INCLUDE_READ_AND_PRINT_DATA_H_
#define PROJECT_INCLUDE_READ_AND_PRINT_DATA_H_

#include "client.h"

#include <bits/types/FILE.h>

int read_person(FILE* output_file, client* person);
int print_person(FILE* output_file, client* person);
int print_person_template_for_input(FILE* output_file);

int read_transaction(FILE* output_file, client* transaction);
int print_transaction(FILE* output_file, client* transaction);
int print_transaction_template_for_input(FILE* output_file);

#endif  // PROJECT_INCLUDE_READ_AND_PRINT_DATA_H_
