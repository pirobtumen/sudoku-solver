package sudoku

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestIsRowValidShouldReturnTrueLine0(t *testing.T) {
	s := NewSudoku()
	for i := 0; i < 9; i++ {
		s.data[i] = i + 1
	}

	assert.True(t, s.isRowValid(1))
	assert.Equal(t, 2, s.data[1])
}

func TestIsRowValidShouldReturnTrueLineN(t *testing.T) {
	s := NewSudoku()
	for i := 0; i < 9; i++ {
		s.data[i+9] = i + 1
	}

	s.data[15] = 2
	assert.False(t, s.isRowValid(10))
	assert.Equal(t, 2, s.data[10])
}

func TestIsRowValidShouldReturnFalse(t *testing.T) {
	s := NewSudoku()
	for i := 0; i < 9; i++ {
		s.data[i] = i + 1
	}

	s.data[2] = 1
	assert.False(t, s.isRowValid(2))
	assert.False(t, s.isRowValid(0))
}

func TestIsColValidShouldReturnTrue(t *testing.T) {
	s := NewSudoku()
	for i := 0; i < SUDOKU_LINE_LENGTH*SUDOKU_LINE_LENGTH; i += 9 {
		s.data[i] = i + 1
	}

	assert.True(t, s.isColValid(0))
	assert.Equal(t, 1, s.data[0])
}

func TestIsColValidShouldReturnFalse(t *testing.T) {
	s := NewSudoku()
	for i := 0; i < SUDOKU_LINE_LENGTH*SUDOKU_LINE_LENGTH; i += 9 {
		s.data[i] = i + 1
	}

	s.data[9] = 1
	assert.False(t, s.isColValid(0))
	assert.False(t, s.isColValid(1))
}

func TestIsSquareValidShouldReturnTrue(t *testing.T) {
	s := NewSudoku()
	count := 1
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			s.data[j*SUDOKU_LINE_LENGTH+i] = count
			count += 1
		}
	}

	assert.True(t, s.isSquareValid(10))
	assert.Equal(t, 5, s.data[10])
}

func TestIsSquareValidShouldReturnFalse(t *testing.T) {
	s := NewSudoku()
	count := 1
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			s.data[j*SUDOKU_LINE_LENGTH+i] = count
			count += 1
		}
	}

	s.data[11] = 5
	assert.False(t, s.isSquareValid(10))
	assert.Equal(t, 5, s.data[10])
}

func TestReadSudokuShouldBeValid(t *testing.T) {
	s := NewSudoku()
	s.ReadFromFile("../../sudoku_easy.txt")

	assert.Equal(t, s.data, [...]int{9, 0, 0, 0, 7, 0, 0, 0, 5, 0, 0, 3, 0, 0, 0, 1, 7, 0, 0, 7, 0, 8, 0, 6, 0, 4, 0, 0, 0, 5, 0, 3, 7, 6, 0, 0, 8, 0, 0, 4, 0, 1, 7, 0, 2, 0, 0, 7, 0, 9, 0, 4, 0, 0, 0, 6, 0, 7, 0, 2, 0, 8, 0, 7, 0, 2, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 7})
	assert.Equal(t, s.edit, [...]bool{false, true, true, true, false, true, true, true, false, true, true, false, true, true, true, false, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, false, false, false, true, true, false, true, true, false, true, false, false, true, false, true, true, false, true, false, true, false, true, true, true, false, true, false, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, true, true, false, true, true, true, false})
}

func TestReadSudokuWhenFileNotExistsShouldReturnError(t *testing.T) {
	s := NewSudoku()
	err := s.ReadFromFile("sudoku_easy.txt")
	assert.NotNil(t, err)
}

func TestSolveSudokuEasyShouldBeValid(t *testing.T) {
	s := NewSudoku()
	s.ReadFromFile("../../sudoku_easy.txt")
	s.Solve()

	assert.True(t, s.Valid())
}

func TestSolveSudokuHardShouldBeValid(t *testing.T) {
	s := NewSudoku()
	s.ReadFromFile("../../sudoku_hard.txt")
	s.Solve()

	assert.True(t, s.Valid())
}
