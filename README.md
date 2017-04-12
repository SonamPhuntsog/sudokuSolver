To build it use cpp 11
 g++ -std=c++11 sudoku.cpp -o sudoku

Use redirection to feed in sudoku problem
./sudoku < sudoku1.txt
./sudoku -d < sudoku1.txt

use -d option to printing each step and some extra information in the end

sudoku1.txt and sudoku2.txt are sudoku problem
these files are 9 x 9 numbers for each box and 0 for empty box
