//
// Created by djchi on 2026-04-07.
//
#include "Organism.h"
#include "City.h"

Organism::Organism()
{
    x = 0;
    y = 0;
    size = 0;
    moved = false;
    city = nullptr;
}

Organism::Organism(City* city, int size)
{
    this->city = city;
    this->size = size;
    moved = false;
    this->x = -1;
    this->y = -1;
}

Organism::~Organism() {}

ostream& operator<<(ostream& output, Organism* organism)
{
    if (organism != nullptr)
        output << organism->getType();
    else
        output << "-";

    return output;
}