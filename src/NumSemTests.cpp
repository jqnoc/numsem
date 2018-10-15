/*!
 * @file    NumericalSemigroup.cpp
 * @brief   NumericalSemigroup class
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#include <chrono>

#include "NumSemTests.h"

NumSemTests::NumSemTests(){
    this->number_of_options = 7;
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
        } else if (option == 1) {
            this->numsem_frobenius_number();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == 2) {
            this->numsem_gaps();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == 3) {
            this->numsem_membership();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == 4) {
            this->numsem_sylvester_denumerant(1);
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == 5) {
            this->sylvester_polynomial_graph();
            this->print_numsem_options();
            std::cin >> option;
            std::cout << std::endl;
        } else if (option == 6) {
            this->ns = this->initialize_numerical_semigroup_input();
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

void NumSemTests::numsem_sylvester_denumerant(int t) {
    int sd = this->ns->sylvester_denumerant(t,true);
    std::cout << "d(" << t << "; ";
    this->ns->print_generators();
    std::cout << ") = " << sd << std::endl << std::endl;
}

void NumSemTests::print_numsem_options() {
    std::cout << std::endl;
    this->ns->print_numerical_semigroup();
    std::cout << std::endl << std::endl << "Select an option:" << std::endl;
    std::cout << "\t" << "1. Calculate the Frobenius number of S." << std::endl;
    std::cout << "\t" << "2. Calculate the set of gaps of S." << std::endl;
    std::cout << "\t" << "3. Solve the membership problem for S and t." << std::endl;
    std::cout << "\t" << "4. Calculate the Sylvester denumerant d(t;S)." << std::endl;
    std::cout << "\t" << "5. Print to file the Sylvester denumerant graph d(t;S)." << std::endl;
    std::cout << "\t" << "6. Define a new numerical semigroup." << std::endl;
    std::cout << "\t" << "7. Exit." << std::endl;
}

void NumSemTests::sylvester_polynomial_graph() {

    std::ofstream ofs;
    ofs.open ("sylvester_polynomial.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    int upper_bound;
    std::cout << "Upper bound for the Sylvester polynomial graph: ";
    std::cin >> upper_bound;
    std::cout << std::endl;

    for (int i = 1; i <= upper_bound; ++i){

        /* calculate denumerant */
        auto begin = std::chrono::high_resolution_clock::now();
        int denumerant = this->ns->sylvester_denumerant(i, false);
        auto end = std::chrono::high_resolution_clock::now();

        ofs.open ("sylvester_polynomial.txt", std::ofstream::out | std::ofstream::app);
        ofs << i << " " << denumerant << " " << this->ns->number_of_bits(i) << " " << this->ns->number_of_iterations() << " " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count() << std::endl;
        ofs.close();
    }

}

void sylvester_denumerant_iter() {

    std::ofstream ofs;
    ofs.open ("sylvester_iters.txt", std::ofstream::out | std::ofstream::trunc);
    std::stringstream ss1;
    std::stringstream ss2;
    ss1 << "[";
    ss2 << "[";
}
