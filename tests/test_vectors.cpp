#include <iostream>
// #include "ipp.h"
#include <vector>
#include <string>
// #include "../include/ipp_ext.h" // extensions header-only templates

#include <catch2/catch_test_macros.hpp>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

// int main()
// {
// 	std::cout << "This is a IPP vector test." << std::endl;
	
// 	// instantiate a standard vector and see characteristics?
// 	std::vector<int> oldvector;
// 	std::cout << "std vector capacity = " << oldvector.capacity() << " and size = " << oldvector.size() << std::endl;
// 	for (int i = 0; i < 1024; i++){
// 		oldvector.push_back(1);
// 		if (oldvector.capacity() != oldvector.size())
// 		{
// 			std::cout << "std vector capacity = " << oldvector.capacity() << " and size = " << oldvector.size() << std::endl;
// 			break;
// 		}
// 	}
// 	// resize to the capacity and check
// 	oldvector.resize(oldvector.capacity());
// 	std::cout << "std vector capacity = " << oldvector.capacity() << " and size = " << oldvector.size() << std::endl;
// 	std::cout << "std vector last element = " << oldvector.back() << std::endl;
// 	oldvector.push_back(10);
// 	std::cout << "std vector capacity = " << oldvector.capacity() << " and size = " << oldvector.size() << std::endl;
// 	std::cout << "std vector last element = " << oldvector.back() << std::endl;
// 	oldvector.resize(2);
// 	std::cout << "std vector capacity = " << oldvector.capacity() << " and size = " << oldvector.size() << std::endl;
	
// 	// test wrong template?
// 	try{
// 		ippe::vector<int> wrongdata;
// 	}
// 	catch(int err)
// 	{
// 		std::cout<<"Caught error " << err << std::endl;
// 	}
	
// 	// create ipp template vectors
// 	ippe::vector<Ipp64fc> data;
// 	std::cout<<"ipp vector capacity = " << data.capacity() << " and size = " << data.size() << std::endl;

// 	// try a resize
// 	data.resize(256);
// 	data.resize(128);
// 	data.resize(8);
// 	std::cout<<"ipp vector capacity = " << data.capacity() << " and size = " << data.size() << std::endl;
	
// 	// pushback some data
// 	Ipp64fc val = {1.0, 2.0};
// 	data.push_back(val);
// 	std::cout<<"ipp vector size after push back is " << data.size() << std::endl;
// 	std::cout << "pushed back value is " << data.back().re << ", " << data.back().im << std::endl;
// 	std::cout << "or directly, = " << data.at(8).re << ", " << data.at(8).im << std::endl;
	
// 	// assign to last value
// 	data.at(data.size()-1) = {10.0, 20.0};
// 	// print allocate
// 	for (int i = 0; i < data.size(); i++){
// 		std::cout << "ipp vector val at " << i << " = " << data.at(i).re << ", " << data.at(i).im << std::endl;
// 	}
// 	// test exceptions
// 	try{
// 		data.at(data.size()) = {100.0, 200.0};
// 	}
// 	catch(std::out_of_range &exc){
// 		std::cout<<exc.what()<<std::endl;
// 	}
	
// 	// test a variety of templates
// 	ippe::vector<Ipp8u> v_8u;
// 	ippe::vector<Ipp16u> v_16u;
// 	ippe::vector<Ipp16sc> v_16sc;
// 	ippe::vector<Ipp32f> v_32f;
// 	ippe::vector<Ipp64f> v_64f;
	
// 	// test their resizes
// 	v_8u.resize(256);
// 	v_16u.resize(256);
// 	v_16sc.resize(256);
// 	v_32f.resize(256);
// 	v_64f.resize(256);

// 	return 0;
// }