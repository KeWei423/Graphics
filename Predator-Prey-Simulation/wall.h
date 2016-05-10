/**********************************************************************
 * File name: Wall.h
 * Wall class declaration
 ***********************************************************************/

#ifndef WALL_H
#define WALL_H

#include "organism.h"
#include <iostream>

class Wall:public Organism
{
public:
    Wall();
    Wall(int r, int c, int type, int age);

    void Move(Organism* world[][BOX_NUMB], int i, int j, int age);
    void Breed(Organism* world[][BOX_NUMB], int i, int j/*, int age*/);
    bool Starve();
    int getType();
    void DrawOrg(sf::RenderWindow& window);
    void Print(ostream& outs) const;

private:
    sf::RectangleShape _wall;
};

#endif // WALL_H
