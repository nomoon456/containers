#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "traits.hpp"

namespace ft{

/*==========
|   EQUAL   |
============*/
template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
    typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
    typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0){
    while (first1 != last1){
        if (*first1 != *first2)
            return (false);
        first1++; first2++;
    }
    return (true);
}


template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred,
    typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
    typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0) {
    while (first1 != last1){
        if (*first1 != *first2)
            return (false ? pred(*first1, *first2) == false : true);
        first1++; first2++;
    }
    return (true ? pred(*first1, *first2) == true : false);
}

/*==========
|  LEXICO   |
============*/
template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
    typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
    typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0) {
    
    while (first1 != last1 && first2 != last2)
    {
        if (*first1 > *first2 || first2 == last2)
            return (false);
        else if (*first1 < *first2)
            return (true);
        first1++; first2++;
    }
    return (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
  bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2, Compare comp,
    typename ft::enable_if<ft::is_iterator<InputIterator1>::value, InputIterator1>::type* = 0,
    typename ft::enable_if<ft::is_iterator<InputIterator2>::value, InputIterator2>::type* = 0) {
    
    while (first1 != last1)
    {
        if (*first1 > *first2 || first2 == last2)
            return (false ? comp(*first1, *first2) == true : false);
        else if (*first1 < *first2)
            return (true ? comp(*first1, *first2) == true : false);
        first1++; first2++;
    }
    return (first2 != last2);
}

/*==========
|  OTHER    |
============*/
template <class InputIT>
int distance(InputIT first, InputIT last){
  size_t	i = 0;
    while (first != last){
        ++first; ++i;
    }
    return (i);
}


}; //end of namepsace
#endif