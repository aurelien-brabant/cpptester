#include <iostream>
#include "Tester.hpp"

using std::cout;

Tester::Tester(void)
{
}

Tester::Tester(const Tester & rhs)
{
	*this = rhs;
}

Tester & Tester::operator=(const Tester & rhs)
{
	if (this == &rhs) {
	}

	return *this;
}

void Tester::registerTest(std::string const & suiteName, const std::string & testName, TestFn fn)
{
	TestSuiteMap::iterator it = _testSuites.find(suiteName);

	if (it == _testSuites.end()) {
		std::vector<Test> vfn;

		vfn.push_back(Test(testName, fn));
		TestSuiteMap::value_type p(suiteName, vfn);
		_testSuites.insert(p);
	} else {
		it->second.push_back(Test(testName, fn));
	}
}

void Tester::runAllSuites(void)
{
	for (TestSuiteMap::const_iterator cit = _testSuites.begin(); cit != _testSuites.end(); ++cit) {
		cout << "========== " << cit->first << " ==========\n\n";
		
		// for each test
		for (std::vector<Test>::const_iterator vcit = cit->second.begin(); vcit != cit->second.end(); ++vcit) {
			if (vcit->fn()){
				std::cout << "[" << "\033[0;31mX\033[0m] " << vcit->name << "\n";
			} else {
				std::cout << "[" << "\033[0;32mV\033[0m] " << vcit->name << "\n";
			}
		}
	}
}


