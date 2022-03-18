#include "is_prime.h"
#include "output_from_1_to_n.h"
#include "utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


#define ERR_ARGS_COUNT   (-1)
#define ERR_WRONG_FLG   (-2)
#define ERR_PTR_VALUE   (-3)

#define TST_FOO_FIX   1
#define TST_FOO_IMPL   2
#define TST_MOD_IMPL   3
#define TST_NEW_CASE_AND_MOD_IMPL   4


long int string_to_long_int(const char *str, long int* res);


int main(int argc, const char **argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    long int Test_case = 0;
    long int returned_value = string_to_long_int(argv[1], &Test_case);
    if (returned_value != 0) {
        return ERR_WRONG_FLG;
    }

    const char *data = argv[2];

    long int arg_2 = 0;  // первый аргумент для некоторого кейса Test_case
    returned_value = string_to_long_int(data, &arg_2);
    if (returned_value != 0) {
        return ERR_WRONG_FLG;
    }

    switch (Test_case) {
        case TST_FOO_FIX: {
            printf("%zu\n", timer_from(arg_2));
            break;
        }
        case TST_FOO_IMPL: {
            if (argc < 4) {
                return ERR_ARGS_COUNT;
            }

            long int base = arg_2;

            long int pow = 0;
            returned_value = string_to_long_int(argv[3], &pow);
            if (returned_value != 0) {
                return ERR_WRONG_FLG;
            }

            long int res = custom_pow(base, pow);
            printf("%ld\n", res);
            break;
        }
        case TST_MOD_IMPL: {
            printf("%ld", is_prime(arg_2));
            break;
        }
        case TST_NEW_CASE_AND_MOD_IMPL: {
            output_from_1_to_n(arg_2);
            printf("\n");
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }
    return 0;
}


long int string_to_long_int(const char *str, long int* res) {
    if (str == NULL) {
        return ERR_PTR_VALUE;
    }
    char *end = NULL;
    *res = (long int) strtol(str, &end, 0);
    if (*end != '\0') {
        return ERR_PTR_VALUE;
    }
    return 0;
}

