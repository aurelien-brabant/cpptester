#ifndef ASSERT_HPP
# define ASSERT_HPP
# include <iostream>

//////////////////////////////////////////////
// EQUALITY CHECK
/////////////////////////////////////////////

# define assert_expr(expr)                     \
if (!(expr)) {                                 \
	tester.error << #expr " is false";         \
	return 1;                                  \
}

# define assert_expr_not(expr)                 \
if ((expr)) {                                  \
	tester.error << #expr " is true";          \
	return 1;                                  \
}

# define assert_eq(actual, expected)			\
if (!((actual) == (expected))) {				\
	tester.error << # actual " != " # expected; \
	return 1;                                   \
}

# define p_assert_eq(arg1, arg2)				\
if (!((arg1) == (arg2))) {							\
	tester.error << (arg1) << " != " << (arg2);	\
	return 1;									\
}

# define assert_throw(ExceptionType, expr)	\
try {										\
	expr;									\
	tester.error << "Expected expression to throw, but didn't";	\
	return 1;								\
} catch (ExceptionType & e) {				\
} catch (std::exception & e) {				\
	tester.error << "Caught exception, but not of right type";	\
	return 1;								\
}

//////////////////////////////////////////////
// ITERATOR ASSERTIONS
/////////////////////////////////////////////

template <class Iterator>
bool range_eq(Tester& tester, Iterator actual_begin, Iterator actual_end, Iterator expected_begin, Iterator expected_end)
{
	if (actual_end - actual_begin != expected_end - expected_begin) {
		tester.error << "Ranges aren't of the same size";
		return false;
	}

	while (actual_begin != actual_end) {
		if (*actual_begin != *expected_begin) {
			tester.error << "Ranges differ at element " << actual_end - actual_begin;
			return false;
		}
		++actual_begin; ++expected_begin;
	}

	return true;
}

# define assert_range_eq(actual_begin, actual_end, expected_begin, expected_end)			\
if (!range_eq(tester, actual_begin, actual_end, expected_begin, expected_end)) {		\
	return 1;																				\
}

# define assert_range_uneq(actual_begin, actual_end, expected_begin, expected_end)			\
if (range_eq(tester, actual_begin, actual_end, expected_begin, expected_end)) {		\
	tester.error << "Ranges are equal";														\
	return 1;																				\
}

#endif
