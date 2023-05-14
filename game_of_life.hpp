#pragma once

#include <array>

using namespace std;
using Matrix = array<array<int, 8>, 8>;

void next_generation(Matrix &matrix);
int get_live_neighbours(int x, int y, Matrix &matrix);