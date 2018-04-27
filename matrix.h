/**
 * \file
 * Реализация функции печати условного ip адреса
 */


/**
 * \brief решение поставленной задачи
 *
 * \todo
 *  - по возможности использовать stl (type_is, enable_if ...)
 *  - реализовать печать tuple чисел
 */


#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>


namespace my
{

template<typename T, T DEF_VAL, std::size_t N = std::numeric_limits<typename std::size_t>::max()>
class matrix
{
private:	

	template<typename U>
	class item
	{
	std::map<int, U> m;
	int wrk_idx;
	public:
		item(){};

		item<U> & operator=(U &val)
		{
			if(val == DEF_VAL)
			{
				// typename std::map<int, T>::iterator it;
				// it = m.find(idx);
				// if(it != m.end())
				// {
				// 	return m[idx];
				// }
				// return def_val;
				m[0] = val;
			}
			return *this;
		}

		U& operator[](int idx)
		{
			return m[0];
		}


		std::size_t size()
		{
			return m.size();
		}

		void set_idx(int idx)
		{
			wrk_idx = idx;
		}
	};


	item<T> it;

public:
	
	matrix()
	{}


	

	item<T>& operator[](int idx)
	{
		it.set_idx(idx);
		return &it;
	}

	std::size_t size()
	{
		return it.size();
	}

};

}