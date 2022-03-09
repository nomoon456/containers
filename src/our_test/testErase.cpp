#include "AllTest.hpp"

/*
    Put in a main for testing all vector erase unit test
*/
void    testErase(){
	std::cout << "------------------" << std::endl;
	std::cout << "      ERASE       " << std::endl;
	std::cout << "------------------" << std::endl;

	ft::vector<int> my_vect; //my vector
	std::vector<int> vect; //std vector

	for(size_t i = 0;i < 10;i++){
		my_vect.insert(my_vect.begin() +i,i);
		vect.insert(vect.begin() +i,i);
	}

	std::cout << "TEST 1" << std::endl;
	my_vect.erase(my_vect.begin());
	vect.erase(vect.begin());
	compErase(my_vect, vect);


	std::cout << "TEST 2" << std::endl;
	my_vect.erase(my_vect.begin(), my_vect.begin()+3);
	vect.erase(vect.begin(), vect.begin()+3);
	compErase(my_vect, vect);

	std::cout << "TEST 3" << std::endl;
	my_vect.erase(my_vect.end()- 3, my_vect.end());
	vect.erase(vect.end() - 3, vect.end());
	compErase(my_vect, vect);

	std::cout << "TEST 4" << std::endl;
	my_vect.erase(my_vect.begin(), my_vect.end());
	vect.erase(vect.begin(), vect.end());
	compErase(my_vect, vect);


	std::cout << "TEST 5" << std::endl;
	my_vect.erase(my_vect.end(), my_vect.end());
	vect.erase(vect.end(), vect.end());
	compErase(my_vect, vect);
}

/*
	== Note ==
	vect.erase(vect.end(), vect.begin()); Overflow
	
*/