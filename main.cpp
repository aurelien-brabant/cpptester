#include "Tester.hpp"
#include "assert.hpp"
#include <stdexcept>

int test1(Tester & tester)
{
	return 0;
}

int test2(Tester & tester)
{
	p_assert_eq(3, 4);

	return 0;
}

int testRanges(Tester& tester)
{
	std::vector<int> v1(10, 42);
	std::vector<int> v2(10, 42);

	assert_throw(std::runtime_error, v2.at(22));

	return 0;
}

int main(void)
{
	Tester tester;

	tester.registerTest("main tests", "test a successful one", &test1);
	tester.registerTest("main tests", "test a failing one", &test2);

	tester.registerTest("other test suite", "vector resize", &test1);
	tester.registerTest("other test suite", "compare vector ranges", &testRanges);

	tester.runAllSuites();

	return 0;
}
