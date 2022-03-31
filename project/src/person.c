#include "constants.h"
#include "person.h"

int scanf_person(FILE *stream, person *person) {
    if (stream == NULL || person == NULL)
        return NULL_PTR_IN_ARGS;

    int return_scanf = fscanf(stream, "%12d%11s%11s%16s%20s%12lf%12lf%12lf",
                              &person->number,
                              person->name,
                              person->surname,
                              person->address,
                              person->tel_number,
                              &person->indebtedness,
                              &person->credit_limit,
                              &person->cash_payments);
    if (return_scanf == EOF || return_scanf != NUM_OF_FIELDS_PERSON)
        return WRONG_SCANF;
    return 0;
}

int print_person(FILE *stream, person *person) {
    if (stream == NULL || person == NULL)
        return NULL_PTR_IN_ARGS;

    fprintf(stream, "%-12d%-11s%-11s%-16s%20s%12.2lf%12.2lf%12.2lf\n",
            person->number, person->name,
            person->surname, person->address,
            person->tel_number, person->indebtedness,
            person->credit_limit, person->cash_payments);
    return 0;
}

int print_person_pattern(FILE *stream) {
    if (stream == NULL)
        return NULL_PTR_IN_ARGS;

    return fprintf(stream, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
                   "1 Number account: ",
                   "2 Client name: ",
                   "3 surname: ",
                   "4 Addres client: ",
                   "5 Client Telnum: ",
                   "6 Client indebtedness: ",
                   "7 Client credit limit: ",
                   "8 Client cash payments: ");
}
