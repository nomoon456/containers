#ifndef PAIR_H
#define PAIR_H

namespace ft{

template <class T1, class T2> 
struct pair{

  /*==========================
  |   MEMBER type/ variable   |
  ===========================*/
	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;

	/*=============================
  |   CONSTRUCT/ COPY/ DESTROY   |
  ==============================*/
	pair():first(), second(){};

	template <class U, class V>
	pair(const pair<U,V>& x) : first(x.first), second(x.second) {};

	pair (const first_type& a, const second_type& b):first(a), second(b)
	{};

	template <class U, class V>
	pair& operator= (const pair& pr){
		this->first = pr.first;
		this->second = pr.second;
		return (*this);
	}

	~pair(){};


	}; //end of pair struct

	/*=============
  	|   FUNCTION   |
 	 ==============*/
	template <class T1, class T2>
 	ft::pair<T1,T2> make_pair (T1 x, T2 y){
		 return (ft::pair<T1, T2>(x, y));
	 }
};// end of namespace

	template <class T1, class T2>
	bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
		return (lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
		return (lhs.second != rhs.second);
	}

	template <class T1, class T2>
	bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
		return (lhs.second < rhs.second);
	}

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
		return (lhs.second <= rhs.second);
	}

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
		return (lhs.second > rhs.second);
	}

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs){
		return (lhs.second >= rhs.second);
	}


#endif