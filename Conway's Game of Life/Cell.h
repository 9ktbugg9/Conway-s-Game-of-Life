#pragma once
#include "SDL.h"

class Cell {
private:
	bool alive = false;

public:

	void die() { alive = false; }
	void live() { alive = true; }
	bool isAlive() { return alive; }

	Cell();
	~Cell();
};

