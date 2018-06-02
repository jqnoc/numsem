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

int NumericalSemigroup::frobenius_number_bound() {
    int a_1 = *this->generators.begin();
    int a_n = *this->generators.rbegin();
    int bound = (a_1 - 1)*(a_n - 1) - 1;
    return bound;
}

std::vector<int> NumericalSemigroup::gaps() {
    std::vector<int> set_gaps;
    int bound = this->frobenius_number_bound();
    for (int i = 1; i <= bound; ++i) {
        if (! this->membership(i)) {
            set_gaps.push_back(i);
        }
    }
    return set_gaps;
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

int NumericalSemigroup::get_number_generators() {

    /* returns the number of generators of S = <A> (i.e., |A|) */
    return this->generators.size();
}

std::vector<int> NumericalSemigroup::ikp_bounds(int t, std::vector<int> new_generators) {

    /* initialize bounds */
    std::vector<int> bounds;

    /* calculate and print bounds as b_i = \floor (t / a_i) */
    /* first bound */
    int generators_index = 0;
    std::cout << "Bounds for t = " << t << ": (";
    int b_i = t / new_generators[generators_index];
    bounds.push_back(b_i);
    std::cout << b_i;
    ++generators_index;

    /* rest of bounds */
    while (generators_index < new_generators.size()) {
        b_i = t / new_generators[generators_index];
        bounds.push_back(b_i);
        std::cout << ", " << b_i;
        ++generators_index;
    }
    std::cout << ")" << std::endl << std::endl;

    return bounds;
}

int NumericalSemigroup::ikp_solution(std::vector<int> lambda, std::vector<int> new_generators) {

    /* returns v = \sum_{i=1}^{n} \lambda_i * a_i */
    int value = 0;
    if (lambda.size() != new_generators.size()){
        std::cout << "Error: Lambda size different to number of generators" << std::endl;
        exit(0);
    } else {
        int lambda_index = 0;
        while (lambda_index < lambda.size()) {
            value += lambda[lambda_index] * new_generators[lambda_index];
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

    /* check frobenius number bound */
    int bound = this->frobenius_number_bound();
    if (t > bound) {
        return true;
    }

    /* calculate bounds for lambda solution */
    std::vector<int> bounds = this->ikp_bounds(t, new_generators);

    /* calculate sylvester denumerant */
    std::vector<int> lambda (new_generators.size(),0);

    while (!lambda.empty()) {

        /* check if this lambda is a solution */
        if (t == ikp_solution(lambda,new_generators)) {
            return true;
        }

        /* calculate next lambda */
        lambda = next_lambda(lambda, bounds);
    }

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

void NumericalSemigroup::print_ikp_solution(std::vector<int> lambda, std::vector<int> new_generators) {
    if (lambda.size() != new_generators.size()) {
        std::cout << "Error: Lambda size different to number of generators" << std::endl;
        exit(0);
    } else {
        int lambda_index = 0;
        std::cout << lambda[lambda_index] << "*(" << new_generators[lambda_index] << ")";
        ++lambda_index;
        while (lambda_index < lambda.size()) {
            std::cout << " + " << lambda[lambda_index] << "*(" << new_generators[lambda_index] << ")";
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

    int denumerant = 0;

    /* calculate bounds for lambda solution */
    std::vector<int> new_generators (this->generators.begin(), this->generators.end());
    std::vector<int> bounds = this->ikp_bounds(t, new_generators);
    std::vector<int> lambda (this->generators.size(),0);

    /* calculate sylvester denumerant */
    while (!lambda.empty()) {

        /* check if this lambda is a solution */
        if (t == ikp_solution(lambda, new_generators)) {

            /* update denumerant */
            ++denumerant;
            /* print solution */
            if (with_solutions) std::cout << "Solution " << denumerant << ":" << std::endl;
            if (with_solutions) this->print_ikp_solution(lambda, new_generators);
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
