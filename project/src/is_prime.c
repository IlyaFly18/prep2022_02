#include "is_prime.h"


long int is_prime(long int number) {
    if (number < 2) {
        return 0;
    }
    for (long int i = 2, k = 1; i * i <= number; i += k) {
        if (number % i == 0) {
            return 0;
        }
        if (i == 3) {
            k++;  // ускоряем в два раза итеративный проход(пропускаем четные)
        }
    }
    return 1;
}
