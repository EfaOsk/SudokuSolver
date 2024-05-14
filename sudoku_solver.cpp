#include "sudoku_solver.h"
#include <iostream>
#include <fstream>
#include <algorithm>  
#include <random>
SudokuSolver::SudokuSolver() {}

bool  SudokuSolver::solveSudoku(std::vector<std::vector<int>>& board) {
    if (smartElem(board)){
        return true;
    }
    // Create a list of blank cells
    std::vector<std::pair<int, int>> blankCells;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                blankCells.push_back({row, col});
            }
        }
    }

    // Randomize!!
    std::random_shuffle(blankCells.begin(), blankCells.end());

    // Iterate through each blank cell and try assigning numbers randomly
    for (const auto& cell : blankCells) {
        int row = cell.first;
        int col = cell.second;

        // Generate a list valid numbers
        std::vector<int> nums;
        getValidNumbers(board, row, col, nums); // = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        // Randomize!!
        std::random_shuffle(nums.begin(), nums.end());

        // Try assigning each number randomly
        for (int num : nums) {
            // Create a copy of the board
            std::vector<std::vector<int>> boardCopy = board;

            boardCopy[row][col] = num;

            // Recursively solve the remaining Sudoku
            if (smartElem(boardCopy)) {
                board = boardCopy;  // Update the original board with the solution
                return true;
            }
            if (solveSudoku(boardCopy)) {
                board = boardCopy;  // Update the original board with the solution
                return true;  // Sudoku solved successfully
            }
        }
        // std::cout << "I failed :'(" << std::endl;
        return false;  // No valid number can be assigned to this cell
    }

    return true;  // All cells filled, Sudoku solved
}

bool  SudokuSolver::smartElem(std::vector<std::vector<int>>& board) {
    int row, col, num;
    bool c;
    c = false;
    // cheack for emty cells
    if (!findUnassignedLocation(board, row, col)){
        // std::cout << "I won :P" << std::endl;
        return true;
    }
    // std::cout << "Obv fill" << std::endl;
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                num = hasObiousAnswer(board, row, col, num);
                if (num != 0){
                    c = true;
                    board[row][col] = num;
                    // std::cout << "Filled cell: (" << row << ", " << col << ") with " << num << std::endl;
                }
            }
        }
    }

    if (c){
        solveSudoku(board);
    } else if (smartFill(board)) {
        solveSudoku(board);

    } else {
        // std::cout << "I failed :'(" << std::endl;
    }
    return false;  
}

bool SudokuSolver::isValid(std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check if the number already exists in the row
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num)
            return false;
    }

    // Check if the number already exists in the column
    for (int i = 0; i < 9; i++) {
        if (board[i][col] == num)
            return false;
    }

    // Check if the number already exists in the 3x3 grid
    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

void SudokuSolver::getValidNumbers(std::vector<std::vector<int>>& board, int row, int col, std::vector<int>& nums) {
    std::vector<int> values(10, 0); // Array to store the count of values (from 1 to 9)

    // Count the occurrences of values in the row
    for (int c = 0; c < 9; c++) {
        if (c != col) {
            int value = board[row][c];
            if (value != 0)
                values[value-1]++;
        }
    }

    // Count the occurrences of values in the column
    for (int r = 0; r < 9; r++) {
        if (r != row) {
            int value = board[r][col];
            if (value != 0)
                values[value-1]++;
        }
    }

    // Count the occurrences of values in the 3x3 box
    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);
    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            int value = board[r][c];
            // std::cout << "(" << r<< ", " << c << ") : "<<value << std::endl;
                
            if (value != 0) {
                values[value-1]++;
            }
        }
    }

    // Find the missing value
    for (int i = 0; i < 9; i++) {
        if (values[i] == 0) {
            nums.push_back(i+1);
        }
    }

    return;
}

int SudokuSolver::hasObiousAnswer(std::vector<std::vector<int>>& board, int row, int col, int num) {
    std::vector<int> values(10, 0); // Array to store the count of values (from 1 to 9)

    // Count the occurrences of values in the row
    for (int c = 0; c < 9; c++) {
        if (c != col) {
            int value = board[row][c];
            if (value != 0)
                values[value]++;
        }
    }

    // Count the occurrences of values in the column
    for (int r = 0; r < 9; r++) {
        if (r != row) {
            int value = board[r][col];
            if (value != 0)
                values[value]++;
        }
    }

    // Count the occurrences of values in the 3x3 box
    int startRow = 3 * (row / 3);
    int startCol = 3 * (col / 3);
    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            int value = board[r][c];
            // std::cout << "(" << r<< ", " << c << ") : "<<value << std::endl;
                
            if (value != 0) {
                values[value]++;
            }
        }
    }

    // Find the missing value
    int missingValue = 0;
    int missingCount = 0;
    for (int i = 1; i <= 9; i++) {
        if (values[i] == 0) {
            missingValue = i;
            missingCount++;
        }
    }

    return missingCount == 1 ? missingValue : 0;
}

bool SudokuSolver::smartFill(std::vector<std::vector<int>>& board) {
    // std::cout << "Smart fill" << std::endl;
    bool hasUpdated = false;

    // Check for each number n in range 1-9
    for (int n = 1; n <= 9; n++) {
        // Check rows
        for (int row = 0; row < 9; row++){
            bool hasUniqueSolution = false;
            // int sr, sc, sn;
            int sc = -1; 

            
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0 && isValid(board, row, col, n)) {
                    if (!hasUniqueSolution) {
                        hasUniqueSolution = true;
                        sc = col;
                    } else {
                        hasUniqueSolution = false;
                        break;
                    }
                }
            }
            if (hasUniqueSolution){
                hasUpdated = true;
                // std::cout << "(s)Filled cell: (" << row << ", " << sc << ") with " << n << std::endl;
                board[row][sc] = n;
            }
        }

        // Check col
        for (int col = 0; col < 9; col++){
            bool hasUniqueSolution = false;
            int s = -1; 

            
            for (int row = 0; row < 9; row++) {
                if (board[row][col] == 0 && isValid(board, row, col, n)) {
                    if (!hasUniqueSolution) {
                        hasUniqueSolution = true;
                        s = row;
                    } else {
                        hasUniqueSolution = false;
                        break;
                    }
                }
            }
            if (hasUniqueSolution){
                hasUpdated = true;
                // std::cout << "(s)Filled cell: (" << s << ", " << col << ") with " << n << std::endl;
                board[s][col] = n;
            }
        }


        // Check 3x3 grids
        for (int r = 0; r<3; r++){
            for (int c = 0; c<3; c++){
                int countSolutions = 0;
                int sr = -1; 
                int sc = -1; 
                for (int i = r*3; i < r*3 + 3; i++) {
                    for (int j = c*3; j < c*3 + 3; j++) {
                        if (board[i][j] == 0 && isValid(board, i, j, n)) {
                                                        countSolutions++;
                            if (countSolutions == 1) {
                                sr = i;
                                sc = j;
                            } 

                        }
                    }
                }
                if (countSolutions==1){
                    hasUpdated = true;
                    // std::cout << "(sb)Filled cell: (" << sr << ", " << sc << ") with " << n << std::endl;
                    board[sr][sc] = n;
                }
            }
        }

    }

    return hasUpdated;
} 

bool SudokuSolver::findUnassignedLocation(std::vector<std::vector<int>>& board, int& row, int& col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (board[row][col] == 0)
                return true;
        }
    }

    return false;  // No unassigned location found
}