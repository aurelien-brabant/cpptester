#pragma once
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Tester
{
  public:
    typedef int (*TestFn)(Tester&);

    struct Test
    {
        std::string name;
        TestFn fn;

        Test(std::string const& name, TestFn fn)
          : name(name)
          , fn(fn){};
    };

    typedef std::map<std::string, std::vector<Test> > TestSuiteMap;

  private:
    static const size_t errorBufsize = 100;
    TestSuiteMap _testSuites;
    std::string _progName;
    std::ofstream _timeDumpOfs, _testNameDumpOfs;

    std::string _consumeError(void);
    size_t _getMaxTestNameLength(void);

  public:
    Tester(const std::string& progName);
    Tester(const Tester& rhs);

    Tester& operator=(const Tester& rhs);

    void registerTest(const std::string& suiteName,
                      const std::string& testName,
                      TestFn fn);
    bool runAllSuites(void);
    bool runSuite(const std::string& suiteName);

    std::ostringstream error;
};
