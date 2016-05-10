/**********************************************************************
 * File name: world.h
 * World class declaration
 ***********************************************************************/
#ifndef WORLD_H
#define WORLD_H


#include "const.h"
#include "doodlebug.h"
#include "wall.h"
#include "ant.h"
#include<SFML/Graphics.hpp>
#include <vector>


class World
{
public:
    World();

    void DrawWorld(sf::RenderWindow& window);
    void Reset();

    void Init();
    void InitD();
    void InitW();
    void InitA();


    void Move();
    void MoveD();
    void MoveA();

    void Starve();

    void Breed();

    int NumbBug();
    int NumbAnt();

private:
    sf::RectangleShape grid;
    Organism* _grid[BOX_NUMB][BOX_NUMB];
};

#endif // WORLD_H
