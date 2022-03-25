#ifndef ITERATOR_VECTOR_H
#define ITERATOR_VECTOR_H

#include "../utils/traits.hpp"
#include "iterator.hpp"
#include "const_iterator_vector.hpp"


namespace ft{

    template <class T>
    class iterator_vector : public iterator<T> {
    public:
        typedef iterator_vector<T> _it;
        typedef std::ptrdiff_t difference_type; 
	    typedef T value_type;
	    typedef	T*  pointer;
		typedef const T* const_pointer;
	    typedef T& reference;
        typedef const T& const_reference;
		typedef ft::random_access_iterator_tag iterator_category;

		iterator_vector(void) : iterator<T>(){};
        iterator_vector(pointer ptr){this->_ptr = ptr;};
        ~iterator_vector(){};
		iterator_vector(const iterator_vector &src) : iterator<T>(src) {};

		_it operator +(difference_type p) {return this->_ptr + p;};
	    _it operator +(difference_type p) const {return(_it(this->_ptr + p));}; // _ptr + p
	    _it operator -(difference_type p) const {return(_it(this->_ptr - p));}; // _ptr - p

	    difference_type operator +(_it p) {return(this->_ptr + p._ptr);}; // _ptr + p
	    difference_type operator -(_it p) {return(this->_ptr - p._ptr);}; // _ptr - p

	    _it operator++() { ++this->_ptr; return(*this);}; // ++_ptr
		_it operator++(int) {_it tmp(*this); ++this->_ptr; return(tmp);}; // _ptr++
		_it operator--() { --this->_ptr; return(*this);}; // --_ptr
		_it operator--(int) {_it tmp(*this); --this->_ptr; return(tmp);}; // _ptr--

	    _it operator +=(difference_type p) {this->_ptr += p; return(*this);}; // _ptr += p
	    _it operator -=(difference_type p) {this->_ptr -= p; return(*this);}; // _ptr -= p

	    pointer operator ->() {return(this->_ptr);}; // _ptr->p
	    pointer operator ->() const {return (this->_ptr);};	
		reference operator *() {return (*this->_ptr);}; // *_ptr
        reference operator *() const {return (*this->_ptr);}; // *_ptr
	    reference operator [](difference_type p) const {return (*(this->_ptr + p));}; // _ptr[]
		reference operator [](difference_type p) { return (*(this->_ptr + p)); };	

    }; //end of iterator_vector definition class
	template <class T>
	iterator_vector<T> operator+(std::ptrdiff_t i, iterator_vector<T> &it) {
		return (it + i);
	}
}//end of namespace ft

#endif
