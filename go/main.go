package main

import (
	"fmt"
	"os"
	"sudoku-solver/sudoku"
)

func main() {
	args := os.Args
	if len(args) != 2 {
		fmt.Println("Wrong arguments. Usage: sudoku-solver <sudoku-file>")
		os.Exit(1)
	}

	filename := args[1]
	sudoku := sudoku.NewSudoku()
	err := sudoku.ReadFromFile(filename)
	if err != nil {
		fmt.Println("Erro reading the file", filename)
		os.Exit(1)
	}

	sudoku.Print()
	sudoku.Solve()
	fmt.Println("-----------------")
	sudoku.Print()
}
