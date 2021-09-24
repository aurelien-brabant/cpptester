#include "Tester.hpp"

int test1(void)
{
	return 0;
}

int test2(void)
{
	return 1;
}

int main(void)
{
	Tester tester;

	tester.registerTest("main tests", "test a successful one", &test1);
	tester.registerTest("main tests", "test a failing one", &test2);

	tester.runAllSuites();

	return 0;
}
