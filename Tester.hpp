#ifndef TESTER_HPP
# define TESTER_HPP
# include <string>
# include <map>
# include <vector>
# include <sstream>

class Tester
{
	public:
		typedef int (*TestFn)(Tester &);

		struct Test
		{
			std::string	name;
			TestFn		fn;
			
			Test(std::string const & name, TestFn fn): name(name), fn(fn) {};
		};

		typedef std::map<std::string, std::vector<Test> > TestSuiteMap;

	private:
		static const size_t	errorBufsize = 100;
		TestSuiteMap		_testSuites;
		std::string			_progName;

		std::string _consumeError(void);
		size_t _getMaxTestNameLength(void);

	public:
		Tester(const std::string& progName);
		Tester(const Tester & rhs);

		Tester & operator=(const Tester & rhs);

		void registerTest(const std::string & suiteName, const std::string &testName, TestFn fn);
		void runAllSuites(void);
		
		std::ostringstream	error;
};

#endif
