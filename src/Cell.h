#pragma once

#include "ofMain.h"

class Cell
{
private:
	float x, y, dim, touched;
	ofPoint pos;
	float energy, absorbedEnergy;
	vector<Cell*> neighbors;
	void absorbEnergy(float e);

public:
	Cell(float _x, float _y);
	void addNeighbors(Cell * c);
	ofPoint getPosition();
	void fillUpEnergy();
	void setTouched();
	bool isTouched();
	void update();
	void draw();

};

