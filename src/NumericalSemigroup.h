/*!
 * @file    NumericalSemigroup.h
 * @brief   NumericalSemigroup class (definitions)
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#pragma once
#ifndef NUMERICAL_SEMIGROUP_H
#define NUMERICAL_SEMIGROUP_H

#include <iostream>
#include <set>

class NumericalSemigroup
{
private:

	std::set<int> generators;	//!< System of generators of the numerical semigroup (default: NULL)
	bool isNumSem;	//!< True if 'generators' is a valid system of generators (i.e., if gcd(a_1,...,a_n) = 1)

public:

    //! @brief Constructor
    NumericalSemigroup(std::set<int> generators);

	//! @brief Empty destructor
	~NumericalSemigroup();

	//! @brief  Adds a generator to the system of generators of the current numerical semigroup
	//! @param	generator  New generator
    //! @return True if the element was already inside the semigroup
	bool addGenerator(int generator);

	int gcd(int a, int b);

    int getNumberOfGenerators();

	bool isNumericalSemigroup();

	void printGenerators();

	void printNumericalSemigroup();

};

#endif
