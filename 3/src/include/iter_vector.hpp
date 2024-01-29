#include <iterator>
#include <vector>
#include "classes.hpp"

typedef std::bidirectional_iterator_tag iterator_category;
typedef initiative_creatures& reference;
typedef initiative_creatures* pointer;

template<typename T>
class my_vector
{
	std::vector<T> v;
	public:
		void push_back(T &obj)
		{
			v.push_back(obj);
		}
		void pop_back()
		{
			v.pop_back();
		}
};

template <class T>
class Init_iterator
{
	typedef T *init_creature;
	Init_iterator(init_creature obj) : initiative_creature(obj) {}

	friend initiative_creature;
};

template<class I>
concept bidirectional_iterator =
	std::forward_iterator<I> &&
	std::derived_form<I> &&
	std::bidirectional_iterator_tag &&
	requires (I i)
	{
		{--i} -> std::same_as<I&>;
		{i--} -> std::same_as<I>;
	}

}
