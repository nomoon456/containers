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
	const_reverse_iterator_vector operator +(difference_type b) { return (const_reverse_iterator_vector(_base - b)); }; // a + b
	const_reverse_iterator_vector operator -(difference_type b) { return (const_reverse_iterator_vector(_base + b)); }; // a - b

	difference_type operator +(const_reverse_iterator_vector b) { return (_base - b._base); }; // a + b
	difference_type operator -(const_reverse_iterator_vector b) { return (_base + b._base); }; // a - b

	// INCREMENTERS
	const_reverse_iterator_vector operator ++() { _base--; return (*this); };			// ++a
	const_reverse_iterator_vector operator ++(int) { _base--; return (const_reverse_iterator_vector(_base + 1)); };	// a++
	const_reverse_iterator_vector operator --() { _base++; return (*this); };			// --a
	const_reverse_iterator_vector operator --(int) { _base++; return (const_reverse_iterator_vector(_base - 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	void operator +=(difference_type b) { _base -= b; };	// a += b
	void operator -=(difference_type b) { _base += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	const_reference operator *() const { return (*_base); };								// *a
	reference operator [](difference_type b) { return (*(_base + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_base + b)); };		// a[]
	pointer operator ->() { return (_base); };											// a->b
	pointer operator ->() const { return (_base); };											// a->b

	static const bool input_iter = true;

	private:
		const_reverse_iterator_vector(pointer ptr) { _base = ptr; };
		pointer _base;
};

}

#endif

// namespace ft {

//     template <typename T>
//     class	const_reverse_iterator_vector : public iterator<T> {
//     public:
//         typedef const_reverse_iterator_vector<T> _it;

//         typedef std::ptrdiff_t difference_type;
// 	    typedef T value_type;
// 	    typedef	T*  pointer;
// 		typedef T& reference;
//         typedef const T& const_reference;
//         typedef const T* const_pointer;
// 		typedef ft::random_access_iterator_tag iterator_category;

// 	    const_reverse_iterator_vector(void) : iterator<T>(){};
// 	    const_reverse_iterator_vector(pointer ptr) {this->_base = ptr; };
// 	    ~const_reverse_iterator_vector() {};
// 		// template <class m> const_reverse_iterator(const const_reverse_iterator_vector<m> &u) : _base(this->_base) { };
// 		const_reverse_iterator_vector(const iterator<T> &src) : iterator<T>(src) {};

// 	    const _it operator+(difference_type p) {return(_it(this->_base - p));}; // _base + p
// 	    const _it operator-(difference_type p) {return(_it(this->_base + p));}; // _base - p

// 	    difference_type operator+(_it p) const {return(this->_base - p._base);}; // _base + p
// 	    difference_type operator-(_it p) const {return(this->_base + p._base);}; // _base - p

// 	    const _it operator++() { --this->_base; return(*this);}; // ++_base
// 		const _it operator++(int) {_it tmp(*this); --this->_base; return(tmp);}; // _base++
// 		const _it operator--() { ++this->_base; return(*this);}; // --_base
// 		const _it operator--(int) {_it tmp(*this); ++this->_base; return(tmp);}; // _base--

// 	    _it operator+=(difference_type p) {this->_base -= p; return(*this);}; // _base += p
// 	    _it operator-=(difference_type p) {this->_base += p; return(*this);}; // _base -= p

// 	    const_pointer operator->() {return(this->_base);}; // _base->p
// 	    const_pointer operator->() const {return (this->_base);};	
//         const_reference operator*() const {return (*this->_base);}; // *_base
// 	    const_reference operator[](difference_type p) const {return (*(this->_base + p));}; // _base[]
//     }; //end of iterator_vector definition class
// }//end of namespace ft

// #endif