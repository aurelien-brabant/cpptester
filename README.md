# Castorno

A simple C++98 testing framework library, designed with simplicity in mind.

## Features

- *Very* easy to use API: only two functions are required to build any amount of test suites.
- Test timing: each test is timed using Castorno's Timer capability, which internally relies to `CLOCK_MONOTONIC` (Reminder: no `chrono` here as we're limited to C++98).
- Bare bones assertion macros, which are provided as testing shortcuts. However, Castorno still accepts customized assertion methods.

## Motivations

I originally decided to build this library to fit my testing needs for one of my school assignments: the [ft_containers](https://github.com/aurelien-brabant/ft-containers) project.
Because I often want to keep things separated, I decided to develop it as a library instead of integrating it directly in my project.

## Getting started

Here is what you need to begin using Castorno:

```cpp
#include "Tester.hpp"
#include "assert.hpp"

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
	Tester.registerTest("test suite 1", "failing test", test1);
	Tester.registerTest("test suite 1", "successful test", test2);
	Tester.registerTest("test suite 2", "successful test", test3);

	/* run all the registered tests and output the results */
	Tester.runAllSuites();

	return 0;
}
```
