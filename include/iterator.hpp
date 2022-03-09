#ifndef ITERATOR_H
#define ITERATOR_H
#include "../utils/traits.hpp"

namespace ft{
    template <class T>
    class iterator {
    public:
        typedef iterator<T> _it;
        typedef std::ptrdiff_t difference_type; 
	    typedef T value_type;
	    typedef	T*  pointer;
		typedef const T* const_pointer;
	    typedef T& reference;
        typedef const T& const_reference;
		typedef ft::random_access_iterator_tag iterator_category;

        iterator(){};
        ~iterator(){};


    bool operator!=(const _it &p){return (this->_ptr != p._ptr);}
	bool operator ==(_it const& p) const {return(this->_ptr == p._ptr);};
	bool operator >(_it const& p) const {return(this->_ptr > p._ptr);};
	bool operator <(_it const& p) const {return(this->_ptr < p._ptr);};
	bool operator >=(_it const& p) const {return(this->_ptr >= p._ptr);};
	bool operator <=(_it const& p) const {return(this->_ptr <= p._ptr);};

    protected:
    pointer _ptr;
    };// end of itertor class

}; // end of ft 

#endif