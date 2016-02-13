#pragma once

#include "ofMain.h"

class Cell
{
private:
	static float minDim, maxDim;
	float x, y, dim, touched, contact;
	ofPoint pos;
	float energy, absorbedEnergy;
	vector<Cell*> neighbors;
	void absorbEnergy(float e);

public:
	Cell(float _x, float _y);
	void addNeighbors(Cell * c);
	ofPoint getPosition();
	float getRadius();
	void fillUpEnergy();
	void setTouched();
	bool isTouched();
	void setContact();
	bool isContact();

	void update();
	void draw();

};



