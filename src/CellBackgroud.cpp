#include "CellBackgroud.h"


///Create backgroud, set width, height and distance between cells
CellBackgroud::CellBackgroud(int _width, int _height, int _distance)
{
	width = _width;
	height = _height;
	distance = _distance;
	counter = 0;
}

///Initialize backgroud made of cells
void CellBackgroud::setup()
{
	//maxymalna ilo�� kom�rek w pionie i poziomie
	int maxX = width / distance + 1;
	int maxY = height / distance + 1;
	//wyznaczenie marginesu tak aby by� r�wny po wszstkich stronach
	int marginX = (width - (maxX - 1)*distance) / 2;
	int marginY = (height - (maxY - 1)*distance) / 2;

	//inicjalizacja dynamicznej tablicy wska�nik�w
	Cell *** c = new Cell **[maxY];
	for (int i = 0; i < maxY; i++)
	{
		c[i] = new Cell*[maxX];
	}

	//stworzenie kom�rek naprzemiennie w wierszach
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
			{
				c[y][x] = new Cell(x * distance + marginX, y * distance + marginY);
			}
		}
	}

	//dodanie kom�rek do kontenera, dodanie do ka�dej kom�rki jej s�siad�w
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
			{
				//sprawd� czy kom�rka nie le�y przy kraw�dzi
				//je�li tak to nie ma jednego z s�siad�w
				if (x != 0 && y != 0) {
					c[y][x]->addNeighbors(c[y - 1][x - 1]);
				}
				if (x != 0 && y != maxY - 1) {
					c[y][x]->addNeighbors(c[y + 1][x - 1]);
				}
				if (x != maxX - 1 && y != 0) {
					c[y][x]->addNeighbors(c[y - 1][x + 1]);
				}
				if (x != maxX - 1 && y != maxY - 1) {
					c[y][x]->addNeighbors(c[y + 1][x + 1]);
				}
				cells.push_back(c[y][x]);
			}
		}
	}
}

///Draw background made of cells
void CellBackgroud::draw()
{
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i]->draw();
	}
}

///Update background made of cells
void CellBackgroud::update(bool randomEnergy)
{
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i]->update();
	}

	if (randomEnergy)
	{
		if ((counter++) % 10 == 0)
		{
			int r = (int)ofRandom(cells.size());
			cells[r]->fillUpEnergy();
		}
	}

}

///update background in places where are points of contour
void CellBackgroud::updateWithPoints(vector<ofPoint>& points)
{
	//je�eli lista punkt�w jest pusta to od�wierz aktualizuj bez nowych punkt�w
	if (points.size() == 0)
	{
		update(false);
		return;
	}
	ofPoint cell, point;

	for (int i = 0; i < cells.size(); i++)
	{
		cell = cells[i]->getPosition();
		//if (true)
		if(!cells[i]->isTouched())
		{
			
			for (int j = 0; j < points.size(); j++)
			{
				point = points[j];
				if (cell.distance(point) < 10)
				{
					cells[i]->fillUpEnergy();
					cells[i]->setTouched();
				}
			}
		}
	}


	update(false);

}

///Fill up energy of 10% of cells
void CellBackgroud::boom()
{
	for (int i = 0; i < cells.size() / 10; i++)
	{
		int r = (int)ofRandom(cells.size());
		cells[r]->fillUpEnergy();
	}
}
