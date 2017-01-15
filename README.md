# Sudoku Solver

Simple algorithm for solving sudokus using backtracking in C++.

## Algorithm

Constant number: the numbers in a sudoku that you cannot change.

- sudoku[index] is not a constant number:
  - If it's a 9: backtrack(index).
  - If it's not a 9:
    - number++
    - It's valid: index++

- sudoku[index] is constant:
  - index++

Backtrack(index):
  - index--
  - while(constant(index))
    - index--


## Usage

  make
  ./sudoku-solver <input file>

## Input

A sudoku where the unkown numbers are 'x'. Examples:
  - sudoku_easy.txt
  - sudoku_hard.txt
