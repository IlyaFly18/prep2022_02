#ifndef PROJECT_INCLUDE_READ_AND_PRINT_DATA_H_
#define PROJECT_INCLUDE_READ_AND_PRINT_DATA_H_

#include "client.h"

int read_person(FILE*, client*);
int print_person(FILE*, client*);
int print_person_template_for_input(FILE*);

int read_transaction(FILE*, client*);
int print_transaction(FILE*, client*);
int print_transaction_template_for_input(FILE*);

#endif  // PROJECT_INCLUDE_READ_AND_PRINT_DATA_H_
