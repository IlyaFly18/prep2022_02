#include "is_prime.h"
#include "print_from_1_to_n.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)
#define ERR_PTR_VALUE (-3)
#define ERR_WRONG_RETURNED_VAL_OF_FUNCTION (-4)

#define TST_UTILS_TIMER 1
#define TST_UTILS_CUSTOM_POW 2
#define TST_IS_PRIME 3
#define TST_PRINT_FROM_1_TO_N 4

static long int string_to_long_int(const char *str, long int *res) {
    if (str == NULL || res == NULL) {
        return ERR_PTR_VALUE;
    }

    char *end = NULL;
    *res = strtol(str, &end, 0);
    if (*end != '\0') {
        return ERR_PTR_VALUE;
    }

    return 0;
}

int main(int argc, const char **argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    long int test_case = 0;
    if (string_to_long_int(argv[1], &test_case) != 0) {
        return ERR_WRONG_FLG;
    }

    const char *data = argv[2];

    long int arg_1_for_case = 0;
    if (string_to_long_int(data, &arg_1_for_case) != 0) {
        return ERR_WRONG_RETURNED_VAL_OF_FUNCTION;
    }

    switch (test_case) {
        case TST_UTILS_TIMER: {
            printf("%zu\n", timer_from(arg_1_for_case));
            break;
        }
        case TST_UTILS_CUSTOM_POW: {
            if (argc < 4) {
                return ERR_ARGS_COUNT;
            }

            long int base = arg_1_for_case;

            long int pow = 0;
            if (string_to_long_int(argv[3], &pow) != 0) {
                return ERR_WRONG_RETURNED_VAL_OF_FUNCTION;
            }

            long int res = custom_pow(base, pow);
            printf("%ld\n", res);
            break;
        }
        case TST_IS_PRIME: {
            printf("%ld", is_prime(arg_1_for_case));
            break;
        }
        case TST_PRINT_FROM_1_TO_N: {
            print_from_1_to_n(arg_1_for_case);
            printf("\n");
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
    return 0;
}
