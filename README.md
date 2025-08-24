# Matrix Application

**Matrix** is a C++ console application for performing a wide range of matrix operations.  
It provides an interactive menu that allows the user to input matrices (from keyboard, file, or randomly generated) and apply various operations step by step.  

The project was developed in Code::Blocks and uses standard C++ libraries together with some Windows-specific features for console styling.  

## Features
- Multiple ways to initialize matrices:
  - Manual input from keyboard  
  - Reading from file (`matrice4.in.txt`)  
  - Random generation (with optional interval)  
- Supported operations:
  - Matrix addition and subtraction  
  - Matrix multiplication (with explanation of element-wise computation on demand)  
  - Transposition  
  - Determinant calculation (for any size \( n \times n \))  
  - Matrix inverse (if determinant ≠ 0)  
  - Matrix exponentiation (up to power 10)  
  - Extracting elements relative to diagonals:
    - Above/below main diagonal  
    - Above/below secondary diagonal  
  - Extracting elements by regions (NORTH, SOUTH, EAST, WEST) based on coordinates  

## Usage
1. Run the program.  
2. Choose how to declare the matrices:
   - Keyboard input  
   - File input (`matrice4.in.txt`)  
   - Randomly generated values  
3. Navigate through the interactive menu to apply operations.  
4. Results are displayed directly in the console with formatted output.  

## Example Menu
1. Add two matrices
2. Subtract two matrices
3. Multiply matrices
4. Show elements relative to diagonals of A
5. Show elements relative to diagonals of B
6. Show elements from a region (NORTH / SOUTH / EAST / WEST)
7. Transpose a matrix
8. Raise matrix to a power (≤ 10)
9. Compute determinant
10. Compute inverse
11. Go back to matrix declaration
12. Exit

## File Structure
- `main.cpp` – main source code implementing all operations and the interactive menu  
- `matrice4.in.txt` – sample input file containing predefined matrices  
- Project files for Code::Blocks (`Aplicatie Matrici.cbp`, `.depend`, `.layout`)  

## Building
### With Code::Blocks
- Open `Aplicatie Matrici.cbp`  
- Build and run the project  

### With g++
```bash
g++ -std=c++11 main.cpp -o matrix_app
./matrix_app
