/*
	Sudoku Solver
	==============================================================================

	Simple program for solving sudokus using backtracking.


	License: MIT. See LICENSE.txt.
	Author: Alberto Sola - Pirobtumen
	Date: 2017
*/

// -----------------------------------------------------------------------------

#include "sudoku.hpp"

// -----------------------------------------------------------------------------

Sudoku::Sudoku(){
  /*
    Initialize an empty sudoku.
  */
  initialize();

  for(int i = 0; i < SUDOKU_LENGTH;i++)
    sudoku[i] = 0;
}

// -----------------------------------------------------------------------------

Sudoku::Sudoku(const char * const file_name){
  /*
    Load sudoku from a file.
  */
  initialize();
  read_from_file(file_name);
}

// -----------------------------------------------------------------------------

Sudoku::~Sudoku(){
  /*
    Free the sudoku memory.
  */
  delete[] sudoku;
  delete[] constant;
}

// -----------------------------------------------------------------------------

void Sudoku::initialize(){
  /*
    Reserve memory for the sudoku.
  */
  sudoku = new int[SUDOKU_LENGTH];
  constant = new bool[SUDOKU_LENGTH];
}

// -----------------------------------------------------------------------------

bool Sudoku::read_from_file(const char * const filename){
  /*
    Load a sudoku from a file.
  */
  bool status = true;
  char element;
  int index = 0;
  ifstream sudoku_file(filename);

  // Check if the file is open
  if(sudoku_file.is_open()){

    // Get the next character
    sudoku_file >> element;

    // While it hasn't reached the end of the file
    while(!sudoku_file.eof() && index < SUDOKU_LENGTH){

      // Empty character
      if(element == 'x'){
        sudoku[index] = 0;
        constant[index] = false;  // We can update this element
      }
      else{
        sudoku[index] = element - '0';
        constant[index] = true;
      }

      // Update vars
      sudoku_file >> element;
      index++;
    }

  }
  else
    status = false;

  sudoku_file.close();

  return status;
}

// -----------------------------------------------------------------------------

bool Sudoku::check_element(int x, int y) const{
  /*
    Check if an element is not repeated.

    Return: true  - not repeated.
            false - repeated.
  */
  return check_row(x,y) && check_col(x,y) && check_square(x,y);
}

// -----------------------------------------------------------------------------

bool Sudoku::check_row(int x, int y) const{
  /*
    Check if an element is not repeated in a row.

    Return: true  - not repeated.
            false - repeated.
  */
  unsigned int row_index = y*SUDOKU_SIZE;
  unsigned int element_index = row_index + x;
  unsigned int row_end = row_index + SUDOKU_SIZE;
  int element = sudoku[element_index];
  bool repeated = false;

  sudoku[element_index] = 0;

  for( ; row_index < row_end && !repeated; row_index++)
    if(sudoku[row_index] == element)
      repeated = true;

  sudoku[element_index] = element;

  return !repeated;
}

// -----------------------------------------------------------------------------

bool Sudoku::check_col(int x, int y) const{
  /*
    Check if an element is not repeated ini a column.

    Return: true  - not repeated.
            false - repeated.
  */
  bool repeated = false;
  int element_index = y*SUDOKU_SIZE + x;
  int element = sudoku[element_index];
  int col_index = x;
  int col_end = x + SUDOKU_SIZE*(SUDOKU_SIZE - 1);

  sudoku[element_index] = 0;

  for( ; col_index < col_end && !repeated; col_index += SUDOKU_SIZE)
    if(sudoku[col_index] == element)
      repeated = true;

  sudoku[element_index] = element;

  return !repeated;
}

// -----------------------------------------------------------------------------

bool Sudoku::check_square(int x, int y) const{
  /*
    Check if an element is not repeated in a square.

    Return: true  - not repeated.
            false - repeated.
  */
  const int SQUARE_SIZE = 3;
  int square_x = x / 3;
  int square_y = y / 3;
  int element_index = y*SUDOKU_SIZE + x;
  bool repeated = false;

  int element = sudoku[element_index];
  int start_x = square_x*SQUARE_SIZE;
  int start_y = square_y*SQUARE_SIZE;

  sudoku[element_index] = 0;

  for(int j = start_y; j < (start_y + SQUARE_SIZE) && !repeated; j++)
    for(int i = start_x; i < (start_x + SQUARE_SIZE) && !repeated; i++)
      if(sudoku[j*SUDOKU_SIZE + i] == element)
        repeated = true;

  sudoku[element_index] = element;

  return !repeated;
}

// -----------------------------------------------------------------------------

void Sudoku::backtrack(int & index) const{
  /*
    Backtrack.
  */

  // Reset the current element
  sudoku[index] = 0;

  // Go back
  index--;

  // Check if the element is constant
  while(constant[index])
    index--;
}

// -----------------------------------------------------------------------------

void Sudoku::solve(){
  /*
    Solve the sudoku using backtracking.
  */
  int index = 0;
  int element;

  // While we haven't reached the end
  while(index < SUDOKU_LENGTH && index >= 0){

    // Check if we can update the current element
    if(!constant[index]){
      element = sudoku[index];

      // If it's the last posibility, backtrack
      if(element == 9)
        backtrack(index);
      else{
        // Update the current element
        sudoku[index] += 1;

        // If it's valid, go to the next one
        if(check_element(index % SUDOKU_SIZE, index / SUDOKU_SIZE ))
          index++;

      }

    }
    // Go to the next element
    else
      index++;

  }

}

// -----------------------------------------------------------------------------

bool Sudoku::valid() const{
  /*
    Check if the sudoku is valid.

    Return: true  - valid.
            false - not valid.
  */
  bool valid = true;

  for(int x = 0; x < SUDOKU_SIZE && valid; x++)
    for(int y = 0; y < SUDOKU_SIZE && valid; y++)
      valid = check_element(x,y);

  return valid;
}

// -----------------------------------------------------------------------------

string Sudoku::to_str() const{
  /*
    Transform the sudoku into a string.
  */
  string sudoku_str;

  for(int i = 0; i < SUDOKU_SIZE; i++){
    for(int j = 0; j < SUDOKU_SIZE; j++){
      sudoku_str += sudoku[i*SUDOKU_SIZE+j] + '0';

      //if( (j+1) % 3 == 0 && j < 8)
      //  sudoku_str += '|';
    }

    //if( (i+1) % 3 == 0 && i < 8)
    //  sudoku_str += "\n-----------";

    sudoku_str += '\n';
  }

  return sudoku_str;
}

// -----------------------------------------------------------------------------
