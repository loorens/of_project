#include "Cell.h"

///Initialize new cell with coordinates
Cell::Cell(float _x, float _y)
{
	x = _x;
	y = _y;
	energy = 0;
	absorbedEnergy = 0;
	//neighbors = vector<Cell *>; 

	//testowy komentarz
}

///add new neighbour to this cell
void Cell::addNeighbors(Cell * c)
{
	neighbors.push_back(c);
}

///Set energy (size) of cell to 1 (max size)
void Cell::fillUpEnergy()
{
	energy = 1.0;
}


///Absorb some of energy from neigbour
void Cell::absorbEnergy(float e)
{
	absorbedEnergy += e;
}

///Update energy in this cell and add some of the energy to the neighbors
void Cell::update()
{
	//oblicz ilo�� energi do doj�cia
	float diffused = energy * 0.04;
	//odejmij energi� danej kom�rki
	energy -= diffused;
	//dodaj cz�� energi do s�siad�w
	for (int i = 0; i < neighbors.size(); i++)
	{
		neighbors[i]->absorbEnergy(diffused / 5.0);
	}
	//dodaj energi� od s�siad�w je�eli jaka� istnieje
	if (absorbedEnergy > 0)
	{
		energy += absorbedEnergy;
		absorbedEnergy = 0.0;
	}
	//nie pozw�l na energi� wi�ksz� od 1.0
	if (energy > 1.0) energy = 1.0;
}

///Draw the Cell as a Circle, color and size depends from the cell energy
void Cell::draw()
{
	//ilo�� koloru niebieskiego zale�y od ilo�ci energi i jest w granicy 200 do 255
	float blue = ofMap(energy, 0, 1, 200, 255);
	ofSetColor(120, 220, blue);
	//rozmiar kom�rki zale�y od pierwiastka energii
	//�atwiej uzyska� wi�kszy rozmiar przy ma�ej ilo�ci energii
	float radius = ofMap(sqrt(energy), 0, 1, 5, 25);
	ofCircle(x, y, radius);
}
