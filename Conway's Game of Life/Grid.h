#pragma once
#include <vector>
#include "Cell.h"

#define ROWS 100
#define COLUMNS ROWS

class Grid {
private:
	int width, height, mW = width / COLUMNS, mH = height / ROWS;
	SDL_Rect cellPos = {0, 0, mW, mH};
	Cell cells[ROWS][COLUMNS];

	double map(double value, double istart, double istop, double ostart, double ostop) {
		return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
	}

public:

	void update();
	void update(int, int);
	void render(SDL_Renderer *);

	Grid(int w, int h) :width(w), height(h) {}
	~Grid() {}
};

