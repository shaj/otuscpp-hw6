/**
 * \file
 * Реализация разреженной матрицы
 */


#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>

#include <boost/log/trivial.hpp>

namespace my
{
/// Класс разреженной матрицы
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

	};

public: 

	class Iterator;

	using iterator = Iterator;

	using item = item_adapter<matrix<T, DEF_VAL, N>>;
	using value_type = T;
	using cell_idx_type = typename std::pair<std::size_t, std::size_t>;
	using container_type = typename std::map<cell_idx_type, T>;
	using iterator_type = typename container_type::iterator;
	using const_iterator_type = typename container_type::const_iterator;


	std::map<cell_idx_type, T> m;

	typedef decltype(m.begin()) iter_type;
	typedef decltype(m.cbegin()) const_iter_type;


    // class Iterator: public std::iterator<
    //                     std::input_iterator_tag,   // iterator_category
    //                     T,                      // value_type
    //                     T,                      // difference_type
    //                     const T*,               // pointer
    //                     T                       // reference
    //                                   >

	class Iterator
	{
        const_iter_type iter;
    public:
        Iterator(const_iter_type const &it) : iter(it) {}

        Iterator& operator++() 
        {
        	iter++;
        	return *this;
        }

        bool operator==(Iterator other) const {return iter == other.iter;}
        bool operator!=(Iterator other) const {return !(*this == other);}
        const Iterator& operator*() const {return *this;}

        // operator const T&() const {return iter->second;}

        // std::tuple<std::size_t, std::size_t, T> operator*()
        // {
        // 	return std::make_tuple(iter->first.first, iter->first.second, iter->second);
        // }

        std::tuple<std::size_t, std::size_t, T> foo()
        {
        	return std::make_tuple(iter->first.first, iter->first.second, iter->second);
        }
    };


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


	Iterator begin() const
	{
		auto a = m.begin();
		return Iterator(a);
	}

	Iterator end() const 
	{
		auto a = m.end();
		return Iterator(a);
	}

};

}