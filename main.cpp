#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "City.h"
#include "GameSpecs.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    srand(time(nullptr)); //set seed to time

    cout << "========================================" << endl;
    cout << "   ZOMBIE SURVIVAL SIMULATION" << endl;
    cout << "========================================" << endl;
    cout << "1. Visual Mode" << endl;
    cout << "2. Mass Mode" << endl;
    cout << "Choose mode (1 or 2): ";

    int mode;
    cin >> mode;

    if (mode == 1)
    {
        //visual mode 1 visual aspect
        cout << "\nEnable delay between generations? 1=Yes, 0=No: ";
        int enableSleep;
        cin >> enableSleep;

        cout << "\nStarting visual simulation...\n" << endl;

        City city;
        cout << city;

        if (enableSleep) Sleep(INTERVAL);

        for(int i = 0; i < ITERATIONS; i++)
        {
            city.step();
            city.reset();
            cout << city;

            int humans = city.countType(HUMAN_CH);
            int zombies = city.countType(ZOMBIE_CH);

            //check extinct
            if(humans == 0)
            {
                cout << "\n!!! EXTINCTION EVENT !!!" << endl;
                cout << "All humans have died! Zombies win!" << endl;
                cout << "Simulation ended after " << (i+1) << " generations." << endl;
                break;
            }
            else if(zombies == 0)
            {
                cout << "\n!!! EXTINCTION EVENT !!!" << endl;
                cout << "All zombies have died! Humans win!" << endl;
                cout << "Simulation ended after " << (i+1) << " generations." << endl;
                break;
            }

            if (enableSleep) Sleep(INTERVAL); //sleep each step
        }
        cout << "\nSimulation complete!" << endl;
    }
    else if (mode == 2)
    {
        cout << "\nHow many simulations to run? : ";
        int numSimulations;
        cin >> numSimulations;

        cout << "\nRunning " << numSimulations << " simulations..." << endl;

        int humansWon = 0;
        int zombiesWon = 0;
        int reachedTurnLimit = 0;


        for (int sim = 0; sim < numSimulations; sim++)
        {
            //seed( time value + sim number so it differs incase sim completes too fast)
            srand(time(nullptr) + sim);

            City city;
            int generations = 0;

            for (int gen = 0; gen < ITERATIONS; gen++)
            {
                city.step();
                city.reset();

                int humansAfter = city.countType(HUMAN_CH);
                int zombiesAfter = city.countType(ZOMBIE_CH);

                generations++;

                //check extinct
                if (humansAfter == 0)
                {
                    zombiesWon++;
                    break;
                }
                else if (zombiesAfter == 0)
                {
                    humansWon++;
                    break;
                }

                //check for turn limit
                if (gen == ITERATIONS - 1)
                {
                    reachedTurnLimit++;
                }
            }
        }

        //give result
        cout << "\n\nResult: " << endl;
        cout << "Humans won: " << humansWon << " times" << endl;
        cout << "Zombies won: " << zombiesWon << " times" << endl;
        cout << "Simulation reached the turn limit " << reachedTurnLimit << " times" << endl;
        cout << endl;

        //check winner
        if (humansWon > zombiesWon)
            cout << "Humans win on average" << endl;
        else if (zombiesWon > humansWon)
            cout << "Zombies win on average" << endl;
        else
            cout << "Its a Tie!" << endl;
    }
    else
    {
        cout << "Invalid Input Try again: " << endl;
    }
    return 0;
}