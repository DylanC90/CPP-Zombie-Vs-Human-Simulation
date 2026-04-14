//
// Created by djchi on 2026-04-07.
//
#ifndef _ZOMBIE_H
#define _ZOMBIE_H

#include "Organism.h"
#include "GameSpecs.h"

class Zombie : public Organism
{
private:
    int breedCounter;
    int starveCounter;
    bool breedReady;

public:
    Zombie(City* city);
    void turn() override;
    char getType() override { return ZOMBIE_CH; }
};

#endif