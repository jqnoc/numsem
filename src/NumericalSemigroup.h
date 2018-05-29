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

	std::set<int> generators;	//!< System of generators of the semigroup (default: NULL)

public:

    //! @brief constructor
    NumericalSemigroup(std::set<int> generators);

	//! @brief  Empty constructor
    NumericalSemigroup();
	//! @brief  Empty destructor
	~NumericalSemigroup();

	//! @brief  Adds a generator to the system of generators of the current numerical semigroup
	//! @param	generator  New generator
    //! @return True if the element was already inside the semigroup
	bool addGenerator(int generator);

    int getNumberOfGenerators();

	void printSemigroup();

};

#endif
