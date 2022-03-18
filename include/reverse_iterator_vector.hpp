#ifndef REVERSE_ITERATOR_vector_H
#define REVERSE_ITERATOR_vector_H

#include "../utils/traits.hpp"

namespace ft{

    template <typename Iterator>
    class	reverse_iterator_vector{
    public:

		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
	
	protected:
		Iterator _current;

	public:
	    reverse_iterator_vector(void):_current() {};
		explicit reverse_iterator_vector(Iterator x):_current(x){};
		template<class U>
		// reverse_iterator_vector(const reverse_iterator_vector<U> &u){*this = u;};
		reverse_iterator_vector(const reverse_iterator_vector<U> &u){_current = u.base();};
	    
		~reverse_iterator_vector(void) {};
	    
		template<class U>
		reverse_iterator_vector &operator=(const reverse_iterator_vector<U> &u) {
			if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
				return (*this);
			this->_base = u.base();
			return (*this);
		};
		reverse_iterator_vector &operator=(const reverse_iterator_vector<Iterator> &u){
			_current = u._current;
			return (*this);
		}

		Iterator base() const{return(_current);};

		reference operator*() const {
			Iterator tmp = _current;
			--tmp;
			return (*(tmp));
		};
		pointer operator->() const{
			return &(operator*());
		};


		reverse_iterator_vector& operator++(){
			--_current;
			return (*this);
		};
		reverse_iterator_vector operator++(int){
			reverse_iterator_vector tmp = *this;
			--_current;
			return (tmp);
		};
		reverse_iterator_vector& operator--(){
			++_current;
			return (*this);
		};
		reverse_iterator_vector operator--(int){
			reverse_iterator_vector tmp = *this;
			++_current;
			return (tmp);
		};
		// reverse_iterator_vector operator+ (difference_type n) const{
		// 	return (reverse_iterator_vector(_current - n));
		// };

		reverse_iterator_vector	operator+ (difference_type n)  { 
			return reverse_iterator_vector(this->_current.operator-(n)); };

		reverse_iterator_vector& operator+=(difference_type n){
			_current -= n;
			return (*this);
		};
		// reverse_iterator_vector operator- (difference_type n) const{
		// 	return (reverse_iterator_vector(_current + n));
		// };

		reverse_iterator_vector	operator- (difference_type n) const { return reverse_iterator_vector(this->_current.operator+(n)); }


		reverse_iterator_vector& operator-=(difference_type n){
			_current += n;
			return (*this);
		};
		reference operator[](difference_type n) const{
			return (_current[-n -1]);
		};

		template <class U> bool	operator==(const reverse_iterator_vector<U> &rhs) {
			return this->_current.operator==(rhs.base()); 
		};

		template <class U>
			difference_type		operator-(const reverse_iterator_vector<U> &u) const {
				return this->_current - u.base(); };


    }; //end of reverse iterator definition class

		/*======================
		|   NO-MEMBER OPERATOR |
		=======================*/
		// template <class U> bool	operator==(const reverse_iterator_vector<U> &rhs) {
		// 	return this->_current.operator==(rhs.base()); 
		// };

		// template <class Iterator>
		// bool operator==(const reverse_iterator_vector<Iterator>& x, const reverse_iterator_vector<Iterator>& y){
		// 	return (x._current == y._current);
		// };

		template <class Iterator>
		bool operator<(const reverse_iterator_vector<Iterator>& x, const reverse_iterator_vector<Iterator>& y){
			return (x.current > y._current);
		}

		template <class Iterator>
		bool operator!=(const reverse_iterator_vector<Iterator>& x, const reverse_iterator_vector<Iterator>& y){
			return (x.current != y._current);
		}

		template <class Iterator>
		bool operator>(const reverse_iterator_vector<Iterator>& x, const reverse_iterator_vector<Iterator>& y){
			return (x.current < y._current);	
		}

		template <class Iterator>
		bool operator>=(const reverse_iterator_vector<Iterator>& x, const reverse_iterator_vector<Iterator>& y){
			return (x.current <= y._current);	
		}

		template <class Iterator>
		bool operator<=(const reverse_iterator_vector<Iterator>& x, const reverse_iterator_vector<Iterator>& y){
			return (x.current >= y._current);	
		}

		// template <class Iterator>
		// bool operator-(const reverse_iterator_vector<Iterator>& x, const reverse_iterator_vector<Iterator>& y){
		// 	return (y.current - x.current);
		// }

		template <class Iterator>
		bool operator+(typename reverse_iterator_vector<Iterator>::difference_type  n, const reverse_iterator_vector<Iterator>& x){
			return (reverse_iterator_vector<Iterator>(x.current - n));
		}
		
		template <class T>
		reverse_iterator_vector<T> operator+(std::ptrdiff_t i, reverse_iterator_vector<T> &it) {
		return (it + i);
	}

}//end of namespace ft

#endif
// #ifndef VECTOR_REVERSE_ITERATOR_vector_vector_vector_HPP
// # define VECTOR_REVERSE_ITERATOR_vector_vector_vector_HPP

// #include "../utils/traits.hpp"
// #include "iterator.hpp"
// #include "iterator_vector.hpp"
// #include <cstddef>

// namespace ft
// {

// template <typename iterator>
// class	reverse_iterator_vector_vector_vector
// {
// public:


//         typedef std::ptrdiff_t difference_type; 
// 	    typedef iterator value_type;
// 	    typedef	iterator*  pointer;
// 	    typedef iterator& reference;
//         typedef const iterator* const_pointer;
//         typedef const iterator& const_reference;
// 		typedef ft::random_access_iterator_tag iterator_category;

// 	// typedef iterator		value_type;
// 	// typedef iterator	reference;
// 	// typedef iterator	const_reference;
// 	// typedef iterator	pointer;
// 	// typedef iterator	const_pointer;
// 	// typedef iterator	difference_type;

// 	reverse_iterator_vector_vector_vector(void) {};
// 	reverse_iterator_vector_vector_vector(pointer ptr) { this->_base = *ptr; };

//     // vectorReverseIterator(iterator_vector<value_type> const &src) { _base = src.operator->(); } ;
// 	// vectorReverseIterator(vectorReverseIterator const &src) { *this = src; } ;

// 	reverse_iterator_vector_vector_vector(iterator_vector<value_type> const &src) { _base = src.operator->(); } ;
// 	reverse_iterator_vector_vector_vector(reverse_iterator_vector_vector_vector const &src) { *this = src; } ;

// 	virtual ~reverse_iterator_vector_vector_vector() {};

// 	iterator base(void) const { return this->_base; };
// 	template <class U> reverse_iterator_vector_vector_vector &operator=(const reverse_iterator_vector_vector_vector<U> &u);
// 	// reverse_iterator_vector_vector_vector &operator=(reverse_iterator_vector_vector_vector const &src) { _base = src._base; return (*this); };

// 	// BOOLEANS
// 	bool operator ==(reverse_iterator_vector_vector_vector const& b) const { return (_base == b._base); };
// 	bool operator !=(reverse_iterator_vector_vector_vector const& b) const { return (_base != b._base); };
// 	bool operator >(reverse_iterator_vector_vector_vector const& b) const { return (_base > b._base); };
// 	bool operator <(reverse_iterator_vector_vector_vector const& b) const { return (_base < b._base); };
// 	bool operator >=(reverse_iterator_vector_vector_vector const& b) const { return (_base >= b._base); };
// 	bool operator <=(reverse_iterator_vector_vector_vector const& b) const { return (_base <= b._base); };

// 	// ARITHMETICS

// 	// difference_type		operator-(const reverse_iterator_vector_vector<U> &u) { return u.base().operator-(this->_base); };
// 	// reverse_iterator_vector_vector	operator- (difference_type n) const { return reverse_iterator_vector_vector(this->_base.operator+(n)); };

// friend reverse_iterator_vector_vector_vector operator+(difference_type n, const reverse_iterator_vector_vector_vector& it ) {return it.operator+(n);}
// //The incremented iterator, that is reverse_iterator_vector_vector<Iter>(it.base() - n)
// difference_type operator-( const reverse_iterator_vector_vector_vector<value_type>& lhs) {return lhs.base().operator-(this->_base);}
// //rhs.base() - lhs.base()
// reverse_iterator_vector_vector_vector operator+( difference_type n ) const {return reverse_iterator_vector_vector_vector(this->_base.operator-(n));}
// //reverse_iterator_vector_vector(base()-n) or reverse_iterator_vector_vector(base()+n)
// reverse_iterator_vector_vector_vector operator-( difference_type n ) const {return reverse_iterator_vector_vector_vector(this->_base.operator+(n));}
// //reverse_iterator_vector_vector(base()-n) or reverse_iterator_vector_vector(base()+n)

// //difference_type operator-(const reverse_iterator_vector_vector<U> &u) { return u.base().operator-(this->_base); };
// //reverse_iterator_vector_vector operator+ (difference_type n) const { return reverse_iterator_vector_vector(this->_base.operator-(n)); };
// //reverse_iterator_vector_vector	operator- (difference_type n) const { return reverse_iterator_vector_vector(this->_base.operator+(n)); };

// //friend reverse_iterator_vector_vector	operator+(difference_type n, const reverse_iterator_vector_vector &rhs)
// 				//{ return rhs.operator+(n); };



// 	// reverse_iterator_vector_vector_vector	operator+ (difference_type n) const { return reverse_iterator_vector_vector_vector(_base.operator-(n)); };
// 	// reverse_iterator_vector_vector_vector operator +(const reverse_iterator_vector_vector_vector b) { return (this->_base - b._base); }; // a + b
// 	// reverse_iterator_vector_vector_vector operator -(const reverse_iterator_vector_vector_vector b) { return (this->_base + b._base); }; // a - b
// 	// reverse_iterator_vector_vector_vector	operator- (difference_type n) const { return reverse_iterator_vector_vector_vector(this->_base.operator+(n)); };

// 	// INCREMENTERS
// 	reverse_iterator_vector_vector_vector operator ++() { _base--; return (*this); };			// ++a
// 	reverse_iterator_vector_vector_vector operator ++(int) { _base--; return (reverse_iterator_vector_vector_vector(_base + 1)); };	// a++
// 	reverse_iterator_vector_vector_vector operator --() { _base++; return (*this); };			// --a
// 	reverse_iterator_vector_vector_vector operator --(int) { _base++; return (reverse_iterator_vector_vector_vector(_base - 1)); };	// a--

// 	//COMPOUND ASSIGNMENTS
// 	reverse_iterator_vector_vector_vector operator +=(difference_type b) { _base -= b; };	// a += b
// 	reverse_iterator_vector_vector_vector operator -=(difference_type b) { _base += b; };	// a -= b

// 	//DEREFERENCING & ADDRESS STUFF

// 	//Reference or pointer to the element previous to current. 

// 	reference operator *() { return (this->_base); };											// *a
// 	const_reference operator *() const { return (*this->_base); };								// *a
// 	// reference operator [](difference_type b) { return ((this->_base + b)); };				// a[]
// 	// const_reference operator [](difference_type b) const { return (*(this->_base + b)); };		// a[]
// 	reference	operator[](difference_type n)  { return *this->operator+(n); };
// 	iterator operator ->() { return (this->_base); };											// a->b
// 	iterator operator ->() const { return (this->_base); };											// a->b	

// 	static const bool input_iter = true;

// 	protected:
// 		iterator super;
// 		iterator _base;
// };

// template <class Iterator> template <class U>
// reverse_iterator_vector_vector_vector<Iterator>	&reverse_iterator_vector_vector_vector<Iterator>::operator=(const reverse_iterator_vector_vector_vector<U> &u) {
// 	if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
// 		return (*this);
// 	this->_base = u.base();
// 	return (*this); }

// template <class T>
// reverse_iterator_vector_vector_vector<T> operator+(std::ptrdiff_t i, reverse_iterator_vector_vector_vector<T> &it) {
// 	return (it - i);
// }


// }

// #endif