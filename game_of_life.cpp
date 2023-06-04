using namespace std;
using Matrix = int[8][8];


int get_live_neighbours(int x, int y, Matrix &matrix) {
	int live_neighbours = 0;

		int neighbour_relative_coordinates[8][2] = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1},
	};

	for (int i=0; i<8; i++) {
		int neighbour_x = (neighbour_relative_coordinates[i][0] + x + 8) % 8;
		int neighbour_y = (neighbour_relative_coordinates[i][1] + y + 8) % 8;

		if (matrix[neighbour_x][neighbour_y] == 1) {
			live_neighbours++;
		}
	}

	return live_neighbours;
}


void cell_next_state(int x, int y, Matrix &matrix, Matrix &new_matrix) {
	int live_neighbours = get_live_neighbours(x, y, matrix);

	if (live_neighbours < 2 || live_neighbours > 3) {
		new_matrix[x][y] = 0;
	}
	else if (live_neighbours == 3) {
		new_matrix[x][y] = 1;
	}
}


void next_generation(Matrix &matrix) {
	Matrix new_matrix;
	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			new_matrix[x][y] = matrix[x][y];
		}
	}

	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			cell_next_state(x, y, matrix, new_matrix);
		}
	}

	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			matrix[x][y] = new_matrix[x][y];
		}
	}
}