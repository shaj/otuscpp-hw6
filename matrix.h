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

		// void set_idx(int idx)
		// {
		// 	row_idx = idx;
		// }
	};

public: 

	template<class tabletype>
	class Iterator;

	using iterator = Iterator<T>;

	using item = item_adapter<matrix<T, DEF_VAL, N>>;
	using value_type = T;
	using cell_idx_type = typename std::pair<std::size_t, std::size_t>;
	using container_type = typename std::map<cell_idx_type, T>;
	using iterator_type = typename container_type::iterator;
	using const_iterator_type = typename container_type::const_iterator;

	template<class tabletype>
	class Iterator
	{
	private:

		using itertype = typename tabletype::const_iterator_type;

		tabletype *table;
		itertype iter;

		Iterator(){}

	public:

		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;

		Iterator(tabletype *tbl, itertype itr) : table(tbl), iter(itr)
		{

		}

		// Проверка на равенство
		bool operator==( const Iterator& other ) const 
		{
			if( this == &other ) 
			{
				return true;
			}
			return iter == other.iter;
		}

		// Проверка на неравенство
		bool operator!=( const Iterator& other ) const 
		{
			return !operator==( other );
		}

		// Получение значения текущего узла
		T operator*() const 
		{
			return *iter;
		}

		// Переход к следующему узлу
		void operator++() 
		{
			iter++;
		}

	};

private: 

	std::map<cell_idx_type, T> m;


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

	const T& get(const cell_idx_type &idx) const
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
		auto it = m.find(idx);
		if(it != m.end())
		{
			return it->second;
		}
		return default_value();
	}

	void set(const cell_idx_type &idx, const T &val)
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

	/// Получить итератор на начало списка
	Iterator<T> begin() const
	{
		// Итератор пойдет от головного элемента...
		return Iterator<T>( this, m.begin() );
	}

	/// Получить итератор на конец списка
	Iterator<T> end() const
	{
		return Iterator<T>( this, m.end() );
	}



};

}