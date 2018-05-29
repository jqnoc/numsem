#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <math.h>

#include "NumericalSemigroup.h"

// int gcd (int a, int b);
// int apery_ilp (std::vector<int> sg_gens, int s, int i);
// int apery_zolp (std::vector<int> sg_gens, int s, int i);
// int apery_qubo (std::vector<int> sg_gens, int s, int i);

int main ( int argc, char *argv[] )
{

	if (argc > 1) {
		std::cout << "Error: Too many arguments." << std::endl;
	}

	std::cout << "NumericalSemigroup::NumericalSemigroup()" << std::endl;
	NumericalSemigroup* ns = new NumericalSemigroup();

	std::cout << "### Add generators to the semigroup (type 0 for no more generators)" << std::endl;
	int newGenerator = 1;
	while (newGenerator != 0){
		std::cout << "Generator " << ns->getNumberOfGenerators() + 1 << ":";
		std::cin >> newGenerator;
		std::cout << std::endl;
		ns->addGenerator(newGenerator);
	}

	std::cout << "Total number of generators: " << ns->getNumberOfGenerators() << std::endl;

	return 1;
}

	// /* parameters */
	// int n;
	// std::vector<int> gens;
	// int i = 0;
	// bool end = true;
	//
	// /* get number of generators */
	// std::cout << "Introduce the number of generators of the semigroup:" << std::endl;
	// std::cin >> n;
	// if (n == 0)
	// 	exit (0);
	//
	// /* get generators */
	// std::cout << "Introduce the generators of the semigroup:" << std::endl;
	// while (i < n){
	// 	int j;
	// 	std::cin >> j;
	// 	gens.push_back(j);
	// 	++i;
	// }
	//
	// /* sort semigroup generators */
	// struct myclass {
	// 	bool operator() (int i,int j) { return (i<j);}
	// } myobject;
	// std::sort (gens.begin(), gens.end(), myobject);
	//
	// /* divide generators by gcd */
	// int d = gens[0];
	// i = 1;
	// while (i < gens.size() && d != 1){
	// 	d = gcd(d,gens[i]);
	// 	++i;
	// }
	// if (d > 1){
	// 	for (i = 0; i < gens.size(); ++i){
	// 		gens[i] = gens[i] / d;
	// 	}
	// }
	// if (gens[0] == 1){
	// 	std::cout << "The generated semigroup is trivial." << std::endl;
	// }
	//
	// /* get multiplicity of the semigroup */
	//
	// int s = gens[0];
	//
	// /* apery calculation */
	//
	// std::vector<int> apery_set;
	// apery_set.push_back(0);
	//
	// for (int i = 1; i < s; ++i){
	// 	apery_ilp(gens,s,i);
	// 	apery_set.push_back(apery_zolp(gens,s,i));
	// 	apery_qubo(gens,s,i);
	// }
	//
	// /* sort apery */
	//
	// std::sort (apery_set.begin(), apery_set.end(), myobject);
	//
	// /* print semigroup generators */
	// std::cout << "S = <" << gens[0];
	// for (i = 1; i < gens.size(); ++i){
	// 	std::cout << ", " << gens[i];
	// }
	// std::cout << ">" << std::endl;
	//
	// /* print multiplicity of the semigroup */
	//
	// std::cout << "s = " << s << std::endl;
	//
	// /* print apery */
	//
	// std::cout << "Ap(S,s) = {" << apery_set[0];
	// for (int i = 1; i < s; ++i){
	// 	std:: cout << ", " << apery_set[i];
	// }
	// std::cout << "}" << std::endl;
	//
	// /* print frobenius */
	//
	// std::cout << "f(S) = " << apery_set[apery_set.size() - 1] - s << std::endl;



// int gcd (int a, int b)
// {
//   int c;
//   while ( a != 0 ) {
//      c = a; a = b%a;  b = c;
//   }
//   return b;
// }
//
// int apery_ilp (std::vector<int> sg_gens, int s, int i)
// {
// 	std::ofstream solver_file;
// 	solver_file.open("apery_tmp.run");
//
// 	int result = -1;
//
// 	if (solver_file.is_open()) {
//
// 		/* print header */
//
// 		solver_file << "reset;" << std::endl;
// 		solver_file << "set VARS := 0.." << sg_gens.size() - 1 << ";" << std::endl;
// 		solver_file << "var X {i in VARS} integer, >= 0;" << std::endl;
// 		solver_file << "var K integer, >= 0;" << std::endl;
//
// 		/* print objective function */
//
// 		solver_file << "minimize Total_Cost:" << std::endl;
// 		solver_file << "\t" << sg_gens[0] << "*X[0]";
// 		for (int j = 1; j < sg_gens.size(); ++j){
// 			solver_file << " + " << sg_gens[j] << "*X[" << j << "]";
// 		}
// 		solver_file << ";" << std::endl;
//
// 		/* print constraint */
//
// 		solver_file << "subject to Constraint:" << std::endl;
// 		solver_file << "\t" << sg_gens[0] << "*X[0]";
// 		for (int j = 1; j < sg_gens.size(); ++j){
// 			solver_file << " + " << sg_gens[j] << "*X[" << j << "]";
// 		}
// 		solver_file << " = " << i << " + " << s << "*K;" << std::endl;
//
// 		/* print solver options */
//
// 		solver_file << "option solver baron;" << std::endl;
// 		solver_file << "solve;" << std::endl;
// 		solver_file << "printf \"%s\", Total_Cost > result.txt;" << std::endl;
//
// 		/* close file */
//
//     	solver_file.close();
//
// 		/* launch ampl */
//
// 		system("ampl ./apery_tmp.run");
//
// 		/* get solution */
//
// 		std::ifstream results_file;
// 		results_file.open("result.txt");
// 		results_file >> result;
//
//
// 	} else {
// 		std::cout << "Unable to open file" << std::endl;
// 	}
//
// 	return result;
// }
//
// int apery_zolp (std::vector<int> sg_gens, int s, int i)
// {
//
// 	/* parameters */
//
// 	double frob_bound = log2 ((sg_gens[0] - 1)*(sg_gens[sg_gens.size() - 1] - 1) - 1);
// 	int n_bits = (int)frob_bound;
//
// 	std::ofstream solver_file;
// 	solver_file.open("apery_tmp.run");
//
// 	int result = -1;
//
// 	if (solver_file.is_open()) {
//
// 		/* print header */
//
// 		solver_file << "reset;" << std::endl;
// 		solver_file << "set VARS := 0.." << sg_gens.size() - 1 << ";" << std::endl;
// 		solver_file << "set VARS2 := 0.." << n_bits - 1 << ";" << std::endl;
// 		solver_file << "var X {i in VARS, j in VARS2} binary;" << std::endl;
// 		solver_file << "var K {k in VARS2} binary;" << std::endl;
//
// 		/* print objective function */
//
// 		solver_file << "minimize Total_Cost:" << std::endl;
// 		solver_file << "\t" << sg_gens[0] << "*(X[0,0]";
// 		for (int k = 1; k < n_bits; ++k){
// 			double power = pow(2,k);
// 			solver_file << " + " << power << "*X[0," << k << "]";
// 		}
// 		solver_file << ")";
//
// 		for (int j = 1; j < sg_gens.size(); ++j){
// 			solver_file << " + " << sg_gens[j] << "*(X[" << j << ",0]";
// 			for (int k = 1; k < n_bits; ++k){
// 				double power = pow(2,k);
// 				solver_file << " + " << power << "*X[" << j << "," << k << "]";
// 			}
// 			solver_file << ")";
// 		}
// 		solver_file << ";" << std::endl;
//
// 		/* print constraint */
//
// 		solver_file << "subject to Constraint:" << std::endl;
// 		solver_file << "\t" << sg_gens[0] << "*(X[0,0]";
// 		for (int k = 1; k < n_bits; ++k){
// 			double power = pow(2,k);
// 			solver_file << " + " << power << "*X[0," << k << "]";
// 		}
// 		solver_file << ")";
//
// 		for (int j = 1; j < sg_gens.size(); ++j){
// 			solver_file << " + " << sg_gens[j] << "*(X[" << j << ",0]";
// 			for (int k = 1; k < n_bits; ++k){
// 				double power = pow(2,k);
// 				solver_file << " + " << power << "*X[" << j << "," << k << "]";
// 			}
// 			solver_file << ")";
// 		}
//
// 		solver_file << " = " << i << " + " << s << "*(K[0]";
// 		for (int k = 1; k < n_bits; ++k){
// 			double power = pow(2,k);
// 			solver_file << " + " << power << "*K[" << k << "]";
// 		}
// 		solver_file << ");" << std::endl;
//
// 		/* print solver options */
//
// 		solver_file << "option solver baron;" << std::endl;
// 		solver_file << "solve;" << std::endl;
// 		solver_file << "display {i in VARS, j in VARS2} X[i,j];" << std::endl;
// 		solver_file << "display {k in VARS2} K[k];" << std::endl;
// 		solver_file << "printf \"%s\", Total_Cost > result.txt;" << std::endl;
//
// 		/* close file */
//
//     	solver_file.close();
//
// 		/* launch ampl */
//
// 		system("ampl ./apery_tmp.run");
//
// 		/* get solution */
//
// 		std::ifstream results_file;
// 		results_file.open("result.txt");
// 		results_file >> result;
//
//
// 	} else {
// 		std::cout << "Unable to open file" << std::endl;
// 	}
//
// 	return result;
// }
//
// int apery_qubo (std::vector<int> sg_gens, int s, int i)
// {
//
// 	/* parameters */
//
// 	double frob_bound = log2 ((sg_gens[0] - 1)*(sg_gens[sg_gens.size() - 1] - 1) - 1);
// 	int n_bits = (int)frob_bound;
//
// 	std::ofstream solver_file;
// 	solver_file.open("apery_tmp.run");
//
// 	int result = -1;
//
// 	if (solver_file.is_open()) {
//
// 		/* print header */
//
// 		solver_file << "reset;" << std::endl;
// 		solver_file << "set VARS := 0.." << sg_gens.size() - 1 << ";" << std::endl;
// 		solver_file << "set VARS2 := 0.." << n_bits - 1 << ";" << std::endl;
// 		solver_file << "var X {i in VARS, j in VARS2} binary;" << std::endl;
// 		solver_file << "var K {k in VARS2} binary;" << std::endl;
//
// 		/* print objective function */
//
// 		solver_file << "minimize Total_Cost:" << std::endl;
// 		solver_file << "\t" << sg_gens[0] << "*(X[0,0]";
// 		for (int k = 1; k < n_bits; ++k){
// 			double power = pow(2,k);
// 			solver_file << " + " << power << "*X[0," << k << "]";
// 		}
// 		solver_file << ")";
//
// 		for (int j = 1; j < sg_gens.size(); ++j){
// 			solver_file << " + " << sg_gens[j] << "*(X[" << j << ",0]";
// 			for (int k = 1; k < n_bits; ++k){
// 				double power = pow(2,k);
// 				solver_file << " + " << power << "*X[" << j << "," << k << "]";
// 			}
// 			solver_file << ")";
// 		}
// 		solver_file << ";" << std::endl;
//
// 		/* print constraint */
//
// 		solver_file << "subject to Constraint:" << std::endl;
// 		solver_file << "\t" << sg_gens[0] << "*(X[0,0]";
// 		for (int k = 1; k < n_bits; ++k){
// 			double power = pow(2,k);
// 			solver_file << " + " << power << "*X[0," << k << "]";
// 		}
// 		solver_file << ")";
//
// 		for (int j = 1; j < sg_gens.size(); ++j){
// 			solver_file << " + " << sg_gens[j] << "*(X[" << j << ",0]";
// 			for (int k = 1; k < n_bits; ++k){
// 				double power = pow(2,k);
// 				solver_file << " + " << power << "*X[" << j << "," << k << "]";
// 			}
// 			solver_file << ")";
// 		}
//
// 		solver_file << " = " << i << " + " << s << "*(K[0]";
// 		for (int k = 1; k < n_bits; ++k){
// 			double power = pow(2,k);
// 			solver_file << " + " << power << "*K[" << k << "]";
// 		}
// 		solver_file << ");" << std::endl;
//
// 		/* print solver options */
//
// 		solver_file << "option solver baron;" << std::endl;
// 		solver_file << "solve;" << std::endl;
// 		solver_file << "display {i in VARS, j in VARS2} X[i,j];" << std::endl;
// 		solver_file << "display {k in VARS2} K[k];" << std::endl;
// 		solver_file << "printf \"%s\", Total_Cost > result.txt;" << std::endl;
//
// 		/* close file */
//
//     	solver_file.close();
//
// 		/* launch ampl */
//
// 		system("ampl ./apery_tmp.run");
//
// 		/* get solution */
//
// 		std::ifstream results_file;
// 		results_file.open("result.txt");
// 		results_file >> result;
//
//
// 	} else {
// 		std::cout << "Unable to open file" << std::endl;
// 	}
//
// 	return result;
// }
