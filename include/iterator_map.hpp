#ifndef ITERATOR_MAP_H
#define ITERATOR_MAP_H

#include "../utils/traits.hpp"
#include "tree_iterator.hpp"

namespace ft{

template <class value_type, class kc>
class iterator_map : public tree_iterator<value_type, kc>{

public:
    typedef value_type* pointer;
    typedef value_type& reference;

    iterator_map(): tree_iterator<value_type, kc>(){};

    virtual ~iterator_map(){
    }
    iterator_map(const iterator_map &src){
        *this = src;
    };
    iterator_map(Node<value_type> *node){
        this->_avlIt._head = node;
    }
    pointer operator->()const{
        return&(this->_avlIt._head->_pair);
    }
    reference operator*()const{
        return (this->_avlIt._head->_pair);
    }

};

}; //end of namespace

#endif