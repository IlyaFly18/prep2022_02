#include "utils.h"

#include <stdio.h>

size_t timer_from(long int from) {
    for (long int i = from; i > 0; --i) {
        printf("%ld ", i);
    }
    if (from > 0) {
        printf("%d\n", 0);
    }
    return from < 0 ? 0 : from + 1;
}

long int custom_pow(long int base, long int power) {  // итеративный алгоритм быстрого возведения в степень
    long int answer = 1;
    while (power != 0) {
        if (power % 2 == 0) {
            base *= base;
            power /= 2;
        } else {
            answer *= base;
            --power;
        }
    }
    return answer;
}
