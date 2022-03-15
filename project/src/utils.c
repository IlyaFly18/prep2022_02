#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        if (i > 0)
            printf("%d ", i);
        else
            printf("%d\n", i);
    }
    return counter;
}

// TODO(stitaevskiy): Implement `power of` function

int custom_pow(int base, int power) {
    if (power == 0) {
        return 1;
    } else if (power % 2 == 0) {
        int tmp = custom_pow(base, power / 2);
        return tmp * tmp;
    }
    return base * custom_pow(base, power - 1);
}

