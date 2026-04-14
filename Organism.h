#ifndef _Organism_H
#define _Organism_H

#include <iostream>

using namespace std;

class City;

class Organism
{
protected:
	int x;
	int y;
	int size;
	bool moved;
	City *city;

public:
	Organism();
	Organism( City *city, int size);
	virtual ~Organism();
	virtual void turn() = 0;
	virtual char getType() = 0; //new
	bool hasMoved() const{return moved;}//new
	void setMoved(bool m){ moved = m;}//new

	friend class City; //ALLOW PROTECTED ACCESS
	friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif
