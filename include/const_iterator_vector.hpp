#ifndef CONST_ITERATOR_VECTOR_H
#define CONST_ITERATOR_VECTOR_H

#include "../utils/traits.hpp"
#include "iterator_vector.hpp"
#include "iterator.hpp"


namespace ft {

    template <typename T>
    class	const_iterator_vector : public iterator<T> {
    public:
        typedef const_iterator_vector<T> _it;

        typedef std::ptrdiff_t difference_type;
	    typedef T value_type;
	    typedef	T*  pointer;
		typedef T& reference;
        typedef const T& const_reference;
        typedef const T* const_pointer;
		typedef ft::random_access_iterator_tag iterator_category;


	    const_iterator_vector(void) : iterator<T>(){};
	    const_iterator_vector(pointer ptr) {this->_ptr = ptr; };
	    ~const_iterator_vector() {};
		const_iterator_vector(const iterator<T> &src) : iterator<T>(src) {};

	    const _it operator+(difference_type p) {return(_it(this->_ptr + p));}; // _ptr + p
	    const _it operator-(difference_type p) {return(_it(this->_ptr - p));}; // _ptr - p

	    difference_type operator+(_it p) const {return(this->_ptr + p._ptr);}; // _ptr + p
	    difference_type operator-(_it p) const {return(this->_ptr - p._ptr);}; // _ptr - p

	    const _it operator++() { ++this->_ptr; return(*this);}; // ++_ptr
		const _it operator++(int) {_it tmp(*this); ++this->_ptr; return(tmp);}; // _ptr++
		const _it operator--() { --this->_ptr; return(*this);}; // --_ptr
		const _it operator--(int) {_it tmp(*this); --this->_ptr; return(tmp);}; // _ptr--

	    _it operator+=(difference_type p) {this->_ptr += p; return(*this);}; // _ptr += p
	    _it operator-=(difference_type p) {this->_ptr -= p; return(*this);}; // _ptr -= p

	    const_pointer operator->() {return(this->_ptr);}; // _ptr->p
	    const_pointer operator->() const {return (this->_ptr);};	
        const_reference operator*() const {return (*this->_ptr);}; // *_ptr
	    const_reference operator[](difference_type p) const {return (*(this->_ptr + p));}; // _ptr[]
    }; //end of iterator_vector definition class
}//end of namespace ft

#endif