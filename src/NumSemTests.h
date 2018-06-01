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

#include "NumericalSemigroup.h"

class NumSemTests
{
private:

	NumericalSemigroup* ns;

public:

    //! @brief Constructor
    NumSemTests();

	//! @brief Empty destructor
	~NumSemTests();

    void Test1();

};

#endif