#ifndef ITERATOR_MAP_H
#define ITERATOR_MAP_H

#include "../utils/traits.hpp"
#include "tree_iterator.hpp"

namespace ft{

template <class T, class kc>
class iterator_map : public tree_iterator<T, kc>{

public:
    typedef T* pointer;
    typedef T& reference;
	typedef	typename tree_iterator<T, kc>::iterator_category		iterator_category;
	typedef	typename tree_iterator<T, kc>::value_type			value_type;

    iterator_map(): tree_iterator<T, kc>(){};

    ~iterator_map(){
			// this->_avlIt.freeDummyNode();
    }
    iterator_map(const iterator_map &src){
        *this = src;
    };
    iterator_map(Node<T> *node){
        this->_avlIt._head = node;
    }
    pointer operator->()const{
        return&(this->_avlIt._head->_pair);
    }
    reference operator*()const{
        return (this->_avlIt._head->_pair);
    }
	iterator_map	&operator++() { tree_iterator<T, kc>::operator++(); return *this; };
	iterator_map	&operator--() { tree_iterator<T, kc>::operator--(); return *this; };
	iterator_map	operator++(int) {
		iterator_map tmp(*this);
		operator++();
		return tmp;
	};
	iterator_map	operator--(int)  {
		iterator_map tmp(*this);
		operator--();
		return tmp;
	};
};

}; //end of namespace

#endif