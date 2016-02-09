#include "Cell.h"


float Cell::minDim = 5.0;
float Cell::maxDim = 15.0;

///Initialize new cell with coordinates
Cell::Cell(float _x, float _y)
{
	pos.x = _x;
	pos.y = _y;
	x = _x;
	y = _y;
	energy = 0;
	absorbedEnergy = 0;
	dim = 2;
	touched = 0;
}

///add new neighbour to this cell
void Cell::addNeighbors(Cell * c)
{
	neighbors.push_back(c);
}

ofPoint Cell::getPosition()
{
	return pos;
}

///Set energy (size) of cell to 1 (max size)
void Cell::fillUpEnergy()
{
	energy = 1.0;
}

void Cell::setTouched()
{
	touched = 1;
}

bool Cell::isTouched()
{
	return touched > 0.9;
}


///Absorb some of energy from neigbour
void Cell::absorbEnergy(float e)
{
	absorbedEnergy += e;
}

///Update energy in this cell and add some of the energy to the neighbors
void Cell::update()
{
	//zmiejsz wartoœæ energi dotkniêcia
	touched *= 0.95;

	//oblicz iloœæ energi do dojêcia
	float diffused = energy * 0.04;
	//odejmij energiê danej komórki
	energy -= diffused;
	//dodaj czêœæ energi do s¹siadów
	for (int i = 0; i < neighbors.size(); i++)
	{
		neighbors[i]->absorbEnergy(diffused / 5.0);
	}
	//dodaj energiê od s¹siadów je¿eli jakaœ istnieje
	if (absorbedEnergy > 0)
	{
		energy += absorbedEnergy;
		absorbedEnergy = 0.0;
	}
	//nie pozwól na energiê wiêksz¹ od 1.0
	if (energy > 1.0) energy = 1.0;
}

///Draw the Cell as a Circle, color and size depends from the cell energy
void Cell::draw()
{
	//iloœæ koloru niebieskiego zale¿y od iloœci energi i jest w granicy 200 do 255
	float red = ofMap(touched, 0, 1, 0, 255);
	float blue = ofMap(energy, 0, 1, 150, 200);
	ofSetColor(red, 50, blue);
	//rozmiar komórki zale¿y od pierwiastka energii
	//³atwiej uzyskaæ wiêkszy rozmiar przy ma³ej iloœci energii
	dim = ofMap(sqrt(energy), 0, 1, minDim, maxDim);
	ofCircle(x, y, dim);
}
