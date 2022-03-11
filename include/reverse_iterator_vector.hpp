#ifndef VECTOR_REVERSE_ITERATOR_vector_HPP
# define VECTOR_REVERSE_ITERATOR_vector_HPP

#include "../utils/traits.hpp"
#include "iterator.hpp"
#include "iterator_vector.hpp"
#include <cstddef>

namespace ft
{

template <typename iterator>
class	reverse_iterator_vector
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
	// typedef iterator	reference;
	// typedef iterator	const_reference;
	// typedef iterator	pointer;
	// typedef iterator	const_pointer;
	// typedef iterator	difference_type;

	reverse_iterator_vector(void) {};
	reverse_iterator_vector(pointer ptr) { this->_base = *ptr; };

    // vectorReverseIterator(iterator_vector<value_type> const &src) { _base = src.operator->(); } ;
	// vectorReverseIterator(vectorReverseIterator const &src) { *this = src; } ;

	reverse_iterator_vector(iterator_vector<value_type> const &src) { _base = src.operator->(); } ;
	reverse_iterator_vector(reverse_iterator_vector const &src) { *this = src; } ;

	virtual ~reverse_iterator_vector() {};

	iterator base(void) const { return this->_base; };
	template <class U> reverse_iterator_vector &operator=(const reverse_iterator_vector<U> &u);
	// reverse_iterator_vector &operator=(reverse_iterator_vector const &src) { _base = src._base; return (*this); };

	// BOOLEANS
	bool operator ==(reverse_iterator_vector const& b) const { return (_base == b._base); };
	bool operator !=(reverse_iterator_vector const& b) const { return (_base != b._base); };
	bool operator >(reverse_iterator_vector const& b) const { return (_base > b._base); };
	bool operator <(reverse_iterator_vector const& b) const { return (_base < b._base); };
	bool operator >=(reverse_iterator_vector const& b) const { return (_base >= b._base); };
	bool operator <=(reverse_iterator_vector const& b) const { return (_base <= b._base); };

	// ARITHMETICS

	// difference_type		operator-(const reverse_iterator<U> &u) { return u.base().operator-(this->_base); };
	// reverse_iterator	operator- (difference_type n) const { return reverse_iterator(this->_base.operator+(n)); };

friend reverse_iterator_vector operator+(difference_type n, const reverse_iterator_vector& it ) {return it.operator+(n);}
//The incremented iterator, that is reverse_iterator<Iter>(it.base() - n)
difference_type operator-( const reverse_iterator_vector<value_type>& lhs) {return lhs.base().operator-(this->_base);}
//rhs.base() - lhs.base()
reverse_iterator_vector operator+( difference_type n ) const {return reverse_iterator_vector(this->_base.operator-(n));}
//reverse_iterator(base()-n) or reverse_iterator(base()+n)
reverse_iterator_vector operator-( difference_type n ) const {return reverse_iterator_vector(this->_base.operator+(n));}
//reverse_iterator(base()-n) or reverse_iterator(base()+n)

//difference_type operator-(const reverse_iterator<U> &u) { return u.base().operator-(this->_base); };
//reverse_iterator operator+ (difference_type n) const { return reverse_iterator(this->_base.operator-(n)); };
//reverse_iterator	operator- (difference_type n) const { return reverse_iterator(this->_base.operator+(n)); };

//friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs)
				//{ return rhs.operator+(n); };



	// reverse_iterator_vector	operator+ (difference_type n) const { return reverse_iterator_vector(_base.operator-(n)); };
	// reverse_iterator_vector operator +(const reverse_iterator_vector b) { return (this->_base - b._base); }; // a + b
	// reverse_iterator_vector operator -(const reverse_iterator_vector b) { return (this->_base + b._base); }; // a - b
	// reverse_iterator_vector	operator- (difference_type n) const { return reverse_iterator_vector(this->_base.operator+(n)); };

	// INCREMENTERS
	reverse_iterator_vector operator ++() { _base--; return (*this); };			// ++a
	reverse_iterator_vector operator ++(int) { _base--; return (reverse_iterator_vector(_base + 1)); };	// a++
	reverse_iterator_vector operator --() { _base++; return (*this); };			// --a
	reverse_iterator_vector operator --(int) { _base++; return (reverse_iterator_vector(_base - 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	reverse_iterator_vector operator +=(difference_type b) { _base -= b; };	// a += b
	reverse_iterator_vector operator -=(difference_type b) { _base += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF

	//Reference or pointer to the element previous to current. 

	reference operator *() { return (this->_base); };											// *a
	const_reference operator *() const { return (*this->_base); };								// *a
	// reference operator [](difference_type b) { return ((this->_base + b)); };				// a[]
	// const_reference operator [](difference_type b) const { return (*(this->_base + b)); };		// a[]
	reference	operator[](difference_type n)  { return *this->operator+(n); };
	iterator operator ->() { return (this->_base); };											// a->b
	iterator operator ->() const { return (this->_base); };											// a->b	

	static const bool input_iter = true;

	protected:
		iterator super;
		iterator _base;
};

template <class Iterator> template <class U>
reverse_iterator_vector<Iterator>	&reverse_iterator_vector<Iterator>::operator=(const reverse_iterator_vector<U> &u) {
	if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
		return (*this);
	this->_base = u.base();
	return (*this); }

template <class T>
reverse_iterator_vector<T> operator+(std::ptrdiff_t i, reverse_iterator_vector<T> &it) {
	return (it - i);
}


}

#endif