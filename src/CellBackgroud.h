#pragma once
#include "ofMain.h"
#include "Cell.h"

class CellBackgroud
{
private:
	vector<Cell *> cells;
	int width, height;
	int marginX, marginY;
	int distance;
	int counter;

public:

	CellBackgroud(int _width, int _height, int _distance);
	void setup();
	void draw();
	void update();
	void updateWithRandomEnergy();
	void updateWithPoints(vector<ofPoint> & points);
	void boom();

};

