CC=g++
EXEC=sudoku-solver
HDR=sudoku.hpp
SRC=sudoku.cpp sudoku-solver.cpp

sudoku: $(SRC) $(HDR)
	$(CC) -o $(EXEC) $(SRC) -O2 -Wall
