/*

The MIT License (MIT)
Copyright (c) 2016 Alberto Sola Comino

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
/*
	Sudoku Solver
	--------------------------
	
	This program solves Sudokus using backtracking.

	- Compiling: make
	- Executing: ./sudoku-solver <sudoku_input_file>

	Sudoku (Game)
	--------------------------
	
	Sudoku board is a 9x9 matrix where each square is a number from 1 to 9.
	The objetive is to fill it with the numbers but it can't be repeated
	numbers in any row/column/submatrix.
		
	
	Sudoku (Object)
	--------------------------
	
	It represents a Sudoku puzzle.
	
	Representation
	--------------
	The internal representation is a one dimension vector (row major order).
	
	Invariant
	---------
	Each vector's element has to be a number from 0 to 9.
	The 0 are unknow valued used for solving it.
	
	* valid() doesn't consider 0 when checking.
	
	Public operations
	-----------------
	read_file, valid, str, solve.
	
	Input file
	----------
	The input file has to be a 9 rows and 9 numbers per column.
	The character 'x' represents unknown values.
	See: sudoku_simple.txt, sudoku_hard.txt .
	
	
	Alberto Sola Comino - 2016
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Sudoku{

private:
	typedef vector<int> sudoku_t;
	typedef sudoku_t::iterator sudoku_iterator;
	static const int SIZE;

	sudoku_t initial_values;
	sudoku_t sudoku;
	
	void get_submatrix( int start, int length, int jump, vector<int> & output ){
		/*
			Return a vector from the Sudoku.
			
			- Start: square index. From 0 to 80. ( Row major order )
			- Length: consecutive squares.
			- Jump: space between iterations.
			
			Examples: (start, length, jump)
			
			- Row:    ( [0,9,18...], 9, 0 )
			- Column: ( [0-8], 1, 9 )
			- Submatrix: ( [0,3,6,27,30,33,54,57,60], 3, 9 )
		*/
		int index = start;
		int count = 1;
		int num;
		
		for( int i = 0; i < SIZE; i++ ){
		
			num = sudoku[index];
			
			if( num > 0 )
				output.push_back( num );
			
			if( count < length ){
				++count;
				++index;
			}

			else{
				count = 1;
				index += jump - length + 1; 
			}
			
		}
		
	}
	
	bool check_repeated( const vector<int> & sudoku_numbers ){
		/*
			Check for repeated elements in a vector.
		*/
		set<int> numbers;
		pair< set<int>::iterator, bool > insert;
		insert.second = true;
		
		vector<int>::const_iterator iter = sudoku_numbers.begin();
		vector<int>::const_iterator end = sudoku_numbers.end();
		
		while( iter != end && insert.second ){

			insert = numbers.insert( (*iter) );
		
			++iter;
		}
		
		return insert.second;		
	}
	
public:
	
	void read_file( const char * const file_name ){
		/*
			Read a sudoku from a file.
		*/
		const char EMPTY_CHAR = 'x';
		const char BASE_CHAR = '0';
		const int READ_BYTES = SIZE*SIZE + 9;
		char data[ READ_BYTES ];
		int digit;

		ifstream file( file_name );
		
		// Read the data and close the file
		file.read( data, READ_BYTES );
		file.close();
		
		// Parse the data
		for( int i = 0; i < READ_BYTES; i++ ){
		
			// Put empty digit
			if( data[i] == EMPTY_CHAR )
				sudoku.push_back( 0 );
			
			// Put digit and save it index
			else if( data[i] >= '0' && data[i] <= '9' ){
				digit = data[i] - BASE_CHAR;
				sudoku.push_back( digit );
				initial_values.push_back( sudoku.size() - 1 );
			}
		
		}
		
	}
	
	string str(){
		/*
			Return the Sudoku as a String.
		*/
		const char BASE_CHAR = '0';
		int count = 1;
		string data = "";
		
		sudoku_iterator iter = sudoku.begin();
		sudoku_iterator end = sudoku.end();
		
		while( iter != end ){

			data += (*iter) + BASE_CHAR;

			// Update
			if( count == 9 ){
				count = 1;
				data += "\n";	
			}
			else
				++count;
		
			++iter;
		}
		
		return data;		
	}

	bool valid(){
		/*
			Checks if the sudoku is valid (no numbers repeated in each row/col/sumatrix).
			The 0s are not considered.
		*/
		int region_corner[9] = {0,3,6,27,30,33,54,57,60};
		vector<int> numbers;
		
		bool valid = true;
		
		// Check ROWS
		for( int i = 0; i < 9 && valid; i++ ){
			
			get_submatrix( i*SIZE, 9, 1, numbers );
			valid = check_repeated( numbers );
			numbers.clear();
			
		}
		
		// Check COLS
		for( int i = 0; i < 9 && valid; i++ ){
			
			get_submatrix( i, 1, 9, numbers );
			valid = check_repeated( numbers );
			numbers.clear();
			
		}
		
		// Check SUBMATRIX
		for( int i = 0; i < 9 && valid; i++ ){
			
			get_submatrix( region_corner[i], 3, 9, numbers );
			valid = check_repeated( numbers );			
			numbers.clear();
			
		}
		
		return valid;
	}


	void solve(){
		/*
			Find a valid solution using backtracking.
		*/
		
		int pos = 0;
		int max_pos = sudoku.size();
		
		int tmp;
		
		vector<int>::const_iterator start = initial_values.begin();
		vector<int>::const_iterator end = initial_values.end();
		
		bool search;
		
		if( valid() ){			
			while( pos < max_pos ){

				if( !binary_search( start, end, pos ) ){
				
					if( sudoku[pos] < 9 ) 			
						++sudoku[pos];
				
					while( !valid() && sudoku[pos] < 9 )
						++sudoku[pos];
				
					// Backtraking
					if( !valid() ){
					
						sudoku[pos] = 0;	
						--pos;					
						search = binary_search( start, end, pos );
					
						while( (search || (sudoku[pos] == 9) && pos > 0 ){
						
							if( sudoku[pos] == 9 && !search )
								sudoku[pos] = 0;
							
							--pos;
						
							search = binary_search( start, end, pos );
						}
					
					}
					else
						++pos;

				}
				else
					++pos;
		
			}
		
		}
	}
};

const int Sudoku::SIZE = 9;   // Sudoku Row/Column length


int main( int args, char ** argv ){

	Sudoku sudoku;
	
	// Read the input file
	// ----------------------------
	sudoku.read_file( argv[1] );

	// Look for a solution
	// ----------------------------
	cout << "Sudoku: " << endl;
	cout << sudoku.str() << endl;
	
	sudoku.solve();
	cout << "Solution: " << endl;
	cout << sudoku.str() << endl;
	
	cout << "Correct: " << sudoku.valid() << endl;

	// Save the solution
	// ----------------------------
	// sudoku.save();

}
