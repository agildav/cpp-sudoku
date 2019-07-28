#include <iostream>
#include "time.h"
using namespace std;

class Sudoku {
  private:
    // Board
    int **board;
    int cEmpty = 0;
    int cRows = 0;
    int cColumns = 0;

    bool isValidInRow(int row, int number) {
      for (int column = 0; column < this->cColumns; column++) {
        if (this->board[row][column] == number)
        {
          return false;
        }
      }

      return true;
    }

    bool isValidInColumn(int column, int number) {
      for (int row = 0; row < this->cRows; row++) {
        if (this->board[row][column] == number)
        {
          return false;
        }
      }

      return true;
    }

    bool isValidInBlock(int row, int column, int number) {
      int rowLimit = row - row % 3;
      int colLimit = column - column % 3;

      for (int r = 0; r < 3; r++) {
        for (int c = 0; c < + 3; c++) {
          if (this->board[r + rowLimit][c + colLimit] == number) {
            return false;
          }
        }
      }
      return true;
    }

    bool isNumberAllowed(int row, int col, int number) {
      return (isValidInRow(row, number) && isValidInColumn(col, number) && isValidInBlock(row, col, number));
    }

  public:
    // Constructor
    Sudoku(int rows, int columns) {
      this->cRows = rows;
      this->cColumns = columns;
      this->board = new int *[rows];

      for (int row = 0; row < rows; row++) {
        this->board[row] = new int[columns];
      }

      for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
          this->board[row][column] = this->cEmpty;
        }
      }
    }

    void printSudoku() {
      int rows = this->cRows;
      int columns = this->cColumns;

      for (int row = 0; row < rows; row++) {
        if (row % 3 == 0 && row != 0) {
          cout << "---------------------\n";
        }

        for (int column = 0; column < columns; column++) {
          if (column % 3 == 0 && column != 0) {
            cout << "| ";
          }

          cout << board[row][column] << " ";
        }
        cout << endl;
      }
    }

    bool resolveSudoku() {
      int rows = this->cRows;
      int columns = this->cColumns;
      int empty = this->cEmpty;

      for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
          if (this->board[row][column] == empty) {
            for (int number = 1; number <= 9; number++) {
              if (isNumberAllowed(row, column, number)) {
                this->board[row][column] = number;
                if (resolveSudoku()) {
                  return true;
                }
                this->board[row][column] = empty;
              }
            }
            return false;
          }
        }
      }
      return true;
    }
};

int main() {
  struct timespec start, finish;
  double elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);


  int n = 9;

  Sudoku cSudoku(n, n);

  cout << ": Initial Sudoku : \n";
  cSudoku.printSudoku();

  cout << "\n: Solution : \n";
  cSudoku.resolveSudoku();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  cout << "Finished in " << elapsed << "secs" << endl;
  cSudoku.printSudoku();
}