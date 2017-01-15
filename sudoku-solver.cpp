/*
	Sudoku Solver
	==============================================================================

	Simple program for solving sudokus using backtracking.


	License: MIT. See LICENSE.txt.
	Author: Alberto Sola - Pirobtumen
	Date: 2017
*/

#include <iostream>
#include <cstdlib>

#include "sudoku.hpp"

using namespace std;

int main( int args, char ** argv ){

	Sudoku sudoku;

	// Check arguments
	// ----------------------------

	if(args != 2){
		std::cout << "Usage: ./sudoku-solver <file_name>" << std::endl;
		exit(-1);
	}

	// Read the input file
	// ----------------------------
	sudoku.read_from_file(argv[1]);

	// Look for a solution
	// ----------------------------
	cout << "Sudoku: " << endl;
	cout << sudoku.to_str() << endl;

	sudoku.solve();
	cout << "Solution: " << endl;
	cout << sudoku.to_str() << endl;

	cout << "Correct: " << sudoku.valid() << endl;

	// Save the solution
	// ----------------------------
	// sudoku.save();

}
