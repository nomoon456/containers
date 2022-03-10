#ifndef VECTOR_REVERSE_ITERATOR_HPP
# define VECTOR_REVERSE_ITERATOR_HPP

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
	reverse_iterator_vector(pointer ptr) { _base = ptr; };

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
	// reverse_iterator_vector operator +(difference_type b) { return (reverse_iterator_vector(_base - b)); }; // a + b
	reverse_iterator_vector	operator+ (difference_type n) { return reverse_iterator_vector(this->_base.operator-(n)); };
	reverse_iterator_vector operator -(difference_type b) { return (reverse_iterator_vector(_base + b)); }; // a - b

	difference_type operator +(reverse_iterator_vector b) { return (_base - b._base); }; // a + b
	difference_type operator -(reverse_iterator_vector b) { return (_base + b._base); }; // a - b

	// INCREMENTERS
	reverse_iterator_vector operator ++() { _base--; return (*this); };			// ++a
	reverse_iterator_vector operator ++(int) { _base--; return (reverse_iterator_vector(_base + 1)); };	// a++
	reverse_iterator_vector operator --() { _base++; return (*this); };			// --a
	reverse_iterator_vector operator --(int) { _base++; return (reverse_iterator_vector(_base - 1)); };	// a--

	//COMPOUND ASSIGNMENTS
	void operator +=(difference_type b) { _base -= b; };	// a += b
	void operator -=(difference_type b) { _base += b; };	// a -= b

	//DEREFERENCING & ADDRESS STUFF
	reference operator *() { return (*_base); };											// *a
	const_reference operator *() const { return (*_base); };								// *a
	reference operator [](difference_type b) { return (*(_base + b)); };					// a[]
	const_reference operator [](difference_type b) const { return (*(_base + b)); };		// a[]
	pointer operator ->() { return (_base); };											// a->b
	pointer operator ->() const { return (_base); };											// a->b

	static const bool input_iter = true;

	private:
		iterator _base;
};

template <class Iterator> template <class U>
reverse_iterator_vector<Iterator>	&reverse_iterator_vector<Iterator>::operator=(const reverse_iterator_vector<U> &u) {
	if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
		return (*this);
	this->_base = u.base();
	return (*this); }


}

#endif

// #ifndef REVERSE_ITERATOR_VECTOR_HPP
// #define REVERSE_ITERATOR_VECTOR_HPP

// #include "../utils/traits.hpp"
// // #include "rev_ite.hpp"
// #include "iterator.hpp"

// namespace ft{

//     template <class T>
//     class reverse_iterator_vector : public iterator<T> {
//     public:
//         typedef reverse_iterator_vector<T> _it;
//         typedef std::ptrdiff_t difference_type; 
// 	    typedef T value_type;
// 	    typedef	T*  pointer;
// 		typedef const T* const_pointer;
// 	    typedef T& reference;
//         typedef const T& const_reference;
// 		typedef ft::random_access_iterator_tag iterator_category;

// 		reverse_iterator_vector(void) : iterator<T>(){};
//         reverse_iterator_vector(pointer ptr){this->_base = ptr;};
//         ~reverse_iterator_vector(){};
//         reverse_iterator_vector(const reverse_iterator_vector &src) : iterator<T>(src) {};
//         reverse_iterator_vector(int src) {this->_base =src;};

// 		_it operator=(const reverse_iterator_vector &rhs) {
// 			if (this == &rhs)
// 				return (*this);
// 			this->_base = rhs._base;
// 			return (*this);
// 		}

// 		_it operator +(difference_type p) {return this->_base - p;};
// 	    _it operator +(difference_type p) const {return(_it(this->_base - p));}; // _base + p
// 	    _it operator -(difference_type p) const {return(_it(this->_base + p));}; // _base - p

// 	    difference_type operator +(_it p) {return(this->_base - p._base);}; // _base + p
// 	    difference_type operator -(_it p) {return(this->_base + p._base);}; // _base - p

// 	    _it operator++() { --this->_base; return(*this);}; // ++_base
// 		_it operator++(int) {_it tmp(*this); --this->_base; return(tmp);}; // _base++
// 		_it operator--() { ++this->_base; return(*this);}; // --_base
// 		_it operator--(int) {_it tmp(*this); ++this->_base; return(tmp);}; // _base--

// 	    _it operator +=(difference_type p) {this->_base -= p; return(*this);}; // _base += p
// 	    _it operator -=(difference_type p) {this->_base += p; return(*this);}; // _base -= p

// 	    pointer operator ->() {return(this->_base);}; // _base->p
// 	    pointer operator ->() const {return (this->_base);};	
// 		reference operator *() {return (*this->_base);}; // *_base
//         reference operator *() const {return (*this->_base);}; // *_base
// 	    reference operator [](difference_type p) const {return (*(this->_base + p));}; // _base[]
// 		reference operator [](difference_type p) { return (*(this->_base + p)); };	

//     }; //end of reverse_iterator_vector definition class
// 	template <class T>
// 	reverse_iterator_vector<T> operator+(std::ptrdiff_t i, reverse_iterator_vector<T> &it) {
// 		return (it - i);
// 	}
// }//end of namespace ft

// #endif
