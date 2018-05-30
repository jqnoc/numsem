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

	//! @brief 	Calculates the greatest common divisor of two integers
	//! @param 	a First integers
	//! @param 	b Second integers
	//! @return gcd(a,b)
	int gcd(int a, int b);

	//! @return The number of generators of the current numerical semigroup
    int get_number_generators();

	//! @param 	lambda A vector of integers with the same size as the number of generators of this numerical semigroup
	//! @return The product $\sum_{i=1}^{n} \lambda_i a_i$
	int ikp_solution(std::vector<int> lambda);

	//! @return A bool that indicates if the present system of generators generates a numerical semigroup
	bool is_numerical_semigroup();

	//! @return Next lambda iteration (used in the function sylvester_denumerant)
	std::vector<int> next_lambda(std::vector<int> lambda, std::vector<int> bounds);

	//! @brief Prints the system of generators
	void print_generators();

	//! @brief Prints the product $\sum_{i=1}^{n} \lambda_i a_i$ (not the result, which is given by ikp_solution)
	void print_ikp_solution(std::vector<int> lambda);

	//! @brief Prints the numerical semigroup in the format $S = <a_1,...,a_n>$
	void print_numerical_semigroup();

	//! @return The Sylvester denumerant of the integer $t$ with respect to the system of generators of the present numerical semigroup
	int sylvester_denumerant(int t);

	//! @return The upper bounds for the ikp solutions of $t$ with respect to $a_1,...,a_n$
	std::vector<int> sylvester_denumerant_bounds(int t);

};

#endif
