#ifndef PROJECT_INCLUDE_PERSON_H_
#define PROJECT_INCLUDE_PERSON_H_

#include <stdio.h>

#define NUM_OF_FIELDS_PERSON 8

enum buf_for_fields_person {
    NUMBER = 12,
    NAME = 20,
    SURNAME = 20,
    ADDRESS = 20,
    TEL_NUMBER = 15,
    // INDEBTEDNESS =
};

typedef struct {
    int number;
    char name[20];
    char surname[20];
    char address[30];
    char tel_number[15];
    double indebtedness;
    double credit_limit;
    double cash_payments;
} person;

int scanf_person(FILE*, person*);

int print_person(FILE*, person*);

int print_person_pattern(FILE*);

#endif  // PROJECT_INCLUDE_PERSON_H_
