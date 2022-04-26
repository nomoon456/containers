#ifndef CONST_ITERATOR_MAP_H
#define CONST_ITERATOR_MAP_H

#include "../utils/traits.hpp"
#include "tree_iterator.hpp"

namespace ft{

template <class value_type, class kc>
class const_iterator_map : public tree_iterator<value_type, kc>{

public:
    typedef const value_type* pointer;
    typedef const value_type& reference;

    const_iterator_map(): tree_iterator<value_type, kc>(){
		};

    virtual ~const_iterator_map(){
    }
    const_iterator_map(const tree_iterator<value_type, kc> &src): tree_iterator<value_type, kc>(src){
    };

    const_iterator_map(Node<value_type> *node){
        this->_avlIt._head = node;
    }
    pointer operator->()const{
        return&(this->_avlIt._head->_pair);
    }
    reference operator*()const{
        return (this->_avlIt._head->_pair);
    }
		const_iterator_map	&operator++() { tree_iterator<value_type, kc>::operator++(); return *this; };
		const_iterator_map	&operator--() { tree_iterator<value_type, kc>::operator--(); return *this; };
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