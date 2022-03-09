#include "AllTest.hpp"

/*
    Put in a main for testing all vector resize unit test
*/
void    testAssign(){
	std::cout << "------------------" << std::endl;
	std::cout << "      ASSIGN      " << std::endl;
	std::cout << "------------------" << std::endl;

	ft::vector<int> my_vect; //my vector
	std::vector<int> vect; //std vector

	for(size_t i = 0;i < 10;i++){
		my_vect.insert(my_vect.begin() +i,i);
		vect.insert(vect.begin() +i,i);
	}

	std::cout << "TEST 1" << std::endl;
    my_vect.assign(10 , 100);
    vect.assign(10 , 100);
    compErase(my_vect, vect);

    std::cout << "TEST 2" << std::endl;
    my_vect.assign(1 , 90);
    vect.assign(1 , 90);
    compErase(my_vect, vect);

    std::cout << "TEST 3" << std::endl;
    my_vect.assign(0 , 80);
    vect.assign(0 , 80);
    compErase(my_vect, vect);

    std::cout << "TEST 4" << std::endl;
    my_vect.assign(20 , 80);
    vect.assign(20, 80);
    compErase(my_vect, vect);
}

/*
	== Note ==
	
*/