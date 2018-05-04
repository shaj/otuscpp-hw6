
/**
	\file
	Модульные тесты
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

	
	// for(auto it: m)
	// {
	// 	std::cout << *it << std::endl;

	// }


	std::stringbuf out_buffer;
	std::ostream out_stream(&out_buffer);
	for(auto it: m)
	{
		std::size_t x;
		std::size_t y;
		int v;
		std::tie(x, y, v) = it.foo();
		out_stream << x << y << v << std::endl;
	}
	BOOST_CHECK(out_buffer.str() == "100100217\n");
	
}

BOOST_AUTO_TEST_SUITE_END()
