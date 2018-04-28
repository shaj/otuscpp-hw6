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

#include <boost/log/trivial.hpp>

namespace my
{

template<typename T, T DEF_VAL, std::size_t N = std::numeric_limits<typename std::size_t>::max()>
class matrix
{
private:	

	template<class tabletype>
	class item_adapter
	{
	private:	

		using item = typename tabletype::item;
		using value_type = typename tabletype::value_type;

		tabletype *table;
		std::size_t row_idx;

		item_adapter(){};

	public:

		item_adapter(tabletype *tbl, std::size_t r)
			:table(tbl), row_idx(r) {}

		item& operator=(const value_type &val)
		{
			BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
			table->set(row_idx, val);
			return *this;
		}

		// U& operator[](int idx)
		// {
		// 	return m[0];
		// }

		operator const value_type&() const
		{
			BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
			return table->get(row_idx);
		}

		// void set_idx(int idx)
		// {
		// 	row_idx = idx;
		// }
	};



	std::map<int, T> m;


public:
	
	using item = item_adapter<matrix<T, DEF_VAL, N>>;
	using value_type = T;

	// This gives us the "default" value to return for an empty bucket.
	// We just use the default constructor on T, the template type
	const T&  default_value() const
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;

		static value_type defaultval = value_type(DEF_VAL);
		return defaultval;
	}

	matrix(){}

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

	const T& get(int idx) const
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
		auto it = m.find(idx);
		if(it != m.end())
		{
			return it->second;
		}
		return default_value();
	}

	void set(int idx, const T &val)
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
		if(val == DEF_VAL)
		{ // Удалить значение из списка
			auto it = m.find(idx);
			if(it != m.end())
			{
				m.erase(idx);
			}
		}
		else
		{ // Заменить (создать) значение в списке
			m[idx] = val;
		}
		return;
	}

};

}