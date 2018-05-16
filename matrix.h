/**
 * \file
 * Реализация разреженной матрицы
 */

#pragma once


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
		using cellidx_t = typename std::pair<std::size_t, std::size_t>;

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
				
			table->set(cell_idx.first, cell_idx.second, val);
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
				
			return table->get(cell_idx.first, cell_idx.second);
		}

	};


    using value_type = T;
    using reference = T&;
    using pointer = T*;

	/// Тип контейнера ячеек
	using cells_list_t = typename std::list<std::tuple<std::size_t, std::size_t, T&>>;
	/// Итератор по всем ячейкам
	using iterator = typename cells_list_t::iterator;
	/// Константный итератор по всем ячейкам
	using const_iterator = typename cells_list_t::const_iterator;

	using item = item_adapter<matrix<T, DEF_VAL>>;



	// void remove_cell(const_iterator &it);
	// const_iterator get_cell(std::size_t r, std::size_t c);

	/**
	 * Контейнер для хранения занятых координат
	 */
	cells_list_t cells;

	/**
	 * Контейнер для хранения объектов ячеек
	 */
	std::list<T> values;


public:


	/**
	 * This gives us the "default" value to return for an empty bucket.
	 * We just use the default constructor on T, the template type
	 */
	const T&  default_value() const
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;

		static T defaultval = T(DEF_VAL);
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
				
		return cells.size();
	}

	const T& get(std::size_t r, std::size_t c) const
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
		
		const auto it = get_cell(r, c);
		if(it != cells.end())
		{
			return std::get<2>(*it);
		}
		return default_value();
	}

	void set(std::size_t r, std::size_t c, const T &val)
	{
		BOOST_LOG_TRIVIAL(info) << __PRETTY_FUNCTION__;
				
		const auto it = get_cell(r, c);

		if(it != cells.end())
		{ // ячейка уже содержит значение
			if(val != std::get<2>(*it))
			{
				if(val == DEF_VAL)
				{
					remove_cell(it);
				}
				else
				{
					std::get<2>(*it) = val;
				}
			} // 
		}
		else
		{ // Такой ячейки еще не существует. (В ячейке значение по умолчанию)
			if(val != DEF_VAL)
			{ 
				values.push_back(val);
				cells.push_back(std::make_tuple(r, c, std::ref(*(--values.end()))));

				BOOST_LOG_TRIVIAL(debug) << "  ~ set value " << val << "  " << std::get<2>(*(--cells.end()));
			}
		}
		return;
	}


	const_iterator begin() const
	{
		return cells.begin();
	}

	const_iterator end() const 
	{
		return cells.end();
	}


private:
	void remove_cell(const const_iterator &it)
	{
		// values.remove_if([](const T &it){})
		cells.erase(it);
	}		

	const_iterator get_cell(std::size_t r, std::size_t c) const
	{
		return std::find_if(cells.begin(), cells.end(), 
			[r, c](auto it)
			{
				return ((std::get<0>(it) == r) && (std::get<1>(it) == c));
			});
	}


};

}
