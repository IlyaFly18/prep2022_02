#include "is_prime.h"

long int is_prime(long int number) {
    if (number < 2) {
        return 0;
    }
    if (number % 2 == 0 && number != 2)
        return 0;
    for (long int i = 3; i * i <= number; i += 2) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}
