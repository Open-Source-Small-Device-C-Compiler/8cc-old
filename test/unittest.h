/*
 * unittest.c - unit test utilities
 *
 * Copyright 2010 Rui Ueyama <rui314@gmail.com>.  All rights reserved.
 * This code is available under the simplified BSD license.  See LICENSE for details.
 */

/*
 * License of all the other files in this directory is the same as above.
 */

#include "../8cc.h"

#define CONSTRUCTOR __attribute__((constructor))

#define NOT_NULL(p) do { if (!(p)) error("Line %d: must not be null " #p, __LINE__); } while (0)
#define EQ(x, y) do { if ((x) != (y)) error("Line %d: must be the same: '%s' and '%s'", __LINE__, #x, #y); } while (0)
#define EQ_CHAR(x, y) do { eq_char(__LINE__, (x), (y)); } while (0)
#define EQ_STR(x, y)  do { eq_str(__LINE__, (x), (y)); } while (0)

extern List* test_funcs;

#define TEST(name)                                     \
    static void TEST_##name(void);                     \
    CONSTRUCTOR static void name##_TEST_INIT(void) {   \
        if (!test_funcs)                               \
            test_funcs = make_list();                  \
        list_push(test_funcs, TEST_##name);            \
        list_push(test_funcs, #name);                  \
    }                                                  \
    static void TEST_##name(void)

#define RUN_TESTS()                                         \
    int main(int argc, char **argv) {                       \
        printf("Running unit tests ...\n");                 \
        while (LIST_LEN(test_funcs) > 0) {                  \
            char *name = (char *)list_pop(test_funcs);      \
            printf("  %s\n", name);                         \
            void (*fn)(void) = list_pop(test_funcs);        \
            fn();                                           \
        }                                                   \
        printf("done\n");                                   \
    }

extern void eq_str(int line, char *expected, char *got);
extern void eq_char(int line, int expected, int got);
extern FILE *create_file(char *content);