#ifndef MAP_H
#define MAP_H
#include <iostream>
#include "Pair.hpp"
#include "AVL.hpp"
#include "../include/tree_iterator.hpp"
#include "../include/iterator_map.hpp"
#include "../utils/traits.hpp"
#include "../utils/algorithm.hpp"


namespace ft{

template < class Key,                                   			 	  // map::key_type
           class T,                                       				// map::mapped_type
           class Compare = std::less<Key>,                   		 	// map::key_compare
           class Allocator = std::allocator<ft::pair <const Key,T> > // map::allocator_type  
					 >    
class map{
public:

	/*==========
  	|   TYPES   |
	===========*/
	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<const Key, T> value_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
  	typedef std::ptrdiff_t difference_type;
 	typedef size_t size_type;

	typedef ft::iterator_map<value_type, key_compare> iterator;
	// typedef implementation defined const_iterator; // See 23.1
	// typedef std::reverse_iterator<iterator> reverse_iterator;
	// typedef std::reverse_iterator<const_iterator> const_reverse_iterator;



	/*=========================
  	|   CLASS VALUE_COMPARE	   |
  	===========================*/
	class value_compare
	: public std::binary_function<value_type,value_type,bool> {
	friend class map;
	protected:
		Compare comp;
		value_compare(Compare c = Compare()) : comp(c) {}
	public:
		bool operator()(const value_type& x, const value_type& y) const {
		return comp(x.first, y.first);
	}
	}; //end of class value_compare

	/*=============================
  	|   CONSTRUCT/ COPY/ DESTROY   |
  	==============================*/
	public:
		explicit map(const Compare& comp = Compare(),
		const Allocator& alloc = Allocator()){
			_avl._alloc = alloc;
			_avl._key_compare = comp;
		};


		// template <class InputIterator>
		// map(InputIterator first, InputIterator last,
		// const Compare& comp = Compare(), const Allocator& alloc = Allocator(),
        // typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0){
		// 	_avl._alloc = alloc;
		// 	_avl._key_compare = comp;
		// }

		// map(const map<Key,T,Compare,Allocator>& x);

		~map(){
			_avl.freeAVL(_avl._head);
		};

		// map<Key,T,Compare,Allocator>&
		// operator=(const map<Key,T,Compare,Allocator>& x);

	private:
		AVL<value_type, key_compare> _avl;
		Node<value_type> _dummyNode;

	/*=============
  |   ITERATOR   |
  ===============*/
	public:
	iterator begin(){
		if (!_avl._head)
			return (&_dummyNode);
		return (_avl.minValNode(_avl._head));
	}
	// const_iterator begin() const;
	iterator end(){
		return (&_dummyNode);
	}
	// const_iterator end() const;
	// reverse_iterator rbegin();
	// const_reverse_iterator rbegin() const;
	// reverse_iterator rend();
	// const_reverse_iterator rend() const;

	/*=============
  |   CAPACITY   |
  ===============*/
	// bool empty() const;
	size_type size() const{
		return (_avl.getSize());
	}
	// size_type max_size() const;
	// allocator_type get_allocator() const;

	/*================
  	|   ELMT ACCESS   |
 	==================*/
	T& operator[](const key_type& x){
		ft::pair<iterator, bool> tmp;

		tmp = insert(value_type(x, mapped_type()));
		return (tmp.first->second);
	}

	/*================
  	|   MODIFIERS     |
 	==================*/

	ft::pair<iterator, bool> insert(const value_type& x){
		size_t sz = _avl.getSize();
		_avl._head = _avl.insert(_avl._head, x);

		Node<value_type> *node = _avl.find(_avl._head, x.first);
		ft::pair<iterator, bool> p(node, false);
		if (_avl.getSize() != sz)
			p = ft::pair<iterator, bool> (node, true);
		return (p);
	}

	iterator insert(iterator , const value_type& x){
		_avl._head = _avl.insert(_avl._head, x);
		return (_avl._head);
	}
  
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last){
		for(;first != last; first++)
			insert(first, *first);
	}

	void erase(iterator position){
		ft::pair<const Key, T> p = *position;
		_avl.deleteNode(_avl._head, p.first);
	}
	// size_type erase(const key_type& x);
	// void erase(iterator first, iterator last);
	// void swap(map<Key,T,Compare,Allocator>&);
	// void clear();

	/*==============
	|   OBSERVERS   |
	===============*/
	// key_compare key_comp() const;
	value_compare value_comp() const{
		return (value_compare());
	}

	/*==================
  	|   MAP OPERATION   |
	===================*/
	iterator find(const key_type& x){
		return (_avl.find(_avl._head, x));
	}
	// const_iterator find(const key_type& x) const;
	// size_type count(const key_type& x) const;
	// iterator lower_bound(const key_type& x);
	// const_iterator lower_bound(const key_type& x) const;
	// iterator upper_bound(const key_type& x);
	// const_iterator upper_bound(const key_type& x) const;

	// pair<iterator,iterator>
	// equal_range(const key_type& x);

	// pair<const_iterator,const_iterator>
	// equal_range(const key_type& x) const;


};// end of class map


/*=========================
|   NON-MEMBER OVERLOADS   |
==========================*/
// template <class Key, class T, class Compare, class Allocator>
// bool operator==(const map<Key,T,Compare,Allocator>& x,
// const map<Key,T,Compare,Allocator>& y);
// template <class Key, class T, class Compare, class Allocator>
// bool operator< (const map<Key,T,Compare,Allocator>& x,
// const map<Key,T,Compare,Allocator>& y);
// template <class Key, class T, class Compare, class Allocator>
// bool operator!=(const map<Key,T,Compare,Allocator>& x,
// const map<Key,T,Compare,Allocator>& y);
// template <class Key, class T, class Compare, class Allocator>
// bool operator> (const map<Key,T,Compare,Allocator>& x,
// const map<Key,T,Compare,Allocator>& y);
// template <class Key, class T, class Compare, class Allocator>
// bool operator>=(const map<Key,T,Compare,Allocator>& x,
// const map<Key,T,Compare,Allocator>& y);
// template <class Key, class T, class Compare, class Allocator>
// bool operator<=(const map<Key,T,Compare,Allocator>& x,
// const map<Key,T,Compare,Allocator>& y);
// template <class Key, class T, class Compare, class Allocator>
// void swap(map<Key,T,Compare,Allocator>& x,
// map<Key,T,Compare,Allocator>& y);

}; // end of namespace
#endif