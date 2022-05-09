#ifndef TREE_ITERATOR_H
#define TREE_ITERATOR_H

#include "../utils/traits.hpp"
#include "../container/map.hpp"

namespace ft{
    template <class T, class value_compare>
    class tree_iterator{
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type; 
	    typedef	T*  pointer;
		typedef const T* const_pointer;
	    typedef T& reference;
        typedef const T& const_reference;
		typedef ft::bidirectional_iterator_tag iterator_category;
        
        typedef typename T::first_type ftype;
        typedef typename T::second_type stype;


        tree_iterator(){};

        tree_iterator(const tree_iterator &ref):_avlIt(ref._avlIt){
        };

        const tree_iterator &operator=(const tree_iterator &rhs){
            if (this == &rhs)
	    	    return (*this);
	        this->_avlIt = rhs._avlIt;
            return (*this);
        }
        virtual ~tree_iterator(){
        }
        
        bool operator==(const tree_iterator &it)const{
            return (_avlIt._head == it._avlIt._head);
        };
        bool operator!=(const tree_iterator &it)const{
            return (_avlIt._head != it._avlIt._head);
        };

        // ++_ptr
        const tree_iterator operator++(){
            if(_avlIt._head->_right){
                _avlIt._head = _avlIt.minValNode(_avlIt._head->_right);
            }
            else if (_avlIt._head->_parent){
                Node<T> *curr = _avlIt._head;
                while (curr->_parent
                && value_compare()(curr->_parent->_pair, curr->_pair))
                    curr = curr->_parent;
                if (curr->_parent
                && value_compare()(_avlIt._head->_pair, curr->_parent->_pair)){
                    _avlIt._head = curr->_parent;
                }
                else{
                    _avlIt._head = _avlIt._dummyNode;
                }
            }
			else{
            	_avlIt._head = _avlIt._dummyNode;
            }
            return (*this);
        }; 
        // _ptr++
	    const tree_iterator operator++(int){
            tree_iterator tmp(*this);
            operator++();
            return (tmp);
        }
			//--_ptr
	    const tree_iterator operator--(){
            if (_avlIt._head != _avlIt._dummyNode &&_avlIt._head->_left){
                _avlIt._head = _avlIt.maxValNode(_avlIt._head->_left);
            }
            else if (_avlIt._head->_parent){
                Node<T> *curr = _avlIt._head;
               while (curr->_parent
                && value_compare()(curr->_pair, curr->_parent->_pair))
                    curr = curr->_parent;
                if (curr->_parent
                && value_compare()(curr->_parent->_pair, _avlIt._head->_pair)){
                    _avlIt._head = curr->_parent;
                }
                else 
                    _avlIt._head = _avlIt._head->_parent;
            }
			else{
            	_avlIt._head = _avlIt._dummyNode;
            }
            return (*this);
		}
			
			// _ptr--
	    const tree_iterator operator--(int){
			tree_iterator tmp(*this);
            operator--();
            return (tmp);
		} 

        bool operator==(tree_iterator &x){
            return(this->_avlIt._head == x._avlIt._head);
        }
        bool operator!=(tree_iterator &x){
            return(this->_avlIt._head != x._avlIt._head);
        }
        protected:
        AVL<T, value_compare> _avlIt;

    }; //end of class

}; //end of namespace


#endif