#include "CellBackgroud.h"



//CellBackgroud::CellBackgroud()
//{
//}

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
	//maxymalna iloœæ komórek w pionie i poziomie
	int maxX = width / distance + 1;
	int maxY = height / distance + 1;
	//wyznaczenie marginesu tak aby by³ równy po wszstkich stronach
	int marginX = (width - (maxX - 1)*distance) / 2;
	int marginY = (height - (maxY - 1)*distance) / 2;

	//inicjalizacja dynamicznej tablicy wskaŸników
	Cell *** c = new Cell **[maxY];
	for (int i = 0; i < maxY; i++)
	{
		c[i] = new Cell*[maxX];
	}

	//stworzenie komórek naprzemiennie w wierszach
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

	//dodanie komórek do kontenera, dodanie do ka¿dej komórki jej s¹siadów
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
			{
				//sprawdŸ czy komórka nie le¿y przy krawêdzi
				//jeœli tak to nie ma jednego z s¹siadów
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
void CellBackgroud::update()
{
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i]->update();
	}

	if ((counter++) % 10 == 0)
	{
		cells[(int)ofRandom(cells.size())]->fillUpEnergy();
	}
	

}


CellBackgroud::~CellBackgroud()
{
}
