#include "Tester.hpp"

int test1(Tester & tester)
{
	return 0;
}

int test2(Tester & tester)
{
	tester.setError("Error message");

	return 1;
}

int main(void)
{
	Tester tester;

	tester.registerTest("main tests", "test a successful one", &test1);
	tester.registerTest("main tests", "test a failing one", &test2);

	tester.registerTest("other test suite", "vector resize", &test1);

	tester.runAllSuites();

	return 0;
}
