package sudoku

import (
	"bufio"
	"fmt"
	"os"
)

const SUDOKU_LINE_LENGTH = 9
const NOT_SET_VALUE = 0

type Sudoku struct {
	data [SUDOKU_LINE_LENGTH * SUDOKU_LINE_LENGTH]int
	edit [SUDOKU_LINE_LENGTH * SUDOKU_LINE_LENGTH]bool
}

func NewSudoku() Sudoku {
	return Sudoku{}
}

func (s *Sudoku) ReadFromFile(filneame string) error {
	file, err := os.Open(filneame)
	if err != nil {
		return err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	lineCount := 0
	for scanner.Scan() {
		line := scanner.Text()

		for i, char := range line {
			value := NOT_SET_VALUE

			if char != 'x' {
				value = int(char - '0')
			}

			s.data[lineCount*SUDOKU_LINE_LENGTH+i] = value
			s.edit[lineCount*SUDOKU_LINE_LENGTH+i] = value == NOT_SET_VALUE
		}

		lineCount += 1
	}

	return nil
}

func (s *Sudoku) Print() {
	for i := 0; i < SUDOKU_LINE_LENGTH; i++ {
		for j := 0; j < SUDOKU_LINE_LENGTH; j++ {
			value := s.data[i*SUDOKU_LINE_LENGTH+j]
			if value == NOT_SET_VALUE {
				fmt.Print("x")
			} else {
				fmt.Print(value)
			}
		}
		fmt.Print("\n")
	}
}

func (s *Sudoku) Solve() {
	for pos := 0; pos >= 0 && pos < len(s.data); {
		if !s.edit[pos] {
			pos += 1
		} else {
			if s.data[pos] == 9 {
				s.data[pos] = NOT_SET_VALUE
				pos -= 1
				for pos >= 0 && pos < len(s.data) && !s.edit[pos] {
					pos -= 1
				}
			} else {
				s.data[pos] += 1

				valid := s.Valid()
				if valid {
					pos += 1
					for pos >= 0 && pos < len(s.data) && !s.edit[pos] {
						pos += 1
					}
				}
			}
		}

	}
}

func (s *Sudoku) Valid() bool {
	for pos := 0; pos < len(s.data); pos++ {
		value := s.data[pos]
		editable := s.edit[pos]

		if value != NOT_SET_VALUE && editable {
			valid := s.isColValid(pos) && s.isRowValid(pos) && s.isSquareValid(pos)

			if !valid {
				return false
			}
		}
	}

	return true
}

func (s *Sudoku) isRowValid(pos int) bool {
	lineIndex := pos / SUDOKU_LINE_LENGTH
	value := s.data[pos]
	s.data[pos] = NOT_SET_VALUE

	for i := lineIndex * SUDOKU_LINE_LENGTH; i < lineIndex*SUDOKU_LINE_LENGTH+SUDOKU_LINE_LENGTH; i++ {
		if s.data[i] == value {
			s.data[pos] = value
			return false
		}
	}

	s.data[pos] = value
	return true
}

func (s *Sudoku) isColValid(pos int) bool {
	columnIndex := pos % SUDOKU_LINE_LENGTH
	value := s.data[pos]
	s.data[pos] = NOT_SET_VALUE

	for i := columnIndex; i < SUDOKU_LINE_LENGTH*SUDOKU_LINE_LENGTH; i += SUDOKU_LINE_LENGTH {
		if s.data[i] == value {
			s.data[pos] = value
			return false
		}
	}

	s.data[pos] = value
	return true
}

func (s *Sudoku) isSquareValid(pos int) bool {
	xIndex := (pos % SUDOKU_LINE_LENGTH) / 3
	yIndex := (pos / SUDOKU_LINE_LENGTH) / 3

	value := s.data[pos]
	s.data[pos] = NOT_SET_VALUE

	for x := xIndex * 3; x < xIndex*3+3; x++ {
		for y := yIndex * 3; y < yIndex*3+3; y++ {
			if s.data[y*SUDOKU_LINE_LENGTH+x] == value {
				s.data[pos] = value
				return false
			}
		}
	}

	s.data[pos] = value
	return true
}
