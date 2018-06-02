/*!
 * @file    NumericalSemigroup.cpp
 * @brief   NumericalSemigroup class
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#include "NumSemTests.h"

NumSemTests::NumSemTests(){
    //this->sylvester_polynomial_graph();
    this->membership_test();
}

int NumSemTests::calculate_sylvester_denumerant() {
    /* calculate denumerant for t = */
    std::cout << "Introduce an integer for the Sylvester denumerant: ";
    int t;
    std::cin >> t;
    int den = this->ns->sylvester_denumerant(t, true);
    std::cout << std::endl;
    return den;
}

NumericalSemigroup* NumSemTests::initialize_numerical_semigroup_input() {

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
    return ns;
}

void NumSemTests::membership_test() {
    this->ns = this->initialize_numerical_semigroup_input();
    while (true) {
        std::cout << "Membership problem input: ";
        int memb_input;
        std::cin >> memb_input;
        std::cout << std::endl;
        if (this->ns->membership(memb_input)) {
            std::cout << "YES";
        } else {
            std::cout << "NO";
        }
        std::cout << std::endl;
    }
}

void NumSemTests::sylvester_polynomial_graph() {

    std::ofstream ofs;
    ofs.open ("sylvester_denumerant.txt", std::ofstream::out | std::ofstream::trunc);
    std::stringstream ss1;
    std::stringstream ss2;
    ss1 << "[";
    ss2 << "[";

    this->ns = this->initialize_numerical_semigroup_input();

    int upper_bound;
    std::cout << "Upper bound for the Sylvester denumerant: ";
    std::cin >> upper_bound;
    std::cout << std::endl;

    for (int i = 0; i < upper_bound; ++i){
        ss1 << i << ", ";
        ss2 << this->ns->sylvester_denumerant(i, false) << ", ";
    }
    ofs << ss1.str() << "]" << std::endl << ss2.str() << "]"  << std::endl;
    ofs.close();

}
