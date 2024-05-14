# Sudoku Solver
## Authors
- [Eva Ósk](https://github.com/efaosk)

## Overview
This project is a Sudoku solver implemented in C++. It uses a combination of smart backtracking algorithms and randomizadion techniques to efficiently solve Sudoku puzzles. The solver reads Sudoku puzzles from an input file, where each line represents a different board with '-' indicating an empty space, and attempts to solve them.

## Features
- **Efficient Solving**: Uses a combination of deterministic filling and randomized backtracking to solve puzzles efficiently.
- **Performance Measurement**: Measures and reports the time taken to solve each puzzle in milliseconds.
- **Flexible Input**: Reads multiple Sudoku puzzles from a single input file, allowing for batch processing of puzzles.

## Prerequisites
To build and run the Sudoku Solver, you will need:
- A C++ compiler (C++11 or later is required)

## Compilation and Execution
1. Compile the program using a C++ compiler. For example, using g++:
   ```bash
   g++ -o sudoku_solver main.cpp sudoku_solver.cpp -std=c++11
   ```
2. Run the program by providing an input file containing Sudoku puzzles:
    ```bash
    ./sudoku_solver <path to input board file>
    ```

## Input File Format
The input file should contain one or more lines, each representing a single Sudoku puzzle. Each line should have $81$ (or $9\times9$) characters, where each character is either a digit (1-9) or '-' for an empty cell. See example boards in the boards folder (single_solution_easy.txt, single_solution_medium.txt and single_solution_hard.txt)

## Output
The solver prints the solution time for each puzzle, and the solved board.
