//
// Created by djchi on 2026-04-07.
//
#ifndef _BUILDING_H
#define _BUILDING_H

#include "Organism.h"
#include "GameSpecs.h"

class Building : public Organism
{
public:
    Building(City* city);
    virtual char getType() { return BUILDING_CH; }
    virtual void turn();  //nothing
};

#endif