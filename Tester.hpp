#ifndef TESTER_HPP
# define TESTER_HPP
# include <string>
# include <map>
# include <vector>

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
		TestSuiteMap	_testSuites;
		std::string		_error;

		std::string _consumeError(void);

	public:
		Tester(void);
		Tester(const Tester & rhs);

		Tester & operator=(const Tester & rhs);

		void registerTest(const std::string & suiteName, const std::string &testName, TestFn fn);
		void runAllSuites(void);
		
		void setError(const std::string & msg);
};

#endif
