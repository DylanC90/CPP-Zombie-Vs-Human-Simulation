//
// Created by djchi on 2026-04-07.
//
#ifndef _Human_H
#define _Human_H
#include "GameSpecs.h"
#include "Organism.h"

class Human : public Organism
{
private:
    int recruitCounter;

public:
    Human(City* city);
    virtual char getType() { return HUMAN_CH; }
    virtual void turn();
};

#endif