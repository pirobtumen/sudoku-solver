/*
	Sudoku Solver
	==============================================================================

	Simple program for solving sudokus using backtracking.


	License: MIT. See LICENSE.txt.
	Author: Alberto Sola - Pirobtumen
	Date: 2017
*/

// -----------------------------------------------------------------------------

#ifndef __SUDOKU_HPP
#define __SUDOKU_HPP

// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// -----------------------------------------------------------------------------

/*
  Sudoku
  =======================================

  The sudoku ADT is a 1D integer vector.

  Each element has to be 1,2,3,4,5,6,7,8 or 9.

  If it's a 0, the sudoku is not solved.

*/

class Sudoku{
private:
  const int SUDOKU_SIZE = 9;
  const int SUDOKU_LENGTH = SUDOKU_SIZE*SUDOKU_SIZE;
  bool * constant;
  int * sudoku;

  void initialize();
  bool check_row(int x, int y) const;
  bool check_col(int x, int y) const;
  bool check_square(int x, int y) const;
  void backtrack(int & index) const;

public:
  Sudoku();
  Sudoku(const char * const file_name);
  ~Sudoku();

  bool check_element(int x, int y) const;

  bool read_from_file(const char * const file_name);
  void solve();
  bool valid() const;

  string to_str() const;
};

// -----------------------------------------------------------------------------

#endif
