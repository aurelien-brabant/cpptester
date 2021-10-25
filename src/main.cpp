#include "Tester.hpp"
#include "assert.hpp"

/**
 * NOTE: a test function should IMPERATIVELY take a Tester& parameter
 * named tester (for use with the assertion API) and should also return 0
 * in at least one execution path to indicate success case
 */

/* 1 != 2, thus will fail */
int
test1(Tester& tester)
{
    p_assert_eq(1, 2);
    return 0;
}

/* 1 == 1, thus will succeed */
int
test2(Tester& tester)
{
    p_assert_eq(1, 1);
    return 0;
}

/* The expression evaluates to true, thus will succeed */
int
test3(Tester& tester)
{
    assert_expr(1 == 1 && 2 > 1);
    return 0;
}

int
main(int ac, char** av)
{
    Tester tester(*av); // program's name, but can be any string

    /* register tests: each test is bound to a test suite */
    tester.registerTest("test suite 1", "failing test", test1);
    tester.registerTest("test suite 1", "successful test", test2);
    tester.registerTest("test suite 2", "successful test", test3);

    /* run all the registered tests and output the results */
    tester.runAllSuites();

    return 0;
}
