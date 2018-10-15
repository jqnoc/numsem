/*!
 * @file    main.cpp
 * @brief   main file
 * @author  Joaquin Ossorio-Castillo (joaquin.ossorio@usc.es)
 * @date    2018-05-28
 *
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <math.h>

#include "InputParser.h"
#include "NumSemTests.h"
#include "NumericalSemigroup.h"

// int gcd (int a, int b);
// int apery_ilp (std::vector<int> sg_gens, int s, int i);
// int apery_zolp (std::vector<int> sg_gens, int s, int i);
// int apery_qubo (std::vector<int> sg_gens, int s, int i);

int main ( int argc, char *argv[] )
{

	std::cout << std::endl << "===========================================================================================" << std::endl;
	std::cout << " NumSem v0.3.0 (2018.10.15)" << std::endl;
	std::cout << " Copyright (C) Joaquín Ossorio-Castillo. All rights reserved." << std::endl;
	std::cout << " This software is free for non-commercial purposes." << std::endl;
	std::cout << " Full license information can be found in the LICENSE.txt file." << std::endl;
	std::cout << " https://github.com/jqnoc/numsem/" << std::endl;
	std::cout << "===========================================================================================" << std::endl;

	system("rm -rf .tmp; mkdir .tmp");

	/* define options */
	std::vector<std::string> list_of_knowns;

	list_of_knowns.push_back("--help");   // help
    bool opt_help = false;

	std::string opt_file;

	list_of_knowns.push_back("-f");  // Frobenius problem
	bool opt_frobenius;

	list_of_knowns.push_back("-g");  // set of gaps
	bool opt_gaps;

	list_of_knowns.push_back("-d");  // Sylvester denumerant
	list_of_knowns.push_back("-ds");  // Sylvester denumerant (with solutions)
	int opt_sylvester_denumerant;

	list_of_knowns.push_back("-dg");  // Sylvester denumerant graph
	int opt_sylvester_denumerant_graph;

	list_of_knowns.push_back("-m");  // numerical semigroup membership
	int opt_nsmp;

	list_of_knowns.push_back("-ampl");  // use AMPL
	bool opt_ampl = false;

	/* parse arguments */
	try {
		InputParser input(argc, argv);

		/* check for empty options */
		if (input.cmdNoProblem() and input.cmdNoOptions()) {
            throw "ERROR: no arguments";
        }

		/* check for errors in options */
		if (input.isErrorCmd()) {
            throw "ERROR: wrong command line syntax";
        }

		/* check for help option */
		if (input.cmdOptionExists("--help")) {
            if (not input.getCmdArg("--help").empty()){
                throw "ERROR: --help option cannot take arguments";
            }
            opt_help = true;
            if (input.getOptionsSize() > 1) {
                std::cout << "Option --help detected: other options are ignored" << std::endl;
            }
        throw "numsem help";
        }

		/* check for file */
		if (input.cmdNoProblem()) {
			throw "ERROR: wrong command line syntax (file must be first argument)";
		}

		/* initialize numerical semigroup from file */
		opt_file = input.getProblem();
		std::fstream ns_file(opt_file, std::ios_base::in);
		int new_generator;
		std::set<int> generators;
		while (ns_file >> new_generator) {
			if (new_generator > 1) {
				generators.insert(new_generator);
			}
		}
		NumericalSemigroup* ns = new NumericalSemigroup(generators);
		std::cout << "Numerical semigroup: ";
		ns->print_numerical_semigroup();
		std::cout << std::endl;
		std::cout << "Total number of generators: " << ns->get_number_generators() << std::endl;

		/* check for unknown options */
		std::string unknown_options = input.UnknownOptionFound(list_of_knowns);
        if (not unknown_options.empty()) {
			throw "ERROR: unknown options";
        }

		/* AMPL */
		if (input.cmdOptionExists("-ampl")) {
            if (not input.getCmdArg("-ampl").empty()) {
                throw "ERROR: option -ampl cannot take arguments";
            }
			opt_ampl = true;
        }

		/* Frobenius problem */
		if (input.cmdOptionExists("-f")) {
            if (not input.getCmdArg("-f").empty()) {
                throw "ERROR: option -f cannot take arguments";
            }
			opt_frobenius = true;
			std::cout << "f(S) = ";
			if (opt_ampl) {
				std::cout << ns->frobenius_number_ampl();
			} else {
				std::cout << ns->frobenius_number();
			}
			std::cout << std::endl;
        }

		/* set of gaps */
		if (input.cmdOptionExists("-g")) {
            if (not input.getCmdArg("-g").empty()){
                throw "ERROR: option -g cannot take arguments";
            }
			opt_gaps = true;
			std::vector<int> set_gaps = ns->gaps();
		    if (set_gaps.size() == 0) {
		        std::cout << "G(S) = Ø" << std::endl;
		    } else {
		        std::cout << "G(S) = {" << set_gaps[0];
		        for (int i = 1; i < set_gaps.size(); ++i) {
		            std::cout << ", " << set_gaps[i];
		        }
		        std::cout << "}" << std::endl;
		    }
        }

		/* Sylvester denumerant */
		if (input.cmdOptionExists("-d")) {
            std::string str_sylvester_denumerant = input.getCmdArg("-d");
            if (str_sylvester_denumerant.empty()){
                throw "ERROR: option -d needs an argument";
            }
			opt_sylvester_denumerant = stoi(str_sylvester_denumerant);
			if (opt_sylvester_denumerant < 1) {
				throw "ERROR: option -d needs an integer greater than 0";
			}
			std::cout << "d(" << opt_sylvester_denumerant << ") = " << ns->sylvester_denumerant(opt_sylvester_denumerant,false) << std::endl;
        }

		/* Sylvester denumerant (with solutions) */
		if (input.cmdOptionExists("-ds")) {
            std::string str_sylvester_denumerant = input.getCmdArg("-ds");
            if (str_sylvester_denumerant.empty()){
                throw "ERROR: option -ds needs an argument";
            }
			opt_sylvester_denumerant = stoi(str_sylvester_denumerant);
			if (opt_sylvester_denumerant < 1) {
				throw "ERROR: option -d needs an integer greater than 0";
			}
			std::cout << "d(" << opt_sylvester_denumerant << ") = " << ns->sylvester_denumerant(opt_sylvester_denumerant,true) << std::endl;
        }
	} catch (char const *e) {
		if (not std::string(e).empty()) {
			std::cout << std::endl;
            std::cout << e << std::endl;
            std::cout << " Use:" << std::endl;
            std::cout << "   numsem *file* [options]" << std::endl << std::endl;
            std::cout << " Available options:" << std::endl;
            std::cout << "   --help: print the help" << std::endl;
            std::cout << "   *file*: the file with the generators of the numerical semigroup S" << std::endl;
            std::cout << "   -f: calculate Frobenius number of S" << std::endl;
            std::cout << "   -g: calculate set of gaps of S" << std::endl;
            std::cout << "   -d *t*: calculate Sylvester denumerant for t and S" << std::endl;
            std::cout << "   -ds *t*: calculate Sylvester denumerant for t and S and print all solutions" << std::endl;
            std::cout << "   -dg *b*: calculate Sylvester function from 0 to b" << std::endl;
            std::cout << "   -m *t*: calculate if t is in S" << std::endl;
            std::cout << std::endl;
			exit(0);
		}
	}

	/* read generators from file */

	//NumSemTests* nst = new NumSemTests();

	return 1;
}
