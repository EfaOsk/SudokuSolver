#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <vector>

class SudokuSolver {
public:
    SudokuSolver();
    bool solveSudoku(std::vector<std::vector<int>>& board);
    
private:
    bool smartElem(std::vector<std::vector<int>>& board);
    bool isValid(std::vector<std::vector<int>>& board, int row, int col, int num);
    void getValidNumbers(std::vector<std::vector<int>>& board, int row, int col, std::vector<int>& num);
    int hasObiousAnswer(std::vector<std::vector<int>>& board, int row, int col, int num);
    bool smartFill(std::vector<std::vector<int>>& board);
    bool findUnassignedLocation(std::vector<std::vector<int>>& board, int& row, int& col);
};

#endif  // SUDOKU_SOLVER_H