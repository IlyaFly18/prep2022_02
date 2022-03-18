#include "utils.h"

#include <stdio.h>



size_t timer_from(long int from) {
    for (long int i = from; i >= 0; --i) {
        if (i == 0) {
            printf("%ld\n", i);
            break;
        }
        printf("%ld ", i);
    }
    return from < 0 ? 0 : from + 1;
}


long int custom_pow(long int base, long int power) {  // итеративный алгоритм быстрого возведения в степень
    long int ans = 1;
    while (power != 0) {
        if (power % 2 == 0) {
            base *= base;
            power /= 2;
        } else {
            ans *= base;
            --power;
        }
    }
    return ans;
}
