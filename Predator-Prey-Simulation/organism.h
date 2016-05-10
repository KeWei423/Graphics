/**********************************************************************
 * File name: organism.h
 * Organism class declaration
 ***********************************************************************/
#ifndef ORGANISM_H
#define ORGANISM_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "const.h"
using namespace std;


class Organism
{

public:
    Organism();
    Organism(int r, int c, int type, int age);

    virtual void Move(Organism* world[][BOX_NUMB], int i, int j, int age) = 0;
    virtual void Breed(Organism* world[][BOX_NUMB], int i, int j/*, int age*/);
    virtual bool Starve() = 0;

    virtual void DrawOrg(sf::RenderWindow& window) = 0;

    virtual int getType();
    virtual int age();
    virtual void Print(ostream& outs) const = 0;

    void setHasMove(bool move);
    bool hasMoved();

    friend ostream& operator << (ostream& outs, const Organism& printThis);

private:
    bool _hasMoved;
    int _lifeSpand;
    int _type;
};

#endif // ORGANISM_H
