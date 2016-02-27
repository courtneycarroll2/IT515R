#include <array>
#include <cmath>
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

//please work!


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
 

//need to create a pointer to char
// need to move array off stack and onto heap



bool is_stable(Grid * grid, float epsilon, uint32_t rows, uint32_t columns) {
	// Loop across all the interior points
	for (uint32_t row = 1; row < rows-1; ++row) {
		for (uint32_t column = 1; column < columns-1; ++column) {
			float center = (*grid)[row][column];
			float east = (*grid)[row][column + 1];
			float west = (*grid)[row][column - 1];
			float south = (*grid)[row + 1][column];
			float north = (*grid)[row - 1][column];
			float average = ((north + south + east + west) / 4.0f);
				//4.0f b/c need float, not integer
				// check to see if the point is stable
				// if it is stable, check the next point
				// if it is not stable, return false;
			 if (epsilon < std::fabs(average - center)) {
				return false;
			}
		}
	}
	return true;
}

Grid * calculate_next(Grid * current, uint32_t rows, uint32_t columns) {
	Grid * next = new Grid(*current);
	for (uint32_t row = 1; row < rows-1; ++row) {
		for (uint32_t column = 1; column < columns-1; ++column) {
			float east = (*current)[row][column + 1];
			float west = (*current)[row][column - 1];
			float south = (*current)[row + 1][column];
			float north = (*current)[row - 1][column];
			(*next)[row][column] = ((north + south + east + west) / 4.0f);
				// reassign values of interior squares	
		}
	}
	delete current;
		// anything after the return line will not be done
	return next;
}

void print_Grid(Grid*grid, uint32_t rows, uint32_t columns, uint32_t iterations, float epsilon, ostream &out) {
	out.write(reinterpret_cast<char*>(&iterations), sizeof(uint32_t));
	out.write(reinterpret_cast<char*>(&epsilon), sizeof(float));
	out.write(reinterpret_cast<char*>(&rows), sizeof(uint32_t));
	out.write(reinterpret_cast<char*>(&columns), sizeof(uint32_t));
	for (uint32_t row = 0; row < rows; ++row) {
		for (uint32_t column = 0; column < columns; ++column) {
			out.write(reinterpret_cast<char*>(&(*grid)[row][column]), sizeof (uint32_t));
		}
		
	}
}


int main(int argc, char* argv[]) {
	//first arg is # of arguments, second is array of strings that gets passed in on command line
	// if argc is 0, nothing got passed in
	// argv: first parameter, argv[1]

	uint32_t iterations = 0;

	float epsilon = 0;
	uint32_t rows = 0;
	uint32_t columns = 0;

	// Create and initialize 2D grids
	
	cin.read(reinterpret_cast<char*>(&iterations), sizeof(uint32_t));
	//sizeof tells how many bytes: reading 4 bytes starting at address of iterations
	// reinterpret tells it to convert from pointer to uint32_t -> pointer to char
	cin.read(reinterpret_cast<char*>(&epsilon), sizeof(float));
	cin.read(reinterpret_cast<char*>(&rows), sizeof(uint32_t));
	cin.read(reinterpret_cast<char*>(&columns), sizeof(uint32_t));
	Grid * grid = new Grid(rows, columns);
	//lowercase grid is pointer to uppercase Grid; need to dereference grid
	cin.read(reinterpret_cast<char*>(&(*grid)[0][0]), sizeof(float) * rows * columns);

	
	string result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	
	
	while (!is_stable(grid, epsilon, rows, columns)) {
		// calculate the new values of the grid
		grid = calculate_next(grid, rows, columns);
		++iterations;
		if (argc > 1){
			int param = stoi(argv[1]);
				// converts index 1 from string to integer
			if (iterations % param == 0) {
				ofstream myfile;
				convert << iterations;      // insert the textual representation of 'Number' in the characters in the stream
				result = convert.str(); // set 'Result' to the contents of the stream
				myfile.open(string{ "chkpt." } +string{result} +string{ ".out" });
				print_Grid(grid, rows, columns, iterations, epsilon, myfile);
				myfile.close();
			}
		}
	}

	
	//sizeof tells how many bytes
	// reinterpret tells it to convert from pointer to uint32_t -> pointer to char
	print_Grid(grid, rows, columns, iterations, epsilon, std::cout);
	
	delete grid;

	return 0;
}

