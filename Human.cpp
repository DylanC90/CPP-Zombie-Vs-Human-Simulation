//
// Created by djchi on 2026-04-07.
//
#include "Human.h"
#include "City.h"
#include "GameSpecs.h"
#include <vector>
using namespace std;

Human::Human(City* city) : Organism(city, GRIDSIZE)
{
    recruitCounter = 0;
}

void Human::turn()
{
    if (moved) return;
    moved = true;
    //MOVE
    //Cardinal directions only: Up, Down, Left, Right
    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { -1, 0, 1, 0 };

    int oldX = x;
    int oldY = y;

    // COLLECT all possible empty adjacent cells (humans can move onto buildings)
    vector<int> emptyDirections;

    for (int d = 0; d < 4; d++)
    {
        int newX = oldX + dx[d];
        int newY = oldY + dy[d];//go through list of 4 spots

        if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE)
        {
            //MOVE INTO EMPTY CELL OR BUILDINGS.
            if (city->getOrganism(newX, newY) == nullptr)//check for empty
            {
                emptyDirections.push_back(d);//add this direction to the list of directions
            }
        }
    }

    //Randomly choose one empty adjacent cell
    if (!emptyDirections.empty())
    {
        int chosen = emptyDirections[rand() % emptyDirections.size()];
        int newX = oldX + dx[chosen];
        int newY = oldY + dy[chosen];

        city->setOrganism(nullptr, oldX, oldY);
        city->setOrganism(this, newX, newY);
    }

    // RECRUIT:
    if (recruitCounter >= HUMAN_BREED)//IF OVER 3
    {
        //Find empty adjacent cells for recruitment
        vector<int> recruitDirs;

        for (int d = 0; d < 4; d++)
        {
            int newX = x + dx[d];
            int newY = y + dy[d];

            if (newX >= 0 && newX < GRIDSIZE && newY >= 0 && newY < GRIDSIZE)
            {
                if (city->getOrganism(newX, newY) == nullptr)
                {
                        recruitDirs.push_back(d);
                }
            }
        }

        if (!recruitDirs.empty()) {
            int chosen = recruitDirs[rand() % recruitDirs.size()];
            int newX = x + dx[chosen];
            int newY = y + dy[chosen];

            Human* newHuman = new Human(city);
            newHuman->setMoved(true);
            city->setOrganism(newHuman, newX, newY);
        }
    recruitCounter = 0;
    }
    else
    {
        recruitCounter++;
    }
}