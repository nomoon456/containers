#ifndef ALL_TEST_H
#define ALL_TEST_H

#include "vector.hpp"
#include "iterator_vector.hpp"
#include "const_iterator_vector.hpp"
#include "traits.hpp"
#include <iostream>
#include <sstream>
#include <vector>

/*
    Print std vector and ft vector
*/
template <typename T>
void print(ft::vector<T> &my_vect, std::vector<T> &vect){
    	std::cout << "== Max_size ==" << std::endl;
	std::cout << "our_test : " << my_vect.max_size() << "| std: " << vect.max_size()<< std::endl;
	std::cout << "== Size ==" << std::endl;
	std::cout << "our_test: " << my_vect.size() << "| std: " << vect.size()<< std::endl;
	std::cout << "== Capacity ==" << std::endl;
	std::cout << "our_test : " << my_vect.capacity() << "| std: " << vect.capacity()<< std::endl;
	std::cout << "== Value ==" << std::endl;
	std::cout << "our_test: " << std::endl;
	for(size_t i = 0; i < my_vect.size();i++)
		std::cout <<"#"<<i<<" " <<my_vect[i] <<" |";
	std::cout << std::endl;
	std::cout << "std: " << std::endl;
	for(size_t i = 0; i < vect.size();i++)
		std::cout <<"#"<<i<<" " << vect[i] <<" |";
	std::cout << std::endl;
}


/*
	Compare the function erase of ft::vector and std::vector
*/
template <typename T>
void compErase(ft::vector<T> &my_vect, std::vector<T> &vect){
    if (my_vect.max_size() != vect.max_size())
		std::cout << "[Error max_size] our_test: " << my_vect.max_size() << "| std: " << vect.max_size()
		<< std::endl;
	if (my_vect.size() != vect.size())
		std::cout << "[Error size] our_test: " << my_vect.size() << "| std: " << vect.size()
		<< std::endl;
	if (my_vect.capacity() != vect.capacity())
		std::cout << "[Error capacity] our_test: " << my_vect.capacity() << "| std: " << vect.capacity()
		<< std::endl;
	for(size_t i = 0; i < vect.size(); i++)
		if (vect[i] != my_vect[i] )
		{
			std::cout << "[Error value] print your vector to see the diff" 
			<< std::endl;
			return;
		}
}



/* unit test */
void testErase();
void testResize();
void testAssign();

#endif