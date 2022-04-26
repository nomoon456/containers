#ifndef TREE_ITERATOR_H
#define TREE_ITERATOR_H

#include "../utils/traits.hpp"
#include "map.hpp"

namespace ft{
    template <class value_type, class kc>
    class tree_iterator{
    public:
        typedef std::ptrdiff_t difference_type; 
	    typedef	value_type*  pointer;
		typedef const value_type* const_pointer;
	    typedef value_type& reference;
        typedef const value_type& const_reference;
		typedef ft::bidirectional_iterator_tag iterator_category;

        typedef typename value_type::first_type ftype;
        typedef typename value_type::second_type stype;


        tree_iterator(){};
        // tree_iterator(const tree_iterator &ref){
        //     _avlIt = ref._avlIt;
        // };
       tree_iterator(const tree_iterator &ref):_avlIt(ref._avlIt){
            // _avlIt = ref._avlIt;
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
            // std::cout << "tree_iterator node: " << _avlIt._head->_pair.first<< std::endl;

            if(_avlIt._head->_right){
                _avlIt._head = _avlIt.minValNode(_avlIt._head->_right);
            }
            else if (_avlIt._head->_parent){
                Node<value_type> *curr = _avlIt._head;
                while (curr->_parent != NULL
                && _avlIt.key_comp(curr, curr->_parent))
                    curr = curr->_parent;
                if (curr->_parent != NULL
                && _avlIt.key_comp(curr->_parent, _avlIt._head))
                    _avlIt._head = curr->_parent;
                else
                    _avlIt._head = _avlIt._dummyNode;
            }
			else
            	_avlIt._head = _avlIt._dummyNode;
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
                // std::cout << "1)" << std::endl;
                _avlIt._head = _avlIt.maxValNode(_avlIt._head->_left);
            }
            else if (_avlIt._head->_parent){
                // std::cout << "2)" << std::endl;
                // Node<value_type> *curr = _avlIt._head;
                // while (curr->_parent
                // && !_avlIt.key_comp(curr, curr->_parent))
                //     curr = curr->_parent;
                // if (curr->_parent
                // && !_avlIt.key_comp(curr->_parent, _avlIt._head)){
                //     _avlIt._head = curr->_parent;
                // }
                _avlIt._head = _avlIt._head->_parent;
            }
			else{
                // std::cout << "3)" << std::endl;
            	_avlIt._head = _avlIt._dummyNode;
            }
            return (*this);
		}
			
			// _ptr--
	    const tree_iterator operator--(int){
				tree_iterator tmp(*this);
        operator++();
        return (tmp);
			} 


        protected:
        AVL<value_type, kc> _avlIt;

    }; //end of class



}; //end of namespace


#endif