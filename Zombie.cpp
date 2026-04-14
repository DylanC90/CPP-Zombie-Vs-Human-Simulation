#include "Zombie.h"
#include "Human.h"
#include "City.h"
#include "GameSpecs.h"
#include <vector>
#include <cstdlib>
using namespace std;

const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

Zombie::Zombie(City* city) : Organism(city, ZOMBIE_CH)
{
    breedCounter = 0;
    starveCounter = 0;
}

static vector<pair<int,int>> getNeighbors(int x, int y, int gridSize)
{
    vector<pair<int,int>> neighbors;
    for (int d = 0; d < 8; d++)
    {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridSize)
            neighbors.push_back({nx, ny});
    }
    return neighbors;
}

void Zombie::turn()
{
    if (moved) return;
    moved = true;

    int oldX = x;
    int oldY = y;
    bool ate = false;

    //8 directions including diagonals
    vector<pair<int,int>> humanCells;
    vector<pair<int,int>> emptyCells;

    for (auto [nx, ny] : getNeighbors(oldX, oldY, GRIDSIZE))
    {
        Organism* target = city->getOrganism(nx, ny);
        if (target != nullptr && target->getType() == HUMAN_CH)
            humanCells.push_back({nx, ny});
        else if (target == nullptr && !city->isCellBuilding(nx, ny))
            emptyCells.push_back({nx, ny});
    }

    //STEP 1: Try to find a human and eat it
    if (!humanCells.empty())
    {
        auto [nx, ny] = humanCells[rand() % humanCells.size()];
        Organism* victim = city->getOrganism(nx, ny);
        city->setOrganism(nullptr, nx, ny);
        delete victim;

        city->setOrganism(nullptr, oldX, oldY);
        city->setOrganism(this, nx, ny);
        starveCounter = 0;
        ate = true;
    }

    // STEP 2: If no humans found move to random cell
    if (!ate)
    {
        if (!emptyCells.empty())
        {
            auto [nx, ny] = emptyCells[rand() % emptyCells.size()];
            city->setOrganism(nullptr, oldX, oldY);
            city->setOrganism(this, nx, ny);
        }
        starveCounter++;
    }
    breedCounter++;


    //STEP 3: BREED Check if survived 8 turns
    if (breedCounter >= ZOMBIE_BREED)
    {
        vector<pair<int,int>> humanTargets;
        for (auto [nx, ny] : getNeighbors(x, y, GRIDSIZE))
        {
            Organism* target = city->getOrganism(nx, ny);
            if (target != nullptr && target->getType() == HUMAN_CH)
                humanTargets.push_back({nx, ny});
        }

        if (!humanTargets.empty())
        {
            //Convert human to zombie
            auto [nx, ny] = humanTargets[rand() % humanTargets.size()];
            Organism* victim = city->getOrganism(nx, ny);
            city->setOrganism(nullptr, nx, ny);
            delete victim;

            //Create new zombie
            Zombie* newZombie = new Zombie(city);
            newZombie->setMoved(true); //so he doesnt act til next round
            city->setOrganism(newZombie, nx, ny);
            breedCounter = 0; //reset
        }
        //if nothing found keep breed counter so it can look again next step
    }

    //STEP 4: STARVE Check if not eaten in 3 turns
    if (starveCounter >= ZOMBIE_STARVE)
    {
        if (rand() % 100 < STARVE_CHANCE)
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