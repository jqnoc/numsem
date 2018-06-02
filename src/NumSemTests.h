/*!
 * @file    NumSemTests.h
 * @brief   NumSemTests class (definitions)
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-06-01
 *
 */

#pragma once
#ifndef NUM_SEM_TESTS_H
#define NUM_SEM_TESTS_H

#include <fstream>
#include <sstream>

#include "NumericalSemigroup.h"

class NumSemTests
{
private:
    NumericalSemigroup* ns;
    int number_of_options;
public:

    //! @brief Constructor
    NumSemTests();

	//! @brief Empty destructor
	~NumSemTests();

    int calculate_sylvester_denumerant();

    NumericalSemigroup* initialize_numerical_semigroup_input();

    void numsem_init();

    void numsem_gaps();

    void numsem_membership();

    void numsem_sylvester_denumerant();

    void print_numsem_options();

    void sylvester_polynomial_graph();

};

#endif
