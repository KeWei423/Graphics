//====================================================================================
//File: shape.h
//Description: All the Tetris pieces with their respective rotation and displacements
//             on the hotspots
//====================================================================================

#ifndef SHAPE_H
#define SHAPE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "tetrisconst.h"
using namespace std;


class Shape
{
public:

//Constructor
    Shape();

//-----------------------------------------------------------
//                 Accessor
//-----------------------------------------------------------
    sf::Color getColor();
    int GetPosX();//Return x position.
    int GetPosY();//Return y position
    int GetElement(int x, int y);//Return x position and y position.
//    int GetColor(); //return the color index from the color array
    int GetRandIndex();
    int GetIndex();

//-----------------------------------------------------------------------
//                  Mutator
//--------------------------------------------------------------------

    void SetPosition(int x,int y);
    //Set position of the shape in x & y

//-------------------------------------------------------------------
//              Generate
//-------------------------------------------------------------------
    void Generate();
    //Get a random number which generates a shape and color.

    void Move(int x, int y);
    //Move shape to the left and the right

    void Rotate();
    //Rotate shape 90 degree to the right.

    void checkColon();
    //Check if the shape is next to the right edge if so the shape moves to the left.

    bool IsValid(int xOffset = 0, int yOffset = 0);
    //Check if the shape is outside of the window if so return false.

    void DrawShape(sf::RenderWindow & window);
    //Draw the shape.

    void drawQuad(sf::RenderWindow & window, float x, float y, sf::Color c);
    int color;


private:
    int randIndex;
    int shapeIndex;
    int data[4][4], posX, posY /*color*/;
    void FillData();//Set the shape.
};

#endif // SHAPE_H
