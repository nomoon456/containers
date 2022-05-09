#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <typeinfo>
#include <limits>
#include "../utils/Pair.hpp"
#include "../utils/AVL.hpp"
#include "../include/tree_iterator.hpp"
#include "../include/iterator_map.hpp"
#include "../include/const_iterator_map.hpp"
#include "../include/reverse_iterator_vector.hpp"
#include "../utils/traits.hpp"
#include "../utils/algorithm.hpp"
#include "./vector.hpp"


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

	/*=========================
  	|   CLASS VALUE_COMPARE	   |
  	===========================*/
	class value_compare
	: public std::binary_function<value_type,value_type,bool> {
	friend class map;
	// protected:
	public:
		Compare comp;
		value_compare(Compare c = Compare()) : comp(c) {}
		bool operator()(const value_type& x, const value_type& y) const {
		return comp(x.first, y.first);
		}

	}; //end of class value_compare

	/*============
  	|   ITERATOR  |
  	==============*/
	
	typedef ft::iterator_map<value_type, value_compare> iterator;
	typedef ft::const_iterator_map<value_type, value_compare> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	/*=============================
  	|   CONSTRUCT/ COPY/ DESTROY   |
  	==============================*/
	public:
		explicit map(const Compare& comp = Compare(),
		const Allocator& alloc = Allocator()){
			_avl._alloc = alloc;
			_avl._key_compare = comp;
			_avl._dummyNode = _avl._alloc.allocate(1);
     		_avl._alloc.construct(_avl._dummyNode, Node<value_type>());
		};


		template <class InputIterator>
		map(InputIterator first, InputIterator last,
		const Compare& comp = Compare(), const Allocator& alloc = Allocator(),
        typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0){
			_avl._alloc = alloc;
			_avl._key_compare = comp;
			_avl._dummyNode = _avl._alloc.allocate(1);
			_avl._alloc.construct(_avl._dummyNode, Node<value_type>());
			insert(first, last);
		}

		map(const map<Key,T,Compare,Allocator>& x,
		const Compare& comp = Compare(), const Allocator& alloc = Allocator()){
			_avl._alloc = alloc;
			_avl._key_compare = comp;
			_avl._dummyNode = _avl._alloc.allocate(1);
			_avl._alloc.construct(_avl._dummyNode, Node<value_type>());
			insert(x.begin(), x.end());
		}

		map<Key,T,Compare,Allocator>&
		operator=(const map<Key,T,Compare,Allocator>& x){
			clear();
			insert(x.begin(), x.end());
			return (*this);
		}

		~map(){
			_avl.freeDummyNode();
			_avl.freeAVL(_avl._head);
		};

	private:
		typedef	Node<value_type> _node;
		typedef typename allocator_type::template rebind<_node>::other		_avl_allocator;

		AVL<value_type, key_compare> _avl;

	/*==============
 	| PRIVATE FUNC  |
	===============*/
	void detachDummyNode(){
		Node<value_type> *curr;

		if (!_avl._head)
			return;
		//detach dummy node at the begining
		curr = _avl.minValNode(_avl._head);
		if (curr){
			curr->_left = NULL;
		}

		//detach dummy node at the end
		curr = _avl.maxValNode(_avl._head);
		if (curr){
			curr->_right = NULL;
			_avl._dummyNode->_parent = NULL;
		}

	}

	void tieDummyNode(){
		Node<value_type> *curr;

		if (!_avl._head)
			return;
		//tie dummy node at the begining
		curr = _avl.minValNode(_avl._head);
		if (curr){
			curr->_left = _avl._dummyNode;
		}

		//tie dummy node at the end
		curr = _avl.maxValNode(_avl._head);
		if (curr){
			curr->_right = _avl._dummyNode;
			_avl._dummyNode->_parent = curr;
		}
	}

	/*=============
  |   ITERATOR   |
  ===============*/
	public:
	iterator begin(){
		if (!_avl._head)
			return (_avl._dummyNode);
		return (_avl.minValNode(_avl._head));
	}
	iterator end(){
		return (_avl._dummyNode);
	}
	const_iterator begin() const{
		if (!_avl._head)
			return (_avl._dummyNode);
		return (_avl.minValNode(_avl._head));
	}
	const_iterator end() const{
		return (_avl._dummyNode);
	}
	reverse_iterator rbegin(){
		return (reverse_iterator(end()));
	}
	const_reverse_iterator rbegin() const{
		return (_avl._dummyNode);
	}
	reverse_iterator rend(){
		return(reverse_iterator(begin()));
	}
	const_reverse_iterator rend() const{
		return (_avl._dummyNode);
	}

	/*=============
	|   CAPACITY   |
  	===============*/
	bool empty() const{
		return (1 ? size() == 0 : 0);
	}
	size_type size() const{
		return (_avl.getSize());
	}
	size_type max_size() const{
		return (_avl_allocator().max_size());
	}
	allocator_type get_allocator() const{
		return (allocator_type());
	}

	/*================
  	|   ELMT ACCESS   |
 	==================*/
	void print(){
		_avl.print(_avl._head);
	}

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
		detachDummyNode();
		_avl._head = _avl.insert(_avl._head, x);
		tieDummyNode();

		Node<value_type> *node = _avl.find(_avl._head, x.first);
		ft::pair<iterator, bool> p(node, false);
		if (_avl.getSize() != sz){
			p = ft::pair<iterator, bool> (node, true);
		}
		return (p);
	}

	iterator insert(iterator , const value_type& x){
		detachDummyNode();
		_avl._head = _avl.insert(_avl._head, x);
		tieDummyNode();
		return (_avl.find(_avl._head, x.first));
	}
  
	template <class InputIterator>
	typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::void_t 
	insert(InputIterator first,InputIterator last){
		for(;first != last; first++){
			insert(*first);
		}
	}

	void erase(iterator position){
		detachDummyNode();
		_avl._head = _avl.deleteNode(_avl._head, position->first);
		tieDummyNode();
	}

	size_type erase(const key_type& x){
		size_t sz = _avl.getSize();
		erase(find(x));
		if (_avl.getSize() != sz)
			return(1);
		return (0);
	}
	void erase(iterator first, iterator last){
		vector<Key> v;
		
		while(first != last){
			v.push_back(first->first);
			first++;
		}
		for(size_t i = 0; i < v.size();i++){
			erase(v[i]);
		}
	}
	
	void swap(map<Key,T,Compare,Allocator>& x){

		std::swap(_avl, x._avl);
	}

	void clear(){
		erase(begin(), end());
		_avl._head = NULL;
	}

	/*==============
	|   OBSERVERS   |
	===============*/
	key_compare key_comp() const{
		return (key_compare());
	}
	value_compare value_comp() const{
		return (value_compare());
	}

	/*==================
  	|   MAP OPERATION   |
	===================*/
	iterator find(const key_type& x){
			Node<value_type> *node = _avl.find(_avl._head, x);
			if (node == NULL)
				return (end());
			return (node);
	}
	const_iterator find(const key_type& x) const{
			Node<value_type> *node = _avl.find(_avl._head, x);
			if (node == NULL)
				return (end());
			return (node);
	}
	size_type count(const key_type& x) const{
		if (_avl.find(_avl._head, x) != NULL)
			return (1);
		return (0);
	}
	iterator lower_bound(const key_type& x){
		key_compare kc;
		iterator it = begin();
		for(; it != end(); it++){
			if (!kc(it->first, x))
				return (it);
		}
		return (end());
	}
	const_iterator lower_bound(const key_type& x) const{
		key_compare kc;
		const_iterator it = begin();
		for(; it != end(); it++){
			if (!kc(it->first, x))
				return (it);
		}
		return (end());
	}

	iterator upper_bound(const key_type& x){
		key_compare kc;
		iterator it = begin();
		for(; it != end(); ++it){
			if (kc(x, it->first))
				return (it);
		}
		return (end());
	}
	const_iterator upper_bound(const key_type& x) const{
		key_compare kc;
		const_iterator it = begin();
		for(; it != end(); ++it){
			if (kc(x, it->first))
				return (it);
		}
		return (end());
	}

	pair<iterator,iterator>
	equal_range(const key_type& x){
		pair<iterator, iterator> p;

		p.first = lower_bound(x);
		p.second = upper_bound(x);
		return (p);
	}

	pair<const_iterator,const_iterator>
	equal_range(const key_type& x) const{
		pair<const_iterator, const_iterator> p;

		p.first = lower_bound(x);
		p.second = upper_bound(x);
		return (p);
	}


};// end of class map

/*=========================
|   NON-MEMBER OVERLOADS   |
==========================*/
template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y){
	if (x.size() != y.size())
		return (false);
	return (ft::equal(x.begin(), x.end(), y.begin()));
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y){
	return (!(x == y));
}

template <class Key, class T, class Compare, class Allocator>
bool operator< (const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y){
	return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
}


template <class Key, class T, class Compare, class Allocator>
bool operator> (const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y){
	return (y < x);
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y){
	return (x == y || (y < x));
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key,T,Compare,Allocator>& x,
const map<Key,T,Compare,Allocator>& y){
	return (x == y || x < y);
}

template <class Key, class T, class Compare, class Allocator>
void swap(map<Key,T,Compare,Allocator>& x,
map<Key,T,Compare,Allocator>& y){
	x.swap(y);
}

}; // end of namespace
#endif