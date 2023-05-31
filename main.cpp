#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "sudoku_solver.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./sudoku_solver <input_file>" << std::endl;
        return 1;
    }
    
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cout << "Error opening input file." << std::endl;
        return 1;
    }
    
    std::vector<std::vector<std::vector<int>>> boards; 
    std::string line;

    SudokuSolver solver; 

    while (std::getline(inputFile, line)) {
        std::vector<std::vector<int>> board;

        for (int i = 0; i < 9; i++) {
            std::vector<int> row;
            for (int j = i * 9; j < (i * 9) + 9; j++) {
                char ch = line[j];
                if (ch >= '1' && ch <= '9') {
                    row.push_back(ch - '0');
                } else if (ch == '-') {
                    row.push_back(0);
                }
            }
            board.push_back(row);
        }

        boards.push_back(board);  

        auto start = std::chrono::high_resolution_clock::now();
        bool sol = solver.solveSudoku(board);
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (sol){
            std::cout << "solved in: " << (double)dur.count()/1000 << " ms" << std::endl;
        } else {
            std::cout << "(failed) tryed for: " << (double)dur.count()/1000 << " ms" << std::endl;
        }

        // Print the solved Sudoku board
        // for (const auto& row : board) {
        //     for (int num : row) {
        //         std::cout << num << ' ';
        //     }
        //     std::cout << std::endl;
        // }
    }

    


    
    return 0;
}
