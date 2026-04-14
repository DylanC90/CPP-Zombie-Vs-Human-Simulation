//
// Created by djchi on 2026-04-07.
//
#include "Building.h"
#include "City.h"
#include "GameSpecs.h"

Building::Building(City* city) : Organism(city, GRIDSIZE)
{
    //nothing
}

void Building::turn()
{
    if (moved) return;
    moved = true;
}