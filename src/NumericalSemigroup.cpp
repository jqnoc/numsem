/*!
 * @file    NumericalSemigroup.cpp
 * @brief   NumericalSemigroup class
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#include "NumericalSemigroup.h"

NumericalSemigroup::NumericalSemigroup(std::set<int> generators) {

    /* get system of generators and initialize is_num_sem */
    this->generators = generators;
    this->is_num_sem = false;

    /* check if $gcd(a_1,...,a_n) = 1$ */
    std::set<int>::iterator it = this->generators.begin();
    int d = *it;
    ++it;
    while (it != this->generators.end()){
        d = this->gcd(d,*it);
        ++it;
    }
    if (d == 1){
        /* gcd (a_1,...,a_n) = 1 - we have a numerical semigroup */
        std::cout << "Created numerical semigroup ";
        this->print_numerical_semigroup();
        std::cout << std::endl;
        this->is_num_sem = true;
    	std::cout << "Total number of generators: " << this->get_number_generators() << std::endl;
    } else {
        /* gcd (a_1,...,a_n) != 1 - we do not have a numerical semigroup and the program exits */
        std::cout << "Error: ";
        this->print_numerical_semigroup();
        std::cout << " is not a numerical semigroup, as gcd(";
        this->print_generators();
        std::cout << ") = " << d << std::endl;
        exit(0);
    }
}

bool NumericalSemigroup::add_generator(int generator) {

    // TODO remains to be checked wheter the new generator was already contained in the numerical semigroup */
    std::pair<std::set<int>::iterator,bool> ret;
    ret = this->generators.insert(generator);
    return ret.second;
}

int NumericalSemigroup::gcd (int a, int b) {

    /* euclidean algorithm for the greatest common divisor ~ gcd(a,b) */
    int c;
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

int get_frobenius_number_bound() {
    int a_1 = this->generators.begin();
    int a_n = this->generators.rbegin();
    int bound = (a_1 - 1)*(a_n - 1) - 1;
    return bound;
}

int NumericalSemigroup::get_number_generators() {

    /* returns the number of generators of S = <A> (i.e., |A|) */
    return this->generators.size();
}

int NumericalSemigroup::ikp_solution(std::vector<int> lambda) {

    /* returns v = \sum_{i=1}^{n} \lambda_i * a_i */
    int value = 0;
    if (lambda.size() != this->generators.size()){
        std::cout << "Error: Lambda size different to number of generators" << std::endl;
        exit(0);
    } else {
        int lambda_index = 0;
        std::set<int>::iterator it = this->generators.begin();
        while (it != this->generators.end()){
            value += (*it)*lambda[lambda_index];
            ++it;
            ++lambda_index;
        }
    }
    return value;
}

bool NumericalSemigroup::is_numerical_semigroup() {

    /* returns true if the present system of generators generates a numerical semigroup (is_num_sem is calculated in the constructor) */
    return this->is_num_sem;
}

bool NumericalSemigroup::membership(int t) {

    /* check if t <= 0 */
    if (t < 0) {
        return false;
    } else if (t == 0) {
        return true;
    }

    /* get and process a_1 (i.e., the smallest generator of the numerical semigroup) */
    std::set<int>::iterator generators_iterator = this->generators.begin();
    int a_1 = *generators_iterator;
    if (t < a_1) {
        return false;
    } else if (t % a_1 == 0) {
        return true;
    }
    std::vector<int> new_generators;
    new_generators.push_back(a_1);
    ++generators_iterator;

    /* get and process the rest of generators */
    while (generators_iterator != this->generators.end()) {
        int a_i = *generators_iterator;
        if (t < a_i) {
            /* solves the membership for the semigroup S = <a_1,...,a_i> */
            return this->membership_core(t, new_generators);
        } else if (t % a_i == 0) {
            return true;
        }
        new_generators.push_back(a_i);
        ++generators_iterator;
    }

    return this->membership_core(t, new_generators);
}

bool NumericalSemigroup::membership_core(int t, std::vector<int> new_generators) {

    /* print new generators */
    // std::cout << "New generators: ";
    // for (int i = 0; i < new_generators.size(); ++i) {
    //     std::cout << new_generators[i] << "\t";
    // }
    // std::cout << std::endl;

    int a_1 = new_generators[0];
    int a_n = new_generators[new_generators.size() - 1];
    return false;
}

std::vector<int> NumericalSemigroup::next_lambda(std::vector<int> lambda, std::vector<int> bounds){

    /* next lambda iteration for the sylvester denumerant */
    int lambda_index = 0;
    bool finished = false;
    while (lambda_index < lambda.size()){
        if (lambda[lambda_index] < bounds[lambda_index]){
            lambda[lambda_index] += 1;
            return lambda;
        }
        lambda[lambda_index] = 0;
        ++lambda_index;
    }
    return std::vector<int>();
}

void NumericalSemigroup::print_generators() {

    /* print first generator */
    std::set<int>::iterator it = this->generators.begin();
    std::cout << *it;
    ++it;

    /* print the rest of generators */
    while (it != this->generators.end()) {
        std::cout << ", " << *it;
        ++it;
    }
}

void NumericalSemigroup::print_ikp_solution(std::vector<int> lambda) {
    if (lambda.size() != this->generators.size()) {
        std::cout << "Error: Lambda size different to number of generators" << std::endl;
        exit(0);
    } else {
        int lambda_index = 0;
        std::set<int>::iterator generators_iterator = this->generators.begin();
        std::cout << lambda[lambda_index] << "*(" << *generators_iterator << ")";
        ++generators_iterator;
        ++lambda_index;
        while (generators_iterator != this->generators.end()) {
            std::cout << " + " << lambda[lambda_index] << "*(" << *generators_iterator << ")";
            ++generators_iterator;
            ++lambda_index;
        }
    }
}

void NumericalSemigroup::print_numerical_semigroup() {
    std::cout << "S = <";
    this->print_generators();
    std::cout << ">";
}

int NumericalSemigroup::sylvester_denumerant(int t, bool with_solutions) {

    /* init */
    std::cout << std::endl << "  - Calculating Sylvester denumerant d(" << t << "; ";
    this->print_generators();
    std::cout << ") -" << std::endl << std::endl;
    int denumerant = 0;

    /* calculate bounds for lambda solution */
    std::vector<int> bounds = this->sylvester_denumerant_bounds(t);

    /* calculate sylvester denumerant */
    std::vector<int> lambda (this->generators.size(),0);

    while (!lambda.empty()) {

        /* check if this lambda is a solution */
        if (t == ikp_solution(lambda)) {

            /* update denumerant */
            ++denumerant;
            /* print solution */
            if (with_solutions) std::cout << "Solution " << denumerant << ":" << std::endl;
            if (with_solutions) this->print_ikp_solution(lambda);
            if (with_solutions) std::cout << std::endl;
        }

        /* calculate next lambda */
        lambda = next_lambda(lambda, bounds);
    }

    std::cout << std::endl << "d(" << t << "; ";
    this->print_generators();
    std::cout << ") = " << denumerant << std::endl << std::endl;
    return denumerant;
}

std::vector<int> NumericalSemigroup::sylvester_denumerant_bounds(int t){

    /* initialize bounds */
    std::vector<int> bounds;

    /* calculate and print bounds as b_i = \floor (t / a_i) */
    /* first bound */
    std::set<int>::iterator generators_iterator = this->generators.begin();
    std::cout << "Bounds for t = " << t << ": (";
    int b_i = t / *generators_iterator;
    bounds.push_back(b_i);
    std::cout << b_i;
    ++generators_iterator;

    /* rest of bounds */
    while (generators_iterator != this->generators.end()) {
        b_i = t / *generators_iterator;
        bounds.push_back(b_i);
        std::cout << ", " << b_i;
        ++generators_iterator;
    }
    std::cout << ")" << std::endl << std::endl;

    return bounds;
}
