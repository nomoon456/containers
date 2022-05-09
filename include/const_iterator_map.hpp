#ifndef CONST_ITERATOR_MAP_H
#define CONST_ITERATOR_MAP_H

#include "../utils/traits.hpp"
#include "tree_iterator.hpp"

namespace ft{

template <class T, class kc>
class const_iterator_map : public tree_iterator<T, kc>{

public:
    typedef const T* pointer;
    typedef const T& reference;
    typedef	typename tree_iterator<T, kc>::iterator_category		iterator_category;
	typedef	typename tree_iterator<T, kc>::value_type			value_type;

    const_iterator_map(): tree_iterator<value_type, kc>(){
		};

    virtual ~const_iterator_map(){
    }
    const_iterator_map(const tree_iterator<value_type, kc> &src): tree_iterator<T, kc>(src){
    };

    const_iterator_map(Node<T> *node){
        this->_avlIt._head = node;
    }
    pointer operator->()const{
        return&(this->_avlIt._head->_pair);
    }
    reference operator*()const{
        return (this->_avlIt._head->_pair);
    }
		const_iterator_map	&operator++() { tree_iterator<T, kc>::operator++(); return *this; };
		const_iterator_map	&operator--() { tree_iterator<T, kc>::operator--(); return *this; };
		const_iterator_map	operator++(int) {
			const_iterator_map tmp(*this);
			operator++();
			return tmp;
		};
		const_iterator_map	operator--(int)  {
			const_iterator_map tmp(*this);
			operator--();
			return tmp;
		};
};

}; //end of namespace

#endif