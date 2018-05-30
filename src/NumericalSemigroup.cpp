/*!
 * @file    NumericalSemigroup.cpp
 * @brief   NumericalSemigroup class
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#include "NumericalSemigroup.h"

NumericalSemigroup::NumericalSemigroup(std::set<int> generators){

    /* get system of generators */
    this->generators = generators;
    this->is_num_sem = false;

    /* check if gcd(a_1,...,a_n) = 1 */
    std::set<int>::iterator it = this->generators.begin();
    int d = *it;
    ++it;
    while (it != this->generators.end()){
        d = this->gcd(d,*it);
        ++it;
    }
    if (d == 1){
        std::cout << "Created numerical semigroup ";
        this->print_numerical_semigroup();
        std::cout << std::endl;
        this->is_num_sem = true;
    	std::cout << "Total number of generators: " << this->get_number_generators() << std::endl;
    } else {
        std::cout << "Error: ";
        this->print_numerical_semigroup();
        std::cout << " is not a numerical semigroup, as gcd(";
        this->print_generators();
        std::cout << ") = " << d << std::endl;
    }
}

bool NumericalSemigroup::add_generator(int generator){
    std::pair<std::set<int>::iterator,bool> ret;
    ret = this->generators.insert(generator);
    return ret.second;
}

int NumericalSemigroup::gcd (int a, int b)
{
    int c;
    while ( a != 0 ) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

int NumericalSemigroup::get_number_generators(){
    return this->generators.size();
}

int NumericalSemigroup::ikp_solution(std::vector<int> lambda){
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

bool NumericalSemigroup::is_numerical_semigroup(){
    return this->is_num_sem;
}

std::vector<int> NumericalSemigroup::next_lambda(std::vector<int> lambda, std::vector<int> bounds){
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

void NumericalSemigroup::print_generators(){
    std::set<int>::iterator it = this->generators.begin();
    std::cout << *it;
    ++it;
    while (it != this->generators.end()){
        std::cout << ", " << *it;
        ++it;
    }
}

void NumericalSemigroup::print_numerical_semigroup(){
    std::cout << "S = <";
    this->print_generators();
    std::cout << ">";
}

int NumericalSemigroup::sylvester_denumerant(int t){

    /* init */
    std::cout << std::endl << "  - Calculating Sylvester denumerant d(" << t << "; ";
    this->print_generators();
    std::cout << ") -" << std::endl << std::endl;
    int denumerant = 0;

    /* calculate bounds for lambda solution */
    std::vector<int> b;
    std::set<int>::iterator it = this->generators.begin();
    std::cout << "Bounds = (";
    int b_i = t / *it;
    b.push_back(b_i);
    std::cout << b_i;
    ++it;
    while (it != this->generators.end()){
        b_i = t / *it;
        b.push_back(b_i);
        std::cout << ", " << b_i;
        ++it;
    }
    std::cout << ")" << std::endl;

    /* calculate sylvester denumerant */
    std::vector<int> lambda (this->generators.size(),0);

    return denumerant;
}
