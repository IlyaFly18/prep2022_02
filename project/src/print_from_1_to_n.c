#include "print_from_1_to_n.h"

#include <stdio.h>

void print_from_1_to_n(long int number) {
    if (number == 1) {
        printf("%d", 1);
        return;
    }
    long int next = number > 1 ? number - 1 : number + 1;
    print_from_1_to_n(next);  // выполняем обратный ход рекурсии
    printf(" %ld", number);
}
