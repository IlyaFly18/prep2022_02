#include "case4.h"

void from_1_to_n(int n) {
    if (n == 1) {
        printf("%d", 1);
        return;
    }
    int next = (n > 1) ? n - 1 : n + 1;
    from_1_to_n(next);
    printf(" %d", n);
    return;
}
