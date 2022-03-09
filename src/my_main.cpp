
// #include "our_test/AllTest.hpp"
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	// #include <map.hpp>
	// #include <stack.hpp>
	#include <vector.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))


int main() {
	ft::vector<int> vct(10);
	ft::vector<int>::iterator it(vct.begin());
	ft::vector<int>::const_iterator ite(vct.end());


	std::cout << "==bool comparison=="<< std::endl;
	if (it != ite)
   		std::cout << "1)" << std::endl;
	if (it == ite)
   		std::cout << "2)" << std::endl;
	if (it < ite)
   		std::cout << "3)" << std::endl;
	if (it > ite)
    	std::cout << "4)" << std::endl;
	if (it <= ite)
  	  std::cout << "5)" << std::endl;
	if (it >= ite)
  	  std::cout << "6)" << std::endl;
	
	std::cout << "==arithmetic=="<< std::endl;
	// std::cout << "it + ite: " << it + ite << std::endl; // Invalid in std
	// std::cout << "it - ite: " << it - ite << std::endl; 



  std::cout << "==END==" << std::endl;
  return 0;
}