# sudoku-solver

Simple algorithm for solving sudokus using backtracking.

> I love programming challenges. I developed a C++ version some years ago. Now I've added a Go version just for fun, in order to improve my coding skills.


## Usage

### Cpp

```
$ cd cpp
$ make
$ ./sudoku-solver <input file>
```

### Go

```
$ cd go
$ go run main.go <input file>
```

This version has unit testing, that you can run with the command `go test -v ./...`.

## Input

A text file sudoku where:
- Each number is a sudoku value [1-9].
- Nine rows, nine columns.
- Unkown numbers are represented with 'x'.

Example files:
  - sudoku_easy.txt
  - sudoku_hard.txt

