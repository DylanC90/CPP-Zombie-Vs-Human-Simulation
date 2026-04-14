#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include "GameSpecs.h"

using namespace std;

class Organism;

class City
{
protected:
	Organism *grid[GRIDSIZE][GRIDSIZE]; //make for organism and populate with human/zombie through polymorphism
	bool isBuilding[GRIDSIZE][GRIDSIZE];
	int generation;

public:
	City();
	virtual ~City();

	Organism *getOrganism( int x, int y );
	void setOrganism( Organism *organism, int x, int y );
	bool isCellBuilding(int x, int y) { return isBuilding[x][y]; } //new

	void step();
	void reset();
	int countType(char);
	friend ostream& operator<<( ostream &output, City &city );
	
	void col(int c);
};

#endif

