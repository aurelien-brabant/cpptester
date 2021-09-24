#include <iostream>
#include <iomanip>
#include "Tester.hpp"
#include "Timer.hpp"

using std::cout;
using std::string;
using std::setw;
using std::right;

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

void Tester::setError(string const & msg)
{
	_error = msg;
}

string Tester::_consumeError(void)
{
	string s(_error);

	_error = "";

	return s;
}

void Tester::registerTest(string const & suiteName, const string & testName, TestFn fn)
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
	size_t suitePassedN = 0;

	for (TestSuiteMap::const_iterator cit = _testSuites.begin(); cit != _testSuites.end(); ++cit) {
		cout << "\033[1;30m>>>>>>>>>> \033[0;36m" << cit->first << " \033[1;30m<<<<<<<<<<\033[0m\n\n";

		/* For each test */
		size_t passedN = 0;
		for (std::vector<Test>::const_iterator vcit = cit->second.begin(); vcit != cit->second.end(); ++vcit) {

			Timer testTimer;

			testTimer.start();
			int ret = vcit->fn(*this);
			testTimer.finish();
			
			cout << "[" << (ret ? "\033[0;31mX" : "\033[0;32m✔") << "\033[0m] " <<
			std::left << setw(40) << (string("\033[0;30m") + vcit->name + "\033[0m");

			passedN += (ret == 0);
			
			cout << "\033[1;35m" << setw(8) << testTimer.getElapsed() << "\033[0m ms";

			if (ret && !_error.empty()) {
				cout << " (\033[0;31m" << _consumeError() << "\033[0m)";
			}
			
			cout << "\n";
		}

		if (passedN == cit->second.size()) {
			++suitePassedN;
		}
		
		cout << "\n\033[1;33mSUITE SUMMARY: \033[0m" << passedN << "/" << cit->second.size() << " passed.\n\n";
	}

	cout << "All tests suites have been processed! " << suitePassedN << "/" << _testSuites.size() << " were successful.\n";
}