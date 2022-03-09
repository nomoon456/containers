#ifndef REVERSE_ITERATOR_VECTOR_H
#define REVERSE_ITERATOR_VECTOR_H

#include "../utils/traits.hpp"

namespace ft{

    template <typename T>
    class	reverse_iterator_vector{
    public:
        typedef reverse_iterator_vector<T> _it;

	    typedef std::ptrdiff_t difference_type;
	    typedef T value_type;
	    typedef	T*  pointer;
		typedef T& reference;
        typedef const T& const_reference;
        typedef const T* const_pointer;
		typedef ft::random_access_iterator_tag iterator_category;

	    reverse_iterator_vector(void) {};
	    reverse_iterator_vector(pointer ptr) { _ptr = ptr; };
	    // reverse_vector_iterator(iterator_vector<value_type> const &p) { _ptr = p.operator->(); } ;
	    reverse_iterator_vector(_it const &p) { *this = p; } ;
	    ~reverse_iterator_vector(void) {};
    
	    _it &operator=(_it const &p) { _ptr = p._ptr; return (*this); };

	    bool operator ==(_it const& p) const {return(this->_ptr == p._ptr);};
	    bool operator !=(_it const& p) const {return(this->_ptr != p._ptr);};
	    bool operator >(_it const& p) const {return(this->_ptr > p._ptr);};
	    bool operator <(_it const& p) const {return(this->_ptr < p._ptr);};
	    bool operator >=(_it const& p) const {return(this->_ptr >= p._ptr);};
	    bool operator <=(_it const& p) const {return(this->_ptr <= p._ptr);};

	    _it operator +(difference_type p) {return(_it(this->_ptr - p));}; // _ptr + p
	    _it operator -(difference_type p) {return(_it(this->_ptr + p));}; // _ptr - p

	    difference_type operator +(_it p) {return(this->_ptr - p._ptr);}; // _ptr + p
	    difference_type operator -(_it p) {return(this->_ptr + p._ptr);}; // _ptr - p

	    _it operator ++() { 
			this->_ptr--; return(*this);
			}; // ++_ptr

	    _it operator ++(int) { 
			this->_ptr--; return(_it(this->_ptr + 1));
			}; // _ptr++



	    _it operator --() { this->_ptr++; return(*this);}; // --_ptr
	    _it operator --(int) { this->_ptr++; return(_it(this->_ptr - 1));}; // _ptr--

	    void operator +=(difference_type p) {this->_ptr -= p;}; // _ptr += p
	    void operator -=(difference_type p) {this->_ptr += p;}; // _ptr -= p

	    pointer operator ->() {return(this->_ptr);}; // _ptr->p
	    pointer operator ->() const {return (this->_ptr);};
        reference operator *() const {return (*this->_ptr);}; // *_ptr
        // const_reference operator *() const {return (*this->_ptr);}; // *_ptr
	    const_reference operator [](difference_type p) const {return (*(this->_ptr + p));}; // _ptr[]
    private:
		pointer _ptr;
    }; //end of reverse iterator definition class
}//end of namespace ft

#endif