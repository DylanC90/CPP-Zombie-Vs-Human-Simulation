cmake_minimum_required(VERSION 4.0.2)
project(ZombieSimulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ZombieSimulation
        main.cpp
        Organism.cpp
        Organism.h
        Human.cpp
        Human.h
        Zombie.cpp
        Zombie.h
        City.cpp
        City.h
        Building.cpp
        Building.h
        GameSpecs.h
)