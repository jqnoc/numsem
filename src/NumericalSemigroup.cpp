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
    this->isNumSem = false;

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
        this->printNumericalSemigroup();
        std::cout << std::endl;
        this->isNumSem = true;
    	std::cout << "Total number of generators: " << this->getNumberOfGenerators() << std::endl;
    } else {
        std::cout << "Error: ";
        this->printNumericalSemigroup();
        std::cout << " is not a numerical semigroup, as gcd(";
        this->printGenerators();
        std::cout << ") = " << d << std::endl;
    }
}

bool NumericalSemigroup::addGenerator(int generator){
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

int NumericalSemigroup::getNumberOfGenerators(){
    return this->generators.size();
}

bool NumericalSemigroup::isNumericalSemigroup(){
    return this->isNumSem;
}

void NumericalSemigroup::printGenerators(){
    std::set<int>::iterator it = this->generators.begin();
    std::cout << *it;
    ++it;
    while (it != this->generators.end()){
        std::cout << ", " << *it;
        ++it;
    }
}

void NumericalSemigroup::printNumericalSemigroup(){
    std::cout << "S = <";
    this->printGenerators();
    std::cout << ">";
}
