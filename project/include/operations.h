#ifndef PROJECT_INCLUDE_OPERATIONS_H_
#define PROJECT_INCLUDE_OPERATIONS_H_

#include "person.h"
#include "transfer.h"

void clients_write(FILE*, person);

void transactions_write(FILE*, transfer);

void clients_after_transactions_write(FILE*, FILE*, FILE*, person, transfer);

#endif  // PROJECT_INCLUDE_OPERATIONS_H_

