#include <array>
#include <cmath>
#include <iostream>
#include <cstdint>
#include <memory>

//Add a new C++ file to your project.This file will read in over standard in the binary format created in Phase 2 
//and will write to standard out a valid plain PGM image for that grid.
//To clarify, I want you to use the "plain" PGM format which uses magic number P2, 
//not the "raw" format which uses the magic number P5.

//Update your Makefile or CMakeLists.txt to also build this program.
//When make is invoked without a target it should build all programs in your project(for example, solver.exe and grid2pgm.exe).

//Make sure to use either a branch or tag for this phase.Once again upload the URL to your project for me to clone.

// Read in binary format

// write out in ASCII format: example-
	// cout<<int(grid[][])
//phase 5: save out grid format every n interations

class Grid {
	uint32_t _rows;
	uint32_t _columns;
	std::unique_ptr<float[]> data;

public:

	Grid(uint32_t rows, uint32_t columns) : _rows{ rows }, _columns{ columns }, data{ std::make_unique<float[]>(rows * columns) } {
	}

	Grid(Grid &other) : Grid{ other._rows, other._columns } {
		for (uint32_t rows = 0; rows < _rows; ++rows) {
			for (uint32_t columns = 0; columns < _columns; ++columns) {
				(*this)[rows][columns] = other[rows][columns];
			}
		}
	}


	uint32_t rows() const {
		return _rows;
	}

	uint32_t columns() const {
		return _columns;
	}

	float * operator[](uint32_t row) {
		return row * _columns + data.get();
	}

};

// allows me to drop std:: before array
using namespace std;
 


// find max value:
//loop through grid values
//find largest value
float find_max(Grid*grid, uint32_t rows, uint32_t columns) {
	float val = 0;
		for (uint32_t row = 0; row < rows; ++row) {
			for (uint32_t column = 0; column < columns; ++column) {
				if ((*grid)[row][column] > val) {
					val = (*grid)[row][column];
				}
			}
		}return val;
}
	

int main() {

	uint32_t iterations = 0;
	float epsilon = 0;
	uint32_t rows = 0;
	uint32_t columns = 0;

	// Create and initialize 2D grids
	
	//sizeof tells how many bytes: reading 4 bytes starting at address of iterations
	// reinterpret tells it to convert from pointer to uint32_t -> pointer to char
	cin.read(reinterpret_cast<char*>(&iterations), sizeof(uint32_t));
	cin.read(reinterpret_cast<char*>(&epsilon), sizeof(float));
	cin.read(reinterpret_cast<char*>(&rows), sizeof(uint32_t));
	cin.read(reinterpret_cast<char*>(&columns), sizeof(uint32_t));
	Grid * grid = new Grid(rows, columns);
	//lowercase grid is pointer to uppercase Grid; need to dereference grid
	cin.read(reinterpret_cast<char*>(&(*grid)[0][0]), sizeof(float) * rows * columns);

	float val = find_max(grid, rows, columns);

	// write out as a PGM file in ASCII format:
	cout << "P2\n" << columns << " " << rows << "\n" << val << "\n";
	for (uint32_t row = 0; row < rows; ++row) {
		for (uint32_t column = 0; column < columns; ++column) {
			cout << int{ (*grid)[row][column] } << " ";
		}
	}
	delete grid;

	return 0;
}

