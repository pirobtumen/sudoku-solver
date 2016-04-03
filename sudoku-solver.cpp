/*

The MIT License (MIT)
Copyright (c) 2016 Alberto Sola Comino

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
/*
	Sudoku Solver
	--------------
	
	(...)
	
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
		
		/*
		cout << "Data: " << endl;
		vector<int>::const_iterator iter = numbers.begin();
		vector<int>::const_iterator end = numbers.end();

		while( iter != end ){

			cout << (*iter);

			++iter;
		}

		cout << endl;
		*/
		
	}
	
	bool check_repeated( const vector<int> & sudoku_numbers ){
		
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
		
		int square_corner[9] = {0,3,6,27,30,33,54,57,60};
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
		
		// Check SQUARES
		for( int i = 0; i < 9 && valid; i++ ){
			
			get_submatrix( square_corner[i], 3, 9, numbers );
			valid = check_repeated( numbers );			
			numbers.clear();
			
		}
		
		return valid;
	}


	void solve(){
		/*
			Find a valid solution using backtracking.
		*/
		
		// TODO: Optimize
		int pos = 0;
		int max_pos = sudoku.size();
		
		int tmp;
		
		vector<int>::const_iterator start = initial_values.begin();
		vector<int>::const_iterator end = initial_values.end();
		
		
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
					
					while( ( binary_search( start, end, pos ) || (sudoku[pos] == 9 && !binary_search( start, end, pos )) ) && pos > 0 )
						--pos;
					
				}
				else
					++pos;

				
			}
			
			else
				++pos;
		
			
			//cout << str() << endl;
			
			//cout << pos << endl;
			
			//cin >> tmp;
		}
		
	}

};

const int Sudoku::SIZE = 9;


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
