#ifndef COORDPLANE_H
#define COORDPLANE_H

#include "SFML/Graphics.hpp"
#include "const.h"

class CoordPlane
{
public:
    CoordPlane();
    void DrawXCoord(sf::RenderWindow& window);
    void DrawYCoord(sf::RenderWindow& window);

private:
    sf::VertexArray _xCoord;
    sf::RectangleShape _xIndex;
    sf::VertexArray _yCoord;
    sf::RectangleShape _yIndex;
};




CoordPlane::CoordPlane():_xCoord(sf::LinesStrip,2) , _yCoord(sf::LinesStrip,2)
{

    _xCoord[0].position = sf::Vector2f(X_OG,-10000);
    _xCoord[1].position = sf::Vector2f(X_OG,10000);

    _yCoord[0].position = sf::Vector2f(-10000,Y_OG);
    _yCoord[1].position = sf::Vector2f(10000,Y_OG);


//    _xIndex.setSize(sf::Vector2f(1,INDEX_H));
//    _xIndex.setFillColor(sf::Color::White);


//    _yIndex.setSize(sf::Vector2f(INDEX_H, 1));
//    _yIndex.setFillColor(sf::Color::White);

}


void CoordPlane::DrawXCoord(sf::RenderWindow &window){
    window.draw(_xCoord);
    for(int i= -10000; i<(WIND_W/GAP); i++){
        if(i *GAP != Y_OG){
            _xIndex.setPosition(sf::Vector2f(i*GAP, Y_OG-(INDEX_H/2)));
            window.draw(_xIndex);
        }

    }
}


void CoordPlane::DrawYCoord(sf::RenderWindow &window){
    window.draw(_yCoord);
    for(int i= 0; i<(WIND_H/GAP); i++){
        _yIndex.setPosition(sf::Vector2f(X_OG-(INDEX_H/2), i*GAP));
        window.draw(_yIndex);
    }
}


#endif // COORDPLANE_H
