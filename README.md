# Castorno

A simple C++98 testing framework library, designed with simplicity in mind.

## Features

- *Very* easy to use API: only two functions are required to build any amount of test suites.
- Test timing: each test is timed using Castorno's Timer capability, which internally relies to `CLOCK_MONOTONIC` (Reminder: no `chrono` here as we're limited to C++98).
- Bare bones assertion macros, which are provided as testing shortcuts. However, Castorno still accepts customized assertion methods.

## Motivations

I originally decided to build this library to fit my testing needs for one of my school assignments: the [ft_containers](https://github.com/aurelien-brabant/ft_containers) project.
Because I often want to keep things separated, I decided to develop it as a library instead of integrating it directly in my project.

## Getting started

Here is what you need to begin using Castorno:

```cpp
#include "castorno/Tester.hpp"
#include "castorno/assert.hpp"

/**
 * NOTE: a test function should IMPERATIVELY take a Tester& parameter
 * named tester (for use with the assertion API) and should also return 0
 * in at least one execution path to indicate success case
 */

/* 1 != 2, thus will fail */
int test1(Tester& tester) { p_assert_eq(1, 2); return 0; } 

/* 1 == 1, thus will succeed */
int test2(Tester& tester) { p_assert_eq(1, 1); return 0; } 

/* The expression evaluates to true, thus will succeed */
int test2(Tester& tester) { assert_expr(1 == 1 && 2 > 1); return 0; } 

int main(int ac, char **av)
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
```

Compile the program like so (assuming Castorno has been cloned in the current working directory):

```shell
gcc -L. -lcastorno -Icastorno/include main.cpp -o test
```

Executing `test` should give you the following (colored) output:

```
>>>>>>>>>> test suite 1 <<<<<<<<<<

[X] failing test          0.007    ms (1 != 2)
[✔] successful test       0        ms

SUITE SUMMARY: 1/2 passed.

>>>>>>>>>> test suite 2 <<<<<<<<<<

[✔] successful test       0        ms

SUITE SUMMARY: 1/1 passed.

All tests suites have been processed! 1/2 were successfull.
```

# Assertion API

Here are all the macros you can make use of to validate tests:

```
assert_eq(arg1, arg2);
```

Ensure that arg1 == arg2. An overload of the `==` operator that compares arg1's type
to arg2's type must of course exist.

```
p_assert_eq(arg1, arg2)
```

Same thing than `assert_eq`, but print on the standard output the two elements in case
they compared unequal. This macro requires that an overload of `<<` exists for arg1 and arg2, where the lhs is of type `std::ostream` and `rhs` of arg's type.

```
assert_range_eq(actual_begin, actual_end, expected_begin, expected_end)
```

Given valid iterator ranges, ensure that each element in the actual range compares equal to each element in the
expected range. `actual_begin::value_type` should be comparable to `expected_begin::value_type`.

```
assert_range_uneq(actual_begin, actual_end, expected_begin, expected_end)
```

Ensure that ranges are NOT equal. Same requirements than `assert_range_eq`.

```
assert_throw(ExceptionType, expr)
```

Ensures that the provided `expr` throws an exception of type `ExceptionType`. The test fails if no exception is
thrown, or if an exception which is not of the specified type is thrown instead of the expected one.

Example:

```cpp
/* ... */

std::vector<int> v(2);

assert_throw(std::out_of_range, v.at(2)); // should throw

/* ... */
```

```
assert_expr(expr)
```

Evaluates the given expression, marking the test as successful or failed depending on whether it's true or false.

```
assert_expr_not
```

Basically `assert_expr(!(expr))`.
