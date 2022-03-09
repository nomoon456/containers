#include "AllTest.hpp"

/*
    Put in a main for testing all vector resize unit test
*/
void    testResize(){
	std::cout << "------------------" << std::endl;
	std::cout << "      RESIZE      " << std::endl;
	std::cout << "------------------" << std::endl;

	ft::vector<int> my_vect; //my vector
	std::vector<int> vect; //std vector

	for(size_t i = 0;i < 10;i++){
		my_vect.insert(my_vect.begin() +i,i);
		vect.insert(vect.begin() +i,i);
	}


	std::cout << "TEST 1" << std::endl;
	my_vect.resize(10);
	vect.resize(10);

	std::cout << "TEST 2" << std::endl;
	my_vect.resize(8, 100);
	vect.resize(8, 100);

	std::cout << "TEST 3" << std::endl;
	my_vect.resize(12);
	vect.resize(12);
	compErase(my_vect, vect);
}

/*
	== Note ==
	
*/