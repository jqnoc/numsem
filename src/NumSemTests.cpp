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
    this->number_of_options = 6;
    this->numsem_init();
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

void NumSemTests::numsem_init() {
    this->ns = this->initialize_numerical_semigroup_input();
    this->print_numsem_options();
    int option;
    std::cin >> option;
    std::cout << std::endl;
    while (option != this->number_of_options) {
        if (option > this->number_of_options || option < 1) {
            std::cout << "Please, select a valid option." << std::endl;
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == this->number_of_options - 1) {
            this->ns = this->initialize_numerical_semigroup_input();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == this->number_of_options - 2) {
            this->numsem_sylvester_denumerant();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == this->number_of_options - 3) {
            this->numsem_membership();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == this->number_of_options - 4) {
            this->numsem_gaps();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == this->number_of_options - 5) {
            this->numsem_frobenius_number();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        }
    }
}

void NumSemTests::numsem_frobenius_number() {
    std::cout << "f(S) = " << this->ns->frobenius_number() << std::endl;
}

void NumSemTests::numsem_gaps() {
    std::vector<int> set_gaps = this->ns->gaps();
    if (set_gaps.size() == 0) {
        std::cout << "G(S) = Ø" << std::endl;
    } else {
        std::cout << "G(S) = {" << set_gaps[0];
        for (int i = 1; i < set_gaps.size(); ++i) {
            std::cout << ", " << set_gaps[i];
        }
        std::cout << "}" << std::endl;
    }
}

void NumSemTests::numsem_membership() {
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

void NumSemTests::numsem_sylvester_denumerant() {
    std::cout << "Sylvester denumerant input (integer): ";
    int sd_input;
    std::cin >> sd_input;
    std::cout << std::endl;
    int sd = this->ns->sylvester_denumerant(sd_input,true);
    std::cout << "d(" << sd_input << "; ";
    this->ns->print_generators();
    std::cout << ") = " << sd << std::endl << std::endl;
}

void NumSemTests::print_numsem_options() {
    std::cout << std::endl;
    this->ns->print_numerical_semigroup();
    std::cout << std::endl << std::endl << "Select an option:" << std::endl;
    std::cout << "\t" << this->number_of_options-5 << ". Calculate the Frobenius number of S." << std::endl;
    std::cout << "\t" << this->number_of_options-4 << ". Calculate the set of gaps of S." << std::endl;
    std::cout << "\t" << this->number_of_options-3 << ". Solve the membership problem for S and t." << std::endl;
    std::cout << "\t" << this->number_of_options-2 << ". Calculate the Sylvester denumerant d(t;S)." << std::endl;
    std::cout << "\t" << this->number_of_options-1 << ". Define a new numerical semigroup." << std::endl;
    std::cout << "\t" << this->number_of_options   << ". Exit." << std::endl;
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
