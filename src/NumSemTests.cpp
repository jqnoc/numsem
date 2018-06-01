/*!
 * @file    NumericalSemigroup.cpp
 * @brief   NumericalSemigroup class
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#include "NumSemTests.h"

NumSemTests::NumSemTests(){
    this->Test1();
}

void NumSemTests::Test1(){

	std::cout << "### Add generators to the semigroup (type -1 for no more generators)" << std::endl;
	int newGenerator = 1;
	std::set<int> generators;
	while (newGenerator >= 0){
		std::cout << "Generator " << generators.size() + 1 << ": ";
		std::cin >> newGenerator;
		std::cout << std::endl;
		if (newGenerator > 1){
			generators.insert(newGenerator);
		} else if (newGenerator == 0 || newGenerator == 1) {
			std::cout << "Generators must be different to 0 and 1 - Try again" << std::endl;
		}
	}

	//std::cout << "NumericalSemigroup::NumericalSemigroup(std::set<int> generators)" << std::endl;
	NumericalSemigroup* ns = new NumericalSemigroup(generators);

	/* calculate denumerant for t = */
	std::cout << "Introduce an integer for the Sylvester denumerant: ";
	int t;
	std::cin >> t;
	ns->sylvester_denumerant(t);
	std::cout << std::endl;
}
