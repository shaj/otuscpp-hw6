
/**
	\file
	Тесты
*/	

#define BOOST_LOG_DYN_LINK 1

#define BOOST_TEST_MODULE test_matrix

#include <boost/test/included/unit_test.hpp>

#include "matrix.h"


/**
 * Основной набор основных тестов 
 */
BOOST_AUTO_TEST_SUITE(test_matrix_suite)

BOOST_AUTO_TEST_CASE(test_matrix) 
{
	my::matrix<int, -1> m;
	BOOST_CHECK(m.size() == 0);

	auto a = m[0][0];
	BOOST_CHECK(a == -1);
	BOOST_CHECK(m.size() == 0);

	m[100][100] = 314;
	BOOST_CHECK(m[100][100] == 314);
	BOOST_CHECK(m.size() == 1);
	
	m[100][100] = -1;
	BOOST_CHECK(m.size() == 0);

	((m[100][100] = 314) = 0) = 217;
	BOOST_CHECK(m[100][100] == 217);


	std::stringbuf out_buffer;
	std::ostream out_stream(&out_buffer);
	for(auto it: m)
	{
		std::size_t x;
		std::size_t y;
		int v;
		std::tie(x, y, v) = *it;
		out_stream << x << y << v << std::endl;
	}
	BOOST_CHECK(out_buffer.str() == "100100217\n");
	
}

BOOST_AUTO_TEST_CASE(test_matrix_range1) 
{
	my::matrix<int, -1, 10> m;

	BOOST_CHECK_THROW(m[10][0], std::out_of_range);
	BOOST_CHECK_THROW(m[0][10], std::out_of_range);

	BOOST_CHECK_THROW(m[-1][0], std::out_of_range);
	BOOST_CHECK_THROW(m[0][-1], std::out_of_range);

}

BOOST_AUTO_TEST_CASE(test_matrix_range2) 
{
	my::matrix<int, -1> m;

	BOOST_CHECK_NO_THROW(m[10][0]);
	BOOST_CHECK_NO_THROW(m[0][10]);

	BOOST_CHECK_THROW(m[-1][0], std::out_of_range);
	BOOST_CHECK_THROW(m[0][-1], std::out_of_range);

}


BOOST_AUTO_TEST_SUITE_END()
