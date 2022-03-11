#ifndef CONST_REVERSE_ITERATOR_VECTOR_H
#define CONST_REVERSE_ITERATOR_VECTOR_H

#include "../utils/traits.hpp"
// #include "rev_ite.hpp"
#include "iterator.hpp"

namespace ft
{

template <typename iterator>
class	const_reverse_iterator_vector
{
public:

	typedef std::ptrdiff_t difference_type; 
	typedef iterator value_type;
	typedef	iterator*  pointer;
	typedef iterator& reference;
    typedef const iterator* const_pointer;
    typedef const iterator& const_reference;
	typedef ft::random_access_iterator_tag iterator_category;

	// typedef iterator		value_type;
	// typedef iterator		reference;
	// typedef iterator	const_reference;
	// typedef iterator			pointer;
	// typedef iterator	const_pointer;
	// typedef iterator	difference_type;

	const_reverse_iterator_vector(void) {};
	const_reverse_iterator_vector(const_reverse_iterator_vector const &src) { *this = src; } ;
	const_reverse_iterator_vector(const_iterator_vector<value_type> const &src) { _base = src.operator->(); } ;
	const_reverse_iterator_vector(iterator_vector<value_type> const &src) { _base = src.operator->(); } ;
	const_reverse_iterator_vector(reverse_iterator_vector<iterator> const &src) { _base = src.operator->(); } ;

	virtual ~const_reverse_iterator_vector() {};

	iterator base(void) const { return this->_base; };
	const_reverse_iterator_vector &operator=(const_reverse_iterator_vector const &src) { _base = src._base; return (*this); };

	// BOOLEANS
	bool operator ==(const_reverse_iterator_vector const& b) const { return (_base == b._base); };
	bool operator !=(const_reverse_iterator_vector const& b) const { return (_base != b._base); };
	bool operator >(const_reverse_iterator_vector const& b) const { return (_base > b._base); };
	bool operator <(const_reverse_iterator_vector const& b) const { return (_base < b._base); };
	bool operator >=(const_reverse_iterator_vector const& b) const { return (_base >= b._base); };
	bool operator <=(const_reverse_iterator_vector const& b) const { return (_base <= b._base); };

	// ARITHMETICS
	const_reverse_iterator_vector operator +(const difference_type b) const { return (_base - b); }; // a + b
	const_reverse_iterator_vector operator -(difference_type b) const { return (_base + b); }; // a - b

friend const_reverse_iterator_vector	operator+(difference_type n, const const_reverse_iterator_vector &rhs)
				{ return rhs.operator+(n); };

	// difference_type operator +(const_reverse_iterator_vector b) { return (_base - b._base); }; // a + b
	difference_type operator -(const_reverse_iterator_vector b) { return (_base + b._base); }; // a - b

	// INCREMENTERS
	const_reverse_iterator_vector operator ++() { _base--; return (*this); };			// ++a
	const_reverse_iterator_vector operator ++(int) { _base--; return (const_reverse_iterator_vector(_base + 1)); };	// a++
	const_reverse_iterator_vector operator --() { _base++; return (*this); };			// --a
	const_reverse_iterator_vector operator --(int) { _base++; return (const_reverse_iterator_vector(_base - 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	const_reverse_iterator_vector operator +=(difference_type b) { _base -= b; };	// a += b
	const_reverse_iterator_vector operator -=(difference_type b) { _base += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	const_reference operator *() const { return (*this->_base); };
	reference operator *() { return (this->_base); };							// *a
	reference operator [](difference_type b) { return (*(_base + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_base + b)); };		// a[]
	pointer operator ->() { return (_base); };											// a->b
	pointer operator ->() const { return (_base); };											// a->b

	static const bool input_iter = true;

	private:
		const_reverse_iterator_vector(iterator ptr) { _base = ptr; };
		iterator _base;
};

template <class T>
const_reverse_iterator_vector<T> operator+(std::ptrdiff_t i, const_reverse_iterator_vector<T> &it) {
	return (it - i);
	}


}

#endif