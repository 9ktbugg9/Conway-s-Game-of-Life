#include "stdafx.h"
#include "Grid.h"


void Grid::update() {
	Cell tempCells[ROWS][COLUMNS];
	for (int i = 0; i < ROWS; i++) {
		for (int k = 0; k < COLUMNS; k++) {
			tempCells[i][k] = cells[i][k];
		}
	}

	for (int i = 0; i < ROWS; i++) {
		for (int k = 0; k < COLUMNS; k++) {
			int nei = 0;
			if (i - 1 >= 0 && tempCells[i - 1][k].isAlive())
				nei++;
			if (i - 1 >= 0 && tempCells[i - 1][k - 1].isAlive())
				nei++;
			if (i - 1 >= 0 && tempCells[i - 1][k + 1].isAlive())
				nei++;
			if (tempCells[i][k - 1].isAlive())
				nei++;
			if (tempCells[i][k + 1].isAlive())
				nei++;
			if (i + 1 < ROWS && tempCells[i + 1][k].isAlive())
				nei++;
			if (i + 1 < ROWS && tempCells[i + 1][k - 1].isAlive())
				nei++;
			if (i + 1 < ROWS && tempCells[i + 1][k + 1].isAlive())
				nei++;

			if (nei < 2 && tempCells[i][k].isAlive())
				cells[i][k].die();
			if (nei > 3 && tempCells[i][k].isAlive())
				cells[i][k].die();
			if (nei == 3 && !tempCells[i][k].isAlive())
				cells[i][k].live();
		}
	}
}

void Grid::update(int y, int x) {
	x = map(x, 0, width, 0, COLUMNS);
	y = map(y, 0, height, 0, ROWS);

	if (cells[x][y].isAlive())
		cells[x][y].die();
	else if (!cells[x][y].isAlive())
		cells[x][y].live();
}

void Grid::render(SDL_Renderer *rend) {
	for (int i = 0; i < COLUMNS; i++) {
		for (int k = 0; k < ROWS; k++) {
			if (cells[i][k].isAlive()) {
				cellPos.x = k * mW;
				cellPos.y = i * mH;
				SDL_RenderFillRect(rend, &cellPos);
			}
		}
	}
}