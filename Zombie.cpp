//
// Created by djchi on 2026-04-07.
//
#include "Zombie.h"
#include "Human.h"
#include "City.h"
#include "GameSpecs.h"
#include <vector>
#include <cstdlib>
using namespace std;

Zombie::Zombie(City* city) : Organism(city, GRIDSIZE)
{
    breedCounter = 0;
    starveCounter = 0;
}

void Zombie::turn()
{
    if (moved) return;
    moved = true;

    // 8 directions including diagonals
    //looks in this order and eats.
    const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    int oldX = x;
    int oldY = y;

    bool ate = false;

    //STEP 1: Try to find a human
    for (int d = 0; d < 8; d++)
    {
        int targetX = oldX + dx[d];
        int targetY = oldY + dy[d];

        if (targetX >= 0 && targetX < GRIDSIZE && targetY >= 0 && targetY < GRIDSIZE)
        {
            Organism* target = city->getOrganism(targetX, targetY);//shallow copy for original deletion

            //Can eat humans even if in buildings
            if (target != nullptr && target->getType() == HUMAN_CH)
            {
                //EAT the human
                city->setOrganism(nullptr, targetX, targetY);
                delete target;

                //move
                city->setOrganism(nullptr, oldX, oldY);
                city->setOrganism(this, targetX, targetY);

                ate = true;
                starveCounter = 0;  // Reset starvation counter
                break;
            }
        }
    }

    // STEP 2: If no humans found move to random cell
    if (!ate)
    {
        vector<int> emptyDirections;

        for (int d = 0; d < 8; d++)
        {
            int newX = oldX + dx[d];
            int newY = oldY + dy[d];

            if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE)
            {
                //Can only move into empty cells not building
                if (city->getOrganism(newX, newY) == nullptr && !city->isCellBuilding(newX, newY))
                {
                    emptyDirections.push_back(d);
                }
            }
        }

        if (!emptyDirections.empty())
        {
            int chosen = emptyDirections[rand() % emptyDirections.size()];
            int newX = oldX + dx[chosen];
            int newY = oldY + dy[chosen];

            //MOVE to empty cell
            city->setOrganism(nullptr, oldX, oldY);
            city->setOrganism(this, newX, newY);
        }

        starveCounter++;
    }
    breedCounter++;

    //STEP 3: BREED Check if survived 8 turns
    if (breedCounter >= ZOMBIE_BREED)
    {

        int convertX = -1, convertY = -1; //default fallback

        for (int d = 0; d < 8; d++)
        {
            int checkX = x + dx[d];
            int checkY = y + dy[d];

            if (checkX >= 0 && checkX < GRIDSIZE && checkY >= 0 && checkY < GRIDSIZE)
            {
                Organism* target = city->getOrganism(checkX, checkY);

                if (target != nullptr && target->getType() == HUMAN_CH) //if human change it
                {
                    convertX = checkX;
                    convertY = checkY;
                    break;  //Take the first human found
                }
            }
        }

        if(convertX != -1)//check if changed or not
        {
            //Convert human to zombie
            Organism* victim = city->getOrganism(convertX, convertY);//shallow copy
            city->setOrganism(nullptr, convertX, convertY);
            delete victim;

            //Create new zombie
            Zombie* newZombie = new Zombie(city);
            newZombie->setMoved(true); //so he doesnt act til next round
            city->setOrganism(newZombie, convertX, convertY);

            breedCounter = 0; //reset
        }
        //if nothing found keep breed conuter so it can look again next step
    }

    // STEP 4: STARVE Check if not eaten in 3 turns
    if (starveCounter >= ZOMBIE_STARVE)
    {
        int chance = rand() % 100;

        if (chance < STARVE_CHANCE)
        {
            //Convert zombie to human
            Human* newHuman = new Human(city);
            newHuman->setMoved(true);
            city->setOrganism(newHuman, x, y);
            delete this;
            return;
        }
        else
        {
            //Zombie stays a zombie, reset starvation counter to avoid constant changing
            starveCounter = 0;
        }
    }
}