#pragma once

using namespace std;
using Matrix = int[8][8];

void next_generation(Matrix &matrix);
int get_live_neighbours(int x, int y, Matrix &matrix);