/**********************************************************************
 * File name: Doodlebug.h
 * Doodlebug class declarations
 ***********************************************************************/

#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "organism.h"
using namespace std;

class Doodlebug:public Organism
{
public:
    Doodlebug();
    Doodlebug(int r, int c, int type, int age);
    Doodlebug(int r, int c, int type, int age, int move);

    void Move(Organism* world[][BOX_NUMB], int i, int j, int age);
    void Breed(Organism* world[][BOX_NUMB], int i, int j/*, int age*/);
    bool Starve();

    int getType();
    int age();
    void DrawOrg(sf::RenderWindow& window);
    void Print(ostream& outs) const;

    bool Eat(Organism* world[][BOX_NUMB], int i, int j);
    void randMove(Organism* world[][BOX_NUMB], int i, int j, int age, int direction);
private:
    sf::RectangleShape _bug;
    int _moveUntilDie;
};

#endif // DOODLEBUG_H
