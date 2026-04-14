//
// Created by djchi on 2026-04-07.
//
#include "City.h"
#include "Human.h"
#include "Zombie.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

using namespace std;

City::City()
{
    generation = 0;

    //Initialize grid to nullptr AND buildings to false for placement method
    //nullptr for absolutely empty cells
    for(int i = 0; i < GRIDSIZE; i++)
        for(int j = 0; j < GRIDSIZE; j++)
        {
            grid[i][j] = nullptr;
            isBuilding[i][j] = false;  //ADD THIS
        }

    //STEP 1: Place BUILDINGS to avoid squishing people / zombies
    int buildingsPlaced = 0;
    while (buildingsPlaced < BUILDING_COUNT)
    {
        int x = rand() % GRIDSIZE;//random x coord based on gridsize shrink it to be within size range.
        int y = rand() % GRIDSIZE;//same but for y

        if (!isBuilding[x][y] && grid[x][y] == nullptr)
        {
            isBuilding[x][y] = true;  //mark it
            buildingsPlaced++;
        }
    }

    //STEP 2: Place HUMANS can be placed on buildings
    int humansPlaced = 0;
    while (humansPlaced < HUMAN_STARTCOUNT)
    {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        if (grid[x][y] == nullptr)//avoid stacking people
        {
            setOrganism(new Human(this), x, y); //polymorphism example
            humansPlaced++;
        }
    }
    //STEP 3: Place ZOMBIES CANNOT be inside buildings
    int zombiesPlaced = 0;
    while (zombiesPlaced < ZOMBIE_STARTCOUNT)
    {
        int x = rand() % GRIDSIZE;
        int y = rand() % GRIDSIZE;

        //Zombies cannot start on buildings and empty cell
        if (grid[x][y] == nullptr && !isBuilding[x][y])
        {
            setOrganism(new Zombie(this), x, y); //polymorphism example
            zombiesPlaced++;
        }
    }
}

//DESTRUCTOR
City::~City()
{
    for(int i = 0; i < GRIDSIZE; i++)
        for(int j = 0; j < GRIDSIZE; j++)
            if(grid[i][j])
                delete grid[i][j];
}

Organism* City::getOrganism(int x, int y)
{
    if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
    {
        return nullptr;//out of bounds
    }
    return grid[x][y];//get element
}

void City::setOrganism(Organism* org, int x, int y)
{
    if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
    {
        if (org) delete org;//remove current
        return;
    }

    //check for zombie and rule for applying them
    if (org && org->getType() == ZOMBIE_CH && isBuilding[x][y])
    {
        delete org;//remove current
        return;
    }

    grid[x][y] = org;
    if(org)
    {
        org->x = x;//set organism position grab from class via pointer
        org->y = y;
    }
}

void City::step()//increase step and turn for all
{
    generation++;

    for (int i = 0; i < GRIDSIZE; i++)
        for (int j = 0; j < GRIDSIZE; j++)
            if (grid[i][j] && !grid[i][j]->moved)
                grid[i][j]->turn();
}

void City::reset() //set moved to false for all
{
    for(int i = 0; i < GRIDSIZE; i++)
        for(int j = 0; j < GRIDSIZE; j++)
            if(grid[i][j])
                grid[i][j]->moved = false;
}

int City::countType(char t)//grab amount of a organism
{
    int c = 0;
    for(int i = 0; i < GRIDSIZE; i++)
        for(int j = 0; j < GRIDSIZE; j++)
            if(grid[i][j] && grid[i][j]->getType() == t)//if char= t increase amount
                c++;
    return c;
}

ostream& operator<<(ostream& out, City& city) //overloaded output operator
{
    out << "Step: " << city.generation
        << ", Zombies: " << city.countType(ZOMBIE_CH)
        << ", Humans: " << city.countType(HUMAN_CH) << endl;

    for(int i = 0; i < GRIDSIZE; i++)
    {
        for(int j = 0; j < GRIDSIZE; j++)
        {
            Organism* o = city.grid[i][j];
            if(!o)//IF NOT ORGANISM
            {
                if(city.isBuilding[i][j])
                {
                    city.col(BUILDING_COLOR);
                    out << (char)BUILDING_CH << " ";
                }
                else
                {
                    city.col(DASH_COLOR);
                    out << (char)SPACE_CH << " ";
                }
            }
            else if(o->getType() == HUMAN_CH)//IF HUMAN
            {
                if(city.isBuilding[i][j])
                {
                    city.col(BUILDING_OCCUPIED);
                    out << (char)BUILDING_CH << " ";
                }
                else
                {
                    city.col(HUMAN_COLOR);
                    out << (char)HUMAN_CH << " ";
                }
            }
            else if(o->getType() == ZOMBIE_CH)//IF ZOMBIE
            {
                city.col(ZOMBIE_COLOR);
                out << (char)ZOMBIE_CH << " ";
            }
        }
        out<<endl;
    }

    city.col(7);
    out << endl << endl;
    return out;
}

//FROM EXAMPLE
void City::col(int c)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, c);
}