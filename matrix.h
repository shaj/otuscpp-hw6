/**
 * \file
 * Реализация разреженной матрицы
 */


#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
#include <map>

#include <stdexcept>
#include <boost/log/trivial.hpp>

namespace my
{
/// Класс разреженной матрицы
template<typename T, T DEF_VAL>
class matrix
{
private:	

	/**
	 * Класс адаптера позволяет получить доступ 
	 * к элементам матрицы через оператор издекса [][]
	 */
	template<class tabletype>
	class item_adapter
	{
	private:	

		using item = typename tabletype::item;
		using value_type = typename tabletype::value_type;
		using cellidx_t = typename tabletype::cell_idx_type;

		tabletype *table;
		std::size_t row_idx;

		cellidx_t cell_idx {0, 0};

		item_adapter(){};

	public:

		item_adapter(tabletype *tbl, std::size_t r)
			:table(tbl), row_idx(r) 
		{
			cell_idx.first = r;
		}

		item& operator=(const value_type &val)
		{
			BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
			table->set(cell_idx, val);
			return *this;
		}

		item& operator[](int idx)
		{
			BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;

			cell_idx.second = idx;
			return *this;
		}

		operator const value_type&() const
		{
			BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
			return table->get(cell_idx);
		}

	};


	std::list<std::tuple<std::size_t, std::size_t, T>> m;



public:


	/**
	 * This gives us the "default" value to return for an empty bucket.
	 * We just use the default constructor on T, the template type
	 */
	const T&  default_value() const
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;

		static value_type defaultval = value_type(DEF_VAL);
		return defaultval;
	}




	matrix()
	{
		BOOST_LOG_TRIVIAL(trace) << __PRETTY_FUNCTION__;
	}

	item operator[](int idx) 
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;

		return item(this, idx);
	}

	std::size_t size()
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
		return m.size();
	}

	const T& get(std::size_t r, std::size_t c) const
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
		
		auto it = std::find_if(m.begin(), m.end(), 
			[](auto it)
			{
				return ((std::get<0>(it) == r) && (std::get<1>(it) == c))
			});
		if(it != m.end())
		{
			return std::get<2>(it);
		}
		return default_value();
	}

	void set(std::size_t r, std::size_t c, const T &val)
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
		auto it = std::find_if(m.begin(), m.end(), 
			[](auto it)
			{
				return ((std::get<0>(it) == r) && (std::get<1>(it) == c))
			});

		if(it != m.end())
		{
			if(val != std::get<3>(it))
			{
				m.erase(it);
				if(val != DEF_VAL)
				{ 
					m.push_back(std::make_tuple(r, c, val))
				}
			}
		}
		else
		{
			if(val != DEF_VAL)
			{ 
				m.emplace(std::make_tuple(r, c, val))
			}
		}
		return;
	}


	Iterator begin() const
	{
		return m.begin();
	}

	Iterator end() const 
	{
		return m.end();
	}

};

}