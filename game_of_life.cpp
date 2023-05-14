#include <array>

using namespace std;
using Matrix = array<array<int, 8>, 8>;


int get_live_neighbours(int x, int y, Matrix &matrix) {
	int live_neighbours = 0;

	array<array<int, 2>, 8> neighbour_relative_coordinates = { {
		{ {-1, -1} },
		{ {-1, 0} },
		{ {-1, 1} },
		{ {0, -1} },
		{ {0, 1} },
		{ {1, -1} },
		{ {1, 0} },
		{ {1, 1} },
	} };

	for (array<int,2> coordinates : neighbour_relative_coordinates) {
		int neighbour_x = (coordinates.at(0) + x + 8) % 8;
		int neighbour_y = (coordinates.at(1) + y + 8) % 8;

		if (matrix.at(neighbour_x).at(neighbour_y) == 1) {
			live_neighbours++;
		}
	}

	return live_neighbours;
}


void cell_next_state(int x, int y, Matrix &matrix, Matrix &new_matrix) {
	int live_neighbours = get_live_neighbours(x, y, matrix);

	if (live_neighbours < 2) {
		new_matrix.at(x).at(y) = 0;
	}
	else if (live_neighbours == 3) {
		new_matrix.at(x).at(y) = 1;
	}
	else if (live_neighbours > 3) {
		new_matrix.at(x).at(y) = 0;
	}
}


void next_generation(Matrix &matrix) {
	Matrix new_matrix = matrix;

	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			cell_next_state(x, y, matrix, new_matrix);
		}
	}

	matrix = new_matrix;
}