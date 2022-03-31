#include "test_print_to_file.h"

enum return_code_of_bad_tests {
    TEST_1 = 1,
    TEST_2
};

int main(void) {
    if (test_print_person() != 0) {
        return TEST_1;
    }
    if (test_print_transfer() != 0) {
        return TEST_2;
    }
    return 0;
}

