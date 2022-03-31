#include "constants.h"
#include "person.h"
#include "test_print_to_file.h"
#include "transfer.h"

#include <string.h>

int compare_person(person *person1, person *person2) {
    if (person1->number != person2->number)
        return -1;
    if (memcmp(person1->name, person2->name, sizeof(person1->name)) != 0)
        return -1;
    if (memcmp(person1->surname, person2->surname, sizeof(person1->surname)) != 0)
        return -1;
    if (memcmp(person1->address, person2->address, sizeof(person1->address)) != 0)
        return -1;
    if (memcmp(person1->tel_number, person2->tel_number, sizeof(person1->tel_number)) != 0)
        return -1;
    if (person1->indebtedness != person2->indebtedness)
        return -1;
    if (person1->credit_limit != person2->credit_limit)
        return -1;
    if (person1->cash_payments != person2->cash_payments)
        return -1;
    return 0;
}

int compare_transfer(transfer *transfer1, transfer *transfer2) {
    if (transfer1->number != transfer2->number)
        return -1;
    if (transfer1->cash_payments != transfer2->cash_payments)
        return -1;
    return 0;
}

int test_print_person() {
    FILE *file = fopen("project/tests/test_person.dat", "r+");

    // выводим тестовые данные в файл
    person person_expected = {10, "name", "surname", "Moscow", "tel_number", 2000, 3000, 4000};
    if (print_person(file, &person_expected) != 0) {
        return WRONG_PRINTF;
    }

    fseek(file, 0, SEEK_SET);

    // получаем тестовые данные из файла
    person person_got = {0};
    if (scanf_person(file, &person_got) != 0) {
        return WRONG_SCANF;
    }

    // сравниваем вводимые и полученные данные
    if (compare_person(&person_expected, &person_got) != 0) {
        puts("Неверный тест!");
        return WRONG_COMPARATION;
    }

    fclose(file);
    return 0;
}

int test_print_transfer() {
    FILE *file = fopen("project/tests/test_transfer.dat", "r+");

    // выводим тестовые данные в файл
    transfer transfer_expected = {10, 4000};
    if (print_transfer(file, &transfer_expected) != 0) {
        return WRONG_PRINTF;
    }

    fseek(file, 0, SEEK_SET);

    // получаем тестовые данные из файла
    transfer transfer_got = {0};
    if (scanf_transfer(file, &transfer_got) != 0) {
        return WRONG_SCANF;
    }

    // сравниваем вводимые и полученные данные
    if (compare_transfer(&transfer_expected, &transfer_got) != 0) {
        return WRONG_COMPARATION;
    }

    fclose(file);
    return 0;
}
