/**********************************************************************
 * File name: ant.h
 * Ant class delcaration
 ***********************************************************************/

#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "organism.h"

using namespace std;

class Ant:public Organism
{
public:
    //ctors
    Ant();
    Ant(int r, int c, int type, int age);

    void Move(Organism *world[][BOX_NUMB], int i, int j, int age);
    void Breed(Organism* world[][BOX_NUMB], int i, int j);
    bool Starve();

    //return the type
    int getType();


    void DrawOrg(sf::RenderWindow& window);
    void Print(ostream& outs) const;

private:
    sf::RectangleShape _ant;

};

#endif // ANT_H
