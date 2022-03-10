#ifndef REV_ITE_HPP
#define REV_ITE_HPP
#include "../utils/traits.hpp"

namespace ft{
    template <class T>
    class rev_ite {
    public:
        typedef rev_ite<T> _it;
        typedef std::ptrdiff_t difference_type; 
	    typedef T value_type;
	    typedef	T*  pointer;
	    typedef T& reference;
		typedef ft::random_access_iterator_tag iterator_category;

        rev_ite(){};
        ~rev_ite(){};
    
	_it operator=(const rev_ite &rhs) {
		if (this == &rhs)
			return (*this);
		this->_ptr = rhs._ptr;
		return (*this);
	}

    bool operator!=(const _it &p){return (this->_ptr != p._ptr);}
	bool operator ==(_it const& p) const {return(this->_ptr == p._ptr);};
	bool operator >(_it const& p) const {return(this->_ptr > p._ptr);};
	bool operator <(_it const& p) const {return(this->_ptr < p._ptr);};
	bool operator >=(_it const& p) const {return(this->_ptr >= p._ptr);};
	bool operator <=(_it const& p) const {return(this->_ptr <= p._ptr);};

    _it operator++() { --this->_ptr; return(*this);}; // ++_ptr
	_it operator++(int) {_it tmp(*this); --this->_ptr; return(tmp);}; // _ptr++
	_it operator--() { ++this->_ptr; return(*this);}; // --_ptr
	_it operator--(int) {_it tmp(*this); ++this->_ptr; return(tmp);}; // _ptr--

    difference_type operator+(_it p) {return(this->_ptr - p._ptr);}; // _ptr + p
	difference_type operator-(_it p) {return(this->_ptr + p._ptr);}; // _ptr - p

    _it operator+=(difference_type p) {this->_ptr -= p; return(*this);}; // _ptr += p
	_it operator-=(difference_type p) {this->_ptr += p; return(*this);}; // _ptr -= p

    protected:
        pointer _ptr;
    };// end of itertor class
}; // end of ft 

#endif