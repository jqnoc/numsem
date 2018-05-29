/*!
 * @file    NumericalSemigroup.cpp
 * @brief   NumericalSemigroup class
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#include "NumericalSemigroup.h"

NumericalSemigroup::NumericalSemigroup(std::set<int> generators) {
    this->generators = generators;
}

NumericalSemigroup::NumericalSemigroup() {

}

bool NumericalSemigroup::addGenerator(int generator){
    std::pair<std::set<int>::iterator,bool> ret;
    ret = this->generators.insert(generator);
    return ret.second;
}

int NumericalSemigroup::getNumberOfGenerators(){
    return this->generators.size();
}

void NumericalSemigroup::printSemigroup(){
    std::cout << "S = <";
    std::cout << ">" << std::endl;
}
