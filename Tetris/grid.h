#ifndef GRID_H
#define GRID_H
#include "shape.h"


class Grid
{
public:
   //======CTOR
   Grid();
   //==========
   void Reset();
   bool IsCollision(Shape part);
   void AddPart(Shape part);
   void ApplyGravity(int h);
   void DestroyLines();
   bool IsFull();
   void draw(sf::RenderWindow & window, float x, float y, sf::Color c);
   void DrawGrid(sf::RenderWindow & window);

   //=============Accessor
   int GetScore();

    bool CheckPiece(int &x, int &y, Shape &s);
    bool isValid(int x,int y,Shape s);

private:
   Shape s;
   int data[HEIGHT][WIDTH];
   int score;
   sf::Color gridCol[HEIGHT][WIDTH];
};

#endif // GRID_H
