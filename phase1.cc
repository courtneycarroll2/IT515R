#include <array>
#include <cmath>
#include <iostream>


// allows me to drop std:: before array

using std::array;


using Grid = array<array<float, 1024>, 1024>;


void initialize(Grid * grid) {
	for (int column = 0; column < 1024; ++column) {
		(*grid)[0][column] = 0;
	}

	for (int row = 1; row < 1023; ++row) {
		(*grid)[row][0] = 0;
		for (int column = 1; column < 1023; ++column) {
			(*grid)[row][column] = 50;
		}
		(*grid)[row][1023] = 0;
	}

	for (int column = 0; column < 1024; ++column) {
		(*grid)[1023][column] = 0;
	}
}

bool is_stable(Grid * grid) {
	float epsilon = 0.1;
	// Loop across all the interior points
	for (int row = 1; row < 1023; ++row) {
		for (int column = 1; column < 1023; ++column) {
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

Grid * calculate_next(Grid * current) {
	Grid * next = new Grid(*current);
	for (int row = 1; row < 1023; ++row) {
		for (int column = 1; column < 1023; ++column) {
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



int main() {

	Grid * grid = new Grid();

	// Create and initialize 2D grids
	initialize(grid);


	int iterations = 0;
	while (!is_stable(grid)) {
		// calculate the new values of the grid
		grid = calculate_next(grid);
		++iterations;
		std::cout << "Iteration:" << iterations << std::endl;
	}


	// print out the number of iterations that took
	std::cout << "Iterations:" << iterations << std::endl;

	return 0;
}

//ok