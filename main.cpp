
/**
 * Программа проверкаи работы 2-мерной
 * бесконечной матрицы
*/

#include <iostream>

#include "matrix.h"


/**
 * \brief main
 *
 * Программа проверкаи работы 2-мерной бесконечной матрицы
 * \return всегда 0
 */
int main ()
{
	try
	{
		// matrix<int, 0> m;
		// for(int i=0; i<10; i++)
		// {
		// 	m[i][i] = 9 - i;
		// 	m[i][9-i] = 9 - i;
		// }

		// for(int i=1; i<9; i++)
		// {
		// 	for(int j=1; j<9; j++)
		// 	{
		// 		std::cout << m[i][j] << " ";
		// 	}
		// 	std::cout << std::endl;
		// }

		my::matrix<int, -10> m;

		std::cout << "size = " << m.size() << std::endl;
		// std::cout << m[1] << " - " << m[100000] << std::endl;
		m[1] = 10;
		int a = m[1];
		// std::cout << "size = " << m.size() << std::endl;
		// std::cout << m[1] << " - " << m[100000] << std::endl;

		// m[1] = -10;
		// m[100000] = 100;
		// std::cout << "size = " << m.size() << std::endl;
		// std::cout << m[1] << " - " << m[100000] << std::endl;


	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

