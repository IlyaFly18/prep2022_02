#include "test_print_to_file.h"

#define WRONG_TESTS (-1)

int main(void) {
    if (test_print_person() != 0 ||
        test_print_transaction() != 0 ||
        test_update_clients() != 0) {
        return WRONG_TESTS;
    }

    return 0;
}
