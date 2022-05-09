#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include "../include/iterator_vector.hpp"
#include "../include/const_iterator_vector.hpp"
#include "../include/reverse_iterator_vector.hpp"
#include "../include/iterator.hpp"
#include "../utils/traits.hpp"
#include "../utils/algorithm.hpp"
#include <sstream>
#include <memory>
#include <iterator>

namespace ft {

template <class T, class A = std::allocator<T> >
class vector {
public:
    typedef T value_type;
    typedef A allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    typedef ft::iterator_vector<T> iterator;
    typedef ft::const_iterator_vector<T> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
    T *_array;
    A _alloc;
    size_type _size;
    size_type  _allocSize;

public:

    /*================
    |   CONSTRUCTOR   |
    ==================*/
    explicit vector (const allocator_type& alloc = allocator_type()):
    _alloc(alloc){
        _array = _alloc.allocate(0);
        _allocSize = 0;
        _size = 0;
    }

    explicit vector (size_type n, const value_type &val = value_type(),
        const allocator_type& alloc = allocator_type()):
    _alloc(alloc),
	_size(n){
        _allocSize = n;
		_array = _alloc.allocate(n);
         for(size_type i = 0;i < n; i++) {
            _alloc.construct(&_array[i], val);
            }
    }
            
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type(),
        typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0):
    _alloc(alloc){
        _array = NULL;
        _size = 0;
        _allocSize = 0;
        assign(first, last);
    }

    vector (const vector& x) : _alloc(){
        _array = NULL;
        _size = 0;
        _allocSize = 0;
        *this = x;
    }

    /*================
    |   DESTRUCTOR   |
    ================*/
        ~vector(){
            clear();
            _alloc.deallocate(_array, this->capacity());
        };

    /*============
    |   OPERATOR  |
    ===============*/
    reference operator[] (size_type n){
        return (_array[n]);
    }
    const_reference operator[] (size_type n)const{
        return (_array[n]);
    }

	vector &operator=(vector const &x)
	{
        this->insert(this->begin(), x.begin(), x.end());
		return (*this);
	}
    /*============
    |   ITERATOR  |
    ===============*/   
    iterator begin() {
        return (_array);
    }

    iterator end() {
        return (_array + _size);}
    
    const_iterator begin() const {
        return (_array);
    }

    const_iterator end() const {
        return (_array + _size);
    }

    reverse_iterator rbegin()
	{
		return (reverse_iterator(end()));
	};
	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(end()));
	};
	reverse_iterator rend()
	{
		return (reverse_iterator(begin()));
	};
	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(begin()));
	};

    /*====================
    |   MEMBER FUNCTION   |
    =====================*/
    
	void reserve(size_t new_cap) {
		if (new_cap > max_size())
			throw std::length_error("vector::reserve");
        size_type y = -1;
        if (_allocSize < new_cap) {
            T *newArr = _alloc.allocate(new_cap + 1);
            while (++y <= new_cap && y < size()) {
                _alloc.construct(&newArr[y], _array[y]);
            }
            _alloc.deallocate(_array, size());
            _allocSize = new_cap;
            _array = newArr;
        }
    }

    size_t size() const {
        return (_size);
    }

    size_t max_size() const {
        return (allocator_type().max_size());
    }

    size_t capacity() const {
        return (_allocSize);
    }


	iterator erase(iterator pos)
	{
		return erase(pos, pos + 1);
	}

	iterator erase(iterator first, iterator last)
	{
		size_t n = last - first;
		size_t offset = first - _array;
		allocator_type actr;

		for (size_t i = 0; i < _size - n - offset; i++)
		{
			_array[offset + i] = _array[offset + i + n];
		}
		_size -= n;
		return (iterator(_array + offset));
	}

    void    clear(){
        if (empty())
            return ;
        erase(begin(),end());
    }

    iterator insert(iterator pos, const T &value)
	{
		difference_type delta = pos - begin();
		insert(pos, 1, value);
		return (begin() + delta);
	}

        void  insert(iterator position, size_t n, const T &val) {
  	difference_type const	idx = position - begin();
	difference_type const	old_end_idx = end() - begin();
	iterator				old_end, end;

    resize(_size + n);
	end = this->end();
	position = begin() + idx;
	old_end = begin() + old_end_idx;
	while (old_end != position)
		*--end = *--old_end;
	while (n-- > 0)
		*position++ = val;
    }

	template <class InputIT>
	void insert(ft::iterator_vector<T> pos, InputIT its,
	typename ft::enable_if<is_iterator<InputIT>::value, InputIT>::type ite)
    {
        size_t delta = 0;
		size_t index = pos - this->begin();

		for (InputIT tmp = its; tmp != ite; ++tmp)
			++delta;

		if (this->_allocSize < this->_size + delta)
		{
			if (this->_size * 2 < this->_size + delta)
				this->reserve(this->_size + delta);
			else
				this->reserve(this->_size * 2 + !this->_allocSize);
		}
		pos = this->begin() + index;
        int on = 0;
        if (_size == 0)
            on = 1;
		this->_size += delta;
        if (on == 0) {
		for (iterator it = end() - 1; it != pos + delta - 1; --it)
			*it = *(it - delta);}
		while (its != ite)
		{
			*pos = *its;
			++pos;
			++its;
		}
    }

    void pop_back() {
        erase(end()- 1);}

    void push_back(const value_type &val) {
        insert(end(), val);
    }


    void resize (size_type size, T val = value_type()) {
	    if (size < this->_size)
	    {
		    while (size < this->_size)
			    this->_alloc.destroy(&this->_array[--this->_size]);
	    }
	    else
	    {
		    size_type const &tmp = this->_size;
		    if (size <= this->_allocSize)
			    ;
		    else if (size <= tmp * 2)
			    this->reserve(tmp * 2);
		    else
			    this->reserve(size);
		    while (this->_size < size)
			    this->_alloc.construct(&this->_array[this->_size++], val);
	    }
    }

    template <class InputIterator>
    void assign (InputIterator first, InputIterator last,
       typename ft::enable_if<ft::is_iterator<InputIterator>::value, InputIterator>::type* = 0) {
        clear();
        insert(begin(), first, last);
    }
    void assign (size_type n, const value_type& val) {
        clear();
        resize(n, val);
    }
  
 
    reference at(size_type pos)
	{
		std::stringstream str;
		if (pos > size())
		{
			str << "vector::_M_range_check: __n (which is " << pos << ") >= size() (which is " << size() << ")";
			throw std::out_of_range(str.str());
		}
		else
			return (_array[pos]);
	};

    const_reference at(size_type pos) const
	{
		std::stringstream str;
		if (pos > size())
		{
			str << "vector::_M_range_check: __n (which is " << pos << ") >= size() (which is " << size() << ")";
			throw std::out_of_range(str.str());
		}
		else
			return (_array[pos]);
	};

    reference front() {
        return (*(begin()));
    }

    const_reference front() const {
         return (*(begin()));
    }

    reference back() {
        return (*(end() - 1));
    }

    const_reference back() const {
        return (*(end() - 1));
    }

    bool empty() const {
        return (_size == 0 ? true : false);
    }

    allocator_type get_allocator()const {
        return (_alloc);
    }

    void swap (vector& x) {
        T* startTmp = _array;
        size_t sizeTmp = size();
        size_t capacityTmp = _allocSize;

        _array = x._array;
        _size = x.size();
        _allocSize = x._allocSize;

        x._array = startTmp;
        x._size = sizeTmp;
        x._allocSize = capacityTmp;
    }

    }; // end of vector class
 //end of ft namespace


/*======================
|   NO-MEMBER OPERATOR |
=======================*/

template <class T, class Alloc>
bool operator==(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    if (lhs.size() != rhs.size())
        return (false);
    return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return (!(lhs == rhs));
}


template <class T, class Alloc>
bool operator<(const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return (rhs < lhs);
}
template <class T, class Alloc>
bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return (!(lhs > rhs));
}
template <class T, class Alloc>
bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs){
    return (!(lhs < rhs));
}

/*======================
|   NO-MEMBER FUNCTION |
=======================*/

template <class T, class Alloc>
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y){
    x.swap(y);
}

};

#endif