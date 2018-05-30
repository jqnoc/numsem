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
#include <vector>

class NumericalSemigroup
{
private:

	std::set<int> generators;	//!< System of generators of the numerical semigroup (default: NULL)
	bool is_num_sem;			//!< True if 'generators' is a valid system of generators (i.e., if gcd(a_1,...,a_n) = 1)

public:

    //! @brief Constructor
    NumericalSemigroup(std::set<int> generators);

	//! @brief Empty destructor
	~NumericalSemigroup();

	//! @brief  Adds a generator to the system of generators of the current numerical semigroup
	//! @param	generator  New generator
    //! @return True if the element was already inside the semigroup
	bool add_generator(int generator);

	int gcd(int a, int b);

    int get_number_generators();

	int ikp_solution(std::vector<int> lambda);

	bool is_numerical_semigroup();

	std::vector<int> next_lambda(std::vector<int> lambda, std::vector<int> bounds);

	void print_generators();

	void print_numerical_semigroup();

	int sylvester_denumerant(int t);

};

#endif
