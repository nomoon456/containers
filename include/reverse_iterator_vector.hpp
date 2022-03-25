#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "../utils/traits.hpp"

namespace ft{

    template <typename Iterator>
    class	reverse_iterator{
    public:

		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
	
	protected:
		Iterator _current;

	public:
	    reverse_iterator(void):_current(0) {};
		explicit reverse_iterator(Iterator x):_current(x){};
		template<class U>
		reverse_iterator(const reverse_iterator<U> &u){*this = u;};
	    ~reverse_iterator(void) {};
		template<class U>
	    reverse_iterator &operator=(const reverse_iterator<U> &u);

		Iterator base() const{return(_current);};

		reference operator*() const{
			Iterator tmp = _current;
			return (*--tmp);
		};

		pointer operator->() const{
			return &(operator*());
		};


		reverse_iterator& operator++(){
			--_current;
			return (*this);
		};
		reverse_iterator operator++(int){
			reverse_iterator tmp = *this;
			--_current;
			return (tmp);
		};
		reverse_iterator& operator--(){
			++_current;
			return (*this);
		};
		reverse_iterator operator--(int){
			reverse_iterator tmp = *this;
			++_current;
			return (tmp);
		};
		reverse_iterator operator+ (difference_type n) const{
			return (reverse_iterator(base().operator-(n)));
		};
		reverse_iterator& operator+=(difference_type n){
			_current -= n;
			return (*this);
		};
		reverse_iterator operator- (difference_type n) const{
			return (reverse_iterator(base().operator+(n)));
		};
		reverse_iterator& operator-=(difference_type n){
			_current += n;
			return (*this);
		};
		reference operator[](difference_type n) const{
			return (_current[-n -1]);
		};
		difference_type		operator-(const reverse_iterator<Iterator> &u) { return u.base().operator-(_current); };
		
		// friend reverse_iterator	operator+(difference_type n, const reverse_iterator &rhs)
		// 		{ return rhs.operator+(n); };

    }; //end of reverse iterator definition class

		/*======================
		|   NO-MEMBER OPERATOR |
		=======================*/
		template <class IteratorLeft, class IteratorRight>
		bool operator==(const reverse_iterator<IteratorLeft>& x, const reverse_iterator<IteratorRight>& y){
			return (x.base() == y.base());
		};

		template <class IteratorLeft, class IteratorRight>
		bool operator<(const reverse_iterator<IteratorLeft>& x, const reverse_iterator<IteratorRight>& y){
			return (x.base() > y.base());
		}

		template <class IteratorLeft, class IteratorRight>
		bool operator!=(const reverse_iterator<IteratorLeft>& x, const reverse_iterator<IteratorRight>& y){
			return (x.base() != y.base());
		}

		template <class IteratorLeft, class IteratorRight>
		bool operator>(const reverse_iterator<IteratorLeft>& x, const reverse_iterator<IteratorRight>& y){
			return (x.base() < y.base());	
		}

		template <class IteratorLeft, class IteratorRight>
		bool operator>=(const reverse_iterator<IteratorLeft>& x, const reverse_iterator<IteratorRight>& y){
			return (x.base() <= y.base());	
		}

		template <class IteratorLeft, class IteratorRight>
		bool operator<=(const reverse_iterator<IteratorLeft>& x, const reverse_iterator<IteratorRight>& y){
			return (x.base() >= y.base());	
		}

		// template <class Iterator>
		// reverse_iterator<Iterator> operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y){
		// 	return (y.base() - x._base());
		// }

		template <class Iterator>
		reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type  n, const reverse_iterator<Iterator>& x){
			return (reverse_iterator<Iterator>(x.base() - n));
		}

		template <class Iterator> template <class U>
		reverse_iterator<Iterator>	&reverse_iterator<Iterator>::operator=(const reverse_iterator<U> &u) {
			if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
				return (*this);
			this->_current = u.base();
			return (*this);
		}


}//end of namespace ft

#endif