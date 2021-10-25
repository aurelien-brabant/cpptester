#include "castorno/Tester.hpp"
#include "castorno/Timer.hpp"
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sys/errno.h>
#include <sys/stat.h>

using std::cout;
using std::setw;
using std::string;

Tester::Tester(const std::string& progName)
  : _progName(progName)
{
    const std::string castornoDir = "./.castorno";

    if (mkdir(castornoDir.c_str(), 0777) && errno != EEXIST) {
        throw std::runtime_error("Could not create log directory");
    }

    _timeDumpOfs.open((castornoDir + "/" + progName + ".time.txt").c_str());
    if (!_timeDumpOfs) {
        throw std::runtime_error("Could not create time dump file");
    }

    _testNameDumpOfs.open(
      (castornoDir + "/" + progName + ".testname.txt").c_str());
    if (!_testNameDumpOfs) {
        throw std::runtime_error("Could not create test name dump file");
    }
}

Tester::Tester(const Tester& rhs)
{
    *this = rhs;
}
Tester&
Tester::operator=(const Tester& rhs)
{

    if (this == &rhs) {
    }

    return *this;
}

string
Tester::_consumeError(void)
{
    string s(error.str());

    error.str("");
    error.clear();

    return s;
}

void
Tester::registerTest(string const& suiteName, const string& testName, TestFn fn)
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

size_t
Tester::_getMaxTestNameLength(void)
{
    size_t greatestLength = 0;

    for (TestSuiteMap::const_iterator cit = _testSuites.begin();
         cit != _testSuites.end();
         ++cit) {
        for (std::vector<Test>::const_iterator citb = cit->second.begin();
             citb != cit->second.end();
             ++citb) {
            if (citb->name.size() > greatestLength) {
                greatestLength = citb->name.size();
            }
        }
    }

    return greatestLength;
}

bool
Tester::runSuite(const std::string& suiteName)
{
    Tester::TestSuiteMap::iterator suiteIt = _testSuites.find(suiteName);
    const size_t offset = _getMaxTestNameLength() + 1;

    if (suiteIt != _testSuites.end()) {
        cout << "\033[1;0m>>>>>>>>>> \033[0;36m" << suiteIt->first
             << " \033[1;0m<<<<<<<<<<\033[0m\n\n";

        /* For each test */
        size_t passedN = 0;
        for (std::vector<Test>::const_iterator cit = suiteIt->second.begin();
             cit != suiteIt->second.end();
             ++cit) {

            // <test_suite>: <test_name>
            _testNameDumpOfs << suiteIt->first << ": " << cit->name << "\n";

            Timer testTimer;

            testTimer.start();
            int ret = cit->fn(*this);
            testTimer.finish();

            cout << "[" << (ret ? "\033[0;31mX" : "\033[0;32m✔") << "\033[0m] "
                 << std::left << setw(offset + 17)
                 << (string("\033[0;34m") + cit->name + "\033[0m");

            passedN += (ret == 0);

            double elapsed = testTimer.getElapsed();
            cout << "\033[1;35m" << setw(8) << elapsed << "\033[0m ms";
            _timeDumpOfs << elapsed << "\n";

            if (ret && !error.str().empty()) {
                cout << " (\033[0;31m" << _consumeError() << "\033[0m)";
            }

            cout << "\n";
        }

        cout << "\n\033[1;33mSUITE SUMMARY: \033[0m" << passedN << "/"
             << suiteIt->second.size() << " passed.\n\n";

        return passedN == suiteIt->second.size();
    }

    return false;
}

bool
Tester::runAllSuites(void)
{
    size_t suitePassedN = 0;

    for (TestSuiteMap::const_iterator cit = _testSuites.begin();
         cit != _testSuites.end();
         ++cit) {

        if (runSuite(cit->first)) {
            ++suitePassedN;
        }
    }

    cout << "All tests suites have been processed! " << suitePassedN << "/"
         << _testSuites.size() << " were successful.\n";

    return suitePassedN == _testSuites.size();
}
