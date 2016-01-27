#pragma once

#include "ofMain.h"

class Cell
{
private:
	float x, y, dim;
	float energy, absorbedEnergy;
	vector<Cell*> neighbors;
	void absorbEnergy(float e);

public:
	Cell(float _x, float _y);
	void addNeighbors(Cell * c);
	void fillUpEnergy();
	
	void update();
	void draw();

};

