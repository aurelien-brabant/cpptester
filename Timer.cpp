#include <ctime>
#include "Timer.hpp"

/* Inspired from https://stackoverflow.com/questions/2962785/c-using-clock-to-measure-time-in-multi-threaded-programs/2962914#2962914 */

Timer::Timer(void)
{
}

Timer::Timer(const Timer & rhs)
{
}

Timer & Timer::operator=(const Timer & rhs)
{
	if (this != &rhs) {
		_st = rhs._st;
		_ft = rhs._ft;
	}

	return *this;
}

void Timer::start(void)
{
	clock_gettime(CLOCK_MONOTONIC, &_st);
}

void Timer::finish(void)
{
	clock_gettime(CLOCK_MONOTONIC, &_ft);
}

double Timer::getElapsed(void)
{
	double elapsed = _ft.tv_sec - _st.tv_sec;

	elapsed += (_ft.tv_nsec - _st.tv_nsec) / 1e+6;

	return elapsed;
}
