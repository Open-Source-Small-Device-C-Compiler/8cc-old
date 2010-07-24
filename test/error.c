#include "unittest.h"
#include "../error.c"

TEST(error) {
    on_error_dst = malloc(sizeof(jmp_buf));
    if (!setjmp(*on_error_dst))
        error("foo");
    on_error_dst = NULL;
    EQ_STR("ERROR: foo", STRING_BODY(on_error_msg));
}
